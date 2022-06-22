#include <GL/glut.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma comment(lib,"glew32.lib")

using namespace std;

GLfloat lightPosition[3] = { 30.0,30.0,30.0 };
GLfloat ambient[4] = { 0.0 , 0.0 , 1.0 , 1.0 };
GLfloat lightcolor[4] = { 1.0 , 1.0 , 1.0 , 1.0 };
GLfloat eyeposition[3] = { 0.0 , 10.0 , 30.0 };
GLfloat Ns = 30;
GLfloat attenuation = 0.01;
GLfloat objectSize = 15.0;
GLuint programHandle;
GLuint vShader, fShader;

//�����ַ���
char *textFileRead(const char *fn)
{
	FILE *fp;
	char *content = NULL;
	int count = 0;
	if (fn != NULL)
	{
		fp = fopen(fn, "rt");
		if (fp != NULL)
		{
			fseek(fp, 0, SEEK_END);
			count = ftell(fp);
			rewind(fp);
			if (count > 0)
			{
				content = (char *)malloc(sizeof(char) * (count + 1));
				count = fread(content, sizeof(char), count, fp);
				content[count] = '\0';
			}
			fclose(fp);
		}
	}
	return content;
}

void initShader(const char *VShaderFile, const char *FShaderFile)
{
	//1���鿴�Կ���GLSL��OpenGL����Ϣ
	const GLubyte *vendor = glGetString(GL_VENDOR);
	const GLubyte *renderer = glGetString(GL_RENDERER);
	const GLubyte *version = glGetString(GL_VERSION);
	const GLubyte *glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
	cout << "�Կ���Ӧ��   : " << vendor << endl;
	cout << "�Կ��ͺ�     : " << renderer << endl;
	cout << "OpenGL�汾   : " << version << endl;
	cout << "GLSL�汾     : " << glslVersion << endl;
	//2��������ɫ��
	//������ɫ�����󣺶�����ɫ��
	vShader = glCreateShader(GL_VERTEX_SHADER);
	//������
	if (0 == vShader)
	{
		cerr << "ERROR : Create vertex shader failed" << endl;
		exit(1);
	}
	//����ɫ��Դ�������ɫ�����������
	const GLchar *vShaderCode = textFileRead(VShaderFile);
	const GLchar *vCodeArray[1] = { vShaderCode };

	//���ַ�����󶨵���Ӧ����ɫ��������
	glShaderSource(vShader, 1, vCodeArray, NULL);

	//������ɫ������
	glCompileShader(vShader);

	//�������Ƿ�ɹ�
	GLint compileResult;
	glGetShaderiv(vShader, GL_COMPILE_STATUS, &compileResult);
	if (GL_FALSE == compileResult)
	{
		GLint logLen;
		//�õ�������־����
		glGetShaderiv(vShader, GL_INFO_LOG_LENGTH, &logLen);
		if (logLen > 0)
		{
			char *log = (char *)malloc(logLen);
			GLsizei written;
			//�õ���־��Ϣ�����
			glGetShaderInfoLog(vShader, logLen, &written, log);
			cerr << "vertex shader compile log : " << endl;
			cerr << log << endl;
			free(log);//�ͷſռ�
		}
	}

	//������ɫ������Ƭ����ɫ��
	fShader = glCreateShader(GL_FRAGMENT_SHADER);
	//������
	if (0 == fShader)
	{
		cerr << "ERROR : Create fragment shader failed" << endl;
		exit(1);
	}

	//����ɫ��Դ�������ɫ�����������
	const GLchar *fShaderCode = textFileRead(FShaderFile);
	const GLchar *fCodeArray[1] = { fShaderCode };
	glShaderSource(fShader, 1, fCodeArray, NULL);

	//������ɫ������
	glCompileShader(fShader);

	//�������Ƿ�ɹ�
	glGetShaderiv(fShader, GL_COMPILE_STATUS, &compileResult);
	if (GL_FALSE == compileResult)
	{
		GLint logLen;
		//�õ�������־����
		glGetShaderiv(fShader, GL_INFO_LOG_LENGTH, &logLen);
		if (logLen > 0)
		{
			char *log = (char *)malloc(logLen);
			GLsizei written;
			//�õ���־��Ϣ�����
			glGetShaderInfoLog(fShader, logLen, &written, log);
			cerr << "fragment shader compile log : " << endl;
			cerr << log << endl;
			free(log);//�ͷſռ�
		}
	}
	//3��������ɫ������
	//������ɫ������
	programHandle = glCreateProgram();
	if (!programHandle)
	{
		cerr << "ERROR : create program failed" << endl;
		exit(1);
	}
	//����ɫ���������ӵ��������ĳ�����
	glAttachShader(programHandle, vShader);
	glAttachShader(programHandle, fShader);
	//����Щ�������ӳ�һ����ִ�г���
	glLinkProgram(programHandle);
	//��ѯ���ӵĽ��
	GLint linkStatus;
	glGetProgramiv(programHandle, GL_LINK_STATUS, &linkStatus);
	if (GL_FALSE == linkStatus)
	{
		cerr << "ERROR : link shader program failed" << endl;
		GLint logLen;
		glGetProgramiv(programHandle, GL_INFO_LOG_LENGTH,
			&logLen);
		if (logLen > 0)
		{
			char *log = (char *)malloc(logLen);
			GLsizei written;
			glGetProgramInfoLog(programHandle, logLen,
				&written, log);
			cerr << "Program log : " << endl;
			cerr << log << endl;
		}
	}
}

//���glew��ʼ���ͼ��ض��㡢Ƭ����ɫ��
void init()
{
	//��ʼ��glew��չ��
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		cout << "Error initializing GLEW: " << glewGetErrorString(err) << endl;
	}
	glEnable(GL_DEPTH_TEST);
	//���ض����Ƭ����ɫ���������ӵ�һ�����������
	initShader("VertexShader.txt", "FragmentShader.txt");

	glClearColor(0.0, 0.0, 0.0, 0.0);
}

void Reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, 1, 0.1, 1000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eyeposition[0], eyeposition[1], eyeposition[2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glUseProgram(programHandle);
	glUniform3f(glGetUniformLocation(programHandle, "lightposition"), lightPosition[0], lightPosition[1], lightPosition[2]);
	glUniform3f(glGetUniformLocation(programHandle, "eyeposition"), eyeposition[0], eyeposition[1], eyeposition[2]);
	glUniform4f(glGetUniformLocation(programHandle, "ambient"), ambient[0], ambient[1], ambient[2], ambient[3]);
	glUniform4f(glGetUniformLocation(programHandle, "lightcolor"), lightcolor[0], lightcolor[1], lightcolor[2], lightcolor[3]);
	glUniform1f(glGetUniformLocation(programHandle, "Ns"), Ns);
	glUniform1f(glGetUniformLocation(programHandle, "attenuation"), attenuation);

	glutSolidTeapot(objectSize);
	//glutSolidSphere(objectSize-3, 100, 100);
	glutSwapBuffers();
}

void SpecialKey(GLint key, GLint x, GLint y)
{
	if (key == GLUT_KEY_UP)
	{
		//do something
	}
	display();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Hello GLSL");
	init();
	glutReshapeFunc(Reshape);
	glutDisplayFunc(display);
	glutSpecialFunc(SpecialKey);
	glutMainLoop();
	return 0;
}
