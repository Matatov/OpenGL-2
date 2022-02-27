//lab01.c
#include<stdio.h>
#include<math.h>
#include"GL/glut.h" // including GLUT library

#define Pi 3.141592654
#define POINTS_NUM 13 // The greater the number, the greater the density of points
						
typedef struct POINT {
	GLfloat x;
	GLfloat y;
} Point;

void function1(float VecDeg, float VecSize, Point* p);
float function2(float a);
void drawCirlce(float radius);
void drawingCB(void);

Point points[POINTS_NUM];

int main(int argc, char* argv[])
{
	int n;
	for (n = 0; n < POINTS_NUM-1; n++) 
	{
		function1((n + 1) * 30, 0.8, &points[n]);
	}
	//the middle point
	points[12].x = 0;
	points[12].y = 0;

	glutInit(&argc, argv);          //initialize the glut
	glutInitWindowPosition(20, 20);	//set position	
	glutInitWindowSize(200, 200);	//set size of window
	glutInitDisplayMode(GLUT_RGB);  

	glutCreateWindow("Clock");

	glutDisplayFunc(drawingCB);    //set the CallBack for Dysplat Event

	glutMainLoop();
}

void function1(float VecDeg, float VecSize, Point* p) // polarToCartesian
{													
	p->x = (GLfloat)cos(function2(VecDeg)) * VecSize;
	p->y = (GLfloat)sin(function2(VecDeg)) * VecSize;
}

float function2(float a) // degreeToRadian(float a)
{								
	return a * Pi / 180.0;
}
/*
*	This Functions create all objects
*	in our window
*/
void drawingCB() 
{
	int n;
	GLenum er;
	
	//set color for backgoround
	glClearColor(0.0f, 1.0f, 0.9f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	
	//set color and size for points (Yellow)
	glColor3f(1.0f, 1.0f, 0.0);
	glPointSize(5.0f);

	//Display points
	glBegin(GL_POINTS);
	for (n = 0; n < POINTS_NUM; n++) {
		glVertex2f(points[n].x, points[n].y);
	}
	glEnd();

	//Display clock hands
	glLineWidth(2.0f);

	glBegin(GL_LINES);
		glColor3f(0.0, 0.0, 1.0f); 
		//minute hand
		glVertex2f(0.0f, 0.0f);
		glVertex2f(0.0f, 0.7f);
		//hour hand
		glVertex2f(0.0f, 0.0f);
		glVertex2f(0.5f, 0.0f);
	glEnd();

	glBegin(GL_LINES);
		drawCirlce(1.0f);
	glEnd();

	glFlush();

	er = glGetError();  //get errors. 0 for no error, find the error codes in: https://www.opengl.org/wiki/OpenGL_Error
	if (er) printf("error: %d\n", er);

}

void drawCirlce(float radius)
{	
	
	Point point;
	function1(360, radius, &point);
	for (int j = 0; j < 360; j++)
	{
		glVertex2f(point.x, point.y); //start point
		function1(j, radius, &point);
		glVertex2f(point.x, point.y); //finish point 
	}
}

