#include "Terrain.h"

Terrain::Terrain(int w2, int l2) {
    w = w2;
    l = l2;
    
    // Initialise le tableau des hauteurs
    hs = new float*[l];
    for(int i = 0; i < l; i++) {
        hs[i] = new float[w];
    }
    
    // Initialise le tableau des normales
    normals = new Vec3f*[l];
    for(int i = 0; i < l; i++) {
        normals[i] = new Vec3f[w];
    }
    
    // Normales pas encore calculées
    computedNormals = false;
}

Terrain::~Terrain() {
    // Supprime les tableaux des hauteurs
    for(int i = 0; i < l; i++) {
        delete[] hs[i];
    }
    delete[] hs;
    
    // Supprime les tableaux des normales
    for(int i = 0; i < l; i++) {
        delete[] normals[i];
    }
    delete[] normals;
}

int Terrain::width() {
    return w;
}

int Terrain::length() {
    return l;
}

//Sets the height at (x, z) to y
void Terrain::setHeight(int x, int z, float y) {
    hs[z][x] = y;
    computedNormals = false;
}

//Returns the height at (x, z)
float Terrain::getHeight(int x, int z) {
    if(x < 0 || x > this->width()-1 || z < 0 || z > this->length()-1) {
        return 0;
    }
    
    return hs[z][x];
}

// Returns the real height at (x, z)
float Terrain::getRealHeight(int x, int z) {
    float terrainX = x * (1/Game::terrain->getScale()) + (Game::terrain->width()/2);
    float terrainZ = z * (1/Game::terrain->getScale()) + (Game::terrain->length()/2);
    float terrainY = getHeight(terrainX, terrainZ)*2+5;
    if(terrainY < 6) {
        terrainY = 6;
    }
    
    return terrainY;
}

float Terrain::getScale()
{
    return scale;
}

float Terrain::getScaleFactor()
{
    return scaleFactor;
}

void Terrain::setScaleFactor(float _scaleFactor)
{
    scaleFactor = _scaleFactor;
}

//Computes the normals, if they haven't been computed yet
void Terrain::computeNormals() {
    if (computedNormals) {
        return;
    }
    
    //Compute the rough version of the normals
    Vec3f** normals2 = new Vec3f*[l];
    for(int i = 0; i < l; i++) {
        normals2[i] = new Vec3f[w];
    }
    
    for(int z = 0; z < l; z++) {
        for(int x = 0; x < w; x++) {
            Vec3f sum(0.0f, 0.0f, 0.0f);
            
            Vec3f out;
            if (z > 0) {
                out = Vec3f(0.0f, hs[z - 1][x] - hs[z][x], -1.0f);
            }
            Vec3f in;
            if (z < l - 1) {
                in = Vec3f(0.0f, hs[z + 1][x] - hs[z][x], 1.0f);
            }
            Vec3f left;
            if (x > 0) {
                left = Vec3f(-1.0f, hs[z][x - 1] - hs[z][x], 0.0f);
            }
            Vec3f right;
            if (x < w - 1) {
                right = Vec3f(1.0f, hs[z][x + 1] - hs[z][x], 0.0f);
            }
            
            if (x > 0 && z > 0) {
                sum += out.cross(left).normalize();
            }
            if (x > 0 && z < l - 1) {
                sum += left.cross(in).normalize();
            }
            if (x < w - 1 && z < l - 1) {
                sum += in.cross(right).normalize();
            }
            if (x < w - 1 && z > 0) {
                sum += right.cross(out).normalize();
            }
            
            normals2[z][x] = sum;
        }
    }
    
    //Smooth out the normals
    const float FALLOUT_RATIO = 0.5f;
    for(int z = 0; z < l; z++) {
        for(int x = 0; x < w; x++) {
            Vec3f sum = normals2[z][x];
            
            if (x > 0) {
                sum += normals2[z][x - 1] * FALLOUT_RATIO;
            }
            if (x < w - 1) {
                sum += normals2[z][x + 1] * FALLOUT_RATIO;
            }
            if (z > 0) {
                sum += normals2[z - 1][x] * FALLOUT_RATIO;
            }
            if (z < l - 1) {
                sum += normals2[z + 1][x] * FALLOUT_RATIO;
            }
            
            if (sum.magnitude() == 0) {
                sum = Vec3f(0.0f, 1.0f, 0.0f);
            }
            normals[z][x] = sum;
        }
    }
    
    for(int i = 0; i < l; i++) {
        delete[] normals2[i];
    }
    delete[] normals2;
    
    computedNormals = true;
}

//Returns the normal at (x, z)
Vec3f Terrain::getNormal(int x, int z) {
    if (!computedNormals) {
        computeNormals();
    }
    return normals[z][x];
}

void Terrain::draw()
{
    glPushMatrix();
    scale = scaleFactor / std::max(this->width() - 1, this->length() - 1);
    glScalef(scale, scale, scale);
    glTranslatef(-(float)(this->width() - 1) / 2,
                 0.0f,
                 -(float)(this->length() - 1) / 2);
    
    glColor3f(0.3f, 0.9f, 0.0f);
    for(int z = 0; z < this->length() - 1; z++) {
        //Makes OpenGL draw a triangle at every three consecutive vertices
        glBegin(GL_TRIANGLE_STRIP);
        for(int x = 0; x < this->width(); x++) {
            /*if(this->getHeight(x, z) > 10) {
                Game::textures->drawTexture("snow");
            } else {
                Game::textures->drawTexture("grass");
            }*/
            
            Vec3f normal = this->getNormal(x, z);
            glNormal3f(normal[0], normal[1], normal[2]);
            glTexCoord2f((float)x / this->width(), (float)z / this->length());
            glVertex3f(x, this->getHeight(x, z), z);
                        
            normal = this->getNormal(x, z + 1);
            glNormal3f(normal[0], normal[1], normal[2]);
            glTexCoord2f((float)x / this->width(), (float)(z+1) / this->length());
            glVertex3f(x, this->getHeight(x, z + 1), z + 1);
        }
        glEnd();
    }
    glPopMatrix();
}

//Loads a terrain from a heightmap.  The heights of the terrain range from
Terrain* loadTerrain(const char* filename, float maxHeight) {
    PngImage* image = loadPngImage(filename);
    Terrain* t = new Terrain(image->width, image->height);
    
    for(int z = 0; z < image->height; z++) {
        for(int x = 0; x < image->width; x++) {
            int color = image->pixels[z][x];
            //printf("%d,", color);
            
            float h = (float)maxHeight * (((float)color / 255.0f)); // Calcule la hauteur du pixel en cours
            //printf("%f,", h);
            
            t->setHeight(x, z, h);
        }
        //printf("\n");
    }
    
    delete image;
    
    t->computeNormals();
    
    return t;
}