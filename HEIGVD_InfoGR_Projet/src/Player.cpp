//
//  Player.cpp
//  HEIGVD_InfoGR_Projet
//
//  Created by Leeroy Brun on 10.04.15.
//  Copyright (c) 2015 Leeroy Brun. All rights reserved.
//

#include "Player.h"

// ------------------------------------------------------------------
//  Classe Player
//
//  Cette classe contient la gestion du joueur.
//
//  Il peut lancer des objets lorsque l'utilisateur appuye sur la
//  touche ENTER ou sur le clic gauche de la souris.
//
//  Todo: déplacer toute la gestion des mouvements de l'utilisateur
//        (clavier/souris), le fait de pouvoir sauter et de rester
//        à la hauteur du terrain dans la classe Player
//        (actuellement dans la classe Camera).
// ------------------------------------------------------------------

// Initialise le joueur
void Player::init()
{
    // On initialise le bonhome de neige que le joueur peut lancer
    snowman = new Snowman(Vec3f(Game::camera->getX(), Game::camera->getY(), Game::camera->getZ()), 1, 0.5);
}

// Gestion des objets lancés par le joueur
// Cette fonction déplace les objets lancés, calcul leur nouvelle position, les fait disparaitre si ils touchent le sol, etc
void Player::drawThrownObjects()
{
    // Si le bonhomme de neige bouge (une des positions de la velocity est définie)
    if(snowman->getVelocity().getX() != 0 || snowman->getVelocity().getY() != 0 || snowman->getVelocity().getZ() != 0)
    {
        // On le déplace à la vitesse de lancé
        snowman->move(throwSpeed);
        
        // On calcul sa hauteur actuelle ainsi que la hauteur du terrain à sa position actuelle
        float snowmanHeight = snowman->getPos(Center).getY();
        float terrainHeight = Game::terrain->getHeightAtRealPos(snowman->getPos(Center).getX(), snowman->getPos(Center).getZ())-10; // On enlève 10, pour ne pas être embêté par le terrain si l'objet serait un peu enfoncé
                
        // Si le bonhomme de neige a atteint le terrain, on reset sa velocity et la vitesse de lancé
        if(snowmanHeight <= terrainHeight) {
            snowman->setVelocity(Vec3f(0, 0, 0));
            throwSpeed = PLAYER_INIT_THROW_SPEED;
        
        // Sinon, le bonhomme de neige n'a pas atteint le terrain, on le dessine
        } else {
            //printf("Snowman is drawn.\n");
            snowman->draw();
        }
        
        // On vérifie si il entre en collision avec un objet du monde
        if(Game::world->detectCollisions(snowman)) {
            // On efface le bonhomme de neige lancé
            snowman->setVelocity(Vec3f(0, 0, 0));
            throwSpeed = PLAYER_INIT_THROW_SPEED;
            
            Game::scores->addPoints(200);
        }
    
    // Si le bonhomme de neige ne bouge pas (pas lancé)
    } else {
        // Si la touche ENTER est enfoncée, on incrémente la vitesse de lancé
        // Cela permet à l'utilisateur de sélectionner la vitesse de lancé en fonction de combien de tempsil laisse la touche ENTER enfoncée avant de la relacher
        if(Game::keyboard->getKeyState(13)) {
            // Le deltaTime est le temps (en secondes) qui a passé depuis la génération de la précédente frame
            // Cela permet d'avoir une vitesse de déplacement constante, peu importe le matériel de l'utilisateur, et donc indépendant du nombre de FPS
            float deltaTime = Game::stats->getDeltaTime();
            
            throwSpeed += 0.1 * deltaTime;
        }
    }
}

// On lance un bonhomme de neige
void Player::throwSnowman()
{
    // On défini sa position (départ) à la position de la caméra
    snowman->setPos(Center, Vec3f(Game::camera->getX(), Game::camera->getY(), Game::camera->getZ()));
   
    // La vélocité permet de lancer l'objet dans la direction du regard de la caméra
    snowman->setVelocity(Game::camera->getDirection());
}

void Player::mouseClick(int button, int state, int x, int y)
{
    if(button == GLUT_LEFT_BUTTON && button == GLUT_DOWN) {
        throwSnowman();
    }
}

void Player::pressKey(unsigned char key, int xx, int yy) {
    
}

void Player::releaseKey(unsigned char key, int xx, int yy) {
    switch (key) {
        case 13: throwSnowman(); break;
    }
}