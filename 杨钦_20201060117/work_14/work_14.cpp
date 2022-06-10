
#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

#define    MAXPOINTS    20


int* C;//����ʽϵ������ָ��
int control_points_n = 0;//���Ƶ�����
int specific_p;//�ض����־
int click_state = 0;//0Ϊ�������Ƶ㣬1Ϊ�ƶ����Ƶ㣬2Ϊ�ѵ��׿��Ƶ����ֵ
int screen_width, screen_height;//��Ļ��ȣ�����

struct point
{
    int x;
    int y;
};
point* P;

void reshape(int w, int h);//����Ӧ��Ļ���ڴ�С�ĸı�
void keyboard(unsigned char button, int x, int y);//���ư�������
void mouse_click(int button, int state, int x, int y);//�������click�¼�����
void mouse_motion(int x, int y);//����ڴ����а��²��ƶ�ʱ���ô˺���
void display(void);//��ʾ����,��Ҫ��ʾʱ���ô˺���


//��λ���꺯��
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int main(int argc, char** argv)
{
    P = new point[MAXPOINTS];//���Ƶ�����ָ��

    printf("����\"ESC\"���˳�������\"R\"�����»���\r\n");
    printf("������20����");

    glutInit(&argc, argv);//gult��ʼ��

    /*�ڴ������ڵ�ʱ��ָ������ʾģʽ�����͡�GLUT_DOUBLE����˫����
    ���https://blog.csdn.net/yangyong0717/article/details/78003913*/
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);//��ʼ�����ھ�����Ļ��ߺ������������
    glutInitWindowSize(500, 500);//��ʼ�����ڿ�Ⱥ͸߶�
    glutCreateWindow("B��zier curve");//�������ڣ�"B��zier curve"Ϊ��������

    //�����ɫ������,��ֹ��������ԭ�е���ɫ��ϢӰ�챾�λ�ͼ
    //���https://blog.csdn.net/jennifer111111/article/details/51649153
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_LINE_STIPPLE);//����ֱ�ߵ㻭����
    glutReshapeFunc(reshape);//����Ļ���ڴ�С�ı������reshape����
    glutKeyboardFunc(keyboard);//������ͨ������Ϣ�����https://blog.csdn.net/xie_zi/article/details/1911891
    glutMouseFunc(mouse_click);//�������click�¼�
    glutMotionFunc(mouse_motion);//������ڴ����а��²��ƶ�ʱ����glutMotionFuncע��Ļص�����
    glutDisplayFunc(display);//���������ݱ�����ʱ����display����
    glutMainLoop();//����gult��ѭ��

    delete[] P;
    return 1;
}

//�������Σ�������ǵ�
void Draw_Square(int x, int y)
{
    glColor3f(0, 1, 0);//������ɫ�����������ֱ����red, green, blue
    glBegin(GL_POLYGON);//������һ��͹����Ρ�����1��n�������������Ρ�
    glVertex2f(x + 2, y + 2);
    glVertex2f(x - 2, y + 2);
    glVertex2f(x - 2, y - 2);
    glVertex2f(x + 2, y - 2);
    glEnd();
}

/*�������ʽϵ��
* nΪ������CΪ��Ŷ���ʽϵ��������
* ������C(n-k)(n)=C(k)(n)
* ��C[k] = C(k)(n),k�����Ͻǣ�n�����½ǣ���֪����ô���Ǹ����š�����*/
void Culculate_Binomial_Coefficient(int n, int* C)
{
    int k, j;

    for (k = 0;k <= n;k++)
    {
        C[k] = 1;
        for (j = n;j >= k + 1;j--)//1*n*(n-1)*(n-2)*...*(k+2)*(k+1)
        {
            C[k] *= j;
        }
        for (j = n-k;j >= 2;j--)//��ʽ / ( (n-k)*(n-k-1)*...*3*2*1 )
        {
            C[k] /= j;
        }
    }
}

//������������
//nΪά�ȣ������Ƶ�����1����pΪ���Ƶ����飬mΪ�ܶ�
void Bezier_curve(int n, point* p, int m)
{
    int i, j;
    float t;
    int C[MAXPOINTS - 1];//����ʽϵ�����顣����������Щ�˷ѿռ䣬����֪�����õİ취

   //����������߹켣��x���ꡣ��float�����int�����߻��ƽ��
    float Bezier_curve_pointx;
    float Bezier_curve_pointy;

    Culculate_Binomial_Coefficient(n, C);
    glLineStipple(1, 0xffff);//����Ϊʵ��
    glBegin(GL_LINE_STRIP);
    //����ʵ�����ǻ���m����ֱ�����ӽ�����������
    for (i = 0;i <= m;i++)
    {
        t = (float)i / (float)m;
        Bezier_curve_pointx = 0;
        Bezier_curve_pointy = 0;
        for (j = 0;j < control_points_n;j++)
        {
            Bezier_curve_pointx += C[j] * pow(1 - t, control_points_n - j - 1) * pow(t, j) * p[j].x;
            Bezier_curve_pointy += C[j] * pow(1 - t, control_points_n - j - 1) * pow(t, j) * p[j].y;
        }
        glVertex2f(Bezier_curve_pointx, Bezier_curve_pointy);
    }
    glEnd();
}

