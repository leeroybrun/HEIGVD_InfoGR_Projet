// inclusion des librairies
#include "main.h"
#include "Game.h"
#include "Camera.h"
#include "Menu.h"
#include "Terrain.h"
#include "ScreenInfos.h"
#include "Debug.h"
#include "Material.h"
#include "Stats.h"
#include "World.h"
#include "Keyboard.h"
#include "Player.h"
#include <math.h>
#include <map>

void renderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    GLfloat ambientColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
    
    GLfloat lightColor0[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat lightPos0[] = {-0.5f, 0.8f, 0.1f, 0.0f};
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightColor0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  lightColor0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightColor0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
    
    Material *whiteMaterial = new Material(
                                           color4(0.1,0.1,0.1, 1),
                                           color4(1,1,1, 1),
                                           color4(0.2,0.2,0.2, 1),
                                           color4(0,0,0, 1),
                                           0);
    
    Game::camera->lookAt();
    
    Game::textures->enable();
    
    Game::world->drawSkydome();
    
    whiteMaterial->apply();
    
    Game::textures->drawTexture("moleson");
    Game::terrain->draw();
    
    // Water
    Game::world->drawWater();
    
    // Draw random objects on map
    Game::world->drawRandomObjects();
    
    Game::player->drawThrownObjects();
    
    if(Game::debug->isDebug()) {
        Game::textures->resetCurrentTexture();
        
        Material *blackMaterial = new Material(color4(0,0,0, 1), color4(0,0,0, 1), color4(0,0,0, 1), color4(0,0,0, 1), 0);
        blackMaterial->apply();
        
        Game::debug->showAxes();
        
        Game::debug->showDebugInfos();
    }
    
    glutSwapBuffers();
    Game::textures->disable();
}

void changeSize(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.0, 2000.0);
}

void idle() {
    Game::stats->computeStats();
    
    Game::camera->doMovement();
    
    if(Game::camera->isOnFloor()) {
        float terrainY = Game::terrain->getRealHeight(Game::camera->getX(), Game::camera->getZ());
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
    
    Game::textures->loadTextures(textures);
    
    Game::terrain = loadTerrain(ABSOLUTE_PATH("data/heightmaps/moleson_360x360.png"), TERRAIN_HEIGHT_FACTOR);
    
    Game::camera = new Camera(Vec3f(28,1.5,-3.5)); // Position de la camera : x,y,z et angle
    
    Game::scrInfos = new ScreenInfos();
    
    Game::debug = new Debug(true);
    
    Game::stats = new Stats();
    
    Game::world = new World();
    
    Game::keyboard = new Keyboard();
    
    Game::player = new Player();
    
    Game::window = new Window(WIN_W, WIN_H);
    
    glClearColor(1.0, 1.0, 1.0, 1.0);
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_CULL_FACE);
    
    //Game::world->drawFog();
    
    Game::world->init();
    Game::textures->init();
    Game::camera->init();
    Game::terrain->setScaleFactor(TERRAIN_SCALE_FACTOR);
    Game::player->init();
}

void pressKey(unsigned char key, int xx, int yy) {
    Game::keyboard->pressKey(key, xx, yy);
    Game::camera->pressKey(key, xx, yy);
    Game::player->pressKey(key, xx, yy);
}

void releaseKey(unsigned char key, int x, int y) {
    Game::player->releaseKey(key, x, y);
    Game::keyboard->releaseKey(key, x, y);
}

void pressSpecialKey(int key, int xx, int yy) {
    Game::keyboard->pressKey(key, xx, yy);
    //Game::camera->pressKey(key, xx, yy);
}

void releaseSpecialKey(int key, int x, int y) {
    Game::keyboard->releaseKey(key, x, y);
    //Game::camera->releaseKey(key, x, y);
}

void mouseMovement(int x, int y) {
    Game::camera->mouseMotion(x, y);
}

// la fonction principal main
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition (50, 50);
    glutInitWindowSize (WIN_W, WIN_H);
    glutCreateWindow("Leeroy BRUN - HEIG-VD - InfoGR - Projet");
    
    init();
    
    glutDisplayFunc(renderScene);
    glutIdleFunc(idle);
    glutReshapeFunc(changeSize);
    //glutKeyboardFunc(processNormalKeys);
    //glutSpecialFunc(processSpecialKeys);
    
    glutIgnoreKeyRepeat(1);
    glutKeyboardFunc(pressKey);
    glutKeyboardUpFunc(releaseKey);
    glutSpecialFunc(pressSpecialKey);
    glutSpecialUpFunc(releaseSpecialKey);
    glutPassiveMotionFunc(mouseMovement);
    
    createMenus();
    
    glutMainLoop();
    
    return 0;
}
