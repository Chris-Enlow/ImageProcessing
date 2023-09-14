#include <iostream>
#include "Image.h"
#include <fstream>
#include <vector>
#include <string>
using namespace std;

void writeFile(const Image& currentImage, const string &currentFile) {
	ofstream file(currentFile, ios_base::out | ios_base::binary);
	file.write((char*)&currentImage.head.idLength, 1);
	file.write((char*)&currentImage.head.colorMapType, 1);
	file.write((char*)&currentImage.head.imageType, 1);
	file.write((char*)&currentImage.head.colorMapOrigin, 2);
	file.write((char*)&currentImage.head.colorMapLength, 2);
	file.write((char*)&currentImage.head.colorMapDepth, 1);
	file.write((char*)&currentImage.head.xOrigin, 2);
	file.write((char*)&currentImage.head.yOrigin, 2);
	file.write((char*)&currentImage.head.width, 2);
	file.write((char*)&currentImage.head.height, 2);
	file.write((char*)&currentImage.head.pixelDepth, 1);
	file.write((char*)&currentImage.head.imageDescriptor, 1);
	for (unsigned int i = 0; i < currentImage.pixels.size(); i++) {
		file.write((char*)&currentImage.pixels[i].blue, 1);
		file.write((char*)&currentImage.pixels[i].green, 1);
		file.write((char*)&currentImage.pixels[i].red, 1);
	}
	file.close();
}

Image readFile(const string &currentFile) {
	Image currentImage;
	fstream file(currentFile, ios_base::in | ios_base::binary);
	file.read((char*)&currentImage.head.idLength, 1);
	file.read((char*)&currentImage.head.colorMapType, 1);
	file.read((char*)&currentImage.head.imageType, 1);
	file.read((char*)&currentImage.head.colorMapOrigin, 2);
	file.read((char*)&currentImage.head.colorMapLength, 2);
	file.read((char*)&currentImage.head.colorMapDepth, 1);
	file.read((char*)&currentImage.head.xOrigin, 2);
	file.read((char*)&currentImage.head.yOrigin, 2);
	file.read((char*)&currentImage.head.width, 2);
	file.read((char*)&currentImage.head.height, 2);
	file.read((char*)&currentImage.head.pixelDepth, 1);
	file.read((char*)&currentImage.head.imageDescriptor, 1);
	unsigned int imageSize = currentImage.head.width * currentImage.head.height;
	for (unsigned int i = 0; i < imageSize; i++) {
		Pixel temp;
		file.read((char*)&temp.blue, 1);
		file.read((char*)&temp.green, 1);
		file.read((char*)&temp.red, 1);
		temp.normalBlue = (float) temp.blue/255;
		temp.normalGreen = (float) temp.green/255;
		temp.normalRed = (float) temp.red/255;
		currentImage.pixels.push_back(temp);
	}
	file.close();
	return currentImage;
}

Image combineImages(Image blueLayer, Image greenLayer, Image redLayer){
	Image temp;
	temp.head = redLayer.head;
	for(unsigned int i=0;i<redLayer.pixels.size();i++){
		Pixel pix;
		pix.blue = blueLayer.pixels[i].blue;
		pix.green = greenLayer.pixels[i].green;
		pix.red = redLayer.pixels[i].red;
		temp.pixels.push_back(pix);
	}
	return temp;
}

