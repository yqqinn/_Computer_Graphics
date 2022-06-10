#include <string>
#include <windows.h>
#include <assert.h>
#include <cmath>
#include <iostream>
#include <vector>
#include <GL/glut.h>


using namespace std;
typedef vector<int> list;
vector<list>  cs;
int old_x, old_y, new_x, new_y, cx, cy, cr;
int mouse_type;
// draw point
void drawPoint(int x, int y) {
	/* Draw a point */


	//glPointSize(2.0f);
	glBegin(GL_POINTS);
	glColor3f(1.0, 0.0, 0.0);    // Red
	glVertex2i(x, y);
	glEnd();
}



// HomeWork

void Bresenham_Circle(int xc, int yc, int r) {
	int x, y, d;
	x = 0; y = r; d = 5 - 4 * r;
	drawPoint(x + xc, y + yc);
	while (x < y)
	{
		if (d < 0) d = d + 8 * x + 12;
		else {
			d = d + 8 * (x - y) + 20;
			y--;
		}
		x++;
		drawPoint(x + xc, y + yc); drawPoint(y + xc, x + yc);
		drawPoint(y + xc, -x + yc); drawPoint(x + xc, -y + yc);
		drawPoint(-x + xc, -y + yc); drawPoint(-y + xc, -x + yc);
		drawPoint(-x + xc, y + yc); drawPoint(-y + xc, x + yc);
	}
}


void draw() {
	int i;
	for (i = 0; i < cs.size(); ++i)
		Bresenham_Circle(cs[i][0], cs[i][1], cs[i][2]);
	if (mouse_type == 3)
		Bresenham_Circle(cx, cy, cr);
}
void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3i(0, 0, 0);
	draw();
	glutSwapBuffers();
}
void mouseclick(int button, int state, int x, int y) {
	cout << "(" << x << "," << y << ")";
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN) {

			cx = x;
			cy = 600 - y; mouse_type = 3;
		}
		else if (state == GLUT_UP) {
			list l;
			l.push_back(cx);
			l.push_back(cy);
			cr = int(sqrt(double(x - cx) * (x - cx) + (600 - y - cy) * (600 - y - cy)) + 0.5);
			l.push_back(cr);
			cs.push_back(l);
			mouse_type = 2;
			glutPostRedisplay();
			for (int i = 0; i < cs.size(); ++i)
				cout << endl << "circle_" << i << ": " << cs[i][0] << "," << cs[i][1] << " " << cs[i][2];
		}
		break;
	case GLUT_MIDDLE_BUTTON:
		break;
	case GLUT_RIGHT_BUTTON:
		break;
	}
}
void screenmotion(int x, int y) {
	if (mouse_type == 3) {
		cr = int(sqrt(double(x - cx) * (x - cx) + (600 - y - cy) * (600 - y - cy)) + 0.5);
		cout << endl << "new-circle: " << cx << "," << cy << " " << cr << endl;
	}
	glutPostRedisplay();
}
void init() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-1.0, 600, 0.0, 601);
}
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100, 50);
	glutInitWindowSize(600, 600);
	glutCreateWindow("OpenGL");
	init();
	glutDisplayFunc(display);
	glutMotionFunc(screenmotion);
	glutMouseFunc(mouseclick);
	glutMainLoop();
	return 0;
}
