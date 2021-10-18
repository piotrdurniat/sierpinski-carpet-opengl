#include <iostream>
#include <ctime>
#include <string>
#include <math.h>
#include <GL/glut.h>

int width, height;
int windowHandle;
const float deformation = 0.0;
const bool color = false;
int iterations = 5;
int carpetWidth = 200;

float randomDeformation(GLdouble width)
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

void drawSquare(GLdouble x, GLdouble y, GLdouble width)
{
	glBegin(GL_POLYGON);

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
	glVertex2f(x + width, y + width);

	setRandomColor();
	x += randomDeformation(width);
	y += randomDeformation(width);
	glVertex2f(x, y + width);

	glEnd();
}

void sierpinskiCarpet(GLdouble x, GLdouble y, GLdouble width, int iterations)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (i == 1 && j == i)
				continue;

			GLdouble squareW = width / 3.0;
			GLdouble squareX = x + squareW * i;
			GLdouble squareY = y + squareW * j;

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


	sierpinskiCarpet(0, 0, carpetWidth, iterations);

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
	for (int i = 1; i < argc; ++i)
	{
		std::string flag = argv[i];

		i++;
		if (i >= argc)
		{
			std::cerr << flag << " requires one argument.\n";
			return 1;
		}

		if (flag == "--width")
		{
			carpetWidth = std::stoi(argv[i]);
			width = carpetWidth;
			height = carpetWidth;
		}
		else if (flag == "--iterations")
		{
			iterations = std::stoi(argv[i]);

			if (iterations < 1)
			{
				std::cerr << "Number of iterations must be greater than 0";
				return 1;
			}
		}
	}

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize((int)width, (int)height);

	glEnable(GL_SMOOTH);


	windowHandle = glutCreateWindow("Sierpinski Carpet in OpenGL and GLUT");

	glutReshapeFunc(reshape);
	glutDisplayFunc(display);

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glLineWidth(3.0);

	glutMainLoop();

	exit(0);
}
