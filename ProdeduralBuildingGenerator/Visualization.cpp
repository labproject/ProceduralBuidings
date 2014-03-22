#include "visualization.h"


stlplus::ntree<Symbol> Tree;
static GLfloat spin = 0.0, aspectRatio;
GLuint cube, shape;
//movement in scene:
static GLdouble xRef = 0.0, yRef = 0.0, zRef = 0.0, zoom = 1.0, horizontal = 0.0, vertical = 0.0;
GLuint	texture[2];

void buildCube(){
	//build a rectangular cube, which can be scaled and rotated

	glBegin(GL_QUADS);
		
		//Top
		//glColor3d(0.5,0.0,0.5);  
		//glEdgeFlag(TRUE);
		glTexCoord2f(0.0f, 0.0f); glVertex3d( 1.0, 1.0,0.0);          
		glTexCoord2f(1.0f, 0.0f); glVertex3d(0.0, 1.0,0.0);          
		glTexCoord2f(1.0f, 1.0f); glVertex3d(0.0, 1.0, 1.0);          
		glTexCoord2f(0.0f, 1.0f); glVertex3d( 1.0, 1.0, 1.0);

		//Bottom
		//glColor3d(0.5,0.0,0.5);   
		//glEdgeFlag(TRUE);
		glTexCoord2f(1.0f, 0.0f); glVertex3d( 1.0,0.0, 1.0);        
		glTexCoord2f(1.0f, 1.0f); glVertex3d(0.0,0.0, 1.0);          
		glTexCoord2f(0.0f, 1.0f); glVertex3d(0.0,0.0,0.0);         
		glTexCoord2f(0.0f, 0.0f); glVertex3d( 1.0,0.0,0.0);          

		//Back
		//glColor3d(0.5,0.0,0.5);         
		//glEdgeFlag(TRUE);
		glTexCoord2f(0.0f, 1.0f); glVertex3d( 1.0, 1.0, 1.0);          
		glTexCoord2f(0.0f, 0.0f); glVertex3d(0.0, 1.0, 1.0);         
		glTexCoord2f(1.0f, 0.0f); glVertex3d(0.0,0.0, 1.0);         
		glTexCoord2f(1.0f, 1.0f); glVertex3d( 1.0,0.0, 1.0);         

		//Front
		//glColor3d(1,0.0,0.8);         
		//glEdgeFlag(TRUE);
		glTexCoord2f(1.0f, 1.0f); glVertex3d( 1.0,0.0,0.0);        
		glTexCoord2f(0.0f, 1.0f); glVertex3d(0.0,0.0,0.0);          
		glTexCoord2f(0.0f, 0.0f); glVertex3d(0.0, 1.0,0.0);         
		glTexCoord2f(1.0f, 0.0f); glVertex3d( 1.0, 1.0,0.0);   

		//Left
		//glColor3d(0.5,0.0,0.5);          
		glTexCoord2f(1.0f, 0.0f); glVertex3d(0.0, 1.0, 1.0);          
		glTexCoord2f(1.0f, 1.0f); glVertex3d(0.0, 1.0,0.0);       
		glTexCoord2f(0.0f, 1.0f); glVertex3d(0.0,0.0,0.0);         
		glTexCoord2f(0.0f, 0.0f); glVertex3d(0.0,0.0, 1.0);         

		//Right
		//glColor3d(0.5,0.0,0.5);          
		glTexCoord2f(0.0f, 0.0f); glVertex3d( 1.0, 1.0,0.0);        
		glTexCoord2f(1.0f, 0.0f); glVertex3d( 1.0, 1.0, 1.0);         
		glTexCoord2f(1.0f, 1.0f); glVertex3d( 1.0,0.0, 1.0);         
		glTexCoord2f(0.0f, 1.0f); glVertex3d( 1.0,0.0,0.0);          

	glEnd();                       
}

void buildShape(){
	//build a rectangular, which can be scaled and rotated

	glBegin(GL_QUADS);       

		glColor3d(0,1.0,0.);         
		glEdgeFlag(TRUE);
		glVertex3d( 1.0,0.0,0.0);        
		glVertex3d(0.0,0.0,0.0);          
		glVertex3d(0.0, 1.0,0.0);         
		glVertex3d( 1.0, 1.0,0.0);   		       

	glEnd();                       
}

