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
	void Conc_rectangles();

	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	Conc_rectangles();

	glutSwapBuffers();
}

void Conc_rectangles()
{
	GLfloat x1, y1, x2, y2, x3, y3, x4, y4;

	x1 = 0.1f;
	y1 = 0.1f;
	x2 = 0.1f;
	y2 = -0.1f;
	x3 = -0.1f;
	y3 = -0.1f;
	x4 = -0.1f;
	y4 = 0.1f;

	for (int i = 0; i < 10; i++)
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

		glVertex3f(x1, y1, 0.0f);
		glVertex3f(x2, y2, 0.0f);
		glVertex3f(x3, y3, 0.0f);
		glVertex3f(x4, y4, 0.0f);
		glEnd();

		x1 += 0.05f;
		y1 += 0.05f;
		x2 += 0.05f;
		y2 -= 0.05f;
		x3 -= 0.05f;
		y3 -= 0.05f;
		x4 -= 0.05f;
		y4 += 0.05f;
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

