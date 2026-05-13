#pragma once
#include <iostream>
#include "raylib.h"
#include <cstdlib>
#include <fstream>
#include "globals.h"
#include <string>
#include "matrixHelper.h"
//Part 1: Template - Based Matrix Data Structure
//Implement a Matrix Class Template

//Your matrix must support :
//• Dynamic memory allocation
//• Any numeric data type(T) [done!?]
//• Row - major storage [okay i will do it]
//Required Operations :
//• Constructor : Matrix(rows, cols)
//• Copy constructor & destructor
//• Element access using operator()(i, j)
//• Matrix addition& subtraction
//• Scalar multiplication
//• Matrix multiplication(if dimensions allow)
//• Transpose

using namespace std;

template <typename T>
class MatriX {
public:
	T width;
	T height;
	int buttonColor[30][30];
	T buttonPositionX[30][30];
	T buttonPositionY[30][30];

	int Iterator = 0;
	bool musicPlaying = false;
	bool SingleMode = false;

	MatriX() {

	};

	//void scalarMultiplication();
	//void transpose();

	Color checkColorValue(T colorValue) {

		if (opacity_ > 255) {
			opacity_ = 0;
		}

		if (opacity_ < 0) {
			opacity_ = 255;
		}

		if (colorValue == 0) {
			return Color{ 255, 0, 13, static_cast<unsigned char>(opacity_)}; //red
		}
		else if (colorValue == 1) {
			return Color{ 0, 0, 200, static_cast<unsigned char>(opacity_) }; //blue
		}
		else if (colorValue == 2) {
			return Color{ 255, 255, 255, static_cast<unsigned char>(opacity_) }; //white
		}
		else if (colorValue == 3) {
			return Color{ 128, 0, 128, static_cast<unsigned char>(opacity_) }; //purple
		}
		else if (colorValue == 4) {
			return Color{ 128, 128, 128, static_cast<unsigned char>(opacity_) };	//gray
		}
		else if (colorValue == 5) {
			return Color{ 255, 255, 255, static_cast<unsigned char>(opacity_) };	//white
		}
		else {
			return Color{ 255, 165, 0, static_cast<unsigned char>(opacity_) }; //orange
		}
	}

	void setDimensionsDefault() {
		width = 20;
		height = 20;
	}

	void drawMatrix() {
		for (int i = 0; i < 30; i++) {
			for (int j = 0; j < 30; j++) {
				DrawRectangle(buttonPositionX[i][j], buttonPositionY[i][j], width, height, checkColorValue(buttonColor[i][j]));
			}
		}
	}

	void setButtonColorDefault() {
		srand(time(0));
		for (int i = 0; i < 30; i++) {
			for (int x = 0; x < 30; x++) {
				buttonColor[i][x] = rand() % 4;
			}
		}
	}

	void setButtonPositionDefault() {
		//create window of 760 by 760
		int incrementorX = 5;
		int incrementorY = 5;
		for (int i = 0; i < 30; i++) {
			for (int j = 0; j < 30; j++) {
				buttonPositionX[i][j] = incrementorX;
				buttonPositionY[i][j] = incrementorY;
				incrementorX += 25;
			}
			incrementorX = 5;
			incrementorY += 25;
		}
	}

	void checkRectanglePressed() {
		if ((IsMouseButtonDown(MOUSE_LEFT_BUTTON) || IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) && SingleMode == false) {
			Vector2 mousePoint = GetMousePosition();
			for (int i = 0; i < 30; i++) {
				for (int j = 0; j < 30; j++) {
					if (mousePoint.x >= buttonPositionX[i][j] && mousePoint.x <= buttonPositionX[i][j] + width) {
						if (mousePoint.y >= buttonPositionY[i][j] && mousePoint.y <= buttonPositionY[i][j] + height) {
							//buttonColor[i][j] = changeButtonColor(buttonColor[i][j]);
							buttonColor[i][j] = 2;
						}
					}
				}
			}
		}
	}

