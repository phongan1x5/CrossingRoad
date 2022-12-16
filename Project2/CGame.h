#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <Windows.h>
#include <conio.h>
#include <thread>
#include "CAnimal.h"
#include "CVehicle.h"
#include "CPeople.h"
#include "ConsoleHandle.h"
#include "CTrafficLight.h"
#include "Point.h"
#include <utility>
using namespace std;
#pragma comment(lib, "winmm.lib")


#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

typedef pair<string, int> si;

void playDeathSound() {
    PlaySound(TEXT("human_die.wav"), NULL, SND_FILENAME);
}

class CGame
{
private:
    vector<CCar> carList;
    vector<CTruck> truckList;
    vector<CBird> birdList;
    vector<CDinausor> dinausorList;
    vector<TrafficLight> lightList;
    CPeople* people;
    int difficulty;
    int stage;
    bool sound;
public:
    CGame()
    {
        this->people = new CPeople(94, 43);
        difficulty = 100;
        stage = 1;
        sound = true;
    }
    ~CGame()
    {
        deleteGame();
    }
    bool getSound()
    {
        return sound;
    }
    void addCar(int x, int y)
    {
        CCar newCar(x, y);
        carList.push_back(newCar);
    }
    void addTruck(int x, int y)
    {
        CTruck newTruck(x, y);
        truckList.push_back(newTruck);
    }
    void addBird(int x, int y)
    {
        CBird newBird(x, y);
        birdList.push_back(newBird);
    }
    void addDinausor(int x, int y)
    {
        CDinausor newDinausor(x, y);
        dinausorList.push_back(newDinausor);
    }
    void addTrafficLight(TrafficLight& newLight)
    {
        lightList.push_back(newLight);
    }
    void createCarList(ConsoleHandle& handle)
    {
        if (carList.size() <= 0)
        {
            CCar newCar(20+14, 10);
            carList.push_back(newCar);
            return;
        }
        auto it = carList.begin();
        srand(time(NULL));
        int n = (rand() % 10) + 6;
        if ((*it).getPos().x == 151 + 12 - (*it).getLength())
        {
            (*it).deleteVehicle(handle, lightList[0]);
            carList.erase(it);
        }
        if (carList.size() < stage/6 + 3)
        {
            if (carList[carList.size() - 1].getPos().x > carList[0].getLength() + 21 + 13 + n)
            {
                CCar newCar(20 + 14, 10);
                carList.push_back(newCar);
            }
        }
    }
    void createTruckList(ConsoleHandle& handle)
    {
        if (truckList.size() <= 0)
        {
            CTruck newTruck(20 + 14, 28);
            truckList.push_back(newTruck);
            return;
        }
        auto it = truckList.begin();
        srand(time(NULL));
        int n = (rand() % 10) + 6;
        if ((*it).getPos().x == 151 + 12 - (*it).getLength())
        {
            (*it).deleteVehicle(handle, lightList[1]);
            truckList.erase(it);
        }
        if (truckList.size() < stage / 6 + 3)
        {
            if (truckList[truckList.size() - 1].getPos().x > truckList[0].getLength() + 14 + 21 + n)
            {
                CTruck newTruck(20 + 14, 28);
                truckList.push_back(newTruck);
            }
        }
    }
    void createBirdList(ConsoleHandle& handle)
    {
        if (birdList.size() <= 0)
        {
            CBird newBird(150, 18);
            birdList.push_back(newBird);
            return;
        }
        auto it = birdList.begin();
        srand(time(NULL));
        int n = (rand() % 10) + 6;
        if ((*it).getPos().x <= 20 + 13)
        {
            (*it).deleteAnimal(handle);
            birdList.erase(it);
        }
        if (birdList.size() < stage / 6 + 3)
        {
            if (birdList[birdList.size() - 1].getPos().x < 162 - n - 2 * birdList[0].getLength())
            {
                CBird newBird(162 - birdList[0].getLength(), 18);
                birdList.push_back(newBird);
            }
        }
    }
    void createDinausorList(ConsoleHandle& handle)
    {
        if (dinausorList.size() <= 0)
        {
            CDinausor newDinausor(144, 36);
            dinausorList.push_back(newDinausor);
            return;
        }
        auto it = dinausorList.begin();
        srand(time(NULL));
        int n = (rand() % 10) + 6;
        if ((*it).getPos().x <= 20+13)
        {
            (*it).deleteAnimal(handle);
            dinausorList.erase(it);
        }
        if (dinausorList.size() < stage / 6 + 3)
        {
            if (dinausorList[dinausorList.size() - 1].getPos().x < 162 - n - 2 * dinausorList[0].getLength())
            {
                CDinausor newDinausor(162 - dinausorList[0].getLength(), 36);
                dinausorList.push_back(newDinausor);
            }
        }
    }
    void createTrafficLightList()
    {
        lightList.resize(2);
        lightList[0].setPos(164, 7);
        lightList[1].setPos(164, 25);
    }
    void moveAllObject(ConsoleHandle& handle)
    {
        for (int i = 0; i < carList.size(); i++)
            carList[i].Move(lightList[0]);
        createCarList(handle);
        for (int i = 0; i < truckList.size(); i++)
            truckList[i].Move(lightList[1]);
        createTruckList(handle);
        for (int i = 0; i < birdList.size(); i++)
            birdList[i].Move();
        createBirdList(handle);
        for (int i = 0; i < dinausorList.size(); i++)
            dinausorList[i].Move();
        createDinausorList(handle);
        for (int i = 0; i < lightList.size(); i++)
            lightList[i].changeType(handle);
    }
    void drawAllMovingObject(ConsoleHandle& handle)
    {
        for (int i = 0; i < carList.size(); i++) {
            carList[i].drawCar(handle);
        }
        for (int i = 0; i < truckList.size(); i++) {
            truckList[i].drawTruck(handle);
        }
        for (int i = 0; i < birdList.size(); i++) {
            birdList[i].drawBird(handle);
        }
        for (int i = 0; i < dinausorList.size(); i++) {
            dinausorList[i].drawDinausor(handle);
        }
        for (int i = 0; i < lightList.size(); i++) {
            lightList[i].drawLight(handle);
        }
        for (int i = 0; i < carList.size(); i++)
        {
            carList[i].deleteVehicle(handle, lightList[0]);
        }
        for (int i = 0; i < truckList.size(); i++)
        {
            truckList[i].deleteVehicle(handle, lightList[1]);
        }
        for (int i = 0; i < dinausorList.size(); i++)
        {
            dinausorList[i].deleteAnimal(handle);
        }
        for (int i = 0; i < birdList.size(); i++)
        {
            birdList[i].deleteAnimal(handle);
        }
    }
    void clearAllData()
    {
        carList.clear();
        truckList.clear();
        birdList.clear();
        dinausorList.clear();
        lightList.clear();
        people->setPos(94, 43);
    }
    vector<CCar> getCarList()
    {
        return carList;
    }
    vector<CTruck> getTruckList()
    {
        return truckList;
    }
    vector<CBird> getBirdList()
    {
        return birdList;
    }
    vector<CDinausor> getDinausorList()
    {
        return dinausorList;
    }
    vector<TrafficLight> getTrafficLightList()
    {
        return lightList;
    }
    string loadGame(ConsoleHandle& handle)
    {
        vector<si> playerList = handle.drawLoadGameMenu("LoadGameMenu.txt");
        string fileData = ".txt";
        vector <char> saveName;
        int c = 0;
        while (1) {
            c = 0;
            c = handle.lowerGetch();
            if ((c >= 'a' && c <= 'z' || c == ' ') && saveName.size() <= 10)
                saveName.push_back(c);
            else if (c == 27)   //exit
            {
                handle.eraseLoadGameMenu(playerList);
                return "NULL" + fileData;
            }
            else if (c == 8)    //backspace
            {
                if (saveName.size() > 0)
                    saveName.pop_back();
            }
            else if (c == 13)   //enter
            {
                string tmp = "";
                for (int i = 0; i < saveName.size(); i++)
                    tmp = tmp + saveName[i];
                for (int i = 0; i < playerList.size(); i++)
                    if (playerList[i].first.compare(tmp) == 0)
                    {
                        handle.eraseLoadGameMenu(playerList);
                        return tmp + fileData;
                    }
                handle.drawNameNotExit();
                saveName.clear();
                handle.drawLoadGameMenu("LoadGameMenu.txt");
            }
            handle.writeNameToConsole(75, 26 + playerList.size(), saveName);
        }
        handle.eraseLoadGameMenu(playerList);
        return "NULL" + fileData;
    }
    void settingMenu(ConsoleHandle& handle)
    {
        int line = 1;
        string fileNamePrefix = "Setting-";
        string fileNameSuffix = ".txt";
        string fileName = "Setting-1.txt";
        handle.drawSettingMenu(fileName);
        bool isInPauseMenu = true;
        int c = 0;
        while (isInPauseMenu) {
            c = 0;
            switch ((c = _getch())) {
            case KEY_UP:
                line--;
                if (line == 0) line = 1;
                fileName = fileNamePrefix + char(line + 48) + fileNameSuffix;
                handle.drawSettingMenu(fileName);
                break;
            case KEY_DOWN:
                line++;
                if (line == 3) line = 2;
                fileName = fileNamePrefix + char(line + 48) + fileNameSuffix;
                handle.drawSettingMenu(fileName);
                break;
            case 'b':
                return;
            case VK_RETURN:
                if (line == 1) {
                    isInPauseMenu = false;
                    sound = true;
                    handle.eraseSettingMenu();
                    return;
                }
                if (line == 2) {
                    isInPauseMenu = false;
                    sound = false;
                    handle.eraseSettingMenu();
                    return;
                }
            default:
                break;
            }
        }
    }
    void gameMenu(ConsoleHandle& handle) {
        string fileData = "NewGameData.txt";
        int line = 1;
        string fileNamePrefix = "Menu-";
        string fileNameSuffix = ".txt";
        string fileName = "Menu-1.txt";
        handle.drawTitle();
        handle.drawMenu(fileName);
        int c = 0;
        while (1)
        {
            c = 0;
            switch ((c = _getch())) {
            case KEY_UP:
                line--;
                if (line == 0) line = 1;
                fileName = fileNamePrefix + char(line + 48) + fileNameSuffix;
                handle.drawMenu(fileName);
                break;
            case KEY_DOWN:
                line++;
                if (line == 6) line = 5;
                fileName = fileNamePrefix + char(line + 48) + fileNameSuffix;
                handle.drawMenu(fileName);
                break;
            case VK_RETURN:
                if (line == 1) {
                    fileData = "NULL.txt";
                    drawMap(handle, fileData);
                    handle.clearrr();
                    handle.drawTitle();
                    handle.drawMenu(fileName);
                    clearAllData();
                }
                else if (line == 2)
                {
                    fileData = loadGame(handle);
                    handle.drawMenu(fileName);
                    if (fileData.compare("NULL.txt") != 0)
                        drawMap(handle, fileData);
                    handle.drawMenu(fileName);
                    clearAllData();
                }
                else if (line == 3)
                {
                    settingMenu(handle);
                    handle.drawMenu(fileName);
                }
                else if (line == 4) {
                    handle.drawAbout();
                    handle.drawTitle();
                    handle.drawMenu(fileName);
                }
                else if (line == 5)
                {
                    handle.cls();
                    return;
                }
                break;
            default:
                break;
            }
        }
    }
    void readData(string dataFile) {
        ifstream fi;
        fi.open(dataFile);
        string buffer;
        int n, posX, posY;
        //Car;
        fi >> buffer;
        fi >> n;
        for (int i = 0; i < n; i++) {
            fi >> posX >> posY;
            addCar(posX, posY);
        }
        //Truck;
        fi >> buffer;
        fi >> n;
        for (int i = 0; i < n; i++) {
            fi >> posX >> posY;
            addTruck(posX, posY);
        }
        //Bird;
        fi >> buffer;
        fi >> n;
        for (int i = 0; i < n; i++) {
            fi >> posX >> posY;
            addBird(posX, posY);
        }
        //Dinausor;
        fi >> buffer;
        fi >> n;
        for (int i = 0; i < n; i++) {
            fi >> posX >> posY;
            addDinausor(posX, posY);
        }
        //TrafficLight
        fi >> buffer;
        fi >> n;
        int currentTime, time, type;
        for (int i = 0; i < n; i++) {
            fi >> posX >> posY;
            TrafficLight newLight(posX, posY);
            fi >> currentTime >> time >> type;
            newLight.setTime(currentTime, time);
            newLight.setType(type);
            addTrafficLight(newLight);
        }
        //Human
        fi >> buffer;
        fi >> posX >> posY;
        people->setPos(posX, posY);

        //Stage;
        fi >> buffer;
        fi >> stage;

        //Difficulty
        fi >> buffer;
        fi >> difficulty;

        fi.close();
    }
    
