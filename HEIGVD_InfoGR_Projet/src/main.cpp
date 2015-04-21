// inclusion des librairies
#include "main.h"
#include "Game.h"
#include "Camera.h"
#include "Menu.h"
#include "Terrain.h"
#include "ScreenInfos.h"
#include "Debug.h"
#include "Light.h"
#include "Material.h"
#include "Materials.h"
#include "Stats.h"
#include "World.h"
#include "Keyboard.h"
#include "Player.h"
#include "Scores.h"
#include <math.h>
#include <map>

bool showTextures = true;
bool showFog = true;
int showLight = 0; // Défini la lumière à afficher : 0 = day, 1 = dusk, 2 = night

Light *dayLight;
Light *duskLight;
Light *nightLight;

float lightAngle = 0;
float lightAngleAddition = 0.5;

Light *colorLight1;
Light *colorLight2;
Light *colorLight3;

bool colorLight1Active = false;
bool colorLight2Active = false;
bool colorLight3Active = false;

// Fonction de display, affiche la scène
void renderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // Couleur ambiante -> blanche
    GLfloat ambientColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
    
    // ---------------------------------------
    //  Gestion du passage jour/nuit
    // ---------------------------------------
    
    glPushMatrix();

    glTranslatef(0, 0, 0); // Position du point de rotation des lumières
    glRotatef(lightAngle, 0, 0, 1); // R0tation autour du point de rotation
    
    // On désactive toutes les lumières
    dayLight->disable();
    duskLight->disable();
    nightLight->disable();
    
    // Position des lumières lorsque l'angle est 0
    dayLight->setPos(LightPos(0, 100, 0, 0));    // Lumière du soleil au zenith : y=100
    duskLight->setPos(LightPos(0, 100, 0, 0));   // Lumière du coucher de soleil au même endroit que le soleil
    nightLight->setPos(LightPos(0, -100, 0, 0)); // Lumière de nuit (apparentée à la lune) à l'inverse du soleil
    
    // Si l'angle est plus grand que 360, on lui enlève 360 (on reste toujours entre 0 et 359)
    if(lightAngle > 360)
    {
        lightAngle -= 360;
        Game::stats->setNbDays(Game::stats->getNbDays()+1); // On a passé une journée complète, on incrémente le nombre de jours passés
    }
    
    // Si l'angle est entre 0 et 70 ou 300 et 359, on est en journée
    if(lightAngle < 70 || lightAngle > 300)
    {
        dayLight->enable();
        dayLight->apply();
        Game::stats->setDayPeriod(0); // jour
    }
    // Si l'angle est entre 70 et 90, coucher de soleil
    else if((lightAngle > 70 && lightAngle <= 90))
    {
        duskLight->enable();
        duskLight->apply();
        Game::stats->setDayPeriod(1); // coucher de soleil
    }
    // Si l'angle est entre 270 et 300, on est en levé de soleil
    else if(lightAngle > 270 && lightAngle <= 300)
    {
        duskLight->enable();
        duskLight->apply();
        Game::stats->setDayPeriod(3); // nuit
    }
    // Sinon, c'est la nuit
    else
    {
        nightLight->enable();
        nightLight->apply();
        Game::stats->setDayPeriod(2); // levé de soleil
    }
    
    glPopMatrix();
    
    // On incrémente l'angle de rotation des lumières
    lightAngle += lightAngleAddition;
    
    // On affiche maintenant des lumières "simples" de couleurs différentes, si demandé
    colorLight1->disable();
    colorLight2->disable();
    colorLight3->disable();
    
    if(colorLight1Active) {
        colorLight1->enable();
        colorLight1->apply();
    }
    
    if(colorLight2Active) {
        colorLight2->enable();
        colorLight2->apply();
    }
    
    if(colorLight3Active) {
        colorLight3->enable();
        colorLight3->apply();
    }
    
    // Défini la position et le target de la camera
    Game::camera->lookAt();
    
    // Affichage du brouillard
    if(showFog)
    {
        glEnable(GL_FOG);
        Game::world->drawFog();
    } else {
        glDisable(GL_FOG);
    }
    
    // Activation des textures
    if(showTextures)
    {
        Game::textures->enable();
    } else {
        Game::textures->disable();
    }
    
    
    // Affichage du skydome
    Game::world->drawSkydome();
    
    // Affichage du terrain (heightmap) avec sa texture
    Game::materials->applyMaterial("white");
    Game::textures->drawTexture("moleson");
    Game::terrain->draw();
    
    // Affichage de l'eau
    Game::world->drawWater();
    
    // Affichage d'objets aléatoirement sur la map
    Game::world->drawRandomObjects();
    
    // Affichage et calcul de la position des objets lancés par le joueur
    Game::player->drawThrownObjects();
    
    // On reset la texture en cours
    Game::textures->resetCurrentTexture();
    
    // Affichage des scores
    Game::scores->draw();
    
    // Debug-> Affichage des axes si besoin
    if(Game::debug->shouldShowAxes())
    {
        Game::debug->showAxes();
    }
    
    // Debug-> Affichage des infos de debug si besoin
    if(Game::debug->shouldShowDebugInfos())
    {
        Game::debug->showDebugInfos();
    }
    
    // Debug-> Affichage des boites de collision si besoin
    if(Game::debug->shouldShowCollBoxes())
    {
        Game::debug->showCollBoxes();
    }
    
    glutSwapBuffers();
    Game::textures->disable();
}

