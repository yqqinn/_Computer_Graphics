#include <cmath>
#include <cstdlib>
#include <iostream>
#include <windows.h>
#include <GL/glut.h>
using namespace std;

GLdouble newMat[4][2] = {0,0, 100,0, 100,100, 0,100};
const GLdouble mat[4][2] = {0,0, 100,0, 100,100, 0,100};

void init() {
    glClearColor( 0.0, 0.0, 0.0, 0.0 );
    glMatrixMode( GL_PROJECTION );
    gluOrtho2D( 0.0, 800.0, 0.0, 600.0 );
}
bool isEqual() {
    for( int i = 0; i < 4; ++i ) {
        if( fabs( mat[i][0] - newMat[i][0] ) >= 1e-6 ) return false;
        if( fabs( mat[i][1] - newMat[i][1] ) >= 1e-6 ) return false;
    }
    return true;
}
void display() {
    glClear( GL_COLOR_BUFFER_BIT );
    glBegin( GL_POLYGON );
        glColor3f( 1.0, 0.0, 0.0 );
        for( int i = 0; i < 4; ++i )
            glVertex2d( mat[i][0], mat[i][1] );
    glEnd();
    glFlush();

    if( !isEqual() ) {
        glBegin( GL_POLYGON );
            glColor3f( 0.0, 1.0, 0.0 ); 
            for( int i = 0; i < 4; ++i )
                glVertex2d( newMat[i][0], newMat[i][1] );
        glEnd();
        glFlush();
    }
}
bool isInner( int x, int y ) {
    unsigned short int c = 0;
    if( x < newMat[0][0] ) c |= 1; c <<= 1;
    if( x > newMat[1][0] ) c |= 1; c <<= 1;
    if( y > newMat[2][1] ) c |= 1; c <<= 1;
    if( y < newMat[0][1] ) c |= 1;
    if( c == 0 ) return true;
    else return false;
}
void mouse_process( int button, int state, int x, int y ) {
    /*
    if( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN ) {
    }
    */
}
void mouse_process_active( int x, int y ) {
    y = 600 - y; 
    if( isInner( x, y ) ) {
        double avgx = ( newMat[0][0] + newMat[1][0] ) / 2.0;
        double avgy = ( newMat[0][1] + newMat[3][1] ) / 2.0;

        double dx = x - avgx;
        double dy = y - avgy;
        for(int i = 0; i < 4; ++i) {
            newMat[i][0] += dx;
            newMat[i][1] += dy;

            if( newMat[i][0] > 800) {
                int dx = newMat[i][0] - 800;
                for(int j = 0; j < 4; ++j)
                    newMat[j][0] -= dx;
                MessageBox( NULL, TEXT("Coordinate out of range"), TEXT("Warning"), MB_ICONWARNING | MB_OK );
                Sleep(1000);
            } else if( newMat[i][0] < 0 ){
                int dx = 0 - newMat[i][0];
                for(int j = 0; j < 4; ++j)
                    newMat[j][0] += dx;
                MessageBox( NULL, TEXT("Coordinate out of range"), TEXT("Warning"), MB_ICONWARNING | MB_OK );
                Sleep(1000);
            } else if( newMat[i][1] > 600 ){
                int dy = newMat[i][1] - 600;
                for(int j = 0; j < 4; ++j)
                    newMat[j][1] -= dy;
                MessageBox( NULL, TEXT("Coordinate out of range"), TEXT("Warning"), MB_ICONWARNING | MB_OK );
                Sleep(1000);
            } else if( newMat[i][1] < 0 ) {
                int dy = 0 - newMat[i][1];
                for(int j = 0; j < 4; ++j)
                    newMat[j][1] += dy;
                MessageBox( NULL, TEXT("Coordinate out of range"), TEXT("Warning"), MB_ICONWARNING | MB_OK );
                Sleep(1000);
            }
        }
        glutPostRedisplay();
    }
}
void mouse_process_passtive( int x, int y ) {}
int main( int argv, char** argc ) {
    glutInit( &argv, argc );
    glutInitDisplayMode( GLUT_SINGLE | GLUT_RGBA );
    glutInitWindowPosition( 100, 100 );
    glutInitWindowSize( 800, 600 );
    glutCreateWindow( "Lab 3" );
    init();

    glutDisplayFunc( display );
    glutMouseFunc( mouse_process );
    glutMotionFunc( mouse_process_active );
    glutPassiveMotionFunc( mouse_process_passtive );

    glutMainLoop();
    return 0;
}

