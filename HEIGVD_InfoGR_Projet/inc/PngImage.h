//
//  loadPngHeightMap.h
//  HeghtMaps_3
//
//  Created by Leeroy Brun on 02.04.15.
//  Copyright (c) 2015 Leeroy Brun. All rights reserved.
//

#ifndef __HeghtMaps_3__loadPngHeightMap__
#define __HeghtMaps_3__loadPngHeightMap__

#include <stdio.h>
#include <stdlib.h>

#include "lodepng.h"

class PngImage {
public:
    PngImage(int **px, unsigned w, unsigned h);
    ~PngImage();
    
    int** pixels;
    unsigned width;
    unsigned height;
};

//Reads a png image from file.
PngImage* loadPngImage(const char* filename);

#endif /* defined(__HeghtMaps_3__loadPngHeightMap__) */
