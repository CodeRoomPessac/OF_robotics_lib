## Orange Robotics Library ##

<a href="https://www.orange.fr/portail"><img src="/images/logo_orange.png" alt="Orange" width="60" height="60"></a> <a href="https://www.arduino.cc/"><img src="/images/arduino_logo.png" alt="Arduino" width="141" height="60"></a><a href="http://wiki.seeedstudio.com/"><img src="/images/seeed_logo.png" alt="Grove Seeed" width="60" height="60"></a><a href="https://www.mblock.cc"><img src="/images/mblock_logo.jpg" alt="mBlock" width="60" height="60"></a>

Une librairie Orange pour la robotique utilisant Arduino et mBlock basée sur les composants [Grove Seeed](http://wiki.seeedstudio.com/).

Vous pourrez retrouver tout ce qui peut-être utilisé avec cette librarie dans le [pack électronique et motorisation](https://www.generationrobots.com/fr/403305-pack-electronique-et-motorisation-pour-challenge-rescue-de-la-robocup-junior.html) de [generation robots](https://www.generationrobots.com/fr/).

### Dans ce dépôt vous trouverez : ###
* **code :**
	* **C - Arduino :** Des exemples de code en C pour utiliser les composants Grove Seeed, ainsi que les librairies nécessaires.
	* **mBlock3 :** La librairie mBlock permettant de coder une carte Arduino Mega et les composants Grove Seeed avec le langage mBlock.
* **modelisation :** La modélisation des composants qui sont liés à cette bibliothèque, en différents formats.

### Explications concernant le nom des fichiers ###

Cette bibliothèque utilise en partie des fichiers déjà existant, provenant pour la plupart du [Github de Seeed Studio](https://github.com/Seeed-Studio/) ou encore du [Github de Generation Robots Lab](https://github.com/generationrobots-lab). Les fichiers ont été renommés **dans un soucis de cohérence et de clarté**, pour ceux qui souhaiterait n'utiliser que les fichiers dont ils ont besoin ou éventuellement modifier directement ceux-ci.
Vous pouvez retrouver la correspondance entre les noms des fichiers(présents dans les en-têtes des fichiers), présentés ici sans les extensions :

* capteur_ultrason <==> Ultrasonic
* encodeur <==> Encoder
* gyro_accelero <==> SparkFunLSM6DS3
* moteur <==> Grove\_I2C\_Motor_Driver
* capteur couleur <==> Adafruit_TCS34725

### Utilisation de la bibliothèque dans mBlock3 ###

Vous devez avoir installé la version de mBlock qui supporte les extensions, soit mBlock3.

TOut d'abord vous devez importer l'extension dans mBlock. Pour cela allez dans
`Extensions => Manage Extensions` :

![extension1](/images/mblock_extension1.png)

La fenêtre suivante va s'ouvrir, vous devez regarder les extensions installées et ajouter une extension :

![extension2](/images/mblock_extension2.png)

Vous pouvez ajouter une extension par un fichier json ou par un dossier zip. Ajoutez donc le dossier zip comme sur l'image suivante :

![extension3](/images/mblock_extension3.png)

Vous voyez la nouvelle extension apparaître :

![extension4](/images/mblock_extension4.png)

Maintenant que l'extension est importée vous devez voir les nouveaux blocs apparaitre. Pour uploader le code vers l'Arduino il faut vous assurer que vous avez bien connecté la bonne carte au logiciel. Pour cela vous devez configurer le type de carte que vous utilisez :

![extension5](/images/mblock_extension5.png)

Et connectez mBlock3 à la carte par le port concerné :

![extension6](/images/mblock_extension6.png)

Et voilà ! Vous devriez maintenant pouvoir utiliser les blocs de la bibliothèque ainsi qu'uploader le code que vous avez écrit vers la carte.

### Création d'un bloc mBlock3 ###

Si vous souhaitez créer vos propres blocs et les ajouter à l'extension existante, ou même créer votre propre extension, vous pouvez suivre ce [guide (attention en anglais)](https://github.com/CodeRoomPessac/OF_robotics_lib/wiki/mblock_extension_guide).