void changeSize(int w, int h) {
    // Quand on redimensionne la fenêtre, on met à jour sa taille
    Game::window->width = w;
    Game::window->height = h;
    
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.0, 2000.0);
}

void idle() {
    // Calcul des statistiques (FPS, time, etc)
    Game::stats->computeStats();
    
    // Calcul de la nouvelle position de la camera ou de son nouveau target
    Game::camera->doMovement();
    
    // Si la camera est sur le sol, on fait en sorte qu'elle reste toujours par dessus le terrain
    if(Game::camera->isOnFloor()) {
        float terrainY = Game::terrain->getHeightAtRealPos(Game::camera->getX(), Game::camera->getZ());
        Game::camera->setY(terrainY);
    }
    
    glutPostRedisplay();
}

// fonction de l'initialisation
void init (void)
{
    // Initialisation de la gestion des textures
    Game::textures = new Textures();
    
    // Vecteur (tableau) qui contiendra la liste des textures à charger
    texturesMapLoad textures;
    textures.insert(std::make_pair("water", ABSOLUTE_PATH("data/textures/water1.png")));
    //textures.insert(std::make_pair("grass", ABSOLUTE_PATH("data/textures/grass.png")));
    //textures.insert(std::make_pair("rock", ABSOLUTE_PATH("data/textures/rock.png")));
    textures.insert(std::make_pair("snow", ABSOLUTE_PATH("data/textures/snow.png")));
    textures.insert(std::make_pair("moleson", ABSOLUTE_PATH("data/textures/moleson.png")));
    textures.insert(std::make_pair("skydome", ABSOLUTE_PATH("data/textures/skydome2.png")));
    
    // Chargement des textures
    Game::textures->loadTextures(textures);
    
    //printf("VBO support: %d", glutExtensionSupported("GL_ARB_vertex_buffer_object"));
    
    // Initialisation des lumières
    dayLight = new Light(0, color4f(1.0f, 1.0f, 1.0f, 1.0f), color4f(1.0f, 1.0f, 1.0f, 1.0f), color4f(1.0f, 1.0f, 1.0f, 1.0f), LightPos(-0.5f, 20.0f, 0.1f, 0.0f));
    duskLight = new Light(0, color4f(1.0f, 0.335f, 0.335f, 1.0f), color4f(1.0f, 0.335f, 0.335f, 1.0f), color4f(1.0f, 0.335f, 0.335f, 1.0f), LightPos(-20.0f, 20.0f, 0.1f, 0.0f));
    nightLight = new Light(1, color4f(0.08f, 0.253f, 0.305f, 1.0f), color4f(0.08f, 0.253f, 0.305f, 1.0f), color4f(0.08f, 0.253f, 0.305f, 1.0f), LightPos(20.0f, 20.0f, 0.1f, 0.0f));
    
    // Lumières de couleur
    colorLight1 = new Light(2, color4f(1, 0, 0, 1.0f), color4f(1, 0, 0, 1.0f), color4f(1, 0, 0, 1.0f), LightPos(20.0f, 20.0f, 0.1f, 0.0f));
    colorLight2 = new Light(3, color4f(0, 1, 0, 1.0f), color4f(0, 1, 0, 1.0f), color4f(0, 1, 0, 1.0f), LightPos(-20.0f, 20.0f, 0.1f, 0.0f));
    colorLight3 = new Light(4, color4f(0, 0, 1, 1.0f), color4f(0, 0, 1, 1.0f), color4f(0, 0, 1, 1.0f), LightPos(-20.0f, 20.0f, -20.1f, 0.0f));
    
    // Chargement de la heightmap du terrain
    Game::terrain = loadTerrain(ABSOLUTE_PATH("data/heightmaps/moleson_360x360.png"), TERRAIN_HEIGHT_FACTOR);
    
    // Position de départ de la caméra
    Game::camera = new Camera(Vec3f(28,1.5,-3.5)); // Position de la camera : x,y,z
    
    // Initialisation des objets du jeu
    Game::scrInfos = new ScreenInfos();
    Game::debug = new Debug();
    Game::stats = new Stats();
    Game::world = new World();
    Game::keyboard = new Keyboard();
    Game::player = new Player();
    Game::materials = new Materials();
    Game::scores = new Scores();
    Game::window = new Window(WIN_W, WIN_H);
    
    glClearColor(1.0, 1.0, 1.0, 1.0);
    
    // Activations de base pour OpenGL
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_CULL_FACE);
    
    // On règle les paramètres pour le multisample
    glDisable(GL_LINE_SMOOTH);
    glDisable(GL_POLYGON_SMOOTH);
    glEnable(GL_MULTISAMPLE);
    glHint(GL_MULTISAMPLE_FILTER_HINT_NV, GL_NICEST);
    
    // Activation de la transparence
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // Initialisation des objets du jeu
    Game::scores->init();
    Game::materials->init();
    Game::world->init();
    Game::textures->init();
    Game::camera->init();
    Game::terrain->setScaleFactor(TERRAIN_SCALE_FACTOR);
    Game::player->init();
    
    // On crée des matériaux de base en mémoire afin de poivoir les réutiliser ensuite dans les différents objet
    Game::materials->addMaterial("whiteTransp", new Material(
                                                             color4f(0.1,0.1,0.1, 0.4),
                                                             color4f(1,1,1, 0.4),
                                                             color4f(0.2,0.2,0.2, 0.4),
                                                             color4f(0,0,0, 1),
                                                             0));
    
    Game::materials->addMaterial("white", new Material(
                                                       color4f(0.1,0.1,0.1, 1),
                                                       color4f(1,1,1, 1),
                                                       color4f(0.2,0.2,0.2, 1),
                                                       color4f(0,0,0, 1),
                                                       0));
    
    Game::materials->addMaterial("black", new Material(
                                                       color4f(0,0,0, 1),
                                                       color4f(0,0,0, 1),
                                                       color4f(0,0,0, 1),
                                                       color4f(0,0,0, 1),
                                                       0));
}

