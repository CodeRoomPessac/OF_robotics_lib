# Capteur de Réflexion Infrarouge #
###*Grove - Infrared Reflective Sensor*###

![capteur reflexion](/images/capteur_reflexion/capteur_reflexion.jpg)

### Fonction ###

Le capteur de réflexion infrarouge Grove est utilisé pour détecter la présence d'un objet dans une plage spécifique. Le capteur est composé d’une LED infrarouge et d’une paire de photodétecteurs (phototransistor). La lumière émise par la LED IR est réfléchie par tout objet placé devant le capteur et cette réflexion est détectée par le photocapteur (phototransistor). Toute surface de couleur blanche (ou plus claire) reflète plus qu'une surface de couleur noire (ou plus foncée). Si l'objet en question est de couleur claire, il provoquera une plus grande élévation de courant que pour un objet foncé. 

Lorsque la lumière réfléchie est détectée, une sortie numérique LOW (ou binaire 0) est émise sur la broche SIG, et l'indicateur LED intégré s'allume. Si aucune réflexion n'est détectée ou si l'objet est trop éloigné du capteur, la sortie de la broche SIG reste à HIGH (ou binaire 1), et le voyant LED intégré sera éteint. La plage détectable de ce capteur est comprise entre 4 et 16 mm. Le module intègre un amplificateur opérationnel rail à rail pour amplifier la sortie du phototransistor. Il existe un potentiomètre permettant de régler le gain de l'amplificateur, c'est-à-dire la sensibilité de la détection.

*Dans le cadre de la Robocup, il servira à faire un robot suiveur de ligne (Rescue Line) ou à détecter une case noire ou argentée (Rescue Maze). Dans le cadre de Rescue Maze, il faudra en mettre deux sur le robot, un réglé (à l’aide du potentiomètre) pour détecter le noir, et l’autre réglé pour détecter le gris argenté.*

### Spécifications ###

- Tension de fonctionnement : 3.3 - 5V
- Courant de fonctionnement : 14.69 à 15.35 mA
- Portée effective : 4 à 15 mm
- Profondeur minimum détectable (lignes monochromes) : 10 mm
- Seuil ajustable avec un potentiomètre
- Temps de réponse : 10 μs
- Longueur d'onde maximale de sensibilité (phototransistor) : 800 nm
- Longueur d'onde maximale d'émission de lumière (LED infrarouge) : 940 nm
- Poids : 4 g

![capteur reflexion front](/images/capteur_reflexion/capteur_reflexion_front.jpg)


### Calibrage du capteur ###

Brancher le capteur sur le shield Grove, sur une entrée digitale (Dx).

![capteur reflexion calib1](/images/capteur_reflexion/capteur_reflexion_calib1.jpg)

Connectez le capteur réflectif à n'importe quel port digital.
Placez ce capteur 12 mm au-dessus du papier blanc (ou d'une autre couleur vive).
Régler le potentiomètre à l'aide d'un tournevis pour modifier la sensibilité du photodétecteur à réflexion, jusqu'à ce que le voyant LED s'allume. En tournant dans le sens des aiguilles d'une montre, le capteur photoélectrique à réflexion sera plus sensible à la lumière.

![capteur reflexion calib2](/images/capteur_reflexion/capteur_reflexion_calib2.jpg)

Respectez la distance verticale, déplacez le capteur horizontalement vers la ligne noire. Le voyant lumineux doit s'éteindre au-dessus de la ligne noire. S'il est toujours allumé, régler le potentiomètre jusqu'à ce qu'il soit éteint.

### Création des blocs mBlock ###

	[
		"r",
		"Valeur du capteur de ligne sur la broche %n",
		"Valeur du capteur de ligne sur la broche",
		"8",
		{
			"setup":"",
			"inc":"",
			"def":"",
			"work":"digitalRead({0})",
			"loop":""
		}
	],

C'est un capteur, il est donc normal de n'avoir qu'un bloc en lecture ("r" comme read). Le capteur utilise une pin digitale.

 - **work :** On lit la valeur (LOW ou HIGH) de la pin digitale à laquelle est connecté le capteur de reflexion

### Utilisation des blocs mBlock ###

On obtient donc dans mBlock le bloc suivant :

![capteur reflexion bloc](/images/capteur_reflexion/capteur_reflexion_bloc.jpg)

Ce qui nous permet de réaliser le petit programme suivant :

![capteur reflexion exemple](/images/capteur_reflexion/capteur_reflexion_exemple.jpg)

Dans cet exemple le capteur est branché sur la pin D8. On affiche sur l'écran LCD la valeur du capteur de ligne sur la première ligne.