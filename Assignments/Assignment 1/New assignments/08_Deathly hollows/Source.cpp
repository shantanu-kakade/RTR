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
	void Deathly_hollows(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat);

	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	Deathly_hollows(0.0f, 0.5f, 0.5f, -0.5f, -0.5f, -0.5f);
	glutSwapBuffers();
}

void Deathly_hollows(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat x3, GLfloat y3)
{
	GLfloat a, b, c, k, r, cx, cy, xm, ym;
	GLint circle_points = 100;
	const GLfloat pi = 3.14f;
	GLfloat rad = 0.1f, angle;

	// Sides of triangle
	a = sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
	b = sqrt(pow((x1 - x3), 2) + pow((y1 - y3), 2));
	c = sqrt(pow((x2 - x3), 2) + pow((y2 - y3), 2));

	k = (a + b + c) / 2;
	r = sqrt((k*(k - a)*(k - b)*(k - c))) / k;

	xm = (x2 + x3) / 2; //X co-ordinate of median
	ym = (y2 + y3) / 2; //Y co-ordinate of median

						//Incenter co-ordinates
	cx = xm;
	cy = ym + r;

	glBegin(GL_LINE_LOOP);
	glVertex3f(x1, y1, 0.0f);
	glVertex3f(x2, y2, 0.0f);
	glVertex3f(x3, y3, 0.0f);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(x1, y1, 0.0f);
	glVertex3f(xm, ym, 0.0f);
	glEnd();

	glBegin(GL_LINE_LOOP);
	for (int j = 0;j < circle_points; j++)
	{
		angle = 2 * pi * j / circle_points;
		glVertex3f(cx + cos(angle)*r, cy + sin(angle)*r, 0.0f);
	}
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

