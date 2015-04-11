//
//  Camera.cpp
//  HEIGVD_InfoGR_Projet
//
//  Created by Leeroy Brun on 10.04.15.
//  Copyright (c) 2015 Leeroy Brun. All rights reserved.
//

#include "Camera.h"

float degreesToRad(float angle) {
    return angle * 3.14159265 / 180.0;
}

Camera::Camera(Vec3f _pos) : pos(_pos){}

Camera::~Camera(){
    
}

// Initialisation de la camera
void Camera::init() {
    // On cache le curseur de la souris
    glutSetCursor(GLUT_CURSOR_NONE);
    
    // Valeurs temporaires, elles seront remplacées au premier mouvement de souric
    lastMouseX = Game::window->width/2;
    lastMouseY = Game::window->height/2;
}

float Camera::getX()
{
    return pos.getX();
}

float Camera::getY()
{
    return pos.getY();
}

float Camera::getZ()
{
    return pos.getZ();
}

Vec3f Camera::getPosition()
{
    return pos;
}

Vec3f Camera::getDirection()
{
    return direction;
}

// Permet de définir le y (hauteur) de la position de la camera
// Cela nous permet de faire en sorte de rester par dessus le terrain
void Camera::setY(float _y)
{
    pos[1] = _y;
}

// Permet de faire sauter la camera
void Camera::jump() {
    if(isJumping) { return; }
    
    isJumping = true;
    jumpDir = Up;
    _isOnFloor = false;
    jumpStartY = getY(); // Position Y de départ, qui sera également notre position de retour
}

bool Camera::isOnFloor() {
    return _isOnFloor;
}

// Calcul de la nouvelle position de la camera en fonction des touches clavier qui sont enclenchées
void Camera::doMovement()
{
    // Le deltaTime est le temps (en secondes) qui a passé depuis la génération de la précédente frame
    // Cela permet d'avoir une vitesse de déplacement constante, peu importe le matériel de l'utilisateur, et donc indépendant du nombre de FPS
    float deltaTime = Game::stats->getDeltaTime();
    if(deltaTime <= 0) {
        deltaTime = 0.5; // Fix car parfois le deltatime est trop court et la camera se retrouve bloquée
    }
    
    GLfloat cameraSpeed = CAMERA_MOVE_SPEED * deltaTime;
    GLfloat jumpSpeed = CAMERA_JUMP_SPEED * deltaTime;
    
    // La touche clavier UP est enfoncée, on va faire un déplacement en avant
    if(Game::keyboard->getKeyState(GLUT_KEY_UP))
    {
        pos += cameraSpeed * direction; // On se déplace dans la direction voulue en fonction de la vitesse
    }
    
    // La touche clavier DOWN est enfoncée, on va faire un déplacement en arrière
    if(Game::keyboard->getKeyState(GLUT_KEY_DOWN))
    {
        pos -= cameraSpeed * direction; // On se déplace dans la direction voulue en fonction de la vitesse
    }
    
    // La touche clavier LEFT est enfoncée, on va faire un déplacement latéral à gauche
    if(Game::keyboard->getKeyState(GLUT_KEY_LEFT))
    {
        pos -= (direction.cross(up)).normalize() * cameraSpeed; // En appliquant un produit croisé entre le vecteur direction et le vecteur UP, on obtient un vecteur perpendiculaire aux deux qui pointe donc vers la droite de la camera
    }
    
    // La touche clavier RIGHT est enfoncée, on va faire un déplacement latéral à droite
    if(Game::keyboard->getKeyState(GLUT_KEY_RIGHT))
    {
        pos += (direction.cross(up)).normalize() * cameraSpeed; // En appliquant un produit croisé entre le vecteur direction et le vecteur UP, on obtient un vecteur perpendiculaire aux deux qui pointe donc vers la droite de la camera
    }
    
    // Si on est en train de sauter, on va devoir faire bouger la position de la camera sur l'axe Y
    if(isJumping){
        // On a pas encore atteint la hauteur maximale de saut
        if(jumpDir == Up && getY() < jumpStartY + CAMERA_JUMP_HEIGHT) {
            // On déplace la position sur l'axe Y à la vitesse jumpSpeed grâce au vecteur up (0,1,0)
            pos += jumpSpeed * up;
            
        // Hauteur maximale atteinte, on redescend
        } else if(jumpDir == Up) {
            jumpDir = Down;
        }
        
        // On est en train de redescendre de notre saut, et on a pas encore atteint le sol
        if(jumpDir == Down && getY() > jumpStartY) {
            // On déplace la position sur l'axe Y à la vitesse jumpSpeed grâce au vecteur up (0,1,0)
            pos -= jumpSpeed * up;
        
        // On est de retour sur le sol (jumpStartY)
        } else if(jumpDir == Down) {
            isJumping = false;
            _isOnFloor = true;
            pos[1] = jumpStartY; // On défini en dur la coordonnée Y de la position, pour être sûr de ne pas être descendu trop bas
        }
    }
}

// Défini la position de la camera en fonction des vecteurs de position, target (calculé en fonction de pos et direction) et up
void Camera::lookAt()
{
    target = pos + direction; // Le target est calculé en fonction de la position de la camera, et du vecteur de direction
    
    gluLookAt(pos.getX(), pos.getY(), pos.getZ(),
              target.getX(), target.getY(), target.getZ(),
              up.getX(),  up.getY(),  up.getZ());
}

void Camera::pressKey(unsigned char key, int xx, int yy) {
    switch (key) {
        case 32: jump(); break;
    }
}

// Calcul du nouveau vecteur de direction en fonction des mouvements de la souris
void Camera::mouseMotion(float x, float y)
{
    // Cela empêche un gros déplacement (bump) lors de la première arrivée de la souris dans la fenêtre
    if(firstMouseMove)
    {
        lastMouseX = x;
        lastMouseY = y;
        firstMouseMove = false;
    }
    
    // Calcul du mouvement de la souris depuis la dernière frame
    GLfloat xoffset = x - lastMouseX;
    GLfloat yoffset = lastMouseY - y; // Inversé car on veut que lorsque la souris monte, la camera onte aussi, et non l'inverse
    
    // Stocke les nouvelles valeurs pour le prochain mouvement
    lastMouseX = x;
    lastMouseY = y;
        
    // La sensibilité permet de rendre plus agréable les mouvements
    // Sans cela, les mouvements seraient trop "brusques" et difficile à controller
    GLfloat sensitivity = 0.25f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;
    
    // Incrément des valeurs de yaw (rotation sur l'axe y) et pitch (rotation sur l'axe x) avec les offset
    yaw   += xoffset;
    pitch += yoffset;
    
    // Si le pitch va au dela de 90 degrés, la vue risque d'être inversée et de en pas bien s'afficher
    // On bloque donc le pitch à maximum 89 et -89 degrés
    if(pitch > 89.0f)
        pitch =  89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;
    
    // Calcul du nouveau vecteur de direction qui nous servira à calculer le target en fonction de la position
    // Le sin du pitch nous donne la position sur l'axe Y
    // Le cos du pitch nous donne la position sur les axes X/Z
    // Le sin du yaw nous donne la position sur l'axe Z
    // Le cos du yaw nous donne la position sur l'axe X
    
    Vec3f _direction;
    _direction[0] = cos(degreesToRad(yaw)) * cos(degreesToRad(pitch));
    _direction[1] = sin(degreesToRad(pitch));
    _direction[2] = sin(degreesToRad(yaw)) * cos(degreesToRad(pitch));
    
    // On le normalise pour que tous nos vecteurs de position/target soient normalisés
    direction = _direction.normalize();
}