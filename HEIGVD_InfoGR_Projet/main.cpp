// inclusion des librairies
#include "main.h"
#include <math.h>
#include <map>

Camera *_camera;
Terrain *_terrain;
ScreenInfos *_scrInfos;
Debug *_debug;
Textures *_textures;
int frameCount, currentTime, previousTime, fps;

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
    
    _camera->lookAt();
    
    _textures->enable();
    
    whiteMaterial->apply();
    
    _textures->drawTexture("grass");
    _terrain->draw(50.0f);
    
    // Plane
    //glColor3d(0.4f, 0.4f, 0.9f);
    glPushMatrix();
    _textures->drawTexture("water");
    glBegin(GL_QUADS);
    glTexCoord2f(1, 0);
    glVertex3f(300.0f, 1.0f, -300.0f);   // Bottom Right
    glTexCoord2f(0, 0);
    glVertex3f(-300.0f, 1.0f, -300.0f);  // Bottom Left
    glTexCoord2f(0, 1);
    glVertex3f(-300.0f, 1.0f, 300.0f);   // Top Right
    glTexCoord2f(1, 1);
    glVertex3f(300.0f, 1.0f, 300.0f);    // Top Left
    glEnd();
    glPopMatrix();
    
    if(_debug->isDebug()) {
        _textures->resetCurrentTexture();
        
        Material *blackMaterial = new Material(color4(0,0,0, 1), color4(0,0,0, 1), color4(0,0,0, 1), color4(0,0,0, 1), 0);
        blackMaterial->apply();
        
        _debug->showAxes(0, 8, 0);
        
        _scrInfos->drawScreenInfos(WIN_W, WIN_H);
    }
    
    glutSwapBuffers();
    _textures->disable();
}

void changeSize(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}

void calculateFPS()
{
    //  Increase frame count
    frameCount++;
    
    //  Get the number of milliseconds since glutInit called
    //  (or first call to glutGet(GLUT ELAPSED TIME)).
    currentTime = glutGet(GLUT_ELAPSED_TIME);
    
    //  Calculate time passed
    int timeInterval = currentTime - previousTime;
    
    if(timeInterval > 1000)
    {
        //  calculate the number of frames per second
        fps = frameCount / (timeInterval / 1000.0f);
        
        //  Set time
        previousTime = currentTime;
        
        //  Reset frame count
        frameCount = 0;
    }
}

void idle() {
    _camera->computePos();
    
    float terrainX = _camera->getX() * (1/_terrain->getScale()) + (_terrain->width()/2);
    float terrainZ = _camera->getZ() * (1/_terrain->getScale()) + (_terrain->length()/2);
    float terrainY = _terrain->getHeight(terrainX, terrainZ)+1.5;
    
    _camera->setY(terrainY);
    
    calculateFPS();
    
    if(_debug->isDebug()) {
        _scrInfos->set("01_camX", "Camera X : %f", _camera->getX());
        _scrInfos->set("02_camY", "Camera Y : %f", _camera->getY());
        _scrInfos->set("03_camZ", "Camera Z : %f", _camera->getZ());
        _scrInfos->set("04_camAngle", "Camera angle : %f", _camera->getAngle());
        
        _scrInfos->set("05_sep1", "------------------------");
        
        _scrInfos->set("06_camTerrX", "Terrain x: %f", terrainX);
        _scrInfos->set("07_camTerrY", "Terrain y: %f", terrainY);
        _scrInfos->set("08_camTerrZ", "Terrain z: %f", terrainZ);
        
        _scrInfos->set("09_sep", "------------------------");
        
        _scrInfos->set("10_terrW", "Terrain width: %d", _terrain->width());
        _scrInfos->set("11_terrL", "Terrain length: %d", _terrain->length());
        _scrInfos->set("12_terrScale", "Terrain scale: %f", _terrain->getScale());
        
        _scrInfos->set("13_sep", "------------------------");
        
        _scrInfos->set("14_fps", "FPS: %d", fps);
    }
    
    glutPostRedisplay();
}

// fonction de l'initialisation
void init (void)
{
    _textures = new Textures();
    
    texturesMapLoad textures;
    textures.insert(std::make_pair("water", "/Users/leeroybrun/Google Drive/HEIG-VD/Cours/2014-2015/Infographie/Exercices/HEIGVD_InfoGR_Projet/HEIGVD_InfoGR_Projet/data/textures/water1.png"));
    textures.insert(std::make_pair("grass", "/Users/leeroybrun/Google Drive/HEIG-VD/Cours/2014-2015/Infographie/Exercices/HEIGVD_InfoGR_Projet/HEIGVD_InfoGR_Projet/data/textures/grass.png"));
    textures.insert(std::make_pair("rock", "/Users/leeroybrun/Google Drive/HEIG-VD/Cours/2014-2015/Infographie/Exercices/HEIGVD_InfoGR_Projet/HEIGVD_InfoGR_Projet/data/textures/rock.png"));
    textures.insert(std::make_pair("snow", "/Users/leeroybrun/Google Drive/HEIG-VD/Cours/2014-2015/Infographie/Exercices/HEIGVD_InfoGR_Projet/HEIGVD_InfoGR_Projet/data/textures/snow.png"));
    
    _textures->loadTextures(textures);
    
    _terrain = loadTerrain("/Users/leeroybrun/Google Drive/HEIG-VD/Cours/2014-2015/Infographie/Exercices/HEIGVD_InfoGR_Projet/HEIGVD_InfoGR_Projet/data/heightmaps/moleson_360x360.png", 45);
    
    _camera = new Camera(28,1.5,-3.5, 4.2); // Position de la camera : x,y,z et angle
    
    _scrInfos = new ScreenInfos();
    
    _debug = new Debug(true);
    
    glClearColor(1.0, 1.0, 1.0, 1.0);
    
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_CULL_FACE);
    
    //_textures->init();
}

void cameraPressKey(int key, int xx, int yy) {
    _camera->pressKey(key, xx, yy);
}

void cameraReleaseKey(int key, int x, int y) {
    _camera->releaseKey(key, x, y);
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
    glutSpecialFunc(cameraPressKey);
    glutSpecialUpFunc(cameraReleaseKey);
    
    createMenus();
    
    glutMainLoop();
    
    return 0;
}
