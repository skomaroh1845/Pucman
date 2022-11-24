#include <iostream>



#include "glutStd.cpp"



// Global variables  


// Main game loop
void display() {
    // Screen cleaning
    glClear(GL_COLOR_BUFFER_BIT);


    // Objects drawing
    // ...


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



// starts program 
int main(int argc, char* argv[])
{
    // user init
    std::cout << "Game is started." << std::endl;


    // glut init
    glutStdStart(display, timer, argc, argv, 700, 500);
}