	void checkRectanglePressedSingle() {
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && SingleMode == true) {
			Vector2 mousePoint = GetMousePosition();
			for (int i = 0; i < 30; i++) {
				for (int j = 0; j < 30; j++) {
					if (mousePoint.x >= buttonPositionX[i][j] && mousePoint.x <= buttonPositionX[i][j] + width) {
						if (mousePoint.y >= buttonPositionY[i][j] && mousePoint.y <= buttonPositionY[i][j] + height) {
							buttonColor[i][j] = changeButtonColor(buttonColor[i][j]);
							//buttonColor[i][j] = 2;
						}
					}
				}
			}
		}
	}

	int changeButtonColor(int colorValue) {
		cout << "Color Value " << colorValue << endl;
		if (colorValue >= 5) {
			return 0;
		}
		else {
			cout << "Returned one more than " << colorValue << endl;
			return ++colorValue;
		}
	}

	void drawSave() {
		DrawRectangle(5, 770, 90, 40, YELLOW);
		DrawText("Save Image", 7, 780, 15, BLACK);
	}

	void saveImage() {
		srand(time(0));
		string fileName = "C:\\Users\\saeed\\OneDrive\\Desktop\\experiments\\DSA finalProject\\DSA finalProject\\output.txt";
		ofstream saver(fileName);
		if (saver) {
			for (int i = 0; i < 30; i++) {
				for (int j = 0; j < 30; j++) {
					saver << buttonColor[i][j];
				}
				saver << "\n";
			}
		}
	}

	void checkSavePressed() {
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			Vector2 mousePoint = GetMousePosition();
			if (mousePoint.x >= 5 && mousePoint.x <= 5 + 90) {
				if (mousePoint.y >= 770 && mousePoint.y <= 770 + 40) {
					saveImage();
					cout << "Image Saved" << endl;
				}
			}
		}
	}

	void clearCanvas() {
		for (int i = 0; i < 30; i++) {
			for (int j = 0; j < 30; j++) {
				buttonColor[i][j] = 0;
			}
		}
		cout << "Canvas Cleared" << endl;
	}

	void drawClearCanvas() {
		DrawRectangle(5, 830, 90, 40, YELLOW);
		DrawText("CLEAR", 16, 840, 15, BLACK);
	}

	void checkClearCanvasPressed() {
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			Vector2 mousePoint = GetMousePosition();
			if (mousePoint.x >= 5 && mousePoint.x <= 5 + 90) {
				if (mousePoint.y >= 840 && mousePoint.y <= 830 + 40) {
					clearCanvas();
				}
			}
		}
	}

	void drawTranspose() {
		DrawRectangle(150, 770, 90, 40, YELLOW);
		DrawText("Transpose", 155, 780, 15, BLACK);
	}

	void Transpose() {
		for (int i = 0; i < 30; i++) {
			for (int j = i + 1; j < 30; j++) {
				swap(buttonPositionX[i][j], buttonPositionX[j][i]);
				swap(buttonPositionY[i][j], buttonPositionY[j][i]);
			}
		}
		cout << "Transpose Pressed" << endl;
	}

	void checkTransposePressed() {
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			Vector2 mousePoint = GetMousePosition();
			if (mousePoint.x >= 150 && mousePoint.x <= 150 + 90) {
				if (mousePoint.y >= 770 && mousePoint.y <= 770 + 40) {
					Transpose();
				}
			}
		}
	}

	void drawDance() {
		Iterator++;
		if (Iterator <= 30) {
			DrawRectangle(150, 830, 90, 40, GREEN);
		}
		else if (Iterator > 30 && Iterator <= 60) {
			DrawRectangle(150, 830, 90, 40, PINK);
		}
		else if (Iterator > 60 && Iterator <= 90) {
			DrawRectangle(150, 830, 90, 40, ORANGE);
		}
		else if (Iterator > 90 && Iterator <= 120) {
			DrawRectangle(150, 830, 90, 40, BLUE);
		}
		else {
			DrawRectangle(150, 830, 90, 40, PURPLE);
			Iterator = 0;
		}
		DrawText("DANCE", 160, 840, 15, BLACK);
	}

	void dance() {
		if (musicPlaying) {
			UpdateMusicStream(bgMusic);
		}
	}

	void checkDancePressed() {
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			Vector2 mousePoint = GetMousePosition();

			if (mousePoint.x >= 150 && mousePoint.x <= 150 + 90) {
				if (mousePoint.y >= 830 && mousePoint.y <= 830 + 40) {

					if (!musicPlaying) {
						PlayMusicStream(bgMusic);
						musicPlaying = true;
					}
					else {
						StopMusicStream(bgMusic);
						musicPlaying = false;
					}

					cout << "Dance Pressed" << endl;
				}
			}
		}
	}

	void drawSingleMode() {
		DrawRectangle(300, 770, 90, 40, YELLOW);
		DrawText("Single Mode", 305, 780, 15, BLACK);
	}

	void singleMode() {
		SingleMode = !SingleMode;
	}

	void checkSingleModePressed() {
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			Vector2 mousePoint = GetMousePosition();
			if (mousePoint.x >= 300 && mousePoint.x <= 300 + 90) {
				if (mousePoint.y >= 770 && mousePoint.y <= 770 + 40) {
					singleMode();
					cout << "Single Mode" << endl;
				}
			}
		}
	}

	void drawLoadSavedImage() {
		DrawRectangle(300, 830, 90, 40, YELLOW);
		DrawText("Load Saved Image", 305, 840 , 15, BLACK);
	}

	void checkLoadSavedImagePressed(int buttonColor[][30]) {
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			Vector2 mousePoint = GetMousePosition();
			if (mousePoint.x >= 300 && mousePoint.x <= 300 + 90) {
				if (mousePoint.y >= 830 && mousePoint.y <= 830 + 40) {
					loadSavedImage(buttonColor);
					cout << "called Load Save Image" << endl;
				}
			}
		}
	}

	void drawReverseImage() {
		DrawRectangle(450, 770, 90, 40, YELLOW);
		DrawText("Reverse", 455, 780, 15, BLACK);
	}

	void checkReverseImagePressed(int buttonColor[][30]) {
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			Vector2 mousePoint = GetMousePosition();
			if (mousePoint.x >= 450 && mousePoint.x <= 450 + 90) {
				if (mousePoint.y >= 770 && mousePoint.y <= 770 + 40) {
					reverseImage(buttonColor);
					cout << "called Reverse Image" << endl;
				}
			}
		}
	}

	void drawGrayScale() {
		DrawRectangle(450, 830, 90, 40, YELLOW);
		DrawText("GrayScale", 455, 840, 15, BLACK);
	}

	void checkGrayScalePressed(int buttonColor[][30]) {
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			Vector2 mousePoint = GetMousePosition();
			if (mousePoint.x >= 450 && mousePoint.x <= 450 + 90) {
				if (mousePoint.y >= 840 && mousePoint.y <= 840 + 40) {
					grayScale(buttonColor);
					cout << "called Load Save Image" << endl;
				}
			}
		}
	}

	void increaseOpacity() {
		opacity_+=17;
		cout << "increase Opacity Called" << endl;
	}

	void drawIncreaseOpacity() {
		DrawRectangle(600, 770, 90, 40, YELLOW);
		DrawText("Brighten", 605, 780, 15, BLACK);
	}

	void checkIncreaseOpacityPressed() {
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			Vector2 mousePoint = GetMousePosition();
			if (mousePoint.x >= 600 && mousePoint.x <= 650 + 90) {
				if (mousePoint.y >= 770 && mousePoint.y <= 770 + 40) {
					increaseOpacity();
					cout << "called Increase Opacity" << endl;
				}
			}
		}
	}

	void decreaseOpacity() {
		opacity_-=17;
		cout << "decreaseOpacity Called" << endl;
	}

	void drawDecreaseOpacity() {
		DrawRectangle(600, 830, 90, 40, YELLOW);
		DrawText("Dim", 605, 840, 15, BLACK);
	}

	void checkDecreaseOpacityPressed() {
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			Vector2 mousePoint = GetMousePosition();
			if (mousePoint.x >= 600 && mousePoint.x <= 650 + 90) {
				if (mousePoint.y >= 830 && mousePoint.y <= 830 + 40) {
					decreaseOpacity();
					cout << "Increase Opacity Pressed" << endl;
				}
			}
		}
	}

	void drawRedWhite() {
		DrawRectangle(5, 890, 90, 40, YELLOW);
		DrawText("Red White", 7, 900, 15, BLACK);
	}

	void checkRedWhitePressed(int buttonColor[][30]) {
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			Vector2 mousePoint = GetMousePosition();
			if (mousePoint.x >= 5 && mousePoint.x <= 5 + 90) {
				if (mousePoint.y >= 890 && mousePoint.y <= 890 + 40) {
					cout << "Red White Pressed" << endl;	
					redWhiteScale(buttonColor);
				}
			}
		}
	}

	void drawCompressFile() {
		DrawRectangle(150, 890, 90, 40, YELLOW);
		DrawText("Compress", 152, 900, 15, BLACK);
	}

	void checkCompressPressed(string fileToSave="x", string compressedFile="y") {
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			Vector2 mousePoint = GetMousePosition();
			if (mousePoint.x >= 150 && mousePoint.x <= 150 + 90) {
				if (mousePoint.y >= 890 && mousePoint.y <= 890 + 40) {
					cout << "Draw Compressed Pressed" << endl;

					if (fileToSave == "x" && compressedFile == "y") {
						saveCompressed();
					}
					else {
						saveCompressed(fileToSave, compressedFile);
					}
				}
			}
		}
	}

	void drawLoadCompressedFile() {
		DrawRectangle(300, 890, 140, 40, YELLOW);
		DrawText("Load Compressed", 302, 900, 15, BLACK);
	}

	void checkLoadCompressPressed(int buttonColors[][30], string compressedFile="x") {
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			Vector2 mousePoint = GetMousePosition();
			if (mousePoint.x >= 300 && mousePoint.x <= 300 + 140) {
				if (mousePoint.y >= 890 && mousePoint.y <= 890 + 40) {
					cout << "Load Compressed Pressed" << endl;

					if (compressedFile == "x") {
						loadCompressed(buttonColors);
					}
					else {
						loadCompressed(buttonColors, compressedFile);
					}
				}
			}
		}
	}

};
