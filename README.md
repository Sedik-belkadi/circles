# Travail pratique 3 : Le jeu *Circles*

## Description

Le projet *Circles* est un jeu développé dans le cadre du cours de programmation en C. L'objectif est de créer une expérience interactive où le joueur contrôle un triangle pour éviter des obstacles en mouvement. Ce projet met en œuvre les concepts abordés en classe, notamment la gestion des structures, des événements et des animations avec SDL2.


## Auteurs

BELKADI MOHAMMED ESSEDIK  
Code permanent : BELM87290502  

## Dépendances

Pour exécuter ce jeu, les dépendances suivantes doivent être installées :  

- **SDL2** : Bibliothèque de développement multimédia (https://libsdl.org).  
- **SDL2_image** : Extension pour gérer les images (https://www.libsdl.org/projects/SDL_image/).  
- **SDL2_mixer** : Extension pour gérer le son et la musique (https://www.libsdl.org/projects/SDL_mixer/).  
- **SDL2_ttf** : Extension pour gérer les polices (https://www.libsdl.org/projects/SDL_ttf/).  

Assurez-vous de télécharger et d'installer les versions compatibles pour votre plateforme.

## Fonctionnement

### Compilation et lancement du jeu
Pour compiler le jeu, exécutez simplement la commande :  
```bash
make
```

pour lancer :
```bash
./circles
```


### Description du jeu
Le but du jeu est de naviguer un triangle dans un espace rempli d'obstacles circulaires en mouvement, tout en évitant les collisions.


### Contrôles

-Menu principal :

Utilisez la souris pour naviguer dans le menu.
Choisissez une difficulté en cliquant sur l'option désirée, puis appuyez sur Play pour lancer la partie.

-Gameplay :

Utilisez la souris pour déplacer le triangle (joueur).


## Plateformes supportées

Le jeu a été testé et développé sur les plateformes suivantes :

Ubuntu 22.04 LTS

## Références

Aucune référence externe n'a été utilisée pour ce projet, en dehors de la documentation officielle des bibliothèques SDL2.

## Division des tâches

Voici les tâches effectuées pour ce projet. Toutes les tâches ont été réalisées par BELKADI MOHAMMED ESSEDIK :

* [x] Gestion du menu
* [x] Affichage de la scène
* [x] Affichage du chronomètre
* [x] Animation des murs
* [X] Animation du joueur
* [x] Détection des collisions
* [x] Affichage d'une partie terminée
* [X] Gestion de la musique principale
* [x] Gestion des sons lorsqu'on navigue dans le menu
* [x] Gestion de la musique de fin de partie

## État du projet

Le projet est fonctionnel et offre une expérience complète. Cependant, il existe une limitation : dans certaines situations, les collisions ne sont pas détectées correctement. Ce problème reste rare et n'impacte pas significativement l'expérience globale du jeu.
