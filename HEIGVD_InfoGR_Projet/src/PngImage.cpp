//
//  loadPngHeightMap.cpp
//  HeghtMaps_3
//
//  Created by Leeroy Brun on 02.04.15.
//  Copyright (c) 2015 Leeroy Brun. All rights reserved.
//

#include "PngImage.h"

PngImage::PngImage(int** px, unsigned w, unsigned h) : pixels(px), width(w), height(h) {
    
}

PngImage::~PngImage() {
    //delete[] pixels;
}

PngImage* loadPngImage(const char* filename) {
    std::vector<unsigned char> image; // Contiendra les valeurs RGBA des pixels en commencant en haut à gauche de l'image, traitant tous les pixels de la première ligne, puis début de la deuxième, etc... R1,G1,B1,A1,R2,G2,B2,A2,R3,G3,... Chaque pixel aura donc 4 éléments concéquitifs le concernant dans le tableau (RGBA)
    unsigned width, height;
    
    // Decode le PNG avec la librairie lodepng
    unsigned error = lodepng::decode(image, width, height, filename);
    
    // En cas d'erreur, on l'affiche
    if(error) {
        printf("PNG decoding error : %u : %s", error, lodepng_error_text(error));
    }
    
    // Les pixels se trouvent maintenant dans le vector "image", 4 bytes par pixel, ordonnés RGBARGBA
    
    // Initialise le tableau des pixels
    // Initialise le tableau des hauteurs
    int **pixels = new int*[height];
    for(int i = 0; i < height; i++) {
        pixels[i] = new int[width];
    }
    
    int x = 0; // No du pixel dans la ligne en cours
    int z = 0; // Ligne de pixels en cours
    
    int rgba = 0; // RGBA permet de savoir sur quelle valeur (R, G, B ou A) nous sommes. Il s'incrémente de 0 (R) à 3 (A) et revient ensuite à 0. Ceci permet de ne garder que la première valeur (R)
    
    for(std::vector<int>::size_type i = 0; i < image.size(); i++) {
        // On est arrivés à la donnée du A (alpha) du pixel, le prochain élément concernera donc le R (rouge) du prochain pixel
        if(rgba == 3) {
            rgba = -1; // On met rgba à -1 car il sera de toute façon incrémenté à 0 à la fin de la boucle
            // Comme l'image est en niveau de gris, on ne s'intéresse qu'au R
        } else if(rgba == 0) {
            // Si on a atteint la fin de la ligne de pixels, on passe à la ligne suivante
            if(x == width) {
                x = 0;
                z++;
                //printf("\n");
            }
            
            pixels[z][x] = image[i]; // Place la valeur de R dans le tableau
            //printf("%d, ", (int)image[i]);
            x++; // Passe au pixel suivant de la ligne
        }
        rgba++; // Passe à la prochaine valeur RGBA
    }
    
    return new PngImage(pixels, width, height);
}
