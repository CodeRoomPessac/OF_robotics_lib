## Multiplexeur I2C Adafruit ##
### *Adafruit TCA9548A 1-to-8 I2C Multiplexer* ###

![multiplexeur](/images/multiplexeur_i2c/multiplexeur.png)

> Cette documentation est une traduction libre de la documentation écrite par Adafruit.
> Vous pourrez la trouver en suivant [ce lien](https://cdn-learn.adafruit.com/downloads/pdf/adafruit-tca9548a-1-to-8-i2c-multiplexer-breakout.pdf?timestamp=1557901314).

Vous venez de trouver le capteur I2C parfait, et vous voulez en brancher deux ou trois ou plus à votre Arduino quand vous réalisez "oh, cette puce a une adresse I2C fixe, et d'après ce que je sais sur l'I2C, vous ne pouvez pas avoir deux appareils avec la même adresse sur les mêmes pins SDA/SCL" ! Vous êtes malchanceux ? Vous le seriez, si vous n'aviez pas ce multiplexeur ultra-cool TCA9548A 1 à 8 I2C !

### Présentation ###


![multiplexeur presentation](/images/multiplexeur_i2c/multiplexeur_presentation.png)

Enfin, un moyen d'obtenir jusqu'à 8 dispositifs I2C de même adresse reliés à un microcontrôleur - ce multiplexeur agit comme un rerouteur, faisant passer les commandes à l'ensemble de pins I2C sélectionné.
Son utilisation est assez simple : le multiplexeur lui-même est à l'adresse I2C 0x70 (mais peut être réglé de 0x70 à 0x77).
Vous écrivez simplement un octet avec le numéro de sortie du multiplexeur désiré sur ce port, et bam - tous les futurs paquets I2C seront envoyés sur ce port. En théorie, vous pourriez avoir 8 de ces multiplexeurs sur chacune des adresses 0x70-0x77 afin de contrôler 64 capteurs possédant la même adresse.
La puce elle-même est compatible 1.8V - 5V, vous pouvez donc l'utiliser avec n'importe quel niveau logique.

### Pinout ###


![multiplexeur pinout](/images/multiplexeur_i2c/multiplexeur_pinout.png)

**Pins d'Alimentation :**

* Vin - C'est la broche d'alimentation. Puisque la puce du capteur utilise du 3 - 5VDC, pour alimenter la carte, donnez-lui la même puissance que le niveau logique de votre microcontrôleur - par exemple, pour un microcontrôleur 5V comme Arduino, utilisez 5V.
* GND - Gnd commun pour l'alimentation et la logique
 

**Pins I2C côté commande :**

* SCL - C'est la pin d'horloge I2C pour la puce elle-même. Connectez la à la pin d'horloge I2C  du microcontrôleur.
* SDA - C'est la pin de données I2C pour la puce elle-même. Connectez à la pin de données I2C  du microcontrôleur.
* RST - C'est la pin de réinitialisation, pour réinitialiser la puce du multiplexeur. Tirée à l'état haut (pull up) par défaut, connecter à la terre pour réinitialiser.
* A0 A1 A2 - ce sont les pin de sélection d'adresse pour le multiplexeur. Par défaut le multiplexeur est à l'adresse 0x70 et ces trois pins sont tirées vers le bas. Connectez-les à Vin pour régler l'adresse sur 0x71 - 0x77.
* A0 est le bit de poids le plus faible (s'il est tiré vers le haut, il augmentera l'adresse de 1).
* A1 est le 2e bit de poids le plus faible (s'il est tiré vers le haut, il augmentera l'adresse de 2).
* A2 est le 3e bit de poids le plus faible (s'il est tiré vers le haut, il augmentera l'adresse de 4).

**Pins I2C côté multiplexage :**

* SDx et SCx:  Il existe 8 paires de pins SDx et SCx, de SD0/SC0 à SD7/SC7 : ce sont les pins multiplexées. Chacune est un jeu de bus I2C complètement séparé. Vous pouvez donc avoir 8 appareils I2C avec des adresses identiques, à condition qu'ils soient sur un bus I2C chacun.


### Câblage et programmation ###

Le multiplexeur TCA9548A est intéressant parce qu'il a une adresse I2C (0x70 par défaut) - et vous lui envoyez une commande pour lui dire à quelle sortie multiplexée I2C vous voulez parler, ensuite vous pouvez vous adresser à la carte que vous souhaitez.

Cette petite fonction est utile pour sélectionner le port avec lequel on souhaite discuter :

```cpp
	#define TCAADDR 0x70
	void tcaselect(uint8_t i)
	{  
		if (i > 7) return;
		Wire.beginTransmission(TCAADDR);
		Wire.write(1 << i);  	
		Wire.endTransmission();
	}
```

Vous pouvez ensuite appeler de tcaselect(0) à tcaselect(7) pour configurer le multiplexeur. Notez que si vous avez des périphériques I2C avec l'adresse I2C 0x70, vous devrez court-circuiter l'une des broches Addr sur la sortie TCA9548 vers Vin afin d'éviter tout conflit. Étant donné que vous pouvez choisir de 0x70 à 0x77, il suffit d'en trouver une qui est libre et tout est bon.


### Exemple - C ###

Connectez chacun des capteurs à Vin, Ground et utilisez l'un des bus multiplexés SCx / SDx :

Sur un Arduino, ce que nous utilisons, nous vous suggérons d'exécuter ce script scanner pratique qui vous indiquera ce qui a eté détecté.
```cpp
	/*
	 * TCA9548 I2CScanner.pde -- I2C bus scanner for Arduino
	 * 
	 * Based on code c. 2009, Tod E. Kurt, http://todbot.com/blog/
	 * 
	 */
	
	#include "Wire.h"
	extern "C" {
	#include "utility/twi.h"
	}
	
	#define TCAADDR 0x70
	
	void tcaselect(uint8_t i)
	{
	  if(i>7) return;
	  Wire.beginTransmission(TCAADDR);
	  Wire.write(1<<i);
	  Wire.endTransmission();
	}
	
	
	void setup() {
	  // put your setup code here, to run once:
	  while(!Serial);
	  delay(1000),
	
	  Wire.begin();
	
	  Serial.begin(9600);
	  Serial.println("\TCAScanner ready!");
	
	  for (uint8_t t=0; t<8; t++)
	  {
	    tcaselect(t);
	    Serial.print("TCA Port #"); Serial.println(t);
	
	    for (uint8_t addr = 0; addr<=127; addr++) 
	    {
	      if (addr == TCAADDR) continue;
	
	      uint8_t data;
	      if (!twi_writeTo(addr, &data,0,1,1))
	      {
	        Serial.print("Found I2C 0x"); Serial.println(addr,HEX);
	      }
	    }
	  }
	  Serial.println("\ndone");
	}
	
	void loop() {
	  // put your main code here, to run repeatedly:
	
	}
```

Vous pouvez retrouver ce code dans le fichier `scanner_i2c_multiplexeur.ino`.

En exécutant le code ci-dessus vous obtiendrez :

![multiplexeur exemple](/images/multiplexeur_i2c/multiplexeur_exemple.png)

Ensuite, vous devrez ajuster n'importe quel code que vous avez pour sélectionner le bon port multiplexé ! Assurez-vous avant d'interroger un capteur que vous appelez tcaselect pour obtenir le bon !

### Création des blocs mBlock ###

			[
			"w",
			"Multiplexeur I2C : Port %n à l'adresse %n",
			"Multiplexeur I2C",
			"0",
			"0x70",
			{
				"setup":"",
				"inc":"\n#include <Wire.h>\n",
				"def":"\n
						#define TCAADDR {1}\n
						void tcaselect(uint8_t i)
						{
							if(i>7) return;
							Wire.beginTransmission(TCAADDR);
							Wire.write(1<<i);
							Wire.endTransmission();
						}\n",
				"work":"tcaselect({0});\n",
				"loop":""
			}
		],

Ce n'est pas un bloc qui va renvoyer une valeur, il est donc normal de n'avoir qu'un bloc en écriture ("w" comme write).

 - **inc :** On inclue la librairie `Wire.h`
 - **def :** On défini l'adresse du multiplexeur, ainsi que la fonction tcaselect vue précédemment
 - **work :** On utilise la méthode `tcaselect(uint8_t i)` pour changer le port du multiplexeur avec lequel on veut discuter


### Utilisation des blocs mBlock ###

On obtient donc dans mBlock le bloc suivant :

![multiplexeur bloc](/images/multiplexeur_i2c/multiplexeur_bloc.png)

Ce qui nous permet de réaliser le petit programme suivant :

![multiplexeur exemple bloc](/images/multiplexeur_i2c/multiplexeur_exemple_bloc.png)

Dans cet exemple on a le multiplexeur I2C branché sur un port I2C configuré à l'adresse 0x70, et 2 capteurs de couleurs branchés sur deux ports différents du multiplexeur I2C. On affiche sur l'écran LCD la valeur du rouge renvoyée par le premier capteur de couleur sur la première ligne, et la valeur du rouge renvoyée par le second capteur de couleur sur la deuxième.

### Datasheets ###

* [TCA9548A datasheet](https://adafru.it/id8) (https://adafru.it/id8)
* [Fritzing object in the Adafruit Fritzing Library](https://adafru.it/aP3) (https://adafru.it/aP3)
* [EagleCAD PCB files on GitHub (https://adafru.it/rzF)](https://adafru.it/rzF)