// Fonction appelée lorsqu'une touche du clavier est pressée
void pressKey(unsigned char key, int xx, int yy) {
    Game::keyboard->pressKey(key, xx, yy);
    Game::camera->pressKey(key, xx, yy);
    Game::player->pressKey(key, xx, yy);
}

// Fonction appelée lorsqu'une touche du clavier est relachée
void releaseKey(unsigned char key, int x, int y) {
    Game::player->releaseKey(key, x, y);
    Game::keyboard->releaseKey(key, x, y);
}

// Fonction appelée lorsqu'une touche spéciale du clavier est pressée
void pressSpecialKey(int key, int xx, int yy) {
    Game::keyboard->pressSpeKey(key, xx, yy);
}

// Fonction appelée lorsqu'une touche spéciale du clavier est relachée
void releaseSpecialKey(int key, int x, int y) {
    Game::keyboard->releaseSpeKey(key, x, y);
}

// Fonction appelée lorsque la souris bouge
void mouseMovement(int x, int y) {
    Game::camera->mouseMotion(x, y);
}

// Fonction appelée lorsque la souris est cliquée
void mouseClick(int button, int state, int x, int y) {
    Game::player->mouseClick(button, state, x, y);
}

// ------------------------------------------------------------------
//  Gestion des menus
// ------------------------------------------------------------------

Menu *debugMenu;
Menu *lightsMenu;
Menu *colorLightsMenu;
Menu *dayCycleMenu;
Menu *polygonModeMenu;
Menu *terrainMenu;
Menu *mainMenu;

// Fonction appelée lorsque l'utilisateur clic sur un des éléments du menu principal
void changeMainMenu(int value)
{
    switch (value) {
        // Activation/désactivation du brouillard
        case 1:
            showFog = !showFog;
            break;
            
        // Activation/désactivation des textures
        case 2:
            showTextures = !showTextures;
            break;
        
        // Quitter
        case 3:
            exit(0);
            break;
            
        default:
            break;
    }
    
    mainMenu->toggleEntryFromValue(value);
    mainMenu->update();
}