//����Ӧ��Ļ���ڴ�С�ĸı�
//����reshape�������Բο�https://blog.csdn.net/qq_41856733/article/details/85309521
void reshape(int w, int h)
{
    screen_width = w;
    screen_height = h;

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, w, 0.0, h);
}

//���ư�������
void keyboard(unsigned char button, int x, int y)
{
    switch (button)
    {
    case 82://"R"
    case 114://"r"
        //���»�ͼ
        //���֮ǰ��ʾ������
        gotoxy(0, 3);
        for (int i = 0;i < control_points_n;i++)
        {
            printf("                   \r\n");
        }

        specific_p = control_points_n = 0;
        click_state = 0;

        /*glutPostRedisplay����������ǵ�ǰ������Ҫ���»��ơ�ͨ��glutMainLoop
        * ��һ��ѭ��ʱ��������ʾ�����ص���������ʾ���ڵ��������*/
        glutPostRedisplay();
        break;
    case 27://"ESC"
        exit(0);//�˳�glutѭ��
    }
}

/*
* �������click�¼�����
* button�����ĸ����������»��ɿ�,�ڶ��������������������÷���ʱ����
* ״̬�����»��ɿ�����x,y��ʾ����ڵ�ǰ���ڵ����꣨�����Ͻ�Ϊԭ�㣩
*/
void mouse_click(int button, int state, int x, int y)
{
    int i;
    int distance;//�������������һ�����

    //�������������
    if (button == GLUT_LEFT_BUTTON)
    {
        //�����ƶ�״̬ʱ�������
        if (state == GLUT_DOWN && click_state != 1)
        {
            for (i = 0;i < control_points_n;i++)
            {
                //�����Ƶ����μ������
                distance = (x - P[i].x) * (x - P[i].x) +
                    (screen_height - y - P[i].y) * (screen_height - y - P[i].y);
                if (distance < 15)//�������С���ض�ֵ
                {
                    click_state = 1;//����״̬1�����ƶ���
                    specific_p = i;
                    break;//����ѭ��
                }
            }
        }

        if (state == GLUT_DOWN && click_state == 0)//������
        {
            if (control_points_n < MAXPOINTS)
            {
                P[control_points_n].x = x;
                P[control_points_n].y = screen_height - y;
                specific_p = control_points_n;
                control_points_n++;
                glutPostRedisplay();
            }
            else click_state = 2;//����״̬2���޷��������Ƶ�
        }
        else if (state == GLUT_DOWN && click_state == 1)//�ƶ���
        {
            P[specific_p].x = x;
            P[specific_p].y = screen_height - y;
            glutPostRedisplay();
        }
        else if (state == GLUT_UP)
        {
            //�жϿ��Ƶ��Ƿ��Ѵ�����
            click_state = control_points_n < MAXPOINTS ? 0 : 2;
        }
    }
}

//����ڴ����а��²��ƶ�ʱ���ô˺���
void mouse_motion(int x, int y)
{
    if (click_state == 1)
    {
        P[specific_p].x = x;
        P[specific_p].y = screen_height - y;
        glutPostRedisplay();
    }
}

//��ʾ����,��Ҫ��ʾʱ���ô˺���
void display(void)
{
    int i;

    glClear(GL_COLOR_BUFFER_BIT);//�建�档GL_COLOR_BUFFER_BIT����ǰ��д����ɫ����

    for (i = 0;i < control_points_n;i++)//�����Ƶ�
    {
        Draw_Square(P[i].x, P[i].y);
    }
    //��ʾ���Ƶ�����
    gotoxy(0, specific_p + 3);
    printf("P%d:(%d, %d)  ", specific_p, P[specific_p].x, P[specific_p].y);

    //0x0f0f��0000 1111 0000 1111�����ڰ׵ȳ�������
    //glLineStipple�������https://blog.csdn.net/oktears/article/details/42262187
    glLineStipple(1, 0x0f0f);
    glBegin(GL_LINE_STRIP);//����ֱ�ߵ㻭����
    glColor3f(1, 1, 1);//������ɫ�����������ֱ����red, green, blue
    for (i = 0;i < control_points_n;i++)//������
    {
        glVertex2f(P[i].x, P[i].y);
    }
    glEnd();

    if (control_points_n > 1)//�д���1�����Ƶ�ͻ�������������
    {
        Bezier_curve(control_points_n - 1, P, 200);
    }

    //�������https://blog.csdn.net/u012442207/article/details/45223261
    glutSwapBuffers();//��������������ָ��
}



