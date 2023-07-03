#include <iostream>
#include <cmath>
#include <Windows.h>

const int screenWidth = 80;
const int screenHeight = 25;

char screen[screenHeight][screenWidth];
const char donutChars[] = "@%#*+=-:. ";

const int numDonutChars = sizeof(donutChars) / sizeof(donutChars[0]);

void clearScreen() {
    for (int y = 0; y < screenHeight; ++y) {
        for (int x = 0; x < screenWidth; ++x) {
            screen[y][x] = ' ';
        }
    }
}

void renderScreen() {
    COORD cursorPos;
    cursorPos.X = 0;
    cursorPos.Y = 0;
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(output, cursorPos);

    for (int y = 0; y < screenHeight; ++y) {
        for (int x = 0; x < screenWidth; ++x) {
            std::cout << screen[y][x];
        }
        std::cout << std::endl;
    }
}

void drawPixel(int x, int y, char c) {
    if (x >= 0 && x < screenWidth && y >= 0 && y < screenHeight) {
        screen[y][x] = c;
    }
}

void drawDonut(double time) {
    double cosTime = cos(time);
    double sinTime = sin(time);

    double cosTime2 = cos(time * 2);
    double sinTime2 = sin(time * 2);

    for (double i = 0; i < 2 * M_PI; i += 0.07) {
        double cosI = cos(i);
        double sinI = sin(i);
        for (double j = 0; j < 2 * M_PI; j += 0.02) {
            double cosJ = cos(j);
            double sinJ = sin(j);
            double circleX = 10 + 8 * cosJ;
            double circleY = 10 + 4 * sinJ;
            double z = 1 / (0.01 + sinI * circleX * cosTime - circleY * sinTime);
            int projX = int(screenWidth / 2 + 40 * z * cosI * cosTime2 - 20 * z * sinI * sinTime2);
            int projY = int(screenHeight / 2 + 12 * z * cosI * sinTime2 + 15 * z * sinI * cosTime2);
            int donutCharIndex = int((z + 1) / 2 * (numDonutChars - 1));
            char donutChar = donutChars[donutCharIndex];
            drawPixel(projX, projY, donutChar);
        }
    }
}

int main() {
    double time = 0;
    while (true) {
        clearScreen();
        drawDonut(time);
        renderScreen();
        time += 0.05;
        Sleep(100);
    }
    return 0;
}