// Fonction appelée lorsque l'utilisateur clic sur un des éléments du menu de sélection du type de polygones
void changePolygonModeMenu(int value)
{
    switch (value) {
        // Mode polygone points
        case 1:
            glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
            break;
            
        // Mode polygone lignes
        case 2:
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            break;
            
        // Mode polygone plein
        case 3:
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            break;
            
        default:
            break;
    }
    
    polygonModeMenu->toggleEntryFromValue(value);
    polygonModeMenu->update();
}

// Fonction appelée lorsque l'utilisateur clic sur un des éléments du menu de sélection de la lumière
void changeLightsMenu(int value)
{
    switch (value) {
            // Mode jour
        case 1:
            lightAngle = 300; // Angle 300, affichera la lumière du jour
            break;
            
            // Mode coucher de soleil
        case 2:
            lightAngle = 70; // Angle 70, affichera le coucher de soleil
            break;
            
            // Mode nuit
        case 3:
            lightAngle = 95; // Angle 95, affichera la nuit
            break;
            
        default:
            break;
    }
    
    lightsMenu->toggleEntryFromValue(value);
    lightsMenu->update();
}

// Fonction appelée lorsque l'utilisateur clic sur un des éléments du menu de sélection de la vitesse de changement de cycle jour/nuit
void changeDayCycleMenu(int value)
{
    switch (value) {
            // Rapide
        case 1:
            lightAngleAddition = 1;
            break;
            
            // Moyenne
        case 2:
            lightAngleAddition = 0.5;
            break;
            
            // Lente
        case 3:
            lightAngleAddition = 0.1;
            break;
            
        default:
            break;
    }
    
    dayCycleMenu->toggleEntryFromValue(value);
    dayCycleMenu->update();
}

// Fonction appelée lorsque l'utilisateur clic sur un des éléments du menu de sélection des lumières de couleur
void changeColorLightsMenu(int value)
{
    switch (value) {
            // Rouge
        case 1:
            colorLight1Active = !colorLight1Active;
            break;
            
            // Vert
        case 2:
            colorLight2Active = !colorLight2Active;
            break;
            
            // Bleu
        case 3:
            colorLight3Active = !colorLight3Active;
            break;
            
        default:
            break;
    }
    
    colorLightsMenu->toggleEntryFromValue(value);
    colorLightsMenu->update();
}

// Fonction appelée lorsque l'utilisateur clic sur un des éléments du menu de debug
void changeDebugMenu(int value)
{
    switch (value) {
        case 1:
            Game::debug->toggleShouldShowAxes();
            break;
            
        case 2:
            Game::debug->toggleShouldShowDebugInfos();
            break;
            
        case 3:
            Game::debug->toggleShouldShowCollBoxes();
            break;
            
        default:
            break;
    }
    
    debugMenu->toggleEntryFromValue(value);
    debugMenu->update();
}

// Fonction appelée lorsque l'utilisateur clic sur un des éléments du menu de changement de terrain
void changeTerrainMenu(int value)
{
    switch (value) {
        case 1:
            Game::terrain->reloadHeightmap(ABSOLUTE_PATH("data/heightmaps/moleson_360x360.png"));
            break;
            
        case 2:
            Game::terrain->reloadHeightmap(ABSOLUTE_PATH("data/heightmaps/cervin.png"));
            break;
            
        case 3:
            Game::terrain->reloadHeightmap(ABSOLUTE_PATH("data/heightmaps/dentsdumidi.png"));
            break;
            
        case 4:
            Game::terrain->reloadHeightmap(ABSOLUTE_PATH("data/heightmaps/pleiades.png"));
            break;
            
        default:
            break;
    }
    
    terrainMenu->toggleEntryFromValue(value);
    terrainMenu->update();
}

