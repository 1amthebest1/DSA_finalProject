#pragma once
#include <iostream>
#include "raylib.h"
#include "matrix.h"
#include <fstream>

using namespace std;

void loadSavedImage(int buttonColor[][30], string filename = "C:\\Users\\saeed\\OneDrive\\Desktop\\experiments\\DSA finalProject\\DSA finalProject\\output.txt") 
{
	cout << "load Saved Image Called" << endl;
	ifstream savedfileReader(filename);
	char ch;
	if (savedfileReader.is_open()) {
		for (int i = 0; i < 30; i++) {
			for (int j = 0; j < 30; j++) {
				savedfileReader.get(ch);
				buttonColor[i][j] = ch - '0';
			}
		}
	}
	else {
		cout << "Error opening file" << endl;
	}
}

void reverseImage(int buttonColor[][30]) {
	cout << "Reverse Image Called" << endl;
	int emptyArray[30][30] = { 0 };
	for (int i = 0; i < 30; i++) {
		for (int j = 29, l=0; j >= 0; j--, l++) {
			emptyArray[i][l] = buttonColor[i][j];
		}
	}
	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 30; j++) {
			buttonColor[i][j] = emptyArray[i][j];
		}
	}
}

void grayScale(int buttonColor[][30]) {
	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 30; j++) {
			if (buttonColor[i][j] > 0) {
				buttonColor[i][j] = 4;
			}
			else {
				buttonColor[i][j] = 5;
			}
		}
	}
}

void rightWhiteScale(int buttonColor[][30]) {
	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 30; j++) {
			if (buttonColor[i][j] == 5) {
				buttonColor[i][j] = 0;
			}
			else {
				buttonColor[i][j] = 2;
			}
		}
	}
}