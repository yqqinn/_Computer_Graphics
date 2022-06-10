#include<windows.h>
#include<stdio.h>
#include<math.h>
#include<GL/glut.h>

#define WIDTH    500        
#define HEIGHT    500       
#define DRAWLINE ProBresenham(100,100,400,400);   
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")       

void Init()    
{
    glClearColor(1.0f,1.0f,1.0f,1.0f);  
    glColor3f(1.0f,0.0f,0.0f);    

    glMatrixMode(GL_PROJECTION);           
     gluOrtho2D(0.0, WIDTH, 0.0, HEIGHT);   
 }

 void ProBresenham(int x0,int y0,int x1,int y1)    
 {
    int x,y,dx,dy,e;
     dx = x1-x0;
     dy = y1-y0;
    e = -dx;
    x = x0;
     y = y0;
     while(x<=x1){
         glBegin(GL_POINTS);
         glVertex2i(x,y);
         glEnd();
         x++;
         e = e+2*dy;
         if(e>0){
             y++;
             e = e-2*dx;
         }
     }
 }

 void Display()    
 {
     glClear(GL_COLOR_BUFFER_BIT);   

     DRAWLINE 

     glFlush();   
 }

 int main(int argc,char** argv)
 {
     glutInit(&argc,argv);
     glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);   
     glutInitWindowSize(WIDTH,HEIGHT);    
     glutInitWindowPosition(200,100);  
     glutCreateWindow("��ֱ��");    

     glutDisplayFunc(Display);    
     Init();        
     glutMainLoop();    
     return 0;
 }