// Fonction de création des menus
void createMenus(void) {
    // Sous-menu pour le changement du mode d'affichage des polygones
    polygonModeMenu = new Menu(changePolygonModeMenu);
    MenuEntriesToggleGroup *polyToggleGroup = new MenuEntriesToggleGroup();
    polygonModeMenu->addToggleGroup(polyToggleGroup);
    polyToggleGroup->addEntry("Sommets", 1, false);
    polyToggleGroup->addEntry("Fils-de-fer", 2, false);
    polyToggleGroup->addEntry("Facettes", 3, true);
    polygonModeMenu->create();
    
    // Sous-menu pour le debug
    debugMenu = new Menu(changeDebugMenu);
    debugMenu->addEntry("Afficher les axes", Toggle, 1, false);
    debugMenu->addEntry("Afficher les infos de debug", Toggle, 2, false);
    debugMenu->addEntry("Afficher les boites de collisions", Toggle, 3, false);
    debugMenu->create();
    
    // Sous-menu pour la vitesse de période de la journée
    lightsMenu = new Menu(changeLightsMenu);
    lightsMenu->addEntry("Jour", Simple, 1, false);
    lightsMenu->addEntry("Coucher de soleil", Simple, 2, false);
    lightsMenu->addEntry("Nuit", Simple, 3, false);
    lightsMenu->create();
    
    // Sous-menu pour la vitesse du changement jour/nuit
    dayCycleMenu = new Menu(changeDayCycleMenu);
    MenuEntriesToggleGroup *dayCycleToggleGroup = new MenuEntriesToggleGroup();
    dayCycleMenu->addToggleGroup(dayCycleToggleGroup);
    dayCycleToggleGroup->addEntry("Rapide", 1, false);
    dayCycleToggleGroup->addEntry("Moyenne", 2, true);
    dayCycleToggleGroup->addEntry("Lente", 3, false);
    dayCycleMenu->create();
    
    // Sous-menu pour le chargement des terrains
    terrainMenu = new Menu(changeTerrainMenu);
    MenuEntriesToggleGroup *terrainToggleGroup = new MenuEntriesToggleGroup();
    terrainMenu->addToggleGroup(terrainToggleGroup);
    terrainToggleGroup->addEntry("Moléson", 1, true);
    terrainToggleGroup->addEntry("Cervin", 2, false);
    terrainToggleGroup->addEntry("Dents du midi", 3, false);
    terrainToggleGroup->addEntry("Pléiades", 4, false);
    terrainMenu->create();
    
    // Sous-menu pour l'affichage ou non des lumières de couleur
    colorLightsMenu = new Menu(changeColorLightsMenu);
    colorLightsMenu->addEntry("Rouge", Toggle, 1, false);
    colorLightsMenu->addEntry("Vert", Toggle, 2, false);
    colorLightsMenu->addEntry("Bleu", Toggle, 3, false);
    colorLightsMenu->create();
    
    // Menu principal
    mainMenu = new Menu(changeMainMenu);
    mainMenu->addEntry("Afficher le brouillard", Toggle, 1, true);
    mainMenu->addEntry("Afficher les textures", Toggle, 2, true);
    mainMenu->addSubMenu("Mode de polygones", polygonModeMenu);
    mainMenu->addSubMenu("Changer de terrain", terrainMenu);
    mainMenu->addSubMenu("Changer la période du jour", lightsMenu);
    mainMenu->addSubMenu("Vitesse du changement de cycle jour/nuit", dayCycleMenu);
    mainMenu->addSubMenu("Activer les lumières de couleur", colorLightsMenu);
    mainMenu->addSubMenu("Debug", debugMenu);
    mainMenu->addEntry("Quitter", Simple, 3);
    mainMenu->create();
    mainMenu->attach(GLUT_RIGHT_BUTTON);
};

// Fonction principale
int main(int argc, char** argv)
{
    // Initialisation de la fenêtre GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE);
    glutInitWindowPosition (50, 50);
    glutInitWindowSize (WIN_W, WIN_H);
    glutCreateWindow("Leeroy BRUN - HEIG-VD - InfoGR - Projet");
    
    // Appel de la fonction d'initialisation
    init();
    
    // Fonctions d'affichage, idle et display
    glutDisplayFunc(renderScene);
    glutIdleFunc(idle);
    glutReshapeFunc(changeSize);
    
    // Fonctions pour la gestion du clavier/souris
    glutIgnoreKeyRepeat(1);
    glutKeyboardFunc(pressKey);
    glutKeyboardUpFunc(releaseKey);
    glutSpecialFunc(pressSpecialKey);
    glutSpecialUpFunc(releaseSpecialKey);
    glutPassiveMotionFunc(mouseMovement);
    glutMouseFunc(mouseClick);
    
    // Création des menus
    createMenus();
    
    glutMainLoop();
    
    return 0;
}
