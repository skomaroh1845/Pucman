#include <iostream>
#include <glut.h>
#include <Windows.h>
#include <algorithm>

#include "Map.h"
#include "Pucman.h"
#include "Ghost.h"




// Global variables  
Map* pMap;
vector <Creature*> creatures;



// Main game loop
void display() {
    // Screen cleaning
    glClear(GL_COLOR_BUFFER_BIT);

    // Map
    pMap->print();
    pMap->animate();
    pMap->updateCreaturesView(creatures);
    pMap->updateCoins(creatures[0]->getCenter());

    // Player
    creatures[0]->print();
    creatures[0]->animate();
    if (creatures[0]->canMove(creatures[0]->direction))
        creatures[0]->move();
    reinterpret_cast<Pucman*>(creatures[0])->turn();

    // Ghosts
    Ghost::playerPos = creatures[0]->getCenter();

    for_each(creatures.begin()+1, creatures.end(),
        [](Creature* el) {
            el->print();
            el->animate();
            reinterpret_cast<Ghost*>(el)->chooseDirection();
            if (el->canMove(el->direction))
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
    if (GetAsyncKeyState((unsigned short)'\x1b')) {
        for_each(creatures.begin(), creatures.end(),
            [](Creature* el) {
                delete el;
            }
        );
        exit(0);
    }
    if (GetAsyncKeyState(VK_LBUTTON)) {
        POINT p;
        GetCursorPos(&p);
    }

    // Buffers swap
    glutSwapBuffers();
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
    // Game map
    Map gameMap(700, 500);
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
    glutInitWindowSize(700, 500);
    glutInitWindowPosition(960 - 700 / 2, 540 - 500 / 2);
    glutCreateWindow("Powered by Primitives");
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 700, 0, 500, -1, 1);
    //glutFullScreen();
    glutDisplayFunc(display);

    // Enter in game loop
    timer(0);
    glutMainLoop();
}