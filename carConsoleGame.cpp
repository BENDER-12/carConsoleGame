#include <iostream>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 29
#define WIN_WIDTH 70

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

int enemyY[3];
int enemyX[3];
int enemyFlag[3];
char car[4][4] = {
    ' ','+','+',' ',
    '+','+','+','+',
    ' ','+','+',' ',
    '+','+','+','+'
};

int carpos = WIN_WIDTH / 2;
int score = 0;

void gotoxy(int x, int y) {
    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(console, CursorPosition);
}

void setcursor(bool visible, DWORD size) {
    if (size == 0)
        size = 50;

    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible;
    lpCursor.dwSize = size;
    SetConsoleCursorInfo(console, &lpCursor);
}

void drawBorder() {
    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        for (int j = 0; j < 18; j++) {
            gotoxy(0 + j, i);
            cout << "0";
            gotoxy(WIN_WIDTH - j, i);
            cout << "0";
        }
    }
    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        gotoxy(SCREEN_WIDTH, i);
        cout << "0";
    }
}

void genEnemy(int ind) {
    enemyX[ind] = 17 + rand() % (33);
}

void drawEnemy(int ind) {
    if (enemyFlag[ind] != 0) {
        gotoxy(enemyX[ind], enemyY[ind]);           cout << "----";
        gotoxy(enemyX[ind], enemyY[ind] + 1);       cout << " -- ";
        gotoxy(enemyX[ind], enemyY[ind] + 2);       cout << "----";
        gotoxy(enemyX[ind], enemyY[ind] + 3);       cout << " -- ";
    }
}

void eraseEnemy(int ind) {
    if (enemyFlag[ind] != 0) {
        gotoxy(enemyX[ind], enemyY[ind]);           cout << "    ";
        gotoxy(enemyX[ind], enemyY[ind] + 1);       cout << "    ";
        gotoxy(enemyX[ind], enemyY[ind] + 2);       cout << "    ";
        gotoxy(enemyX[ind], enemyY[ind] + 3);       cout << "    ";
    }
}

void resetEnemy(int ind) {
    eraseEnemy(ind);
    enemyY[ind] = 1;
    genEnemy(ind);
}

void drawCar() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            gotoxy(j + carpos, i + 22); cout << car[i][j];
        }
    }
}

void eraseCar() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            gotoxy(j + carpos, i + 22); cout << " ";
        }
    }
}

int collision() {
    if (enemyY[0] + 4 >= 23) {
        if (enemyX[0] + 4 - carpos >= 0 && enemyX[0] + 4 - carpos < 9) {
            return 1;
        }
    }
    return 0;
}

void gameover() {
    system("cls");
    cout << "\n\t\t----------------------------";
    cout << "\n\t\t--------- Game Over --------";
    cout << "\n\t\t----------------------------";
    cout << "\n\t\tPress any Key to go back to menu.";
    _getch();
}

void updateScore() {
    gotoxy(WIN_WIDTH + 7, 5);
    cout << "Score: " << score << endl;
}

void instructions() {
    system("cls");
    cout << "Instructions";
    cout << "\n-----------------";
    cout << "\n Avoid car by moving left or right.";
    cout << "\n\n Press 'Arrow Keys' to move the Car";
    cout << "\n\n Press 'escape' to Exit";
    cout << "\n\n Press any Key to go back to the menu";
    _getch();
}

void play() {
    carpos = -1 + WIN_WIDTH / 2;
    score = 0;
    enemyFlag[0] = 1;
    enemyFlag[1] = 0;
    enemyY[0] = enemyY[1] = 1;

    system("cls");
    drawBorder();
    updateScore();
    genEnemy(0);
    genEnemy(1);

    while (1) {
        if (_kbhit()) {
            char ch = _getch();
            if (ch == 'a' || ch == 'A' || ch == 75) {
                if (carpos > 18) carpos -= 4;
            }
            if (ch == 'd' || ch == 'D' || ch == 77) {
                if (carpos < 50) carpos += 4;
            }
            if (ch == 27) break;
        }

        drawCar();
        drawEnemy(0);
        drawEnemy(1);
        if (collision() == 1) {
            gameover();
            return;
        }
        Sleep(50);
        eraseCar();
        eraseEnemy(0);
        eraseEnemy(1);

        if (enemyY[0] == 10 && enemyFlag[1] == 0) enemyFlag[1] = 1;

        if (enemyFlag[0] != 0) enemyY[0] += 1;
        if (enemyFlag[1] != 0) enemyY[1] += 1;

        if (enemyY[0] > SCREEN_HEIGHT - 4) {
            resetEnemy(0);
            score++;
            updateScore();
        }
        if (enemyY[1] > SCREEN_HEIGHT - 4) {
            resetEnemy(1);
            score++;
            updateScore();
        }
    }
}

int main() {
    setcursor(0, 0);
    srand((unsigned)time(NULL));

    while (1) {
        system("cls");
        cout << "1. Start Game\n2. Instructions\n3. Quit\nSelect option: ";
        char op = _getche();

        if (op == '1') play();
        else if (op == '2') instructions();
        else if (op == '3') break;
    }

    return 0;
}
