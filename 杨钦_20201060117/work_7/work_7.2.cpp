#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

#define N 1000
int ww, hh;
int line[N][4], k = 0;

void Myinit(){
	glClearColor(0,0,0,0);
	glLineWidth(3.0);
}

void Reshape(int w, int h){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0,0,w,h);
	gluOrtho2D(0,w,0,h);        
	ww = w;
	hh = h;
}

void drawlines(){
	for (int i = 0; i <= k; i++)
	{
		glBegin(GL_LINES);
		glVertex2f(line[i][0],line[i][1]);
		glVertex2f(line[i][2],line[i][3]);
		glEnd();
	}
}

void display(void){
	glClear(GL_COLOR_BUFFER_BIT);
	drawlines();
	glutSwapBuffers();

}

void mymouse(int button, int state, int x, int y){

	if(state==GLUT_DOWN && button == GLUT_LEFT_BUTTON){
		line[k][0] = x;
		line[k][1] = hh - y;
	}

	if(state == GLUT_UP && button == GLUT_LEFT_BUTTON){
		line[k][2] = x;
		line[k][3] = hh - y;
		k++;
		glutPostRedisplay();
	}
}

void mymotion(int x, int y){
	line[k][2] = x;
	line[k][3] = hh - y;
	glutPostRedisplay();
}



int main(HINSTANCE hInstance,
						HINSTANCE hPrevInstance,
						LPTSTR lpCmdLine,
						int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	char *argv[] = {"hello ", ""};
	int argc = 2;
	glutInit(&argc, argv);
	glutInitDisplayMode(GL_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800,600);
	glutCreateWindow("��껭ͼ");
	Myinit();
	glutDisplayFunc(display);
	glutMouseFunc(mymouse);
	glutMotionFunc(mymotion);
	glutReshapeFunc(Reshape);
	glutMainLoop();
	return 0;
}

