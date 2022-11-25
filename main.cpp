#include <iostream>
#include <glut.h>

#include "Map.h"
#include "Pucman.h"




// Global variables  
Map* pMap;
Pucman* Player;




// Main game loop
void display() {
    // Screen cleaning
    glClear(GL_COLOR_BUFFER_BIT);


    // Objects drawing
    // ...
    pMap->print();
    pMap->animate();
    
    Player->print();
    Player->animate();


    // Events managment
    // ...


    // Keyboard clicks processing
    // ...


    // Buffers swap
    glutSwapBuffers();
}



// game timer func
void timer(int = 0) {
    display();
    glutTimerFunc(20, timer, 0);
}


// User input //
void MouseClick(int button, int state, int x, int y) {

}


void MouseMotion(int x, int y) {

}


void KeyBoardClick(unsigned char key, int x, int y) {

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
    Pucman user(gameMap.getPlayerSpawn(rand()), gameMap.getPlayerSize());
    Player = &user;

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

    // Manage user input 
    glutMouseFunc(MouseClick);
    glutMotionFunc(MouseMotion);
    glutKeyboardFunc(KeyBoardClick);

    // Enter in game loop
    timer(0);
    glutMainLoop();
}