#include "visualization.h"


stlplus::ntree<Symbol> Tree;
static GLfloat spin = 0.0;

void buildObjects(){
	//glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	glBegin(GL_QUADS);
	
	glColor3d(0.5,0.0,0.5);  
	glEdgeFlag(TRUE);
	glVertex3d( 1.0, 1.0,-1.0);          // Top Right Of The Quad (Top)
	glVertex3d(-1.0, 1.0,-1.0);          // Top Left Of The Quad (Top)
	glVertex3d(-1.0, 1.0, 1.0);          // Bottom Ledt Of The Quad (Top)
	glVertex3d( 1.0, 1.0, 1.0);

	glColor3d(0.5,0.0,0.5);   
	glEdgeFlag(TRUE);
	glVertex3d( 1.0,-1.0, 1.0);          // Top Right Of The Quad (Bottom)
	glVertex3d(-1.0,-1.0, 1.0);          // Top Left Of The Quad (Bottom)
	glVertex3d(-1.0,-1.0,-1.0);          // Bottom Left Of The Quad (Bottom)
	glVertex3d( 1.0,-1.0,-1.0);          // Bottom Right Od The Quad (Bottom)


	glColor3d(0.5,0.0,0.5);         
	glEdgeFlag(TRUE);
	glVertex3d( 1.0, 1.0, 1.0);          // Top Right Of The Quad (Front)
	glVertex3d(-1.0, 1.0, 1.0);          // Top Left Of The Quad (Front)
	glVertex3d(-1.0,-1.0, 1.0);          // Bottom Left Of The Quad (Front)
	glVertex3d( 1.0,-1.0, 1.0);          // Bottom Right Of The Quad (Front)

	glColor3d(0.8,0.0,0.8);          // front
	glEdgeFlag(TRUE);
	glVertex3d( 1.0,-1.0,-1.0);          // Bottom Left Of The Quad (Back)
	glVertex3d(-1.0,-1.0,-1.0);          // Bottom Right Of The Quad (Back)
	glVertex3d(-1.0, 1.0,-1.0);          // Top Right Of The Quad (Back)
	glVertex3d( 1.0, 1.0,-1.0);          // Top Left Of The Quad (Back)

	glColor3d(0.5,0.0,0.5);          
	glVertex3d(-1.0, 1.0, 1.0);          // Top Right Of The Quad (Left)
	glVertex3d(-1.0, 1.0,-1.0);          // Top Left Of The Quad (Left)
	glVertex3d(-1.0,-1.0,-1.0);          // Bottom Left Of The Quad (Left)
	glVertex3d(-1.0,-1.0, 1.0);          // Bottom Right Of The Quad (Left)

	glColor3d(0.5,0.0,0.5);          
	glVertex3d( 1.0, 1.0,-1.0);          // Top Right Of The Quad (Right)
	glVertex3d( 1.0, 1.0, 1.0);          // Top Left Of The Quad (Right)
	glVertex3d( 1.0,-1.0, 1.0);          // Bottom Left Of The Quad (Right)
	glVertex3d( 1.0,-1.0,-1.0);          // Bottom Right Of The Quad (Right)
    glEnd();                       



}


void display() {

 	glClearColor(1.0, 1.0, 1.0, 1.0);
	glLoadIdentity();

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
	glMatrixMode(GL_PROJECTION);                  // Select The Projection Matrix
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


void initTestTree(){
	vector<double> pos, scale;
	pos.push_back(1);
	pos.push_back(1);
	pos.push_back(0);
	
	scale.push_back(8);
	scale.push_back(5);
	scale.push_back(10);

	Symbol *a = new Symbol(pos,scale, "facade");

	pos[0] = pos[1] = pos[2] = 3;
	scale[0] = 10;
	scale[1] = 4;
	scale[2] = 6;

	Symbol *b = new Symbol(pos,scale, "sidewing");

	pos[0] = pos[1] = 10;
	scale[0] = 20;
	scale[1] = 8;
	scale[2] = 10;

	Symbol *c = new Symbol(pos,scale, "house");

	Tree.insert(*a);
	stlplus::ntree<Symbol>::iterator it = Tree.root();
	Tree.append(it,*b);
	Tree.append(it,*c);

}

void visualization(int argc, char **argv){

	cout<<"-----------------------"<<endl<<"VISUALIZATION"<<endl<<"-----------------------"<<endl<<endl<<endl;


	glutInit(&argc, argv); // Initialize GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_DEPTH); 
	glutInitWindowSize(500, 500); // Set the width and height of the window
	glutInitWindowPosition(100, 100); // Set the position of the window
	glutCreateWindow("symbol"); // Set the title for the window

	glutDisplayFunc(display); 
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	init();


	glutMainLoop(); 
}