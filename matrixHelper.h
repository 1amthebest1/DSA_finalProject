#pragma once
#include <iostream>
#include "raylib.h"
#include "matrix.h"
#include <fstream>
#include "globals.h"
#include <sstream>

using namespace std;

void loadSavedImage(int buttonColor[][30],
	string filename = "C:\\Users\\saeed\\OneDrive\\Desktop\\experiments\\DSA finalProject\\DSA finalProject\\output.txt")
{
	cout << "load Saved Image Called" << endl;

	ifstream savedfileReader(filename);

	if (!savedfileReader.is_open()) {
		cout << "Error opening file" << endl;
		return;
	}

	char ch;

	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 30; j++) {
			savedfileReader.get(ch);
			// Skip newline characters
			while (ch == '\n' || ch == '\r') {
				savedfileReader.get(ch);
			}
			buttonColor[i][j] = ch - '0';
		}
	}
	savedfileReader.close();
}

void reverseImage(int buttonColor[][30]) {
	cout << "Reverse Image Called" << endl;
	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 15; j++) {
			std::swap(buttonColor[i][j], buttonColor[i][29 - j]);
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

void redWhiteScale(int buttonColor[][30]) {
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

void saveCompressed(
	string fileToSave =
	"C:\\Users\\saeed\\OneDrive\\Desktop\\experiments\\DSA finalProject\\DSA finalProject\\output.txt",

	string compressedFile =
	"C:\\Users\\saeed\\OneDrive\\Desktop\\experiments\\DSA finalProject\\DSA finalProject\\compressed.txt")
{
	ifstream inFile(fileToSave);
	ofstream outFile(compressedFile);

	if (!inFile.is_open() || !outFile.is_open())
	{
		cout << "File error\n";
		return;
	}

	string line;

	while (getline(inFile, line))
	{
		char prev = line[0];
		int count = 1;

		for (int i = 1; i < line.length(); i++)
		{
			if (line[i] == prev)
			{
				count++;
			}
			else
			{
				outFile << count << ":" << prev << " ";

				prev = line[i];
				count = 1;
			}
		}

		// last sequence
		outFile << count << ":" << prev;

		outFile << '\n';
	}

	cout << "File Compressed\n";
}

void loadCompressed(
	int buttonColors[][30],
	string compressedFile =
	"C:\\Users\\saeed\\OneDrive\\Desktop\\experiments\\DSA finalProject\\DSA finalProject\\compressed.txt")
{
	ifstream inFile(compressedFile);

	if (!inFile.is_open())
	{
		cout << "File error\n";
		return;
	}

	string line;

	for (int row = 0; row < 30; row++)
	{
		getline(inFile, line);

		stringstream ss(line);

		string token;

		int col = 0;

		while (ss >> token)
		{
			// token example: 7:0

			int colonPos = token.find(':');

			int count = stoi(token.substr(0, colonPos));

			int value = token[colonPos + 1] - '0';

			for (int k = 0; k < count; k++)
			{
				buttonColors[row][col] = value;
				col++;
			}
		}
	}

	cout << "File Loaded\n";
}
