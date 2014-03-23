#include "visualization.h"
#define START 1
#define BOXES 2
#define FACADES 3
#define TEXTURES 4

bool start = true, boxes = true, facades = true, textures = true;
static GLfloat spin = 0.0, aspectRatio, n = 20.0f;
GLuint cube, shape;
//movement in scene:
static GLdouble xRef = 0.0, yRef = -10.0, zRef = 0.0, zoom = 1.0, horizontal = 0.0, vertical = 0.0, angle = 0.0;
GLuint	texture[3];

//Tree
tree<Symbol> Tree;

//set up light
GLfloat LightAmbient[]= { 1,1, 1, 1 };    
GLfloat LightDiffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f }; 	
GLfloat LightPosition[]= { 0.0f, -20.0f, -2.0f, 1.0f }; 


void buildCube(){
	//build a rectangular cube, which can be scaled and rotated
	GLfloat x = 2048.0f/512.0f;

	glBegin(GL_QUADS);
		
		//Top
		//glColor3d(0.5,0.0,0.5);  
		//glEdgeFlag(TRUE);
		glTexCoord2f(0.0f, 0.0f); glVertex3d( 1.0, 1.0,0.0);          
		glTexCoord2f(x, 0.0f); glVertex3d(0.0, 1.0,0.0);          
		glTexCoord2f(x, x); glVertex3d(0.0, 1.0, 1.0);          
		glTexCoord2f(0.0f, x); glVertex3d( 1.0, 1.0, 1.0);

		//Bottom
		//glColor3d(0.5,0.0,0.5);   
		//glEdgeFlag(TRUE);
		glTexCoord2f(x, 0.0f); glVertex3d( 1.0,0.0, 1.0);        
		glTexCoord2f(x, x); glVertex3d(0.0,0.0, 1.0);          
		glTexCoord2f(0.0f, x); glVertex3d(0.0,0.0,0.0);         
		glTexCoord2f(0.0f, 0.0f); glVertex3d( 1.0,0.0,0.0);          

		//Back
		//glColor3d(0.5,0.0,0.5);         
		//glEdgeFlag(TRUE);
		glTexCoord2f(x, x); glVertex3d( 1.0, 1.0, 1.0);          
		glTexCoord2f(0.0f, x); glVertex3d(0.0, 1.0, 1.0);         
		glTexCoord2f(0.0f, 0.0f); glVertex3d(0.0,0.0, 1.0);         
		glTexCoord2f(x, 0.0f); glVertex3d( 1.0,0.0, 1.0);         

		//Front
		//glColor3d(1,0.0,0.8);         
		//glEdgeFlag(TRUE);
		glTexCoord2f(x, x); glVertex3d( 1.0,0.0,0.0);        
		glTexCoord2f(0.0f, x); glVertex3d(0.0,0.0,0.0);          
		glTexCoord2f(0.0f, 0.0f); glVertex3d(0.0, 1.0,0.0);         
		glTexCoord2f(x, 0.0f); glVertex3d( 1.0, 1.0,0.0);   

		//Left
		//glColor3d(0.5,0.0,0.5);          
		glTexCoord2f(0, 0.0f); glVertex3d(0.0, 1.0, 1.0);          
		glTexCoord2f(x, 0); glVertex3d(0.0, 1.0,0.0);       
		glTexCoord2f(x, x); glVertex3d(0.0,0.0,0.0);         
		glTexCoord2f(0.0f, x); glVertex3d(0.0,0.0, 1.0);         

		//Right
		//glColor3d(0.5,0.0,0.5);          
		glTexCoord2f(0.0f, 0.0f); glVertex3d( 1.0, 1.0,0.0);        
		glTexCoord2f(x, 0.0f); glVertex3d( 1.0, 1.0, 1.0);         
		glTexCoord2f(x, x); glVertex3d( 1.0,0.0, 1.0);         
		glTexCoord2f(0.0f, x); glVertex3d( 1.0,0.0,0.0);          

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
    texture[0] = SOIL_load_OGL_texture("textures/glass1.jpg",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
	texture[1] = SOIL_load_OGL_texture("textures/glass2.jpg",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
	texture[2] = SOIL_load_OGL_texture("textures/concrete.jpg",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);


    if(texture[0] == 0 || texture[1] == 0 || texture[2] == 0)
        cout << "Problem loading texture" << endl;    

 
    return true;                                        
}

void display() {

	//gluLookAt (0.0 + horizontal, 0.0 + vertical, -10.0+zoom, xRef, yRef, zRef, 0.0, 1, 0); 
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0, 1.0, 1.0, 1.0);

	glLoadIdentity();
	gluLookAt (-1.0+horizontal, -1+vertical, -20+zoom, xRef, yRef, zRef, 0.0, 1, 0); 

	//glScaled(zoom,zoom,zoom);
	glTranslated(0,-10,0);
	glRotated(angle,0,1,0);
	//draw ground
	GLfloat x = 1.0f;//4096.0f/512.0f; //test size
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glBegin(GL_QUADS);
		glTexCoord2f(0, 0); glVertex3d(-n+2, -0.1, -n+2);          
		glTexCoord2f(x, 0); glVertex3d(-n+2, -0.1, n-2);          
		glTexCoord2f(x, x); glVertex3d(n-2, -0.1, n-2);          
		glTexCoord2f(0, x); glVertex3d(n-2, -0.1, -n+2);
	glEnd();

	glTranslated(-5,0,-5);


	//Iterate over Tree
	
	tree<Symbol>::leaf_iterator leaf = Tree.begin_leaf();
	Symbol *child;

	while (leaf != Tree.end_leaf()){

		glPushMatrix();
		
		//cout << node.name << endl;
		if((*leaf).getName() == "facade"){
			//glColor4d(1,0, 0, 0.9); 
			if(textures)
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

		glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
		glTranslated((*leaf).position[0], (*leaf).position[1], (*leaf).position[2]);
		glScaled((*leaf).scale[0], (*leaf).scale[1], (*leaf).scale[2]);
		glCallList(cube);
		glPopMatrix();
		leaf++;
	}



	glFlush();
	glutSwapBuffers();
}


void reshape(GLsizei w, GLsizei h){

	glLoadIdentity();

	
	
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

	
	gluPerspective(4, aspectRatio, 1, 10);

 
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

		//Light
		glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);  
		glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
		glLightfv(GL_LIGHT1, GL_POSITION,LightPosition); 
		//glEnable(GL_LIGHT1); 
		//glEnable(GL_LIGHTING);

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
	
	scale.push_back(10);
	scale.push_back(10);
	scale.push_back(10);

	Symbol *start = new Symbol(pos,scale, "start");

	pos[0] = 0; 
	pos[1] = 0; 
	pos[2] = 0;
	
	scale[0] = 10;
	scale[1] = 10;
	scale[2] = 1;

	Symbol *facade = new Symbol(pos,scale, "facade");


	pos[0] = 0; 
	pos[1] = 0; 
	pos[2] = 1;
	
	scale[0] = 10;
	scale[1] = 8;
	scale[2] = 8;

	Symbol *sidewings = new Symbol(pos,scale, "sidewings");

	pos[0] = 0; 
	pos[1] = 0; 
	pos[2] = 1;
	
	scale[0] = 3;
	scale[1] = 8;
	scale[2] = 8;

	Symbol *sidewing1 = new Symbol(pos,scale, "sidewing1");

	pos[0] = 7; 
	pos[1] = 0; 
	pos[2] = 1;
	
	scale[0] = 3;
	scale[1] = 6;
	scale[2] = 6;

	Symbol *sidewing2 = new Symbol(pos,scale, "sidewing2");

	tree<Symbol> derivTree;
	tree<Symbol>::iterator root, one, two;

	root = derivTree.begin();

	one = derivTree.insert(root, *start);
	two = derivTree.append_child(one, *facade);
	two = derivTree.append_child(one, *sidewings);
	derivTree.append_child(two, *sidewing1);
	derivTree.append_child(two, *sidewing2);

	tree<Symbol>::leaf_iterator leaf = derivTree.begin_leaf();

	while (leaf != derivTree.end_leaf()){
		//if(leaf != derivTree.begin())
			cout << (*leaf).getName() << endl;
		leaf++;
	}

	Tree = derivTree;

	cout << (*Tree.begin_leaf()).getName() << endl;




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

	case 43: //+ = move camera pos left
		horizontal += 0.5;
		glutPostRedisplay();
		break;

	case 45: //- move camera pos right
		horizontal -= 0.5;
		glutPostRedisplay();
		break;
	
	} 
}

