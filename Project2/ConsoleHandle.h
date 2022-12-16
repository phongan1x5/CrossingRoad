#pragma once
#include <Windows.h>
#include <string>
#include <conio.h>
#include <iostream>
#include <vector>
#include <utility>
#include <tchar.h>

using namespace std;
#define consoleWidth 176
#define consoleHeight 50	

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

typedef pair<string, int> si;

CHAR_INFO consoleBuffer[consoleWidth * consoleHeight];
SMALL_RECT consoleWriteArea = { 0, 0, consoleWidth - 1, consoleHeight - 1 };
COORD characterBufferSize = { consoleWidth, consoleHeight };
COORD characterPosition = { 0, 0 };
HANDLE wHnd = GetStdHandle(STD_OUTPUT_HANDLE);


class ConsoleHandle
{
private:
    int width;
    int height;
public:
    ConsoleHandle()
    {
        FixConsoleWindow();
        clearrr();
    }
    void gotoXY(int x, int y) {
        COORD point;
        point.X = x;
        point.Y = y;
        SetConsoleCursorPosition(wHnd, point);
    }
    void SetColor(int color)
    {
        SetConsoleTextAttribute(wHnd, color);
    }
    void HideCursor() {
        CONSOLE_CURSOR_INFO info;
        info.dwSize = 100;
        info.bVisible = FALSE;
        SetConsoleCursorInfo(wHnd, &info);
    }
    void FixConsoleWindow() {
        HWND consoleWindow = GetConsoleWindow();
        LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
        style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
        SetWindowLong(consoleWindow, GWL_STYLE, style);

        SetConsoleTitle(_T("Road Crossing Game Group 11"));
        COORD const size = { consoleWidth , consoleHeight + 2 };
        SMALL_RECT const minimal_window = { 0, 0, 1, 1 };
        SetConsoleWindowInfo(wHnd, TRUE, &minimal_window);
        SetConsoleScreenBufferSize(wHnd, size);
        SMALL_RECT const window = { 0, 0, size.X - 1, size.Y - 1 };
        SetConsoleWindowInfo(wHnd, TRUE, &window);
        SetConsoleCP(65001);
        HideCursor();

    }
    void resizeConsole(int width, int height)
    {
        HWND console = GetConsoleWindow();
        RECT r;
        GetWindowRect(console, &r);
        MoveWindow(console, r.left, r.top, width, height, true);
    }
    void drawGraphic(int mX, int mY, string graphicFile) {
        ifstream op;
        op.open(graphicFile);
        vector<string> line;
        string tmp;
        while (getline(op, tmp))
            line.push_back(tmp);
        for (int y = 0; y < line.size(); ++y)
        {
            for (int x = 0; x < line[y].size(); ++x)
            {
                consoleBuffer[mX + x + consoleWidth * (mY + y)].Char.AsciiChar = line[y][x];
                consoleBuffer[mX + x + consoleWidth * (mY + y)].Attributes = 240;
            }
        }
        WriteConsoleOutputA(wHnd, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea);
        op.close();
    }
    void drawGraphic(int mX, int mY, string graphicFile, int atribute) {
        ifstream op;
        op.open(graphicFile);
        vector<string> line;
        string tmp;
        while (getline(op, tmp))
            line.push_back(tmp);
        for (int y = 0; y < line.size(); ++y)
        {
            for (int x = 0; x < line[y].size(); ++x)
            {
                consoleBuffer[mX + x + consoleWidth * (mY + y)].Char.AsciiChar = line[y][x];
                consoleBuffer[mX + x + consoleWidth * (mY + y)].Attributes = atribute;
            }
        }
        WriteConsoleOutputA(wHnd, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea);
        op.close();
    }
    void drawString(int mX, int mY, string s) {
        for (int x = 0; x < s.length(); ++x)
        {
            consoleBuffer[mX + x + consoleWidth * (mY)].Char.AsciiChar = s[x];
            consoleBuffer[mX + x + consoleWidth * (mY)].Attributes = 240;
        }
        WriteConsoleOutputA(wHnd, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea);
    }
    void drawString(int mX, int mY, string s, int atribute) {
        for (int x = 0; x < s.length(); ++x)
        {
            consoleBuffer[mX + x + consoleWidth * (mY)].Char.AsciiChar = s[x];
            consoleBuffer[mX + x + consoleWidth * (mY)].Attributes = atribute;
        }
        WriteConsoleOutputA(wHnd, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea);
    }
    void deleteGraphic(int mX, int mY, int a, int b) {
        for (int y = 0; y < a; ++y)
        {
            for (int x = 0; x < b; ++x)
            {
                consoleBuffer[mX + x + consoleWidth * (mY + y)].Char.AsciiChar = ' ';
                consoleBuffer[mX + x + consoleWidth * (mY + y)].Attributes = 240;
            }
        }
    }
    void clearrr()
    {
        for (int y = 0; y < consoleHeight; ++y)
        {
            for (int x = 0; x < consoleWidth; ++x)
            {
                consoleBuffer[x + consoleWidth * y].Char.AsciiChar = ' ';
                consoleBuffer[x + consoleWidth * y].Attributes = 240;
            }
        }
    }
    void cls()
    {
        for (int y = 0; y < consoleHeight; ++y)
        {
            for (int x = 0; x < consoleWidth; ++x)
            {
                consoleBuffer[x + consoleWidth * y].Char.AsciiChar = ' ';
                consoleBuffer[x + consoleWidth * y].Attributes = 7;
            }
        }
        WriteConsoleOutputA(wHnd, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea);
    }
    void drawTitle() {
        drawGraphic(7, 0, "GameTitle0.txt",240);
    }
    void drawMenu(string menuFileName) {
        drawGraphic(60, 20, menuFileName);
    }
    void eraseMenu()
    {
        deleteGraphic(60, 20, 18, 52);
    }
    void drawStage(int stage) {

        drawString(19, 10, to_string(stage));
    }
    vector<si> drawLoadGameMenu(string menuFileName) {
        drawGraphic(7, 0, "GameTitle0.txt");
        eraseMenu();
        drawGraphic(60, 20, menuFileName);
        vector<si> playerList;
        ifstream fin;
        fin.open("LoadGame.txt");
        while (!fin.eof())
        {
            si tmp;
            fin >> tmp.first;
            fin >> tmp.second;
            playerList.push_back(tmp);
        }
        playerList.pop_back();
        fin.close();
        int i = 0;
        for (; i < playerList.size(); i++)
        {
            drawString(60, 25 + i, "|");
            drawString(73 - (playerList[i].first).length() / 2, 25 + i, playerList[i].first);
            drawString(85, 25 + i, "|");
            drawString(100, 25 + i, to_string(playerList[i].second));
            drawString(112, 25 + i, "|");
        }
        drawGraphic(60, 25+i, "LoadGameMenu-2.txt");
        return playerList;
    }

