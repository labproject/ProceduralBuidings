#include "visualization.h"

#include "symbol.h"
#include <GL/freeglut.h>




static GLfloat spin = 0.0;

void buildObjects(){
	//glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	glBegin(GL_QUADS);
	
	glColor3d(0.5,0.0,0.5);  
	glEdgeFlag(TRUE);// Set The Color To Green
	glVertex3d( 1.0, 1.0,-1.0);          // Top Right Of The Quad (Top)
	glVertex3d(-1.0, 1.0,-1.0);          // Top Left Of The Quad (Top)
	glVertex3d(-1.0, 1.0, 1.0);          // Bottom Ledt Od The Quad (Top)
	glVertex3d( 1.0, 1.0, 1.0);

	glColor3d(0.5,0.0,0.5);   
	glEdgeFlag(TRUE);// Set The Color To Orange
	glVertex3d( 1.0,-1.0, 1.0);          // Top Right Of The Quad (Bottom)
	glVertex3d(-1.0,-1.0, 1.0);          // Top Left Of The Quad (Bottom)
	glVertex3d(-1.0,-1.0,-1.0);          // Bottom Left Of The Quad (Bottom)
	glVertex3d( 1.0,-1.0,-1.0);          // Bottom Right Od The Quad (Bottom)


	glColor3d(0.5,0.0,0.5);          // Set The Color To Red
	glEdgeFlag(TRUE);
	glVertex3d( 1.0, 1.0, 1.0);          // Top Right Of The Quad (Front)
	glVertex3d(-1.0, 1.0, 1.0);          // Top Left Of The Quad (Front)
	glVertex3d(-1.0,-1.0, 1.0);          // Bottom Left Of The Quad (Front)
	glVertex3d( 1.0,-1.0, 1.0);          // Bottom Right Of The Quad (Front)

	glColor3d(0.8,0.0,0.8);          // Set The Color To Yellow
	glEdgeFlag(TRUE);
	glVertex3d( 1.0,-1.0,-1.0);          // Bottom Left Of The Quad (Back)
	glVertex3d(-1.0,-1.0,-1.0);          // Bottom Right Of The Quad (Back)
	glVertex3d(-1.0, 1.0,-1.0);          // Top Right Of The Quad (Back)
	glVertex3d( 1.0, 1.0,-1.0);          // Top Left Of The Quad (Back)

	glColor3d(0.5,0.0,0.5);          // Set The Color To Blue
	glVertex3d(-1.0, 1.0, 1.0);          // Top Right Of The Quad (Left)
	glVertex3d(-1.0, 1.0,-1.0);          // Top Left Of The Quad (Left)
	glVertex3d(-1.0,-1.0,-1.0);          // Bottom Left Of The Quad (Left)
	glVertex3d(-1.0,-1.0, 1.0);          // Bottom Right Of The Quad (Left)

	glColor3d(0.5,0.0,0.5);          // Set The Color To Violet
	glVertex3d( 1.0, 1.0,-1.0);          // Top Right Of The Quad (Right)
	glVertex3d( 1.0, 1.0, 1.0);          // Top Left Of The Quad (Right)
	glVertex3d( 1.0,-1.0, 1.0);          // Bottom Left Of The Quad (Right)
	glVertex3d( 1.0,-1.0,-1.0);          // Bottom Right Of The Quad (Right)
    glEnd();                        // Done Drawing The Quad



}


void display() {

 	glClearColor(1.0, 1.0, 1.0, 1.0);
	

	vector<double> sVec;
	sVec.push_back(10);
	sVec.push_back(-10);
	sVec.push_back(0);

	Symbol *a = new Symbol(sVec,sVec,"test");

	glLoadIdentity();




	glColor3d(1.0, 0.0, 0.5);

	double x = a->position[0];
	double y = a->position[1];
	double z = a->position[2];

	glRotated(60,-0.1,1,0);
	glTranslated(0,0,0);	
	glScaled(40,24,5);	
	
	buildObjects();

	glPopMatrix();
	glLoadIdentity();

	glRotated(60,-0.1,1,0);
	glTranslated(25,-2,20);	
	glScaled(15,22,15);	
	
	buildObjects();

	glPopMatrix();
	glLoadIdentity();

	glRotated(60,-0.1,1,0);
	glTranslated(-25,-2,20);	
	glScaled(15,22,15);	
	
	buildObjects();
	glFlush();
}

void spinDisplay(void)
{
   spin = spin + 2.0;
   if (spin > 360.0)
      spin = spin - 360.0;
   glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) 
{
   switch (button) {
      case GLUT_LEFT_BUTTON:
         if (state == GLUT_DOWN)
            glutIdleFunc(spinDisplay);
         break;
      case GLUT_MIDDLE_BUTTON:
         if (state == GLUT_DOWN)
            glutIdleFunc(NULL);
         break;
      default:
         break;
   }
}


void reshape(GLsizei w, GLsizei h){
			

	GLfloat aspectRatio, n; //n is size of coordinate system
	n = 70.0f;
	if(h==0) //don't divide by zero
		h=1;

	//set viewport
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);                        // Select The Projection Matrix
    glLoadIdentity();                           // Reset The Projection Matrix
 
    aspectRatio = (GLfloat) w / (GLfloat) h;

	if(w <= h)
		glOrtho(-n, n, -n / aspectRatio, n / aspectRatio, n, -n); 
	else
		glOrtho(-n * aspectRatio, n * aspectRatio, -n, n, 1.0, -1.0);
 
    glMatrixMode(GL_MODELVIEW);                     // Select The Modelview Matrix
    glLoadIdentity();   

}

void init(){
		glClearColor(1.0, 1.0, 1.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_POINT_SMOOTH); // Smooth out points
glEnable(GL_LINE_SMOOTH); // Smooth out lines
glEnable(GL_POLYGON_SMOOTH); // Smooth out polygon edges
}


void visualization(int argc, char **argv){

	cout<<"-----------------------"<<endl<<"VISUALIZATION"<<endl<<"-----------------------"<<endl<<endl<<endl;


	glutInit(&argc, argv); // Initialize GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_DEPTH); // Set up a basic display buffer (only single buffered for now)
	glutInitWindowSize(500, 500); // Set the width and height of the window
	glutInitWindowPosition(100, 100); // Set the position of the window
	glutCreateWindow("symbol"); // Set the title for the window

	glutDisplayFunc(display); // Tell GLUT to use the method "display" for rendering
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse); // Tell GLUT to use the method "display" as our idle method as well
	init();


	glutMainLoop(); // Enter GLUT's main loop

}