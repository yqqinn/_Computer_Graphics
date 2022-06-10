
#include <stdio.h>
#include <windows.h>
#include <GL/glut.h>
#include <iostream>

float a = 0.0;
float b = 0.0;

float A = 0.0;
float D = 0.0;
float Q = 0.0;


float c = 1.0;
float d = 1.0;
float z = 1.0;


void drawBox() {
	glBegin(GL_QUADS);

	glColor3f(1.0, 1.0, 1.0);
	// FRONT
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);

	// BACK
	glVertex3f(-0.5, -0.5, -0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(0.5, -0.5, -0.5);

	glColor3f(0.0, 1.0, 1.0);//��ɫ
	// LEFT
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	// RIGHT
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, -0.5, 0.5);

	glColor3f(1.0, 1.0, 0.0);//��ɫ
	// TOP
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	// BOTTOM
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glEnd();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	gluLookAt(
		0.0, 0.0, 5.0,
		0.0, 0.0, 0.0,
		0.0, 1.0, 0.0);

	glTranslatef( a, 0.0, 0.0);//ƽ�ƺ���
	glTranslatef( 0.0, b, 0.0);

	glRotatef(A, 1.0, 0.0, 0.0);//��ת����
	glRotatef(D, 0.0, 1.0, 0.0);
	glRotatef(Q, 0.0, 0.0, 1.0);

	glScalef(c, 1.0 , 1.0);//���ź���
	glScalef(1.0, d , 1.0);
	glScalef(1.0, 1.0 , z);

	drawBox();
	glFlush();
	glutSwapBuffers();
}

void SpecialKeys(GLint key, GLint x, GLint y) {
	if (key == GLUT_KEY_UP)
	{
		b += 0.1;
	}
	if (key == GLUT_KEY_LEFT)
	{
		a -= 0.1;
	}
	if (key == GLUT_KEY_DOWN)
	{
		b -= 0.1;
	}
	if (key == GLUT_KEY_RIGHT)
	{
		a += 0.1;
	}
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
	switch (key)
	{
	case 'W'://��ת
	case 'w':
		A -= 10;
		break;
	case 'S':
	case 's':
		A += 10;
		break;
	case 'A':
	case 'a':
		D -= 10;
		break;
	case 'D':
	case 'd':
		D += 10;
		break;
	case 'Q':
	case 'q':
		Q += 10;
		break;
	case 'E':
	case 'e':
		Q -= 10;
		break;
		//����
	case '4':
		c += 0.1;
		break;
	case '6':
		c -= 0.1;
		break;
	case '8':
		z += 0.1;
		break;
	case '2':
		z -= 0.1;
		break;
	case '1':
		d += 0.1;
		break;
	case '3':
		d -= 0.1;
		break;
	}
	glutPostRedisplay();
}

void resize(int w, int h) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(45.0f, 1.0f * w / h, 1.0f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);

	glutInitWindowPosition(50, 50);
	glutInitWindowSize(1000, 1000);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

	int main = glutCreateWindow("ͼ�α任");
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(SpecialKeys);

	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glEnable(GL_DEPTH_TEST);

	glutMainLoop();
	return 0;
}


