# Capteur de Distance #
###*Grove - Ultrasonic Ranger*###

![capteur distance](/images/capteur_distance/capteur_distance.jpg)

### Fonction ###

Le télémètre à ultrasons SEN10737P est un module Grove vous permettant de mesurer précisément les distances sans contact au moyen de transducteurs à ultrasons. 
En pratique, ce petit module est capable de vous garantir une performance d’un niveau industriel : une portée de 3 cm à 4 m, avec une résolution de 1 cm. 

*Dans le cadre de la Robocup, il sert comme capteur de distance générique. Il est moins rapide et précis que les capteurs de distance infrarouge (2-15 cm), c’est pourquoi on le préférera qu’en cas de besoin de portée supérieure à 15 cm (ce capteur est moins indiqué pour Rescue Maze).*

### Spécifications ###

- Module compatible Grove 
- Alimentation : 3.2~5.2V
- Consommation : 15 mA
- Fréquence : 40 kHz
- Portée de détection : 2 – 350cm
- Angle de mesure : 15°
- Résolution : 1cm
- Dimensions : 50x25x16mm


### Utilisation ###

Brancher le capteur sur le shield Grove, sur une entrée digitale (Dx).

![capteur distance connect](/images/capteur_distance/connect_capteur_distance.jpg)

### Création des blocs mBlock ###

	[
		"r",
		"Valeur du capteur distance sur la broche %n",
		"Valeur du capteur distance sur la broche",
		"8",
		{
			"setup":"",
			"inc":"#include \"OF_Ultrasonic.h\"\n",
			"def":"Ultrasonic ultrasonic_{0}({0});\n",
			"work":"ultrasonic_{0}.MeasureInCentimeters()",
			"loop":""
		}
	],

C'est un capteur, il est donc normal de n'avoir qu'un bloc en lecture ("r" comme read). Le capteur utilise une pin digitale.

 - **inc :** On inclue la librairie `OF_Ultrasonic.h`
 - **def :** On défini un objet de type Ultrasonic
 - **work :** On utilise la méthode `MeasureInCentimeters()` pour récupérer la distance mesurée par le capteur en cm


### Utilisation des blocs mBlock ###

On obtient donc dans mBlock le bloc suivant :

![capteur distance bloc](/images/capteur_distance/capteur_distance_bloc.jpg)

Ce qui nous permet de réaliser le petit programme suivant :

![capteur distance exemple](/images/capteur_distance/capteur_distance_exemple.jpg)

Dans cet exemple le capteur est branché sur la pin D8. On affiche sur l'écran LCD la valeur de la distance mesurée sur la première ligne.