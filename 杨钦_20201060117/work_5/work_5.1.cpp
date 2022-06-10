#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

class screenPt
{
private:
	GLint x, y;
public:
	screenPt()
	{
		x = y = 0;
	}
	void setCoords(GLint xCoordValue, GLint yCoordValue)
	{
		x = xCoordValue;
		y = yCoordValue;
	}
	GLint getx() const
	{
		return x;
	}
	GLint gety() const
	{
		return y;
	}
	void incrementx()
	{
		x++;
	}
	void decrementy()
	{
		y--;
	}
};

void setPixel(GLint x, GLint y)
{
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_POINTS);

	glVertex2i(x, y);

	glEnd();
	glFlush();
}
void circleMidpoint(GLint xc, GLint yc, GLint radius)
{
	screenPt circPt;
	GLint p = 1 - radius;
	circPt.setCoords(0, radius);

	void circlePlotPoints(GLint xc, GLint yc, screenPt circPt);

	circlePlotPoints(xc, yc, circPt);
	while (circPt.getx() < circPt.gety())
	{
		circPt.incrementx();
		if (p < 0)
			p += 2 * circPt.getx() + 1;
		else
		{
			circPt.decrementy();
			p += 2 * (circPt.getx() - circPt.gety()) + 1;
		}
		circlePlotPoints(xc, yc, circPt);
	}
}
void circlePlotPoints(GLint xc, GLint yc, screenPt circPt)
{
	setPixel(xc + circPt.getx(), yc + circPt.gety());
	setPixel(xc - circPt.getx(), yc + circPt.gety());
	setPixel(xc + circPt.getx(), yc - circPt.gety());
	setPixel(xc - circPt.getx(), yc - circPt.gety());
	setPixel(xc + circPt.gety(), yc + circPt.getx());
	setPixel(xc - circPt.gety(), yc + circPt.getx());
	setPixel(xc + circPt.gety(), yc - circPt.getx());
	setPixel(xc - circPt.gety(), yc - circPt.getx());
}


void init(void)
{

	glClearColor(1.0, 1.0, 1.0, 0.0);

	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 400.0, 0.0, 300.0);
}

void lineSegment(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);

	glBegin(GL_LINES);
	glVertex2i(50, 100);
	glEnd();

	circleMidpoint(100, 100, 50);

	glFlush();
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 100);
	glutInitWindowSize(400, 300);

	glutCreateWindow("my first opengl window");
	init();
	glutDisplayFunc(lineSegment);
	glutMainLoop();
}




