#include <GL/freeglut.h>

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

	glutInitWindowSize(800, 600);
	glutInitWindowPosition(glutGet(GLUT_SCREEN_WIDTH) / 2 - 400, glutGet(GLUT_SCREEN_HEIGHT) / 2 - 300);
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
	void Kundali();

	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	Kundali();

	glutSwapBuffers();
}

void Kundali()
{
	//Outer rectangle
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.5f, 0.5f, 0.0f);
	glVertex3f(0.5f, 0.5f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.0f);
	glVertex3f(-0.5f, -0.5f, 0.0f);
	glEnd();

	//Inner rectangle
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.0f, 0.5f, 0.0f);
	glVertex3f(0.5f, 0.0f, 0.0f);
	glVertex3f(0.0f, -0.5f, 0.0f);
	glVertex3f(-0.5f, -0.0f, 0.0f);
	glEnd();

	//Diagonals
	glBegin(GL_LINES);
	glVertex3f(-0.5f, 0.5f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.0f);

	glVertex3f(0.5f, 0.5f, 0.0f);
	glVertex3f(-0.5f, -0.5f, 0.0f);

	glEnd();
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

