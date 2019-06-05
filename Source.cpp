
#include <stdlib.h>
#include <glut.h>
#include <iostream>
#include <string.h>
#include <sstream>
#include <cstdio>
#include <time.h>
#include<math.h>
#include <thread>

int c = 010;
int i, q, z;
float speed = 0;
int score = 0, score1 = 0;
int screen = 0;
bool collide = false;
char buffer[10];
int tileX = 240, tileY = 70;
int otileX[4], otileY[4];
char space11[] = "SPACE";
char score11[] = "Score :";
char dodge[] = "Dodge :";

void drawText(char ch[], int xpos, int ypos, int z = 0)
{
	int numofchar = strlen(ch);
	glLoadIdentity();
	glRasterPos2f(xpos, ypos);
	for (i = 0; i <= numofchar - 1; i++)
	{

		if (z == 1)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ch[i]);
		else
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ch[i]);

	}
}

void drawTextNum(char ch[], int numtext, int xpos, int ypos)
{
	int len;
	int k;
	k = 0;
	len = numtext - strlen(ch);
	glLoadIdentity();
	glRasterPos2f(xpos, ypos);
	for (i = 0; i <= numtext - 1; i++)
	{
		if (i < len)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '0');
		else
		{
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ch[k]);
			k++;
		}
	}
}

void ovpos()
{

	for (i = 0; i < 4; i++)
	{
		if (rand() % 2 == 0)
		{
			otileX[i] = 200;
		}
		else if (rand() % 3 == 0 || rand() % 5 == 0)
		{
			otileX[i] = 280;
		}
		else
		{
			otileX[i] = 360;
		}
		otileY[i] = 1000 - i * 160;
	}
}

void drawPath()
{

	glBegin(GL_QUADS);
	glColor3f(0.4, 0.4, 0.4);
	glVertex2f(120, 500);
	glVertex2f(120, 0);
	glVertex2f(130, 0);
	glVertex2f(130, 500);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.4, 0.4, 0.4);
	glVertex2f(370, 500);
	glVertex2f(370, 0);
	glVertex2f(380, 0);
	glVertex2f(380, 500);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0, 0, 0);
	glVertex2f(230 - 100, 500);
	glVertex2f(230 - 100, 0);
	glVertex2f(270 + 100, 0);
	glVertex2f(270 + 100, 500);
	glEnd();
}

void drawCircle(int tileX, int tileY, int radius)
{
	float x2, y2;
	float angle;
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(tileX, tileY);

	for (angle = 1.0f; angle < 361.0f; angle += 1)
	{
		x2 = tileX + sin(angle)*radius;
		y2 = tileY + cos(angle)*radius;
		glVertex2f(x2, y2);
	}

	glEnd();
}

void drawUFO()
{
	glColor3f(0.9, 0.9, 0.9);
	drawCircle(tileX, tileY, 20);

	glColor3f(1, 0.5, 0);
	drawCircle(tileX, tileY, 10);

	glColor3f(0, 0, 0.8);
	drawCircle(tileX + 10, tileY + 10, 4);

	glColor3f(0.8, 0, 0.8);
	drawCircle(tileX + 10, tileY - 10, 4);

	glColor3f(0.8, 0, 0);
	drawCircle(tileX - 10, tileY + 10, 4);

	glColor3f(0, 0.8, 0);
	drawCircle(tileX - 10, tileY - 10, 4);
}

void drawObject()
{

	for (i = 0; i < 4; i++)
	{
		glPointSize(90.0);
		glBegin(GL_QUADS);
		if (i == 0)
			glColor3f(0.8, 0.2, 0);
		else if (i == 1)
			glColor3f(0.5, 0.2, 0.8);
		else if (i == 2)
			glColor3f(0.5, 0.8, 0.2);
		else
			glColor3f(0.8, 0.2, 0.5);

		glVertex2f(otileX[i] - 60, otileY[i] - 50);
		glVertex2f(otileX[i] - 60, otileY[i]);
		glVertex2f(otileX[i], otileY[i]);
		glVertex2f(otileX[i], otileY[i] - 50);
		glEnd();
		otileY[i] = otileY[i] - 10 * speed;

		if (otileY[i] > tileY - 50 && otileY[i] < tileY + 50 && otileX[i] == tileX + 40)
		{
			collide = true;


		}

		if (otileY[i] < -25)
		{
			if (rand() % 2 == 0)
			{
				otileX[i] = 200;
			}
			else if (rand() % 3 == 0 || rand() % 5 == 0)
			{
				otileX[i] = 280;
			}
			else
			{
				otileX[i] = 360;
			}
			otileY[i] = 600;
		}
	}
}

void Specialkey(int key, int x, int y)
{

	switch (key)
	{

	case GLUT_KEY_LEFT:
		if (c == 100)
		{
			tileX = 160;
		}
		else if (c == 010)
		{
			c = 100;
			tileX = 160;
		}
		else if (c == 001)
		{
			tileX = 240;
			c = 010;
		}
		else
			tileX = 160;

		break;
	case GLUT_KEY_RIGHT:

		if (c == 001)
		{
			tileX = 320;
		}
		else if (c == 010)
		{
			tileX = 320;
			c = 001;
		}
		else if (c == 100)
		{
			tileX = 240;
			c = 010;
		}
		else
			tileX = 320;
		break;
	}
	glutPostRedisplay();
}

