#include <iostream>
#include <random>
#include <gl/glew.h> // �ʿ��� ������� include
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
float a = 1;
float b = 1;
float c = 1;
int start = 1;
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution <float> random_float(0.f, 1.f);



void main(int argc, char** argv) //--- ������ ����ϰ� �ݹ��Լ� ����
{
	//--- ������ �����ϱ�
	glutInit(&argc, argv); // glut �ʱ�ȭ
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // ���÷��� ��� ����
	glutInitWindowPosition(0, 0); // �������� ��ġ ����
	glutInitWindowSize(800, 600); // �������� ũ�� ����
	glutCreateWindow("Example1"); // ������ ����(������ �̸�)
	//--- GLEW �ʱ�ȭ�ϱ�
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) // glew �ʱ�ȭ
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n";
	glutDisplayFunc(drawScene); // ��� �ݹ��Լ��� ����
	glutReshapeFunc(Reshape); // �ٽ� �׸��� �ݹ��Լ� ����
	glutKeyboardFunc(Keyboard); // Ű���� �Է� �ݹ��Լ� ����
	glutMainLoop(); // �̺�Ʈ ó�� ����
}
GLvoid drawScene() //--- �ݹ� �Լ�: �׸��� �ݹ� �Լ�
{
	//--- ����� ���� ����
	glClearColor(a, b, c, 1.0f); //--- �������� ����
	glClear(GL_COLOR_BUFFER_BIT); //--- ������ ������ ��ü�� ĥ�ϱ�
	glutSwapBuffers(); //--- ȭ�鿡 ����ϱ�
}
GLvoid Reshape(int w, int h) //--- �ݹ� �Լ�: �ٽ� �׸��� �ݹ� �Լ�
{
	glViewport(0, 0, w, h);
}
GLvoid TimerFunction(int value)
{
	a = random_float(gen);
	b = random_float(gen);
	c = random_float(gen);
	glutPostRedisplay();
	if (start == 0) {
		glutTimerFunc(100, TimerFunction, 1);
	}
}
GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'c':
		a = 0;
		b = 1;
		c = 1;
		break; //--- ������ û�ϻ����� ����
	case 'm':
		a = 1;
		b = 0;
		c = 1;
		break; //--- ������ ��ȫ������ ����
	case 'y':
		a = 1;
		b = 1;
		c = 0;
		break; //--- ������ ��������� ����
	case 'a':
		a = random_float(gen);
		b = random_float(gen);
		c = random_float(gen);
		break; //--- ���� ����
	case 'w':
		a = 1;
		b = 1;
		c = 1;
		break; //--- ������ ������� ����
	case 'k':
		a = 0;
		b = 0;
		c = 0;
		break; //--- ������ ���������� ����
	case 't':
		start = 0;
		glutTimerFunc(100, TimerFunction, 1);
		break; //--- Ÿ�̸Ӹ� �����Ͽ� Ư�� �ð����� ����
	case 's':
		start = 1;
		break; //-- Ÿ�̸� ����
	case 'q':
		glutDestroyWindow(1);
		break; //--- ���α׷� ����
	}
	glutPostRedisplay(); //--- ������ �ٲ� ������ ��� �ݹ� �Լ��� ȣ���Ͽ� ȭ���� refresh �Ѵ�
}