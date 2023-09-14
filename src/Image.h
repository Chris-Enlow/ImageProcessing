#include <iostream>
#include <vector>
#include "Header.h"
#include "Pixel.h"
using namespace std;

class Image {
public:
	Header head;
	vector<Pixel> pixels;

	Image operator + (Image &image){
		Image temp;
		temp.head = this->head;
		for(unsigned int i=0;i<this->pixels.size();i++){
			temp.pixels.push_back(this->pixels[i] + image.pixels[i]);
		}
		return temp;
	}

	bool operator == (Image &image){
		for(unsigned int i=0;i<this->pixels.size();i++){
			if (this->pixels[i] != image.pixels[i]){
				return false;}}
		return true;
	}

	Image operator * (Image &image){
		Image temp;
		temp.head = this->head;
		for(unsigned int i=0;i<this->pixels.size();i++){
			temp.pixels.push_back(this->pixels[i] * image.pixels[i]);
		}
		return temp;
	}

	Image operator - (Image &image){
		Image temp;
		temp.head = this->head;
		for(unsigned int i=0;i<this->pixels.size();i++){
			temp.pixels.push_back(this->pixels[i] - image.pixels[i]);
		}
		return temp;
	}

	Image operator ^ (Image &image){
		Image temp;
		temp.head = this->head;
		for(unsigned int i=0;i<this->pixels.size();i++){
			temp.pixels.push_back(image.pixels[i] ^ (this->pixels[i]));
		}
		return temp;
	}

	Image operator << (Image &image){
		Image temp;
		temp.head = this->head;
		for(unsigned int i=0;i<this->pixels.size();i++){
			temp.pixels.push_back(this->pixels[i] << image.pixels[i]);
		}
		return temp;
	}

	void addColor(string color, unsigned char num){
		if (color == "Blue"){
			for(unsigned int i=0;i<this->pixels.size();i++){
				int blue = this->pixels[i].blue;
				blue += num;
				if (blue >= 255){
					blue = 255;}
				this->pixels[i].blue = (unsigned char) blue;}}
		if (color == "Green"){
			for(unsigned int i=0;i<this->pixels.size();i++){
				int green = this->pixels[i].green;
				green += num;
				if (green >= 255){
					green = 255;}
				this->pixels[i].green = (unsigned char) green;}}
		if (color == "Red"){
			for(unsigned int i=0;i<this->pixels.size();i++){
				int red = this->pixels[i].red;
				red += num;
				if (red >= 255){
					red = 255;}
				this->pixels[i].red = (unsigned char) red;}}
		}

		void scale(string color, float num){
		if (color == "Blue"){
			for(unsigned int i=0;i<this->pixels.size();i++){
				int blue = this->pixels[i].blue;
				blue *= num;
				if (blue >= 255){
					blue = 255;}
				if (blue <= 0){
					blue = 0;}
				this->pixels[i].blue = (unsigned char) blue;}}
		if (color == "Green"){
			for(unsigned int i=0;i<this->pixels.size();i++){
				int green = this->pixels[i].green;
				green *= num;
				if (green >= 255){
					green = 255;}
				if (green <= 0){
					green = 0;}
				this->pixels[i].green = (unsigned char) green;}}
		if (color == "Red"){
			for(unsigned int i=0;i<this->pixels.size();i++){
				int red = this->pixels[i].red;
				red *= num;
				if (red >= 255){
					red = 255;}
				if (red <= 0){
					red = 0;}
				this->pixels[i].red = (unsigned char) red;}}
		}

		Image isolateChannel(string color){
		Image temp;
		temp.head = this->head; 
		for(unsigned int i=0;i<this->pixels.size();i++){
			if (color == "Blue"){
				Pixel pix;
				pix.blue = this->pixels[i].blue;
				pix.green = this->pixels[i].blue;
				pix.red = this->pixels[i].blue;
				temp.pixels.push_back(pix);
			}
			if (color == "Green"){
				Pixel pix;
				pix.blue = this->pixels[i].green;
				pix.green = this->pixels[i].green;
				pix.red = this->pixels[i].green;
				temp.pixels.push_back(pix);
			}
			if (color == "Red"){
				Pixel pix;
				pix.blue = this->pixels[i].red;
				pix.green = this->pixels[i].red;
				pix.red = this->pixels[i].red;
				temp.pixels.push_back(pix);
			}}
		return temp;
		}

		void rotate180(){
			vector<Pixel> temp;
			unsigned int size = this->pixels.size()-1;
			for(unsigned int i = 0; i<this->pixels.size();i++){
				Pixel pix;
				pix.blue = this->pixels[size-i].blue;
				pix.green = this->pixels[size-i].green;
				pix.red = this->pixels[size-i].red;
				temp.push_back(pix);
				}
			for(unsigned int i=0;i<this->pixels.size();i++){
				this->pixels[i] = temp[i];}
		}




};
