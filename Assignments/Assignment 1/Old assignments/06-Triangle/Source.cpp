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
	void grid();
	void triangle();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	grid();
	triangle();

	glutSwapBuffers();
}

void grid()
{
	int i;
	GLfloat x, y;

	glLineWidth(3.0f);
	glBegin(GL_LINES);

	//Horizontal red line
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);

	//Verticle green line
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, -1.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glEnd();

	glLineWidth(1.0f);
	glBegin(GL_LINES);

	//Horizontal blue lines
	glColor3f(0.0f, 0.0f, 1.0f);
	for (i = 0, y = 0.0f; i<20; i++, y += 0.05f)
	{
		glVertex3f(-1.0f, y, 0.0f);
		glVertex3f(1.0f, y, 0.0f);
	}
	for (i = 0, y = 0.0f; i<20; i++, y -= 0.05f)
	{
		glVertex3f(-1.0f, y, 0.0f);
		glVertex3f(1.0f, y, 0.0f);
	}

	//Verticle blue lines
	glColor3f(0.0f, 0.0f, 1.0f);
	for (i = 0, x = 0.0f; i<20; i++, x += 0.05f)
	{
		glVertex3f(x, -1.0f, 0.0f);
		glVertex3f(x, 1.0f, 0.0f);
	}

	for (i = 0, x = 0.0f; i<20; i++, x -= 0.05f)
	{
		glVertex3f(x, -1.0f, 0.0f);
		glVertex3f(x, 1.0f, 0.0f);
	}
	glEnd();

}

void triangle()
{

	//Yellow triangle
	glBegin(GL_LINES);
	glColor3f(1.0f, 1.0f, 0.0f);

	glVertex3f(0.0f, 0.5f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.0f);

	glVertex3f(0.5f, -0.5f, 0.0f);
	glVertex3f(-0.5f, -0.5f, 0.0f);

	glVertex3f(-0.5f, -0.5f, 0.0f);
	glVertex3f(0.0f, 0.5f, 0.0f);
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

