//lab02.c
#include<stdio.h>
#include<math.h>
#include"GL/glut.h" 

#define Pi 3.141592654

//vertex array
typedef struct POINT {
	GLfloat x;
	GLfloat y;
} Point;
#define POINTS_VERTEX_NUM 12 
#define CIRCLE_VERTEX_NUM 72 
Point points_vertexes[POINTS_VERTEX_NUM];
Point circle_vertexes[CIRCLE_VERTEX_NUM];

//function declerations
void Deg2Vector(float VecDeg, float VecSize, Point* p);
float Deg2Rad(float deg);
void drawingCB(void);
void reshapeCB(int width, int height);



int main(int argc, char* argv[])
{
	//initializing points and circle array
	int n;
	for (n = 0; n < POINTS_VERTEX_NUM; n++) {
		Deg2Vector((n + 1) * 360 / POINTS_VERTEX_NUM, 0.7, &points_vertexes[n]);
	}
	for (n = 0; n < CIRCLE_VERTEX_NUM; n++) {
		Deg2Vector((n + 1) * 360 / CIRCLE_VERTEX_NUM, 0.9, &circle_vertexes[n]);
	}

	//initizlizing GLUT
	glutInit(&argc, argv);

	//initializing window
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(200, 200);
	glutInitDisplayMode(GLUT_RGB);
	glutCreateWindow("Clock");

	//registering callbacks
	glutReshapeFunc(reshapeCB);
	glutDisplayFunc(drawingCB);
	
	//starting main loop
	glutMainLoop();
}

// create vector from angle and size of vector
void Deg2Vector(float VecDeg, float VecSize, Point* p)
{
	p->x = (GLfloat)cos(Deg2Rad(VecDeg)) * VecSize;
	p->y = (GLfloat)sin(Deg2Rad(VecDeg)) * VecSize;
}

// convert degree to radians
float Deg2Rad(float deg)
{
	return deg * Pi / 180.0;
}

// rendering callback
void drawingCB()
{
	int n;
	GLenum er;

	//clearing the background
	glClearColor(0.2f, 0.8f, 0.7f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	//drawing points
	glColor3f(0.1f, 0.5f, 0.1f);
	glPointSize(4);
	glBegin(GL_POINTS);
	for (n = 0; n < POINTS_VERTEX_NUM; n++) {
		glVertex2f(points_vertexes[n].x, points_vertexes[n].y);
	}
	glEnd();

	//drawing circle
	glLineWidth(2);
	glColor3f(0.1f, 0.4f, 0.8f);
	glBegin(GL_LINE_LOOP);
	for (n = 0; n < CIRCLE_VERTEX_NUM; n++) {
		glVertex2f(circle_vertexes[n].x, circle_vertexes[n].y);
	}
	glEnd();

	//drawing clock lines
	glColor3f(0.0f, 0.0f, 0.8f);
	glBegin(GL_LINES);
	glVertex2f(0, 0);
	glVertex2f(0.4, 0);
	glVertex2f(0, 0);
	glVertex2f(0, 0.6);
	glEnd();

	//drawing middle point
	glColor3f(0.1f, 0.5f, 0.1f);
	glPointSize(6);
	glBegin(GL_POINTS);
	glVertex2f(0, 0);
	glEnd();

	//forces execution of OpenGL functions in finite time
	glFlush();

	//check for errors
	er = glGetError();  //get errors. 0 for no error, find the error codes in: https://www.opengl.org/wiki/OpenGL_Error
	if (er) printf("error: %d\n", er);
}


void reshapeCB(int width, int height)
{
	float left, right, bottom, top;
	float AR;

	// define our ortho
	left = -1.5;
	right = 1.5;
	top = 1.5;
	bottom = -1.5;

	// 1)update viewport
	glViewport(0, 0, width, height);
	// 2) clear the transformation matrices (load identity)
	glLoadIdentity();
	// 3) compute the aspect ratio
	AR = (float)width / height;
	// 4) if AR>=1 update left, right
	if (AR >= 1)
	{
		left = left * AR;
		right = right * AR;
	}
	// 5) else i.e. AR<1 update the top, bottom
	else
	{
		top = top / AR;
		bottom = bottom / AR;
	}
	// 6) definnig the boundary of the model using gluOrtho2D 
	gluOrtho2D(left, right, bottom, top);
}