void reinit()
{
	c = 010;
	speed = 0;
	score = 0;
	collide = false;
	tileX = 240; tileY = 70;
	ovpos();
}

void Normalkey(unsigned char key, int x, int y)
{
	switch (key)
	{
	case ' ':if (screen == 0)
		screen = 1;
			 else if (screen == 3)
	{
		reinit();
		screen = 1;
	}
			 break;
	case 'b':
	case 'B':if (screen == 1)
		screen = 2;
		speed = 0.8;
		break;
	case 'i':
	case 'I':if (screen == 1)
		screen = 2;
		speed = 1.2;
		break;
	case 'e':
	case 'E':if (screen == 1)
		screen = 2;
		speed = 1.5;
		break;
	case 27:
		exit(0);
	}
}

void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 500, 0, 500);
	glMatrixMode(GL_MODELVIEW);
}

void restart()
{
	char gameover[] = "Game Over";
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0, 0, 0, 0);
	glFlush();
	glColor3f(1, 1, 1);
	drawText(gameover, 190, 340, 1);
	glColor3f(0, 0.5, 1);
	drawText(score11, 190, 250);
	sprintf_s(buffer, "%d", score);
	drawTextNum(buffer, 6, 245, 250);

	glColor3f(1, 0.5, 0);
	drawText(dodge, 190, 280);
	sprintf_s(buffer, "%d", score / 20);
	drawTextNum(buffer, 6, 245, 280);

	glColor3f(1, 1, 1);
	char playAgain[] = "To play again, press ";
	drawText(playAgain, 165, 205);
	glColor3f((rand() % 100 + 50) / 100, (rand() % 100 + 50) / 100, (rand() % 100 + 50) / 100);
	drawText(space11, 200, 180);
	glutSwapBuffers();
	//getchar();
}

void display()
{
	if (screen == 0)
	{
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(1, 1, 0);
		glFlush();
		glColor3f(1, 1, 1);
		char gat[] = "GLOBAL ACADEMY OF TECHNOLOGY";
		drawText(gat, 160, 400);
		char twodgame[] = "2D DODGE GAME";
		drawText(twodgame, 180, 280, 1);
		glColor3f(1, 1, 1);
		char continuegame[] = "To continue , press ";
		drawText(continuegame, 180, 205);
		glColor3f((rand() % 100 + 50) / 100, (rand() % 100 + 50) / 100, (rand() % 100 + 50) / 100);
		drawText(space11, 240, 180);
		glutSwapBuffers();
	}
	else if (screen == 1)
	{
		char instructions[] = "INSTRUCTIONS:";
		char aim[] = "The aim of the game is to dodge the obstacles for as long as you can!";
		char controls[] = "CONTROLS:";
		char leftmove1[] = "Use <- to move left";
		char rightmove1[] = "Use -> to move right";
		char levels[] = "LEVELS:";
		char b[] = "B - Beginner";
		char i[] = "I  - Intermediate";
		char e[] = "E - Expert";
		char selection[] = "Select (B,I,E) - ";
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(1, 0.75, 0);
		glFlush();
		drawText(instructions, 30, 440, 1);
		glColor3f(1, 1, 1);
		drawText(aim, 30, 400);
		glColor3f(1, 0.75, 0);
		drawText(controls, 30, 340, 1);
		glColor3f(0, 0.75, 1);
		drawText(leftmove1, 170, 310);
		drawText(rightmove1, 170, 270);
		glColor3f(1, 0.75, 0);
		drawText(levels, 30, 210, 1);
		glColor3f(0, 1, 0.75);
		drawText(b, 170, 190);
		drawText(i, 170, 160);
		drawText(e, 170, 130);
		glColor3f(1, 1, 1);
		drawText(selection, 30, 80, 1);

		glutSwapBuffers();
	}
	else if (screen == 2)
	{

		glClearColor(0.1, 0.4, 0.7, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		drawPath();
		drawUFO();
		drawObject();
		score = score + 1;
		glColor3f(0, 1, 0);

		drawText(score11, 395, 465);
		sprintf_s(buffer, "%d", score);
		drawTextNum(buffer, 6, 450, 465);

		glColor3f(1, 0.5, 0);
		drawText(dodge, 395, 425);
		sprintf_s(buffer, "%d", score / 20);
		drawTextNum(buffer, 6, 450, 425);

		glutSwapBuffers();
		for (q = 0; q <= 10000000; q++) { ; }
		if (collide == true)
		{
			screen = 3;
		}
	}
	else if (screen == 3)
	{

		restart();

	}

}

int main(int argc, char **argv)
{

	srand(time(NULL));
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 500);
	glutCreateWindow("2D Dodge game");
	ovpos();
	init();
	glutDisplayFunc(display);
	glutSpecialFunc(Specialkey);
	glutKeyboardFunc(Normalkey);
	glutIdleFunc(display);
	glutMainLoop();
}