    void eraseLoadGameMenu(vector<si> list)
    {
        deleteGraphic(60, 20, 18+list.size(), 53);
    }

    void drawPauseMenu(string pauseMenuFileName) {
        drawGraphic(60, 20, pauseMenuFileName);
    }

    void erasePauseMenu()
    {
        deleteGraphic(60, 20, 16, 52);
    }

    void drawFailGameMenu(string pauseMenuFileName) {
        drawGraphic(75, 17, pauseMenuFileName);
    }

    void eraseFailGameMenu()
    {
        deleteGraphic(75, 17,13 , 19);
    }

    void DrawGameMap()
    {
        drawGraphic(5, 2, "GameMap2.txt");
    }

    void drawSettingMenu(string pauseMenuFileName) {

        clearrr();
        drawGraphic(7, 0, "GameTitle0.txt");
        drawGraphic(66, 25, pauseMenuFileName);
    }

    void eraseSettingMenu()
    {
        deleteGraphic(7, 0, 14, 170);
        deleteGraphic(66, 25, 7, 38);
    }

    void drawNameNotExit()
    {
        clearrr();
        drawGraphic(7, 0, "GameTitle0.txt");
        drawGraphic(75, 25, "NameNotExit.txt");
        while (1) {
            char c = _getch();
            if (c == 'b') 
                return;
        }
    }

    void earseNameNotExit()
    {
        deleteGraphic(75, 25, 8, 19);
    }
    void drawAbout() {
        clearrr();
        drawGraphic(7, 0, "GameTitle0.txt");
        drawGraphic(60, 20, "About.txt");
        while (1) {
            char c = _getch();
            if (c == 'b')
            {
                clearrr();
                return;
            }
        }
    }
    void drawSavePanel(string pauseMenuFileName) {
        drawGraphic(60, 20, pauseMenuFileName);
    }

    void earseSaveGamePanel()
    {
        deleteGraphic(60, 20, 21, 52);
    }

    void writeNameToConsole(int x, int y, vector <char> name) {
        string s = "";
        for (int i = 0; i < name.size(); i++) 
            s += name[i];
        s += "_";
        if (name.size() <= 10)
            for (int i = 0; i <= (10 - name.size()); i++)
                s += " ";
        drawString(x, y, s);
    }

    char lowerGetch() {
        char c = _getch();
        c = tolower(c);
        return c;
    }
};