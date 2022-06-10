#include <stdio.h>
#include <windows.h>
#include <GL/glut.h>
#include <iostream>

int m = 0;
GLdouble m1 =0, m2 = 0;

void bresenham(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2) {
	double dx = x2 - x1-m1;
	double dy = y2 - y1-m2;
	double k = dy / dx;
	double e = 0.5;
	glBegin(GL_POINTS);//��ʾ��һ����
	for (int i = 0;i <= dx;i++) {
		glVertex2f(x1+m1, y1+m2);
		x1 = x1 + 1;
		e = e + k;
		if (e >= 0) {
			y1++;
			e = e - 1;
		}
	}
	glEnd();
}

void halfzd(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2) {
	double a = y1+m2-y2;
	double b = x2-x1-m1;
	double d = a + a + b;
	double d1 = a + a;
	double d2 = a + b + a + b;
	glBegin(GL_POINTS);
	glVertex2f(x1+m1, y1+m2);
	while (x1+m1 < x2) {
		if (d < 0) {
			x1++;y1++;d += d2;
		}
		else {
			x1++;d += d1;
		}
		glVertex2f(x1+m1, y1+m2);
	}
	glEnd();
}

void myDDA(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2) {
	x1 = x1 + m1;
	y1 = y1 + m2;
	double dx = x2 - x1;
	double dy = y2 - y1;
	double steps;
	if (dx > dy)
		steps = dx;
	else
		steps = dy;
	double stepX = dx / steps;
	double stepY = dy / steps;
	glBegin(GL_POINTS);
	for (int i = 0;i < (int)steps;i++) {
		glVertex2f(x1, y1);
		x1 += stepX;
		y1 += stepY;
	}
	glEnd();
}

//���̵������
void myKayBoard(unsigned char key, int x, int y) {//key��Ӧ���������һ����
	switch (key)
	{
	case'z':m = 0;break;
	case'x':m = 1;break;
	case'c':m = 2;break;
	}
	//�ı�ֵ������Ҫʹͼ��������ʾһ��
	glutPostRedisplay();

}

//���������
void mouseMoton(GLint button,GLint state,GLint x,GLint y) {
	//�������
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		m1 = x;
		m2 = y;
		glutPostRedisplay();
	}
	//�����ּ�
	if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {
		m1 = x;
		m2 = y;
		glutPostRedisplay();
	}
	//����ҵ��
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		m1 = x;
		m2 = y;
		glutPostRedisplay();
	}
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);//����ɫˢ��
	glColor3f(0.8, 0.5, 0.6);//���Ƶ���ɫ
	glPointSize(1);//�������صĴ�С
	if (m==0)
		bresenham(1.08,2.00, 373.80,367.66);
	if (m==1)
		halfzd(99.09,120.08,373.80, 367.66);
	if (m==2)
		myDDA(140.7, 200.3, 373.80, 367.66);
	glFlush();
}



void init(void) {
	glClearColor(1.0, 1.0, 1.0, 0.0);//����һ��ˢ�µ���ɫ
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 500, 0, 500);
	//glShadeModel(GL_FLAT);
}

//������
int main(int argc, char** argv) {
	glutInit(&argc, argv);//��ʼ��openGl
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);//��ʾ���ڵ�λ��
	glutInitWindowSize(350, 150);//��ʾ���ڵĴ�С
	glutCreateWindow("ʵ��1");//��ʾ�ü��������н�����

	init();//�Զ���ķ���
	glutDisplayFunc(display);//���ƺ���
	glutKeyboardFunc(myKayBoard);//������̵�ʱ��ͻ���ø÷���
	glutMouseFunc(mouseMoton);//�����ʱ����ø÷���
	glutMainLoop();
	return 0;
}

