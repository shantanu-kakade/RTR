#include <GL/freeglut.h>
#include<math.h>
bool bFullscreen = false;

int main(int argc, char** argv)
{
	void display(void);
	void resize(int, int);
	void keyboard(unsigned char, int, int);
	void mouse(int, int, int, int);
	void initialize(void);
	void uninitialize(void);

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	glutInitWindowSize(800, 800);
	glutInitWindowPosition(glutGet(GLUT_SCREEN_WIDTH) / 2 - 400, glutGet(GLUT_SCREEN_HEIGHT) / 2 - 400);
	glutCreateWindow("My window");

	initialize();

	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutCloseFunc(uninitialize);

	glutMainLoop();

	//	return(0); 
}

void display(void)
{
	void Conc_circles();

	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	Conc_circles();
	glutSwapBuffers();
}

void Conc_circles()
{
	GLint circle_points = 100;
	const GLfloat pi = 3.14f;
	GLfloat rad = 0.1f, angle;

	for (int i = 0; i < 10; i++, rad += 0.1f)
	{
		glBegin(GL_LINE_LOOP);

		switch (i)
		{
		case 0:
			glColor3f(1.0f, 0.0f, 0.0f);
			break;
		case 1:
			glColor3f(0.0f, 1.0f, 0.0f);
			break;
		case 2:
			glColor3f(0.0f, 0.0f, 1.0f);
			break;
		case 3:
			glColor3f(0.0f, 1.0f, 1.0f);
			break;
		case 4:
			glColor3f(1.0f, 0.0f, 1.0f);
			break;
		case 5:
			glColor3f(1.0f, 1.0f, 0.0f);
			break;
		case 6:
			glColor3f(1.0f, 0.5f, 0.0f);
			break;
		case 7:
			glColor3f(0.5f, 0.5f, 0.5f);
			break;
		case 8:
			glColor3f(0.5f, 1.0f, 1.0f);
			break;
		case 9:
			glColor3f(1.0f, 0.5f, 1.0f);
			break;
		}

		for (int j = 0;j < circle_points; j++)
		{
			angle = 2 * pi * j / circle_points;
			glVertex3f(cos(angle)*rad, sin(angle)*rad, 0.0f);
		}
		glEnd();

	}
}
void initialize(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		glutLeaveMainLoop();
		break;
	case 'F':
	case 'f':
		if (bFullscreen == false)
		{
			glutFullScreen();
			bFullscreen = true;
		}
		else
		{
			glutLeaveFullScreen();
			bFullscreen = false;
		}
		break;
	default:
		break;
	}
}

void mouse(int button, int state, int x, int y)
{
	switch (button)
	{
	case GLUT_LEFT_BUTTON:
		break;
	default:
		break;
	}
}

void resize(int width, int height)
{
}

void uninitialize(void)
{
}

