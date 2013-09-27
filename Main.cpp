#include <Windows.h>
#include <gl/glut.h>
#include <iostream>
#include "Camera.h"
#include "OBJReader.h"

void init();
void draw(void);
void update(void);
void reshapeHandle(int w, int h);
void resetView(void);
void changeCamera();
void keyboardHandle(unsigned char key, int x, int y);
void passiveMotionHandle(int x, int y);

int width = 800;
int height = 600;

Camera* cam;
Mesh* mesh;

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	

	glutCreateWindow("Object");
	glutFullScreen();
	init();

	glutDisplayFunc(draw);
	glutKeyboardFunc(keyboardHandle);
	glutPassiveMotionFunc(passiveMotionHandle);
	glutReshapeFunc(reshapeHandle);
	glutIdleFunc(update);

	glutMainLoop();

	return 0;
}

void init()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClearDepth(1.0);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);

	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
    GLfloat light_specular[] = {1.0, 1.0, 0.0,1.0};
    GLfloat light_diffuse[] = {0.50, 0.50, 0.5,1.0};
    GLfloat mat_specular[] = { 0.8, 0.5, 0.5, 1.0 };
    GLfloat mat_shininess[] = { 20.0 };
    GLfloat mat_ambient[] = { 0.2, 0.4, 0.99, 1.0 };
    GLfloat mat_diffuse[] = { 0.4, 0.4, 0.4, 1.0 };
    glShadeModel (GL_SMOOTH);
    
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);

	cam = new Camera(90);
	cam->resetView(width, height);

	mesh = new Mesh();

	OBJReader r = OBJReader("cow.obj", mesh);
	r.readObj();
}

void draw(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3f(0.1, 0.1, 1.0);

	for (int i = 0; i < mesh->getGroups().size(); i++)
	{
		for (int j = 0; j < mesh->getGroups().at(i).getFaces().size(); j++)
		{
			glBegin(GL_POLYGON);

			for (int k = 0; k < mesh->getGroups().at(i).getFaces().at(j).getVertexes().size(); k++)
			{
				glNormal3fv(mesh->getNormals().at(mesh->getGroups().at(i).getFaces().at(j).getNormals().at(k)).getPoints());
				glVertex3fv(mesh->getVertexes().at(mesh->getGroups().at(i).getFaces().at(j).getVertexes().at(k)).getPoints());
			}

			glEnd();
		}
	}

	cam->resetView(width, height);
	glutSwapBuffers();
}

void update(void)
{
	glutPostRedisplay();
}

void reshapeHandle(int w, int h)
{
	if (h < 1)
		h = 1;
	
	width = w;
	height = h;

	cam->resetView(w, h);
}

void keyboardHandle(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 'q':
		case 'Q':
			exit(0);
			break;
		case 'a':
		case 'A':
			cam->moveSide(1);
			break;
		case 's':
		case 'S':
			cam->move(-1);
			break;
		case 'd':
		case 'D':
			cam->moveSide(-1);
			break;
		case 'w':
		case 'W':
			cam->move(1);
			break;

	}
}

void passiveMotionHandle(int x, int y)
{
	float y2 = (height - y) / (float)height;
	if (y2 != 0.5 || x != width/2) 
	{
		if(y2 != 0.5)
		{
			cam->setDirectionY(y2 - 0.5);
		}
		if(x != width/2)
		{
			cam->changeAngle((x - width/2) / 10);
		}
		
		glutWarpPointer(width/2, height/2);
	}
}

