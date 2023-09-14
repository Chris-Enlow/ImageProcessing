#include <iostream>
using namespace std;

struct Pixel {
    unsigned char blue;
    unsigned char green;
    unsigned char red;
    float normalBlue;
    float normalGreen;
    float normalRed;

    float getNormal(unsigned char a){
        a = (float) a;
        return a/255.0f;
    }

    Pixel operator * (Pixel &pixel){
        Pixel temp;
        float blue1 = getNormal(this->blue);
        float blue2 = getNormal(pixel.blue);
        float green1 = getNormal(this->green);
        float green2 = getNormal(pixel.green);
        float red1 = getNormal(this->red);
        float red2 = getNormal(pixel.red);
        float blue = (blue1) * (blue2) * 255 +0.5f;
        float green = (green1) * (green2) * 255 +0.5f;
        float red = (red1) * (red2) * 255 +0.5f;
        temp.blue = (unsigned char)blue;
        temp.green = (unsigned char)green;
        temp.red = (unsigned char)red;
        return temp;
    }


    Pixel operator ^(Pixel &pixel){
        Pixel temp;
        float blue1 = getNormal(this->blue);
        float blue2 = getNormal(pixel.blue);
        float green1 = getNormal(this->green);
        float green2 = getNormal(pixel.green);
        float red1 = getNormal(this->red);
        float red2 = getNormal(pixel.red);
        float blue = (1 - ((1-blue1) * (1-blue2))) * 255 +0.5f;
        float green = (1 - ((1-green1) * (1-green2))) * 255 +0.5f;
        float red = (1 - ((1-red1) * (1-red2))) * 255 +0.5f;
        temp.blue = (unsigned char)blue;
        temp.green = (unsigned char)green;
        temp.red = (unsigned char)red;
        return temp;
    }

    Pixel operator - (Pixel &pixel){
        Pixel temp;
        int b = (int)(this->blue - pixel.blue);
        if (b > 0){
            temp.blue = (unsigned char)((int)this->blue - (int)pixel.blue);}
        else{temp.blue = 0;}
        int g = (int)(this->green - pixel.green);
        if (g > 0){
            temp.green = (unsigned char)((int)this->green - (int)pixel.green);}
        else{temp.green = 0;}
        int r = (int)(this->red - pixel.red);
        if (r > 0){
            temp.red = (unsigned char)((int)this->red - (int)pixel.red);}
        else{temp.red = 0;}
        return temp;
    }

    Pixel operator + (Pixel &pixel){
        Pixel temp;
        if ((int)this->blue + (int)pixel.blue < 255){
            temp.blue = (unsigned char)((int)this->blue + (int)pixel.blue);}
        else{temp.blue = 255;}
        if ((int)this->green + (int)pixel.green < 255){
            temp.green = (unsigned char)((int)this->green + (int)pixel.green);}
        else{temp.green = 255;}
        if ((int)this->red + (int)pixel.red < 255){
            temp.red = (unsigned char)((int)this->red + (int)pixel.red);}
        else{temp.red = 255;}
        return temp;
    }

    Pixel operator << (Pixel &pixel){
        Pixel temp;
        float blue1 = getNormal(this->blue);
        float blue2 = getNormal(pixel.blue);
        float green1 = getNormal(this->green);
        float green2 = getNormal(pixel.green);
        float red1 = getNormal(this->red);
        float red2 = getNormal(pixel.red);
        float blue;
        float green;
        float red;

        if(blue2<=0.5f){
            blue = (2*blue1*blue2) * 255 + 0.5f;}
        else{blue = ((1 - 2*(1-blue1)*(1-blue2))) * 255 + 0.5f;}

        if(blue > 255.0f){
            blue = 255.0f;}
        else if(blue < 0){
            blue = 0;}

        if(green2<=0.5f){
            green = (2*green1*green2) * 255 + 0.5f;}
        else{green = (1 - (2*(1-green1)*(1-green2))) * 255 + 0.5f;}

        if(green > 255.0f){
            green = 255.0f;}
        else if(green < 0){
            green = 0;}

        if(red2<=0.5f){
            red = (2*red1*red2) * 255 + 0.5f;}
        else{red = (1 - (2*(1-red1)*(1-red2))) * 255 + 0.5f;}

        if(red > 255.0f){
            red = 255.0f;}
        else if(red < 0){
            red = 0;}

        temp.blue = (unsigned char) blue;
        temp.green = (unsigned char) green;
        temp.red = (unsigned char) red;
        return temp;
    }

    bool operator != (Pixel &pixel){
        if(this->blue != pixel.blue){
            return true;}
        else if(this->green != pixel.green){
            return true;}
        else if(this->red != pixel.red){
            return true;}
        else {return false;}
        }

    bool operator == (Pixel &pixel){
        if(this->blue != pixel.blue){
            return false;}
        else if(this->green != pixel.green){
            return false;}
        else if(this->red != pixel.red){
            return false;}
        else {return true;}
        }

    Pixel operator = (Pixel &pixel){
        this->blue = pixel.blue;
        this->green = pixel.green;
        this->red = pixel.red;
        return *this;
        }
    

    };
