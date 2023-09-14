#include <iostream>
#include <vector>
using namespace std;
#pragma once

struct Header {
    char  idLength;
    char  colorMapType;
    char  imageType;
    short colorMapOrigin;
    short colorMapLength;
    char  colorMapDepth;
    short xOrigin;
    short yOrigin;
    short width;
    short height;
    char  pixelDepth;
    char  imageDescriptor;
};
