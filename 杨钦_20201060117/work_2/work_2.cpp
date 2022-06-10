#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#include<iostream>

typedef struct {
	int x,y;
}point;
void init()
{
	glClearColor(1.0f,1.0f,1.0f,1.0f);
    //glMatrixMode(GL_PROJECTION);
	//gluOrtho2D(-250.0, 250.0, -250.0, 250.0);
}
int LineMidPoint(int x0,int y0,int x1,int y1,point pixels[])
{
    using namespace std;
	int num,x,y,dx,dy;
	int a,b,d;
	float k;
	dx = x1-x0;
	dy = y1-y0;
	//cout<<"dy is "<<dy<<endl
    //    <<"dx is "<<dx<<endl;
	if(dy == 0)
        k=dx;
    else
        k = (float)dy/dx;
	num = 0;
	/*cout<<"k is "<<k<<endl
        <<"x0 is "<<x0<<endl
        <<"x1 is "<<x1<<endl
        <<"y0 is "<<y0<<endl
        <<"y1 is "<<y1<<endl
        <<"k should be"<<dy/dx<<endl;*/
	if(dx>0)
    {
        a=-dy;
        b=dx;
    }
    else
    {
        a=dy;
        b=-dx;
    }

	if(dx==0) //��ֱ��
	{
		for(y=y0;y<=y1;y++)
		{
			pixels[num].x = x0;
			pixels[num].y = y;
			num ++;
		}

	}
	else if(dy==0)
	{
		for(x=x0;x<=x1;x++)
		{
			pixels[num].x = x;
			pixels[num].y = y0;
			num ++;
		}
	}
	else if(k<=1&&k>0)
	{
	    x = x0;
		y = y0;
		d = 2*a+b;
		pixels[num].x = x0;
        pixels[num].y = y0;
        num ++;
		for(x=x0;x<x1;x++)
		{

		    if(d>=0){
                pixels[num].x = x+1;
                pixels[num].y = y;
                num ++;

                d+=2*a;
		    }
			else
            {
                pixels[num].x = x+1;
                pixels[num].y = y+1;
                num ++;
                //cout<<"I'm here "<<endl;
                y++;
                d+=2*a+2*b;
            }

		}
	}
	else if(k>1)
	{
		x = x0;
		y = y0;
		d = a+2*b;
		pixels[num].x = x0;
        pixels[num].y = y0;
        num ++;
		for(y=y0;y<y1;y++)
		{

		    if(d>0){
                pixels[num].x = x+1;
                pixels[num].y = y+1;
                num ++;
                x++;

                d+=2*a+2*b;
		    }
			else
            {
                pixels[num].x = x;
                pixels[num].y = y+1;
                num ++;


                d+=2*b;
            }

		}
	}
    else if(k<0&&k>=-1)
	{
	    x = x0;
		y = y0;
		d = 2*a-b;
		pixels[num].x = x0;
        pixels[num].y = y0;
        num ++;
		for(x=x0;x<x1;x++)
		{

		    if(d>=0){
                pixels[num].x = x+1;
                pixels[num].y = y-1;
                num ++;

                y--;
                d+=2*a-2*b;
		    }
			else
            {
                pixels[num].x = x+1;
                pixels[num].y = y;
                num ++;


                d+=2*a;
            }

		}
	}
	else
    {
        x = x0;
		y = y0;
		d = a-2*b;
		pixels[num].x = x0;
        pixels[num].y = y0;
        num ++;
		for(y=y0;y>y1;y--)
		{

		    if(d>0){
                pixels[num].x = x;
                pixels[num].y = y-1;
                num ++;


                d-=2*b;
		    }
			else
            {
                pixels[num].x = x+1;
                pixels[num].y = y-1;
                num ++;
                x++;

                d+=2*a-2*b;
            }

		}
    }
	return num;
}



void drawLine(int x1,int y1,int x2,int y2)
{
	point pixels[1000];
	int num;
	int i;
	num = LineMidPoint(x1,y1,x2,y2,pixels);
	glBegin(GL_POINTS);
		for(i=0;i<num;i++)
			glVertex2d(pixels[i].x,pixels[i].y);
	glEnd();
}



void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0f,0.0f,0.f);
	drawLine(0,-50,0,50);
	glFlush();
}

void ChangeSize(GLsizei w,GLsizei h)
{
	GLfloat aspectRatio;
	if(h==0)
		h = 1;
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	aspectRatio = (GLfloat)w/(GLfloat)h;
	if(w<=h)
		glOrtho(-100.0,100.0,-100.0/aspectRatio,100.0/aspectRatio,1.0,-1.0);
	else
		glOrtho(-100.0*aspectRatio,100.0*aspectRatio,-100.0,100.0,1.0,-1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main()
{

	glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
	glutCreateWindow("My_MidPointLine");

	init();

	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);

	glutMainLoop();
	return 0;
}

