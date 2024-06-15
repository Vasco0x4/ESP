# Dayz Simple ESP 

Un projet simple permettant de comprendre les bases du reverse engineering sur la mémoire afin de récupérer les bons offsets.

Ce projet est basé sur le jeu DayZ en mode hors ligne. Il récupère les entités autour du joueur pour les marquer à l'écran. Le projet est en développement. Pour l'instant, il affiche uniquement la position des entités et du joueur dans le menu de débogage. Il reste encore à traduire les données reçues pour les afficher sous forme d'ESP.

Les offsets sont basés sur la version 1.25 de la version officielle de DayZ. Les offsets changent à chaque version.

### memory.hpp & memory.cpp
- fonctions pour lire et écrire dans la mémoire du processus du jeu.

### Graphics.h & Graphics.cpp
- DirectX et gestion du rendu.

### ImGuiSetup.h & ImGuiSetup.cpp
- ImGui pour l'interface utilisateur.

### CheatFunctions.hpp & CheatFunctions.cpp
- Gestion des fonctions incluant  l'affichage des entités.

### vector3.hpp & vector3.cpp
- Gestion des vecteurs 3D pour représenter les positions des entités.

### main.cpp
- Point d'entrée principal, initialise la fenêtre, DirectX, ImGui, et boucle principale.

### offsets.hpp
-  offsets utilisés pour accéder aux structures de données spécifiques dans la mémoire du jeu.

## Disclaimer
Le projet ne possède aucun moyen de contourner Battle eyes. Par conséquent, il reste à but éducatif. Le lancer sans désactiver BattlEye vous entraînera simplement un bannissement.