    int failGame(ConsoleHandle& handle, int stage, int difficulty) {
        int line = 1;
        string fileNamePrefix = "FailGame-";
        string fileNameSuffix = ".txt";
        string fileName = "FailGame-1.txt";
        handle.drawFailGameMenu(fileName);
        bool isInFailGameMenu = true;
        int c = 0;
        while (isInFailGameMenu) {
            c = 0;
            switch ((c = _getch())) {
            case KEY_UP:
                line--;
                if (line == 0) line = 1;
                fileName = fileNamePrefix + char(line + 48) + fileNameSuffix;
                handle.drawFailGameMenu(fileName);
                break;
            case KEY_DOWN:
                line++;
                if (line == 5) line = 4;
                fileName = fileNamePrefix + char(line + 48) + fileNameSuffix;
                handle.drawFailGameMenu(fileName);
                break;
            case VK_RETURN:
                if (line == 1) {    //resume
                    continue;
                    isInFailGameMenu = false;
                    handle.eraseFailGameMenu();
                    people->deletePeople(handle);
                    people->setPos(94, 43);
                    return 1;
                }
                if (line == 2) {    //save game
                    saveGamePanel(handle, stage, difficulty);
                    handle.drawFailGameMenu(fileName);
                    return 2;
                }
                if (line == 3)  //setting
                {
                    settingMenu(handle);
                    handle.eraseSettingMenu();
                    return 3;
                }
                if (line == 4) {    //exit
                    isInFailGameMenu = false;
                    return 4;
                }
                break;
            default:
                break;
            }
        }
    }
    void drawMap(ConsoleHandle& handle, string dataFile) {
        handle.clearrr();
        if (dataFile.compare("NULL.txt") != 0)
            readData(dataFile);
        else
        {
            createCarList(handle);
            createBirdList(handle);
            createTruckList(handle);
            createDinausorList(handle);
            createTrafficLightList();
        }
        int ch;
        handle.DrawGameMap();
        while (1) {
            //detect keyboard
            if (_kbhit()) {
                ch = _getch();
                if (ch == 224)
                {
                    ch = _getch();
                    people->deletePeople(handle);
                    if (ch == KEY_LEFT) {
                        people->Left();
                    }
                    else if (ch == KEY_RIGHT) {
                        people->Right();
                    }
                    else if (ch == KEY_DOWN) {
                        people->Down();
                    }
                    else if (ch == KEY_UP) {
                        people->Up();
                    }
                }
                else if (ch == 'p' || ch == 'P') {
                    int option = pauseGamePanel(handle, stage, difficulty);
                    if (option == 1 || option == 3 || option == 2)
                        continue;
                    else if (option == 4)
                        return;
                }
            }
            people->draw(handle);
            handle.drawGraphic(33, 2, "GameMap.txt");
            //handle.drawGraphic(152, 17, "Stage.txt");
            handle.drawStage(stage);
            drawAllMovingObject(handle);
            moveAllObject(handle);
            Sleep(difficulty);
            Point cord = people->getPos();

            if (people->isImpact(carList) || people->isImpact(truckList) || people->isImpact(birdList) || people->isImpact(dinausorList))
            {
                //people->draw(handle);
                thread t1 (playDeathSound);
                people->drawDeathEffect(handle);
                t1.join();
                Sleep(1500);

                int option = failGame(handle, stage, difficulty);
                if (option == 1 || option == 3)
                    continue;
                else if (option == 4 || option == 2)
                    return;
            }
            if (people->isFinish()) {
                people->deletePeople(handle);
                people->setPos(94, 43);
                if (difficulty > 20)
                    difficulty -= 20;
                else 
                    difficulty = 100;
                stage++;
            }
        }
    }
    int pauseGamePanel(ConsoleHandle& handle, int stage, int difficulty) {
        int line = 1;
        string fileNamePrefix = "PauseMenu-";
        string fileNameSuffix = ".txt";
        string fileName = "PauseMenu-1.txt";
        handle.drawPauseMenu(fileName);
        bool isInPauseMenu = true;
        int c = 0;
        while (isInPauseMenu) {
            c = 0;
            switch ((c = _getch())) {
            case KEY_UP:
                line--;
                if (line == 0) line = 1;
                fileName = fileNamePrefix + char(line + 48) + fileNameSuffix;
                handle.drawPauseMenu(fileName);
                break;
            case KEY_DOWN:
                line++;
                if (line == 5) line = 4;
                fileName = fileNamePrefix + char(line + 48) + fileNameSuffix;
                handle.drawPauseMenu(fileName);
                break;
            case VK_RETURN:
                if (line == 1) {    //resume
                    isInPauseMenu = false;
                    handle.erasePauseMenu();
                    return 1;
                }
                if (line == 2) {    //save game
                    saveGamePanel(handle, stage, difficulty);
                    handle.earseSaveGamePanel();
                    handle.drawPauseMenu(fileName);
                }
                if (line == 3)
                {
                    settingMenu(handle);
                    handle.eraseSettingMenu();
                    return 3;
                }
                if (line == 4) {    //exit
                    isInPauseMenu = false;
                    return 4;
                }
                break;
            default:
                break;
            }
        }
    }
    void saveGame(int stage, int difficulty, vector<char>saveName) {
        string fileName = "";
        for (int i = 0; i < saveName.size(); i++) fileName += saveName[i];
        ofstream fo;
        fo.open("LoadGame.txt", ios::app);
        fo << fileName << " " << stage << endl;
        fo.close();
        fileName += ".txt";
        fo.open(fileName);

        fo << "//Car//" << '\n';
        fo << carList.size() << '\n';
        for (int i = 0; i < carList.size(); i++) {
            Point cord = carList[i].getPos();
            fo << cord.x << char(32) << cord.y << '\n';
        }

        fo << "//Truck//" << '\n';
        fo << truckList.size() << '\n';
        for (int i = 0; i < truckList.size(); i++) {
            Point cord = truckList[i].getPos();
            fo << cord.x << char(32) << cord.y << '\n';
        }

        fo << "//Bird//" << '\n';
        fo << birdList.size() << '\n';
        for (int i = 0; i < birdList.size(); i++) {
            Point cord = birdList[i].getPos();
            fo << cord.x << char(32) << cord.y << '\n';
        }

        fo << "//Dinausor//" << '\n';
        fo << dinausorList.size() << '\n';
        for (int i = 0; i < dinausorList.size(); i++) {
            Point cord = dinausorList[i].getPos();
            fo << cord.x << char(32) << cord.y << '\n';
        }

        fo << "//TrafficLight//" << '\n';
        fo << lightList.size() << '\n';
        for (int i = 0; i < lightList.size(); i++) {
            fo << lightList[i].getPos().x << char(32) << lightList[i].getPos().y << char(32) << lightList[i].getCurrentTime() << char(32) << lightList[i].getTime();
            if (lightList[i].getStatus().compare("Light-2.txt") == 0)
                fo << " 2" << endl;
            else
                fo << " 1" << endl;
        }

        fo << "//Human//" << '\n';
        Point cord = people->getPos();
        fo << cord.x << char(32) << cord.y << '\n';

        fo << "//stage//" << '\n';
        fo << stage << '\n';

        fo << "difficuly" << '\n';
        fo << difficulty << '\n';

        fo.close();
    }
    void saveGamePanel(ConsoleHandle& handle, int stage, int difficulty) {
        vector <char> saveName;
        string fileName = "SaveGamePanel.txt";
        handle.drawSavePanel(fileName);
        int c = 0;
        while (1) {
            c = 0;
            c = handle.lowerGetch();
            if ((c >= 'a' && c <= 'z' || c == ' ') && saveName.size() <= 10)
                saveName.push_back(c);
            else if (c == 27)   //exit
                return;
            else if (c == 8)
            {
                if (saveName.size() > 0)
                    saveName.pop_back();
            }
            else if (c == 13)
            {
                saveGame(stage, difficulty, saveName);
                return;
            }
            handle.writeNameToConsole(75, 21, saveName);
        }
    }
    void deleteGame()
    {
        delete people;
        stage = 1;
        difficulty = 100;
        clearAllData();
    }
};