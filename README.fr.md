# Circles

[English](README.md) | **Français**

Circles est un jeu en C inspiré de *Super Hexagon*, réalisé dans le cadre du cours de programmation en C. Le joueur dirige un triangle autour du centre de l'arène et évite des obstacles qui se rapprochent.

## Fonctionnalités

- Menu avec trois niveaux de difficulté
- Déplacement du joueur à la souris
- Obstacles en mouvement et détection des collisions
- Chronomètre de survie
- Écran et effet sonore de fin de partie
- Musique et effets sonores

## Technologies

- C
- SDL2 pour la fenêtre, le rendu et les événements
- SDL2_image pour le chargement des images
- SDL2_mixer pour la musique et les effets sonores
- SDL2_gfx pour le dessin des formes

## Compilation et lancement

Le projet a été développé et testé sur Ubuntu 22.04. Il nécessite GCC, Make, `sdl2-config` et les bibliothèques de développement SDL2 indiquées ci-dessus.

Sur Ubuntu, installez les dépendances avec :

```bash
sudo apt update
sudo apt install build-essential libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-gfx-dev
```

Depuis la racine du dépôt, compilez et lancez le jeu depuis le dossier `src` :

```bash
cd src
make
./circles
```

L'exécutable charge les ressources depuis `../assets`; lancez-le depuis `src` pour que les chemins des fichiers soient résolus correctement.

## Contrôles

- Dans le menu, déplacez la souris pour parcourir les options. Cliquez sur une difficulté, puis sur **Play** pour commencer.
- Pendant la partie, déplacez la souris autour du centre de la fenêtre pour orienter le triangle.
- Cliquez sur **Quit** pour fermer le jeu.

## Auteur

Mohammed Essedik Belkadi  
Réalisé individuellement dans le cadre du travail pratique 3.

## Références

Documentation officielle des bibliothèques SDL2 utilisées.
