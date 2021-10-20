#ifdef _WIN32
#include <windows.h>
#endif

#include <iostream>
#include <ctime>
#include <string>
#include <math.h>
#include <GL/gl.h>
#include <GL/glut.h>

int carpetWidth = 728;
int width = carpetWidth;
int height = carpetWidth;
float deformation = 0.0;
bool color = false;
int iterations = 6;

int intPow(int base, int exp)
{
	int result = 1;
	while (true)
	{
		if (exp & 1)
			result *= base;
		exp >>= 1;
		if (!exp)
			break;
		base *= base;
	}

	return result;
}

float randomFloat(float LO, float HI)
{
	return LO + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (HI - LO)));
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

/**
 * Adds a random value between -width and width to x and y
 * Sets a random color
 */
void setRandomParameters(GLdouble &x, GLdouble &y, GLdouble width)
{
	setRandomColor();
	x += randomFloat(-width * deformation, width * deformation);
	y += randomFloat(-width * deformation, width * deformation);
}

void drawSquare(GLdouble x, GLdouble y, GLdouble width)
{
	glBegin(GL_POLYGON);

	x = x - 1.0;
	y = y - 1.0;

	setRandomParameters(x, y, width);
	glVertex2f(x, y);

	setRandomParameters(x, y, width);
	glVertex2f(x + width, y);

	setRandomParameters(x, y, width);
	glVertex2f(x + width, y + width);

	setRandomParameters(x, y, width);
	glVertex2f(x, y + width);

	glEnd();
}

void sierpinskiCarpet(int x, int y, GLdouble width, int currentIteration, int iterations)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (i == 1 && j == i)
				continue;

			int step = intPow(3, (iterations - currentIteration));
			int newX = x + i * step;
			int newY = y + j * step;

			if (currentIteration == iterations)
			{
				GLdouble squareW = 2.0 / intPow(3, iterations);
				GLdouble squareX = newX * squareW;
				GLdouble squareY = newY * squareW;

				drawSquare(squareX, squareY, squareW);
			}
			else
			{
				sierpinskiCarpet(newX, newY, width, currentIteration + 1, iterations);
			}
		}
	}
}

void sierpinskiCarpet(int x, int y, int width, int iterations)
{
	sierpinskiCarpet(x, y, width, 1, iterations);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	sierpinskiCarpet(0, 0, carpetWidth, 1, iterations);
	glFlush();
	return;
}

int main(int argc, char *argv[])
{
	for (int i = 1; i < argc; ++i)
	{
		std::string flag = argv[i];

		if (flag == "--color")
		{
			color = true;
			continue;
		}
		else if (flag == "--help" || flag == "-h")
		{
			std::cout << "Available flags: \n"
					  << "    --color - Draws the quadrilaterals on the carpet using random colors\n"
					  << "    -h or -help - Prints the available flags\n"
					  << "    --width <number> - Sets the carpet width to the specified number\n"
					  << "    --iterations <number> - Sets the number of iterations used for drawing the carpet\n";
			return 0;
		}

		i++;

		if (i >= argc)
		{
			std::cerr << flag << " flag requires one argument.\n";
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
		else if (flag == "--deformation")
		{
			deformation = std::stof(argv[i]);

			if (deformation<0.0 | deformation> 1.0)
			{
				std::cerr << "Deformation value must be between 0.0 and 1.0";
			}
		}
	}

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize((int)width, (int)height);

	glutCreateWindow("Sierpinski Carpet in OpenGL and GLUT");
	glutDisplayFunc(display);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glutMainLoop();
	exit(0);
}
