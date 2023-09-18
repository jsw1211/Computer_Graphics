#include <iostream>
#include <random>
#include <gl/glew.h> // 필요한 헤더파일 include
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



void main(int argc, char** argv) //--- 윈도우 출력하고 콜백함수 설정
{
	//--- 윈도우 생성하기
	glutInit(&argc, argv); // glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // 디스플레이 모드 설정
	glutInitWindowPosition(0, 0); // 윈도우의 위치 지정
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정
	glutCreateWindow("Example1"); // 윈도우 생성(윈도우 이름)
	//--- GLEW 초기화하기
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) // glew 초기화
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n";
	glutDisplayFunc(drawScene); // 출력 콜백함수의 지정
	glutReshapeFunc(Reshape); // 다시 그리기 콜백함수 지정
	glutKeyboardFunc(Keyboard); // 키보드 입력 콜백함수 지정
	glutMainLoop(); // 이벤트 처리 시작
}
GLvoid drawScene() //--- 콜백 함수: 그리기 콜백 함수
{
	//--- 변경된 배경색 설정
	glClearColor(a, b, c, 1.0f); //--- 바탕색을 변경
	glClear(GL_COLOR_BUFFER_BIT); //--- 설정된 색으로 전체를 칠하기
	glutSwapBuffers(); //--- 화면에 출력하기
}
GLvoid Reshape(int w, int h) //--- 콜백 함수: 다시 그리기 콜백 함수
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
		break; //--- 배경색을 청록색으로 설정
	case 'm':
		a = 1;
		b = 0;
		c = 1;
		break; //--- 배경색을 자홍색으로 설정
	case 'y':
		a = 1;
		b = 1;
		c = 0;
		break; //--- 배경색을 노랑색으로 설정
	case 'a':
		a = random_float(gen);
		b = random_float(gen);
		c = random_float(gen);
		break; //--- 랜덤 설정
	case 'w':
		a = 1;
		b = 1;
		c = 1;
		break; //--- 배경색을 흰색으로 설정
	case 'k':
		a = 0;
		b = 0;
		c = 0;
		break; //--- 배경색을 검은색으로 설정
	case 't':
		start = 0;
		glutTimerFunc(100, TimerFunction, 1);
		break; //--- 타이머를 설정하여 특정 시간마다 랜덤
	case 's':
		start = 1;
		break; //-- 타이머 종료
	case 'q':
		glutDestroyWindow(1);
		break; //--- 프로그램 종료
	}
	glutPostRedisplay(); //--- 배경색이 바뀔 때마다 출력 콜백 함수를 호출하여 화면을 refresh 한다
}