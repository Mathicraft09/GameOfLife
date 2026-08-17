# Jeu de la Vie de Conway

Une implémentation du **Jeu de la Vie** (Conway's Game of Life) en C++ avec interface graphique.

## Description

Le Jeu de la Vie est un automate cellulaire inventé par le mathématicien John Conway en 1970. C'est un système évolutif basé sur des règles simples qui génère des comportements complexes fascinants.

### Règles du jeu
1. **Survie** : Une cellule vivante reste en vie si elle a 2 ou 3 voisins vivants
2. **Naissance** : Une cellule morte naît si elle a exactement 3 voisins vivants
3. **Mort** : Dans tous les autres cas, la cellule meurt ou reste morte

## Installation et Utilisation

### Version C++ (Graphique avec Raylib)

**Prérequis** : CMake 3.15+, compilateur C++17

```bash
# Générer le projet avec CMake
cmake -B build

# Compiler
cmake --build build --config Release

# Exécuter
./build/GameOfLife.exe  # Windows
# ou
./build/GameOfLife      # Linux/macOS
```

## Contrôles (Version C++)

| Touche | Action |
|--------|--------|
| `Espace` | Pause / Reprendre la simulation |
| `C` | Effacer la grille |
| `Clic Gauche` | Dessiner des cellules vivantes |
| `Clic Droit` | Effacer des cellules |

## Structure du Projet

```
GameOfLife/
├── game_of_life.cpp     # Version C++ avec interface graphique Raylib
├── CMakeLists.txt       # Fichier de configuration CMake
├── build/               # Dossier de compilation (généré)
└── README.md           # Ce fichier
```

## Technologies Utilisées

- **C++17** : Implémentation performante
- **Raylib** : Bibliothèque graphique pour la visualisation
- **CMake** : Système de build

## Notes

- La version C++ inclut un motif initial "Glider" pour démontrer le comportement du système
- La grille est de 1000x800 pixels avec des cellules de 10x10 pixels
- La simulation évolue à 10 Hz (toutes les 0.1 secondes)

## 🎓 Apprentissage

Ce projet fait partie d'un apprentissage sur les automates cellulaires et la vie artificielle. Il illustre comment des règles simples peuvent générer des comportements émergents complexes.