void Tests(){
	Image car = readFile("input/car.tga");
	Image circles = readFile("input/circles.tga");
	Image layerBlue = readFile("input/layer_blue.tga");
	Image layerGreen = readFile("input/layer_green.tga");
	Image layerRed = readFile("input/layer_red.tga");
	Image layer1 = readFile("input/layer1.tga");
	Image layer2 = readFile("input/layer2.tga");
	Image pattern1 = readFile("input/pattern1.tga");
	Image pattern2 = readFile("input/pattern2.tga");
	Image text = readFile("input/text.tga");
	Image text2 = readFile("input/text2.tga");
	Image example1 = readFile("examples/EXAMPLE_part1.tga");
	Image example2 = readFile("examples/EXAMPLE_part2.tga");
	Image example3 = readFile("examples/EXAMPLE_part3.tga");
	Image example4 = readFile("examples/EXAMPLE_part4.tga");
	Image example5 = readFile("examples/EXAMPLE_part5.tga");
	Image example6 = readFile("examples/EXAMPLE_part6.tga");
	Image example7 = readFile("examples/EXAMPLE_part7.tga");
	Image example8blue = readFile("examples/EXAMPLE_part8_b.tga");
	Image example8green = readFile("examples/EXAMPLE_part8_g.tga");
	Image example8red = readFile("examples/EXAMPLE_part8_r.tga");
	Image example9 = readFile("examples/EXAMPLE_part9.tga");
	Image example10 = readFile("examples/EXAMPLE_part10.tga");
	
	int testsPassed = 0;

	Image answer1 = layer1 * pattern1;
	writeFile(answer1, "output/out.tga");
	if (answer1 == example1){
		testsPassed++;}

	Image answer2 = car - layer2;
	writeFile(answer2, "output/out.tga");
	if (answer2 == example2){
		testsPassed++;}

	Image step = layer1 * pattern2;
	Image answer3 = text ^ step;
	writeFile(answer3, "output/out.tga");
	if(answer3 == example3){
		testsPassed++;}

	
	Image step1 = layer2 * circles;
	Image answer4 = step1 - pattern2;
	writeFile(answer4, "output/out.tga");
	if(answer4 == example4){
		testsPassed++;}

	Image answer5 = layer1 << (pattern1);
	writeFile(answer5, "output/out.tga");
	if(answer5 == example5){
		testsPassed++;}

	Image answer6 = car;
	answer6.addColor("Green", 200);
	writeFile(answer6, "output/out.tga");
	if(answer6 == example6){
		testsPassed++;}
	
	Image answer7 = car;
	answer7.scale("Red", 4);
	answer7.scale("Blue", 0);
	writeFile(answer7, "output/out.tga");
	if(answer7 == example7){
		testsPassed++;}

	
	Image carBlue = car.isolateChannel("Blue");
	writeFile(carBlue, "output/out.tga");
	Image carGreen = car.isolateChannel("Green");
	writeFile(carGreen, "output/out.tga");
	Image carRed = car.isolateChannel("Red");
	writeFile(carRed, "output/out.tga");
	if(carBlue == example8blue){
		testsPassed++;}
	if(carGreen == example8green){
		testsPassed++;}
	if(carRed == example8red){
		testsPassed++;}

	Image answer9 = combineImages(layerBlue, layerGreen, layerRed);
	writeFile(answer9, "output/out.tga");
	if(answer9 == example9){
		testsPassed++;}

	
	Image answer10 = text2;
	answer10.rotate180();
	writeFile(answer10, "output/out.tga");
	if(answer10 == example10){
		testsPassed++;}

	cout<<"Tests Passed: "<<testsPassed;
}

bool isImageFile(string a){
	if(a.length() < 4){
        return false;}
	string temp = a.substr(a.length()-4, 4);
	if (temp==".tga")
		{return true;}
	return false;}

bool isOutputFile(string a){
	if(a.length() < 4){
        return false;}
	string temp = a.substr(a.length()-4, 4);
	if (temp==".tga")
		{return true;}
	return false;}

bool isValidImage(string a){
	vector<string> images;
	images.push_back("input/car.tga");
	images.push_back("input/circles.tga");
	images.push_back("input/layer_blue.tga");
	images.push_back("input/layer_green.tga");
	images.push_back("input/layer_red.tga");
	images.push_back("input/layer1.tga");
	images.push_back("input/layer2.tga");
	images.push_back("input/pattern1.tga");
	images.push_back("input/pattern2.tga");
	images.push_back("input/text.tga");
	images.push_back("input/text2.tga");
	for(unsigned int i=0;i<images.size();i++){
		if(images[i] == a){
			return true;}}
	return false;
}

bool isInteger(string a){
	try {
		int x = stoi(a);}
	catch(invalid_argument& e){
		return false;}
	return true;
}

