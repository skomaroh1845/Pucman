#include <iostream>
#include <glut.h>
#include <Windows.h>
#include <algorithm>

#include "Map.h"
#include "Pucman.h"
#include "Ghost.h"
#include "Interface.h"


#define W 700    // window characteristics (for not full screen mod)
#define H 500


// Global variables  
Map* pMap;                      // pointer to game map obj
Interface* gameInterface;       // pointer to game interface obj
vector <Creature*> creatures;   // there are all game creatures - player and ghosts

// Game function list
void display();
void keyboardClick(unsigned char key, int x, int y);
void mouseClick(int button, int state, int x, int y);
void timer(int);
void closeGame();
void initGame();


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
    if (!Interface::menuOn)
    {
        creatures[0]->print();
        creatures[0]->animate();
        if (creatures[0]->canMove(creatures[0]->direction) && !Interface::interfaceOn)
            creatures[0]->move();
        reinterpret_cast<Pucman*>(creatures[0])->turn();
    }

    // Ghosts
    if (Interface::interfaceOn)
        Ghost::brainMod = false;  // random movement
    else
    {
        Ghost::brainMod = true;  // gradient  movement
        Ghost::playerPos = creatures[0]->getCenter();
    }
    for_each(creatures.begin()+1, creatures.end(),
        [](Creature* el) {
            el->print();
            el->animate();
            reinterpret_cast<Ghost*>(el)->chooseDirection();
            if (el->canMove(el->direction) && !Interface::pauseOn)
                el->move();
        }
    );    

    // Game interface 
    if (Interface::interfaceOn)
    {
        // get mouse info
        POINT p;
        GetCursorPos(&p); 
        
        // interface processing
        if (Interface::pauseOn) {
            gameInterface->Pause(p.x, p.y);
        } 
        else if (Interface::menuOn) {
            gameInterface->Menu(p.x, p.y);
        }
        else if (Interface::winOn) {
            gameInterface->Win(p.x, p.y);
        }
        else if (Interface::lossOn) {
            gameInterface->Loss(p.x, p.y);
        }
        
        if (Interface::exit) closeGame();
        if (Interface::startGame) { 
            Interface::startGame = false;
            initGame(); 
        }
    }

    // Buffers swap
    glutSwapBuffers();
}


// Used to interface management
void keyboardClick(unsigned char key, int x, int y) {
    
    if (key == '\x1b')
    {
        if (Interface::pauseOn)
        {
            Interface::interfaceOn = false;
            Interface::pauseOn = false;
        }
        else
        {
            Interface::interfaceOn = true;
            Interface::pauseOn = true;
        }
    }
    // Player control
    if (creatures.empty()) return;
    if (key == 'W' || key == 'w') {
        reinterpret_cast<Pucman*>(creatures[0])->setTurnDirection(90);
    }
    if (key == 'A' || key == 'a') {
        reinterpret_cast<Pucman*>(creatures[0])->setTurnDirection(180);
    }
    if (key == 'S' || key == 's') {
        reinterpret_cast<Pucman*>(creatures[0])->setTurnDirection(270);
    }
    if (key == 'D' || key == 'd') {
        reinterpret_cast<Pucman*>(creatures[0])->setTurnDirection(0);
    }
}

void mouseClick(int button, int state, int x, int y)
{
    Interface::mouseClick = state;
}


// game timer func
void timer(int = 0) {
    glutPostRedisplay();
    glutTimerFunc(20, timer, 0);
}


void closeGame()
{
    for_each(creatures.begin(), creatures.end(),
        [](Creature* el) {
            delete el;
        }
    );
    exit(0);
}


void initGame()
{
    // Map
    pMap->mapInit();
    
    // clear creature vector if it has something
    if (creatures.size() > 0) {    
        for_each(creatures.begin(), creatures.end(),
            [](Creature* el) {
                delete el;
            } );
        creatures.clear();
    }
    
    // Player
    srand(time(0));
    Pucman* user = new Pucman(pMap->getSpawn(rand()), pMap->getSize());
    creatures.push_back(user);
    
    // Ghosts
    for (int i = 0; i < pMap->numGhosts; ++i)
    {
        Ghost* enemy = new Ghost(pMap->getSpawn(rand()), pMap->getSize(),
            float(rand() % 10) / 9, float(rand() % 10) / 9, float(rand() % 10) / 9);
        creatures.push_back(enemy);
    }
}


// starts program 
int main(int argc, char* argv[])
{
    //---Game start---//
    // Interface init
    Interface gameInter(W, H);
    gameInterface = &gameInter;  // pass to global variable to use in other funcs

    // Game map loading
    Map gameMap(W, H);
    gameMap.loadMap("Level1.txt");
    if (!gameMap.is_loaded()) 
    {
        cout << "Program was shutdown. Level map could not be loaded. "
                "Check game files location." << endl;
        return -1;
    }
    pMap = &gameMap;  // pass to global variable to use in other funcs

    // Game init
    initGame();
    //----------------//

    // glut init
    glutInit(&argc, argv); 
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(W, H);
    glutInitWindowPosition(960 - W / 2, 540 - H / 2);
    glutCreateWindow("Powered by Primitives");
    glClearColor(0.0, 0.0, 0.0, 1.0);

    glutFullScreen();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboardClick);
    glutMouseFunc(mouseClick);

    // Enter in game loop
    timer(0);
    glutMainLoop();
}