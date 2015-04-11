## OpenGL/GLUT Game

### TODO
- Menu
- Brouillard
- Class light
- Class materials (comme textures)
- Ajouter lumières
- Ajouter mode jour/nuit
- Ajouter textures terrain
    - Eau
    - Sable
    - Herbe
    - Cailloux
    - Neige
- Ajouter objets aléatoirement
    - Arbres
    - « Ennemis »
- Pouvoir lancer des objets et toucher d’autres objets (arbres, ennemis, etc)
    - Points à chaque objet touché
- Pouvoir charger plusieurs terrains
    - Cervin
    - Moléson
    - Pléiades
    - Dents du midi
- Collisions : http://www.swiftless.com/tutorials/opengl/collision.html
- Skybox à la place de Skydome ?
    - https://sidvind.com/wiki/Skybox_tutorial
    - http://raptor.developpez.com/tutorial/opengl/skybox/

### Done

- Camera doit rester au-dessus du terrain (bug)
- Bouger la camera avec la souris (FPS)
- Pouvoir sauter

### Améliorations possibles
- Plusieurs textures sur le terrain (fonction de la hauteur, etc) (http://3dgep.com/multi-textured-terrain-in-opengl/)
- Utiliser VBO pour accélérer rendu terrain : http://www.swiftless.com/tutorials/opengl/6_vbo.html
- Display Lists : http://www.swiftless.com/tutorials/opengl/displaylists.html
- Ajouter « téléphérique » ou quelque chose comme ça
    - Sur l’axe X ou Z
    - Du point le plus bas, au point le plus haut sur cet axe
    - Pouvoir prendre le téléphérique pour monter en haut
    - Cabines ne font que monter, pas descendre (plus simple)

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