GLint loadTextures()                                    
{
    texture[0] = SOIL_load_OGL_texture("wall.jpg",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
	texture[1] = SOIL_load_OGL_texture("wall2.png",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    if(texture[0] == 0)
        return false;
 
 
    

 
    return true;                                        
}

void display() {

	//gluLookAt (0.0 + horizontal, 0.0 + vertical, -10.0+zoom, xRef, yRef, zRef, 0.0, 1, 0); 
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0, 1.0, 1.0, 1.0);

	glLoadIdentity();
	gluLookAt (1.0, 0, 5+zoom, xRef, yRef, zRef, 0.0, 1, 0); 

	//Iterate over Tree
	stlplus::ntree<Symbol>::iterator it = Tree.root();

	for (unsigned int i=0;i<Tree.children(it);i++){
		glPushMatrix();
		stlplus::ntree<Symbol>::iterator child = Tree.child(it,i);
		Symbol node = *child;
		cout << node.name << endl;
		if(node.name == "facade"){
			//glColor4d(1,0, 0, 0.9); 
		    glBindTexture(GL_TEXTURE_2D, texture[0]);

		}
		else{
			//glColor4d(0.3,0, 0.3, 1);
			glBindTexture(GL_TEXTURE_2D, texture[1]);
		}

		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTranslated(node.position[0], node.position[1], node.position[2]);
		glScaled(node.scale[0], node.scale[1], node.scale[2]);
		glCallList(cube);
		glPopMatrix();
	}



	glFlush();
	glutSwapBuffers();
}






void reshape(GLsizei w, GLsizei h){

	glLoadIdentity();

	GLfloat n; //n is size of coordinate system
	n = 20.0f;
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
		glOrtho(-n * aspectRatio, n * aspectRatio, -n, n, n, -n);

	
	//gluPerspective(60, aspectRatio, 1, 10);

 
    glMatrixMode(GL_MODELVIEW);                     // Select The Modelview Matrix
    glLoadIdentity();   

}

//initialize Scene and build display lists
void init(){
		glClearColor(1.0, 1.0, 1.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glEnable(GL_TEXTURE_2D);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//Enable Smoothing
		glEnable(GL_POINT_SMOOTH); 
		glEnable(GL_LINE_SMOOTH); 
		glEnable(GL_POLYGON_SMOOTH); 

		loadTextures();
		
		cube = glGenLists (1);
		glNewList(cube, GL_COMPILE);
			buildCube();
		glEndList();

		shape = glGenLists(1);
		glNewList(shape, GL_COMPILE);
			buildShape();
		glEndList();
}


void initTestTree(){
	vector<double> pos, scale;
	pos.push_back(0);
	pos.push_back(0);
	pos.push_back(0);
	
	scale.push_back(5);
	scale.push_back(10);
	scale.push_back(2);

	Symbol *a = new Symbol(pos,scale, "facade");

	Symbol *aa = new Symbol(pos,scale, "facade");


	pos[0] = 0; pos[2] = 2.1;
	pos[1] = 0;
	scale[0] = 2;
	scale[1] = 8;
	scale[2] = 12;

	Symbol *b = new Symbol(pos,scale, "sidewing");


	pos[0] = 5.1; pos[2] = 0;
	pos[1] = 0;
	scale[0] = 4;
	scale[1] = 4;
	scale[2] = 4;

	Symbol *c = new Symbol(pos,scale, "house");


	Tree.insert(*a);
	stlplus::ntree<Symbol>::iterator it = Tree.root();
	Tree.append(it,*aa);
	Tree.append(it,*b);
	Tree.append(it,*c);


}

GLvoid keyboard( GLubyte key, GLint x, GLint y )
{
    switch (key) { 
	case 27:    exit(0); //ESC = exit
	
	case 97: //a = move forward
		zRef += 0.5;
		//if (zRef > 15.0) zRef = 15.0;
        glutPostRedisplay();
		break;

	case 121: //y = move back
		zRef -= 0.5;
		//if (zRef < -15.0) zRef = -15.0;
        glutPostRedisplay();
		break;
	
	} 
}

GLvoid specialkeys( GLint key, GLint x, GLint y )
{
    switch (key) {

    case GLUT_KEY_LEFT:  //move left
         xRef -= 0.5;
         //if (xRef < -15.0) xRef = -15.0;
         glutPostRedisplay();
         break;

    case GLUT_KEY_RIGHT:    //move right
         xRef += 0.5;
         //if (xRef > 15.0) xRef = 15.0;
         glutPostRedisplay();
         break;

    case GLUT_KEY_UP:    //move up
         yRef += 0.5;
        // if (yRef > 15.0) yRef = 15.0;
         glutPostRedisplay();
         break;

    case GLUT_KEY_DOWN:     //move down
         yRef -= 0.5;
         //if (yRef < -15.0) yRef = -15.0;
         glutPostRedisplay();
         break;
    }
}

GLvoid mousewheel(GLint wheel, GLint direction, GLint x, GLint y)
{
    
    if (direction==-1)
    {
        zoom -= 0.5;
		
 
    }
    else if (direction==+1)
    {
        zoom += 0.5;
    }
 
 glutPostRedisplay();
 
}

GLvoid mouse(GLint button, GLint state, GLint x, GLint y) 
{
   switch (button) {
      case GLUT_LEFT_BUTTON:
         if (state == GLUT_DOWN)
            horizontal += 0.5;
		  glutPostRedisplay();
         break;
	  case GLUT_RIGHT_BUTTON:
         if (state == GLUT_DOWN)
            horizontal -= 0.5;
		  glutPostRedisplay();
         break;
      default:
         break;
   }
}

void visualization(int argc, char **argv){

	cout<<"-----------------------"<<endl<<"VISUALIZATION"<<endl<<"-----------------------"<<endl<<endl<<endl;


	glutInit(&argc, argv); // Initialize GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); 
	glutInitWindowSize(800, 600); // Set the width and height of the window
	glutInitWindowPosition(100, 100); // Set the position of the window
	glutCreateWindow("Buildings"); // Set the title for the window

	init();
	initTestTree();
	glutReshapeFunc(reshape);
	glutDisplayFunc(display); 
	//glutIdleFunc(display);
    glutKeyboardFunc( keyboard );
    glutSpecialFunc( specialkeys );
	glutMouseWheelFunc(mousewheel);

	glutMainLoop(); 
}