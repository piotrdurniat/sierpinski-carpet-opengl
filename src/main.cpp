#include <stdio.h>
#include <stdlib.h>
#include <ctime>

#include <GL/glut.h>

GLdouble width, height;
int windowHandle;
const float deformation = 0.0;
const bool color = false;

void init(void)
{
	width = 800.0;
	height = 800.0;
	return;
}

float randomDeformation(float width)
{
	if (deformation == 0)
		return 0.0;
	float maxDeformation = width * deformation;
	return maxDeformation / 2 - rand() % int(maxDeformation);
}

void setRandomColor()
{
	int r = 255;
	int g = 255;
	int b = 255;

	if (color == true)
	{
		r = rand() % 255;
		g = rand() % 255;
		b = rand() % 255;
	}
	glColor3ub(r, g, b);
}

void drawSquare(float x, float y, float width)
{
	glBegin(GL_TRIANGLE_STRIP);

	setRandomColor();
	x += randomDeformation(width);
	y += randomDeformation(width);
	glVertex2f(x, y);

	setRandomColor();
	x += randomDeformation(width);
	y += randomDeformation(width);
	glVertex2f(x + width, y);

	setRandomColor();
	x += randomDeformation(width);
	y += randomDeformation(width);
	glVertex2f(x, y + width);

	setRandomColor();
	x += randomDeformation(width);
	y += randomDeformation(width);
	glVertex2f(x + width, y + width);

	glEnd();
}

void sierpinskiCarpet(float x, float y, float width, float iterations)
{

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (i == 1 && j == i)
				continue;

			float squareW = width / 3;
			float squareX = x + squareW * i;
			float squareY = y + squareW * j;

			if (iterations == 0)
			{
				drawSquare(squareX, squareY, squareW);
			}
			else
			{
				sierpinskiCarpet(squareX, squareY, squareW, iterations - 1);
			}
		}
	}
}

void display(void)
{
	int i;

	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_LINES);

	const int iterations = 5;

	sierpinskiCarpet(0, 0, 800.0f, iterations);

	glEnd();
	glFlush();

	return;
}

void reshape(int w, int h)
{
	width = (GLdouble)w;
	height = (GLdouble)h;

	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, width, 0.0, height, -1.f, 1.f);

	return;
}

int main(int argc, char *argv[])
{
	init();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize((int)width, (int)height);

	windowHandle = glutCreateWindow("Sierpinski Carpet in OpenGL and GLUT");

	glutReshapeFunc(reshape);
	glutDisplayFunc(display);

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glLineWidth(3.0);

	glutMainLoop();

	exit(0);
}
