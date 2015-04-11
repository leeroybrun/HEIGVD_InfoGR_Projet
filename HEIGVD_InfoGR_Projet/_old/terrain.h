#ifndef _TERRAIN_H
#define _TERRAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include <GLUT/GLUT.h>


/////// * /////////// * /////////// * NEW * /////// * /////////// * /////////// *


#define MAP_SIZE		1024				// This is the size of our .raw height map
#define STEP_SIZE		16					// This is width and height of each QUAD
#define HEIGHT_RATIO	1.5f				// This is the ratio that the Y is scaled according to the X and Z

// This returns the height (0 to 255) from a heightmap given an X and Y
int Height(unsigned char *pHeightMap, int X, int Y);

// This loads a .raw file of a certain size from the file
void LoadRawFile(const char * strName, int nSize, unsigned char *pHeightMap);

// This turns heightmap data into primitives and draws them to the screen
void RenderHeightMap(unsigned char *pHeightMap);



/////// * /////////// * /////////// * NEW * /////// * /////////// * /////////// *

#endif


/////////////////////////////////////////////////////////////////////////////////
//
// * QUICK NOTES *
//
// This file holds all our defines and functions for dealing with the terrain.
// As more tutorials are put out, we will add to this file to better handle
// terrain rendering.  This is actually a huge subject, so there is much to code.
//
//
// Ben Humphrey (DigiBen)
// Game Programmer
// DigiBen@GameTutorials.com
// ©2000-2005 GameTutorials
//
//