#include<windows.h>
#include<GL/glut.h>
#include<iostream>
#include<math.h>

void myDisplay(void);
void setPixel(int x,int y);
int round(const float a);
void ChangeSize(GLsizei w, GLsizei h);
void lineBres(int x0,int y0,int xEnd,int yEnd);

void myDisplay(void){
	lineBres(50,50,200,200);
}

void setPixel(int x,int y){
	glPointSize(5.0f);
	glBegin(GL_POINTS);
		glVertex2i(x,y);
	glEnd();
	glFlush();
}

int round(const float a){
	return int(a+0.5);
}

void ChangeSize(GLsizei w, GLsizei h){
    if(h==0)
		h=1;
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(0.0f,250.0f,0.0f,250.0f*h/w,1.0,-1.0);
    else
        glOrtho(0.0f,250.0f*w/h,0.0f,250.0f,1.0,-1.0);
}

void lineBres(int x0,int y0,int xEnd,int yEnd){
	glPointSize(3.0f);
	int dx=xEnd-x0,dy=yEnd-y0;
	int p=2*dy-dx;//p0
	int twoDy=2*dy,twoDyMinusDx=2*(dy-dx);
	int x,y;
	if(x0>xEnd){
		x=xEnd;
		y=yEnd;
		xEnd=x0;
	}
	else{
		x=x0;
		y=y0;
	}
	setPixel(x,y);
	while(x<xEnd){
		x++;
		if(p<0)
			p+=twoDy;
		else{
			y++;
			p+=twoDyMinusDx;
		}
		setPixel(x,y);
	}
}

int main(int argc,char* argv[]){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
	glutInitWindowPosition(200,200);
	glutInitWindowSize(400,400);
	glutCreateWindow("Daily Practice");
	glutDisplayFunc(&myDisplay);
	glutReshapeFunc(ChangeSize);
	glutMainLoop();
	return 0;
}