int main(int argc, char *argv[]) {
//Check for help message
	if(argc == 1){
		cout<<"Project 2: Image Processing, Spring 2023"<<endl<<endl;
		cout<<"Usage:"<<endl;
		cout<<" 	./project2.out [output] [firstImage] [method] [...]";}
	else{
	string checkHelp = (string) argv[1];
	if(checkHelp == "--help"){
		cout<<"Project 2: Image Processing, Spring 2023"<<endl<<endl;
		cout<<"Usage:"<<endl;
		cout<<" 	./project2.out [output] [firstImage] [method] [...] ";}
	else{
//Do stuff
	bool executedProperly = false;
	Image image;
	string outputFile = (string) argv[1];
	if(!isOutputFile(outputFile)){
		cout<<"Invalid file name."; return 0;
		}

	string initialImage = (string) argv[2];
	if(!isImageFile(initialImage)){
		cout<<"Invalid file name."; return 0;
		}
	if (!isValidImage(initialImage)){
		cout<<"File does not exist.";
		}
	image = readFile(argv[2]);
	if (argc == 3){
		cout<<"Invalid method name."; return 0;
	}

	int i = 3;
	while (i < argc){
		executedProperly = false;
		string arg = (string) argv[i];
		if(arg == "multiply"){
			if(i+1 == argc){
				cout<<"Missing argument."; return 0;}
			string arg1 = (string) argv[i+1];
			if(!isImageFile(arg1))
				{cout<<"Invalid argument, invalid file name."; return 0;}
			if(!isValidImage(arg1))
				{cout<<"Invalid argument, file does not exist.";}
			Image temp = readFile(arg1);
			image = image * temp;
			i++;
		}
		else if(arg == "subtract"){
			if(i+1 == argc){
				cout<<"Missing argument."; return 0;}
			string arg1 = (string) argv[i+1];
			if(!isImageFile(arg1))
				{cout<<"Invalid argument, invalid file name."; return 0;}
			if(!isValidImage(arg1))
				{cout<<"Invalid argument, file does not exist.";}
			Image temp = readFile(arg1);
			image = image - temp;
			i++;
		}
		else if(arg == "overlay"){
			if(i+1 == argc){
				cout<<"Missing argument."; return 0;}
			string arg1 = (string) argv[i+1];
			if(!isImageFile(arg1))
				{cout<<"Invalid argument, invalid file name."; return 0;}
			if(!isValidImage(arg1))
				{cout<<"Invalid argument, file does not exist.";}
			Image temp = readFile(arg1);
			image = image << temp;
			i++;
		}
		else if(arg == "screen"){
			if(i+1 == argc){
				cout<<"Missing argument."; return 0;}
			string arg1 = (string) argv[i+1];
			if(!isImageFile(arg1))
				{cout<<"Invalid argument, invalid file name."; return 0;}
			if(!isValidImage(arg1))
				{cout<<"Invalid argument, file does not exist.";}
			Image temp = readFile(arg1);
			image = image ^ temp;
			i++;
		}
		else if(arg == "combine"){
			if(i+1 == argc){
				cout<<"Missing argument."; return 0;}
			if(i+2 == argc+1){
				cout<<"Missing argument."; return 0;}
			string arg1 = (string) argv[i+1];
			if(!isImageFile(arg1))
				{cout<<"Invalid argument, invalid file name."; return 0;}
			if(!isValidImage(arg1))
				{cout<<"Invalid argument, file does not exist.";}
			string arg2 = (string) argv[i+2];
			if(!isImageFile(arg2))
				{cout<<"Invalid argument, invalid file name."; return 0;}
			if(!isValidImage(arg2))
				{cout<<"Invalid argument, file does not exist.";}
			Image temp1 = readFile(arg1);
			Image temp2 = readFile(arg2);
			image = combineImages(temp2, temp1, image);
			i+=2;
		}
		else if(arg == "flip"){
			image.rotate180();
		}
		else if(arg == "onlyred"){
			image = image.isolateChannel("Red");
		}
		else if(arg == "onlygreen"){
			image = image.isolateChannel("Green");
		}
		else if(arg == "onlyblue"){
			image = image.isolateChannel("Blue");
		}
		else if(arg == "addred"){
			if(i+1 == argc){
				cout<<"Missing argument."; return 0;}
			string arg1 = (string) argv[i+1];
			if (!isInteger(arg1)){
				cout<<"Invalid argument, expected number."; return 0;}
			int num = stoi(arg1);
			image.addColor("Red", num);
			i++;
		}
		else if(arg == "addgreen"){
			if(i+1 == argc){
				cout<<"Missing argument."; break;}
			string arg1 = (string) argv[i+1];
			if (!isInteger(arg1)){
				cout<<"Invalid argument, expected number."; return 0;}
			int num = stoi(arg1);
			image.addColor("Green", num);
			i++;
		}
		else if(arg == "addblue"){
			if(i+1 == argc){
				cout<<"Missing argument."; return 0;}
			string arg1 = (string) argv[i+1];
			if (!isInteger(arg1)){
				cout<<"Invalid argument, expected number."; return 0;}
			int num = stoi(arg1);
			image.addColor("Blue", num);
			i++;
		}
		else if(arg == "scalered"){
			if(i+1 == argc){
				cout<<"Missing argument."; return 0;}
			string arg1 = (string) argv[i+1];
			if (!isInteger(arg1)){
				cout<<"Invalid argument, expected number."; return 0;}
			int num = stoi(arg1);
			image.scale("Red", num);
			i++;
		}
		else if(arg == "scalegreen"){
			if(i+1 == argc){
				cout<<"Missing argument."; return 0;}
			string arg1 = (string) argv[i+1];
			if (!isInteger(arg1)){
				cout<<"Invalid argument, expected number."; return 0;}
			int num = stoi(arg1);
			image.scale("Green", num);
			i++;
		}
		else if(arg == "scaleblue"){
			if(i+1 == argc){
				cout<<"Missing argument."; return 0;}
			string arg1 = (string) argv[i+1];
			if (!isInteger(arg1)){
				cout<<"Invalid argument, expected number."; return 0;}
			int num = stoi(arg1);
			image.scale("Blue", num);
			i++;
		}
		else{cout<<"Invalid method name."; return 0;}
		i++;
		executedProperly = true;
	}
	if(executedProperly){
	writeFile(image, outputFile);}}}
	return 0;
}
