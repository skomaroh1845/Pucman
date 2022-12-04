#include <iostream>
#include <glut.h>
#include <Windows.h>
#include <algorithm>

#include "Map.h"
#include "Pucman.h"
#include "Ghost.h"
#include "Interface.h"


#define W 700    // window characteristics 
#define H 500


// Global variables  
Map* pMap;
Interface* gameInter;
vector <Creature*> creatures;



// Main game loop
void display() {
    // glut staff
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, W, 0, H, -1, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    // Map
    pMap->print();
    pMap->animate();
    pMap->updateCreaturesView(creatures);
    pMap->updateCoins(creatures[0]->getCenter());

    // Player
    creatures[0]->print();
    creatures[0]->animate();
    if (creatures[0]->canMove(creatures[0]->direction) && !Interface::pauseOn)
        creatures[0]->move();
    reinterpret_cast<Pucman*>(creatures[0])->turn();

    // Ghosts
    Ghost::playerPos = creatures[0]->getCenter();

    for_each(creatures.begin()+1, creatures.end(),
        [](Creature* el) {
            el->print();
            el->animate();
            reinterpret_cast<Ghost*>(el)->chooseDirection();
            if (el->canMove(el->direction) && !Interface::pauseOn)
                el->move();
        }
    );    

    // Keyboard clicks processing
    if (GetAsyncKeyState((unsigned short)'W')) {
        reinterpret_cast<Pucman*>(creatures[0])->setTurnDirection(90);
    }
    if (GetAsyncKeyState((unsigned short)'A')) {
        reinterpret_cast<Pucman*>(creatures[0])->setTurnDirection(180);
    }
    if (GetAsyncKeyState((unsigned short)'S')) {
        reinterpret_cast<Pucman*>(creatures[0])->setTurnDirection(270);
    }
    if (GetAsyncKeyState((unsigned short)'D')) {
        reinterpret_cast<Pucman*>(creatures[0])->setTurnDirection(0);
    }
    if (GetAsyncKeyState(VK_LBUTTON)) {
    }


    // Interface 
    if (Interface::pauseOn) 
    {
        POINT p;
        GetCursorPos(&p);
        gameInter->PrintPause(p.x, p.y);
    }

    // Buffers swap
    glutSwapBuffers();
}


void KeyboardClick(unsigned char key, int x, int y) {
    
    if (key == ' ') 
    {
        if (Interface::pauseOn)
            Interface::pauseOn = false;
        else
            Interface::pauseOn = true;
    }
    if (key == '\x1b') {
        for_each(creatures.begin(), creatures.end(),
            [](Creature* el) {
                delete el;
            }
        );
        cout << "Game finished." << endl;
        exit(0);
    }
}



// game timer func
void timer(int = 0) {
    display();
    glutTimerFunc(20, timer, 0);
}


// starts program 
int main(int argc, char* argv[])
{
    // Game init //
    std::cout << "Game is started." << std::endl;
    Interface gameInterface(W, H);
    gameInter = &gameInterface;

    // Game map
    Map gameMap(W, H);
    gameMap.loadMap("Level1.txt");
    if (!gameMap.is_loaded()) return 1;
    gameMap.mapInit();
    pMap = &gameMap;

    // Player 
    srand(time(0));
    Pucman* user = new Pucman(gameMap.getSpawn(rand()), gameMap.getSize());
    creatures.push_back(user);
    // Ghosts
    for (int i = 0; i < gameMap.numGhosts; ++i)
    {
        Ghost* enemy = new Ghost( gameMap.getSpawn(rand()), gameMap.getSize(), 
                                  float(rand()%10)/9, float(rand() % 10)/9, float(rand() % 10)/9 );
        creatures.push_back(enemy);
    }

    // glut init
    glutInit(&argc, argv); 
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(W, H);
    glutInitWindowPosition(960 - W / 2, 540 - H / 2);
    glutCreateWindow("Powered by Primitives");
    glClearColor(0.0, 0.0, 0.0, 1.0);

    glutFullScreen();
    glutDisplayFunc(display);
    glutKeyboardFunc(KeyboardClick);

    // Enter in game loop
    timer(0);
    glutMainLoop();
}