GLvoid specialkeys( GLint key, GLint x, GLint y )
{
    switch (key) {

    case GLUT_KEY_LEFT:  //move left
         //xRef -= 0.5;
         //if (xRef < -15.0) xRef = -15.0;
        angle += 0.5;
		if (angle > 360) angle = 0;
		
		glutPostRedisplay();
         break;

    case GLUT_KEY_RIGHT:    //move right
        // xRef += 0.5;
         //if (xRef > 15.0) xRef = 15.0;
		angle -= 0.5;
		if (angle < 0) angle = 360;
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

void menuEvents(int opt){
	switch(opt){
	case START:
		start = true;
		break;
	case BOXES:
		boxes = true;
		break;
	case FACADES:
		facades = true;
		break;
	case TEXTURES:
		textures = true;
		glutPostRedisplay();
		break;
	}
}


void createMenu(){
	int menu;
	menu = glutCreateMenu(menuEvents);

	//add entries to menu
	glutAddMenuEntry("Draw Start Symbol",START);
	glutAddMenuEntry("Draw simple Boxes",BOXES);
	glutAddMenuEntry("Draw Facades",FACADES);
	glutAddMenuEntry("Draw Textures",TEXTURES);

	//attach menu to right mouse button
	glutAttachMenu(GLUT_RIGHT_BUTTON);
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
	createMenu();
	glutReshapeFunc(reshape);
	glutDisplayFunc(display); 
	//glutIdleFunc(display);
    glutKeyboardFunc( keyboard );
    glutSpecialFunc( specialkeys );
	glutMouseWheelFunc(mousewheel);

	glutMainLoop(); 
}