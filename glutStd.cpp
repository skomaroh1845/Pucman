#pragma once

#include <glut.h>

void glutStdStart(void (*display)(void), void (*timer)(int), int argc, char** argv, 
				  int ScrW, int ScrH, double Xmin = -10, double Xmax = 10, double Ymin = -10, double Ymax = 10)
{
	glutInit(&argc, argv);  // window init
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(ScrW, ScrH);
	glutInitWindowPosition(960 - ScrW / 2, 540 - ScrH / 2);
	glutCreateWindow("Powered by Primitives");
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(Xmin, Xmax, Ymin, Ymax, -1, 1);
	//glutFullScreen();
	glutDisplayFunc(display);
	(*timer)(0);
	glutMainLoop();
}
