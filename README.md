# Bring-me-the-engine

Bring me the engine est un moteur de rendu et un moteur graphique 3D codé en C++ et basé sur OpenGL.
___________________________________________
## Compilation et Exécution
Pour faire fonctionner le projet, cmake ainsi que les bibliothèques GLFW et GLM sont nécessaires.

Pour compiler le projet, créer et se déplacer dans le dossier `build` :
```bash
mkdir build && cd build
```
Puis lancer la commande suivante qui va créer les fichiers de compilation :
```bash
cmake ..
```
Ensuite, pour compiler le projet, lancer la commande suivante :
```bash
make
```
Enfin, pour lancer le projet, exécuter la commande suivante :
```bash
../bin/BringMeTheEngine
```
Pour lancer les fichiers de tests, exécuter la commande suivante :
```bash
../bin/Bring-me-the-engine-tests
```

Une automatisation de tout le processus de pré-compilation et de compilation est possible en lançant à partir de la racine du projet la commande suivante :
```bash
./rebuild.sh
```
Puis le lancement du projet se fait de la même manière qu'avant :
```bash
./bin/BringMeTheEngine
```
(En présupposant la présence du dossier bin dans le dossier courant bien évidemment)
____________________________________________
## Utilisation
Afin de pouvoir naviguer dans le moteur, 3 types de déplacements sont possibles :
- **Déplacement avec les touches ZSAD** : 
  - Z : Avancer
  - S : Reculer
  - A : Aller à gauche
  - D : Aller à droite 
- **Rotation avec la souris** : 
  - Déplacer la souris en utilisant le clic droit pour faire pivoter la caméra.
- **Déplacement sur les axes verticaux et horizontaux** :
  - Pour se faire il suffit de maintenir la touche `Ctrl` enfoncée et de déplacer la souris.

Tout ses déplacements sont faisable en même temps, notamment le fait de pouvoir avancer avec ZASD tout en faisant pivoter l'axe de vue de la caméra.
____________________________________________
## Auteur
Romain Soares  
Mail: <soares.romain69100@gmail.com>  
Profil Github: [kyutsune](https://www.github.com/Kyutsune)
___________________________________________
## Les sources qui m'ont aidé lors de la réalisation de ce projet sont:
https://opengl.developpez.com/tutoriels/apprendre-opengl-2/?page=eclairage-simple

https://learnopengl.com/Guest-Articles/2021/Scene/Frustum-Culling

http://learnopengl.com/Advanced-Lighting/Shadows/Shadow-Mapping

https://learnopengl.com/Advanced-Lighting/Shadows/Point-Shadows

https://www.youtube.com/@TheCherno
