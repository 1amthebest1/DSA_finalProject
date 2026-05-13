#include "raylib.h"
#include "utility.h"
#include "matrix.h"
#include "globals.h"
#include "matrixHelper.h"
//---- GRAPHIC FUNCTIONS ----//

void setFPS(int FPS) {
	SetTargetFPS(FPS);
}

void createWindow(int width, int height) {
	InitWindow(width, height, "B4k3r");
}

void finishWindow() {
	CloseWindow();
}

void createCanvasBlack() {
	BeginDrawing();
	ClearBackground(BLACK);
};

void finishCanvas() {
	EndDrawing();
}

int main() {
	MatriX <int> grid;
	grid.setDimensionsDefault();
	grid.setButtonPositionDefault();
	grid.setButtonColorDefault();

	createWindow(760, 1000);
	InitAudioDevice();
	bgMusic = LoadMusicStream("D:/music/0513.mp3");
	setFPS(60);
	while (!WindowShouldClose()) {
		createCanvasBlack();

		grid.checkRectanglePressed();
		grid.checkRectanglePressedSingle();
		grid.drawMatrix();
		grid.drawSave();
		grid.drawClearCanvas();
		grid.drawTranspose();
		grid.drawDance();
		grid.drawSingleMode();
		grid.drawLoadSavedImage();
		grid.drawReverseImage();
		grid.drawGrayScale();
		grid.drawIncreaseOpacity();
		grid.drawDecreaseOpacity();
		grid.drawRedWhite();
		grid.drawCompressFile();
		grid.drawLoadCompressedFile();
		grid.dance();

		grid.checkSavePressed();
		grid.checkClearCanvasPressed();
		grid.checkTransposePressed();
		grid.checkDancePressed();
		grid.checkSingleModePressed();
		grid.checkLoadSavedImagePressed(grid.buttonColor);
		grid.checkReverseImagePressed(grid.buttonColor);
		grid.checkGrayScalePressed(grid.buttonColor);
		grid.checkIncreaseOpacityPressed();
		grid.checkDecreaseOpacityPressed();
		grid.checkRedWhitePressed(grid.buttonColor);
		grid.checkCompressPressed();
		grid.checkLoadCompressPressed(grid.buttonColor);

		finishCanvas();
	}
	StopMusicStream(bgMusic);
	UnloadMusicStream(bgMusic);
	CloseAudioDevice();
	finishWindow();
}

//---- ----------------- ----//
