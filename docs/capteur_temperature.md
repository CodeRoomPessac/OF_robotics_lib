# Capteur de Température #
###*Grove - Infrared Temperature Sensor*###

![capteur temp](/images/capteur_temp/capteur_temp.jpg)

### Fonction ###

Ce capteur infrarouge peut mesurer des températures allant de -10 à +100°C, avec une précision de plus ou moins 2°C. 116 éléments de thermocouple entrent dans sa conception : la tension délivrée est proportionnelle à la température mesurée.
 
*Dans le cadre de la Robocup, ce capteur sera utile pour l’épreuve de rescue Maze pour l’identification de victimes, car certaines de celles-ci seront chauffées entre 28 et 40°C et au moins de 10°C de plus que la température ambiante.*



### Spécifications ###

- Alimentation : 3 à 5 Vcc
- Consommation : 200 µA max
- Plage de mesure : -10 à +100 °C
- Précision : ±2 °C
- Distance nominale de mesure : 9 cm	
- Dimensions : 40 x 20 x 13 mm


### Calibrage du capteur ###

Brancher le capteur sur le shield Grove, sur une entrée analogique (Ax).

![connect capteur temp](/images/capteur_temp/connect_capteur_temp.jpg)

Vous devrez ensuite calibrer le capteur de température, en effet on ne peut pas être certains que tous les capteurs sont exactement les mêmes. Ouvrez donc le programme de test `capteur_temp_calib.ino` (on ne s'en servira que pour ça).

 - **Régler la tension**

Mettre le capteur à température ambiante pendant 5 minutes puis ouvrir le moniteur de série et régler le code comme ci-dessous pour que la tension affichée dans le moniteur de série soit de 0.000V (et ainsi la température mesurée de l’objet est égale à la température ambiante).

![capteur temp code 1](/images/capteur_temp/capteur_temp_code_1.jpg)
![capteur temp serialmonitor](/images/capteur_temp/capteur_temp_serialmonitor.jpg)

 - **Régler la distance de mesure**
 
Selon notre expérience, la distance de mesure nominale du capteur est de 9cm, mais nous ne pouvons pas garantir que tous les capteurs soient identiques. Donc si vous voulez avoir un résultat précis, vous devez le réguler avec un mélange de glace et d'eau pour mesurer le 0℃, et utiliser de l'eau bouillante pour réguler le 100℃. Ensuite, vous pourrez obtenir la distance effective du capteur.

La méthode de mesure spécifique consiste à remplir de glace et d'eau un récipient sombre à surface plane. En attendant que le conteneur tombe à 0℃, gardez le capteur à 9cm de l'objet, déplacez le capteur vers l'avant ou vers l'arrière et vérifiez le résultat, si la sortie est 0℃, notez la valeur de la distance. Procédez avec la même méthode pour vérifier l'eau bouillante. Si vous avez deux valeurs différentes de distance, faites une moyenne.

- **Reporter les résultats dans la librairie mBlock**

Pour que ces résultats de calibrage soient utilisés par les blocs de la librairie, il faut modifier le fichier `OF_TempSensor.h` de la même manière que vous avez modifié le fichier `capteur_temp_calib.ino`.

```cpp
	inline Temp_sensor::Temp_sensor() : 
		temp_calibration(0), temperature_range(10), 
		offset_vol(0.014), tempValue(0), 
		objtValue(0), current_temp(0),
		temp(0), temp1(0), temp2(0), temp3(0),
		reference_vol(0.500), clear_num(0), 
		R(0), voltage(0)
	{}
```

Remplacer la valeur de `offset_vol` par celle mesurée lors du calibrage.


### Création des blocs mBlock ###

	[
		"r",
		"Temperature Objet sur les broches %n et %n",
		"Capteur Temperature Objet",
		"0",
		"1",
		{
			"setup":"TempSensor.setup({0},{1});\n",
			"inc":"\n#include \"OF_TempSensor.h\"\n",
			"def":"Temp_sensor TempSensor;\n ",
			"work":"TempSensor.measureObjectTemp()",
			"loop":""
		}
	],
	[
		"r",
		"Temperature Environnante sur les broches %n et %n",
		"Capteur Temperature Environs",
		"0",
		"1",
		{
			"setup":"TempSensor.setup({0},{1});\n",
			"inc":"\n#include \"OF_TempSensor.h\"\n",
			"def":"Temp_sensor TempSensor;\n ",
			"work":"TempSensor.measureSurTemp()",
			"loop":""
		}
	],

C'est un capteur, il est donc normal de n'avoir que des blocs en lecture ("r" comme read). Le capteur utilise deux pins analogiques : une pour mesurer la température ambiante et une pour la température de l'objet ciblé.

 - **inc :** On inclue la librairie `OF_TempSensor.h`
 - **def :** On défini un objet de type Temp_sensor
 - **setup :** On utilise la méthode `setup` de l'objet pour le démarrer
 - **work :** On utilise soit la méthode `measureSurTemp()`, soit `measureObjectTemp()` suivant ce qu'on veut mesurer


### Utilisation des blocs mBlock ###

On obtient donc dans mBlock les blocs suivants :

![capteur temp blocs](/images/capteur_temp/capteur_temp_blocs.png)

Ce qui nous permet de réaliser le petit programme suivant :

![capteur temp exemple](/images/capteur_temp/capteur_temp_exemple.png)

Dans cet exemple le capteur est branché sur les pins A0 et A1. On affiche sur l'écran LCD la valeur de la température ambiante sur la première ligne, et la valeur de la température de l'objet sur la deuxième.