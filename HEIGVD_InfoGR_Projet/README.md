## OpenGL/GLUT Game

Créé par Leeroy BRUN pour le projet du cours Infographie de la HEIG-VD, Yverdon-les-bains, Suisse.

ATTENTION! Avant de compiler le projet, il faut changer le chemin absolu (ROOT_PATH) qui se trouve dans le fichier "inc/Game.h" ! Sinon la heightmap et les textures ne chargeront pas.

### Fonctionnalités

- Chargement facile d'un terrain sous forme de heightmap
- Gestion des collisions entre les objets du monde
- Chargement d'objets au format OBJ
- Apparition aléatoire d'objets sur la map
- Gestion d'un 
cycle jour/coucher de soleil/nuit/levé de soleil/jour
- Le joueur peut sauter et lancer des objets, il gagne des points lorsqu'il touche d'autres objets de la map
- Gestion facilitée des textures, matériaux et lumières avec des classes dediées

### Contrôles

- Touches UP/DOWN/LEFT/RIGHT du clavier ou touches WASD : avancer, reculer, déplacement latéral
- Déplacement de la souris : regarder autour de soi
- Clic gauche de la souris : lancer un objet
- Clic droit de la souris : afficher le menu
- Touche ENTER : lancer un objet

### Structure des dossiers

#### Dossier "types/"

Contient différents types utiles (size3f, color4f).

#### Dossier "data/"

Contient des fichiers de données tels que textures, heightmaps, modèles OBJ, etc.

#### Dossier "lib/"

Contient des librairies externes telles que Vec3f, LodePNG ou GLM.

#### Dossier "inc/"

Contient les fichiers .h du programme

#### Dossier "src/"

Contient les fichiers source du programme.

Dans chaque fichier source se trouve toute la documentation des différentes classes.

### Points qui pourraient être améliorés
- Changer la texture du skydome en fonction de si on est le jour/nuit/coucher de soleil
- Ajouter objets aléatoirement
    - Arbres
    - « Ennemis » qui bougent (AI)
- Lors du rechargement du terrain -> recalculer position objets
- Skybox à la place de Skydome
- Plusieurs textures sur le terrain (en fonction de la hauteur et l'inclinaison' par exemple)
    - Eau
    - Sable
    - Herbe
    - Cailloux
    - Neige
- Utiliser VBO (Vertex Buffer Object) pour accélérer le rendu du terrain

### Cahier des charges

#### Objectifs

Permettre à l’étudiant-e de:
- aller plus loin avec OpenGL
- modéliser un petit monde virtuel autonome en 3D
- réaliser un jeu simple par l’animation
- réaliser une interface utilisateur par le menu, la souris et touches clavier
- appliquer plusieurs types de lumières à la scène 3D
- appliquer les textures différentes à chaque objet 3D de la scène

#### Cahier de charges
Chaque étudiant-e :
- programme individuellement et apporte l’entête et des commentaires au code
- défini un petit monde virtuel en 3D, nécessaire pour développer un jeu simple
- réalise un simple jeu non-existante (à imaginer) en utilisant les animations
- utilise le bouton de la souris afin d’enclencher l’animation
- place bien la camera afin d’avoir une visualisation correcte de la scène et ajout l’option de changer le point de vue de la scène par les touches clavier
- applique au moins trois types de lumières de la couleur différente chaque une
- ajute l’effet de transparence ou le brouillard
- applique des textures sur tous les objets de la scène
- défini un menu avec les sous-menus permettant de choisir différentes options de
    - visualisation de la scène comme :
        - un affichage en sommets, fil-de-fer et à facettes pleines o activer ou désactiver chaque lumière séparément
        - activer ou désactiver la transparence (brouillard)
        - activer ou désactiver les textures et
        - quitter l’application
- se satisfait avec son travail qui réalisera

Délai: dernière séance du cours, démo en classe.