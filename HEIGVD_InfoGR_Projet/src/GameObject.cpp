//
//  GameObject.cpp
//  HEIGVD_InfoGR_Projet
//
//  Created by Leeroy Brun on 10.04.15.
//  Copyright (c) 2015 Leeroy Brun. All rights reserved.
//

#include "GameObject.h"

// ------------------------------------------------------------------
//  Classe GameObject
//
//  Cette classe contient la gestion des objets du jeu.
//
//  Elle permet de gérer les informations de base d'un objet
//  (taille, position, scale, gravité) ainsi que le mouvement d'un
//  objet dans l'espace en fonction d'un vecteur de vélocité.
//
//  Elle permet également de détecter les collisions entre différents
//  objets en fonction de la position et de la taille des objets.
//
//  Cette classe doit être dérivée afin de spécialiser la méthode
//  draw() des différents objets. Voir le dossier "GameObjects"
//  pour des exemples.
// ------------------------------------------------------------------

// Initlaise un objet du jeu
GameObject::GameObject(TypeGameObjectPos typePos, Vec3f pos, Size3f size, float scale, float gravity)
{
    // Défini la taille et le scale
    this->scale = scale;
    this->size.x = size.x * scale;
    this->size.y = size.y * scale;
    this->size.z = size.z * scale;
    
    // Défini sa position
    setPos(typePos, pos);
    
    // Défini la gravité de l'objet
    this->gravity = gravity;
}

// Retourne la position en fonction du type de position
Vec3f GameObject::getPos(TypeGameObjectPos typePos)
{
    if(typePos == TopLeft) {
        return topLeftPos;
    } else if(typePos == Center) {
        return centerPos;
    } else {
        return Vec3f();
    }
}

// Défini la position en fonction du type de position
void GameObject::setPos(TypeGameObjectPos typePos, Vec3f pos)
{
    if(typePos == TopLeft) {
        topLeftPos = pos;
        centerPos = Vec3f(pos.getX()+size.x, pos.getY()+size.y, pos.getZ()+size.z);
    } else if(typePos == Center) {
        centerPos = pos;
        topLeftPos = Vec3f(pos.getX()-(size.x/2), pos.getY()-(size.y/2), pos.getZ()-(size.z/2));
    }
}

// Retourne la taille de l'objet
Size3f GameObject::getSize()
{
    return size;
}

// Retourne la gravité de l'objet
float GameObject::getGravity()
{
    return gravity;
}

// Défini la gravité de l'objet
void GameObject::setGravity(float _gravity)
{
    gravity = _gravity;
}

// Retourne la vélocité de l'objet
Vec3f GameObject::getVelocity()
{
    return velocity;
}

// Défini la vélocité de l'objet
void GameObject::setVelocity(Vec3f _velocity)
{
    velocity = _velocity;
}

// Déplace l'objet à la vitesse passée en paramètre
void GameObject::move(float speed)
{
    if(gravity != 0) {
        velocity[1] -= gravity*0.01;
    }
    
    topLeftPos += speed * velocity;
    centerPos += speed * velocity;
}

// Détecte la collision avec un autre objet passé en paramètre
bool GameObject::detectCollision(GameObject &obj2)
{
    // Collision sur l'axe X ?
    bool collisionX = topLeftPos.getX() + size.x >= obj2.topLeftPos.getX() &&
    obj2.topLeftPos.getX() + obj2.size.x >= topLeftPos.getX();
    
    // Collision sur l'axe Y ?
    bool collisionY = topLeftPos.getY() + size.y >= obj2.topLeftPos.getY() &&
    obj2.topLeftPos.getY() + obj2.size.y >= topLeftPos.getY();
    
    // Collision sur l'axe Z ?
    bool collisionZ = topLeftPos.getZ() + size.z >= obj2.topLeftPos.getZ() &&
    obj2.topLeftPos.getZ() + obj2.size.z >= topLeftPos.getZ();
    
    // Collision seulement si elle survient sur les 3 axes en même temps
    return collisionX && collisionY && collisionZ;
}

// Dessine la "boite" de détection des collisions pour l'objet
void GameObject::drawCollisionBox()
{
    glPushMatrix();
    glTranslatef(topLeftPos.getX(), topLeftPos.getY(), topLeftPos.getZ());
    
    Game::materials->applyMaterial("whiteTransp");
    
    // Face de gauche
    glBegin(GL_QUADS);
    glVertex3f(0, 0, size.z);
    glVertex3f(0, size.y, size.z);
    glVertex3f(0, size.y, 0);
    glVertex3f(0, 0, 0);
    glEnd();
    
    glTranslatef(0, 0, size.z);
    
    // Face de devant
    glBegin(GL_QUADS);
    glVertex3f(size.x, 0, 0);
    glVertex3f(size.x, size.y, 0);
    glVertex3f(0, size.y, 0);
    glVertex3f(0, 0, 0);
    glEnd();
    
    glTranslatef(size.x, 0, 0);
    
    // Face de droite
    glBegin(GL_QUADS);
    glVertex3f(0, 0, -size.z);
    glVertex3f(0, size.y, -size.z);
    glVertex3f(0, size.y, 0);
    glVertex3f(0, 0, 0);
    glEnd();
    
    glTranslatef(0, 0, -size.z);
    
    // Face de derrière
    glBegin(GL_QUADS);
    glVertex3f(-size.x, 0, 0);
    glVertex3f(-size.x, size.y, 0);
    glVertex3f(0, size.y, 0);
    glVertex3f(0, 0, 0);
    glEnd();
    
    Game::materials->restorePrevMaterial();
    
    glPopMatrix();
}