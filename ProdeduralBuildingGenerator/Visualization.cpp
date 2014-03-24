#include "visualization.h"
#define START 1
#define BOXES 2
#define FACADES 3
#define TEXTURES 4

bool start = false, boxes = true, facades = true, textures = true;
static GLfloat spin = 0.0, aspectRatio, n = 20.0f;
GLuint cube, shape;
//movement in scene:
static GLdouble xRef = 0.0, yRef = -10.0, zRef = 0.0, zoom = 1.0, horizontal = 0.0, vertical = 0.0, angle = 0.0;
GLuint	texture[10], t_size = 10;

//Tree
tree<Symbol> Tree;

//set up light
GLfloat LightAmbient[]= { 0.8,0.8, 0.8, 1 };    
GLfloat LightDiffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f }; 	
GLfloat LightPosition[]= { 0.0f, 10.0f, -20.0f, 1.0f }; 


void buildCube(){
	//build a rectangular cube, which can be scaled and rotated
	GLfloat x = 2048.0f/512.0f;

	glBegin(GL_QUADS);
		
		//Top
		glTexCoord2f(x, 0.0f); glVertex3d( 1.0, 1.0,0.0);          
		glTexCoord2f(0, 0.0f); glVertex3d(0.0, 1.0,0.0);          
		glTexCoord2f(0, x); glVertex3d(0.0, 1.0, 1.0);          
		glTexCoord2f(x, x); glVertex3d( 1.0, 1.0, 1.0);

		//Bottom
		glTexCoord2f(x, 0.0f); glVertex3d( 1.0,0.0, 1.0);        
		glTexCoord2f(x, x); glVertex3d(0.0,0.0, 1.0);          
		glTexCoord2f(0.0f, x); glVertex3d(0.0,0.0,0.0);         
		glTexCoord2f(0.0f, 0.0f); glVertex3d( 1.0,0.0,0.0);          

		//Back
		glTexCoord2f(0.0f, 0.0f); glVertex3d( 1.0, 1.0, 1.0);          
		glTexCoord2f(x, 0); glVertex3d(0.0, 1.0, 1.0);         
		glTexCoord2f(x,x); glVertex3d(0.0,0.0, 1.0);         
		glTexCoord2f(0.0f, x); glVertex3d( 1.0,0.0, 1.0);         

		//Front
		glTexCoord2f(x, x); glVertex3d( 1.0,0.0,0.0);        
		glTexCoord2f(0.0f, x); glVertex3d(0.0,0.0,0.0);          
		glTexCoord2f(0.0f, 0.0f); glVertex3d(0.0, 1.0,0.0);         
		glTexCoord2f(x, 0.0f); glVertex3d( 1.0, 1.0,0.0);   

		//Left
		glTexCoord2f(0, 0.0f); glVertex3d(0.0, 1.0, 1.0);          
		glTexCoord2f(x, 0); glVertex3d(0.0, 1.0,0.0);       
		glTexCoord2f(x, x); glVertex3d(0.0,0.0,0.0);         
		glTexCoord2f(0.0f, x); glVertex3d(0.0,0.0, 1.0);         

		//Right
		glTexCoord2f(0.0f, 0.0f); glVertex3d( 1.0, 1.0,0.0);        
		glTexCoord2f(x, 0.0f); glVertex3d( 1.0, 1.0, 1.0);         
		glTexCoord2f(x, x); glVertex3d( 1.0,0.0, 1.0);         
		glTexCoord2f(0.0f, x); glVertex3d( 1.0,0.0,0.0);          

	glEnd();                       
}

void buildShape(){
	//build a rectangular, which can be scaled and rotated

	glBegin(GL_QUADS);       

		glVertex3d( 1.0,0.0,0.0);        
		glVertex3d(0.0,0.0,0.0);          
		glVertex3d(0.0, 1.0,0.0);         
		glVertex3d( 1.0, 1.0,0.0);   		       

	glEnd();                       
}

GLint loadTextures()                                    
{
			texture[0] = SOIL_load_OGL_texture("textures/windowfront3.jpg",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
			texture[1] = SOIL_load_OGL_texture("textures/glass2.jpg",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
			texture[2] = SOIL_load_OGL_texture("textures/concrete.jpg",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
			texture[3] = SOIL_load_OGL_texture("textures/wall2.png",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
			texture[4] = SOIL_load_OGL_texture("textures/brick10.jpg",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
			texture[5] = SOIL_load_OGL_texture("textures/brick5.jpg",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
			texture[6] = SOIL_load_OGL_texture("textures/brick1.jpg",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);



	for (int i = 0; i < t_size; i++){
		if(texture[i] == 0)
			 cout << "Problem loading texture " << i << endl;    
	}

 
    return true;                                        
}

void display() {

	//gluLookAt (0.0 + horizontal, 0.0 + vertical, -10.0+zoom, xRef, yRef, zRef, 0.0, 1, 0); 
	if(start){
		glEnable(GL_LIGHT1); 
		glEnable(GL_LIGHTING);
	}
	else{
		glDisable(GL_LIGHT1);
		glDisable(GL_LIGHTING);
	}
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0, 1.0, 1.0, 1.0);

	glLoadIdentity();
	gluLookAt (-1.0+horizontal, 4+vertical, -20+zoom, xRef, yRef, zRef, 0.0, 1, 0); 

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
		if((*leaf).getName() == "front"){
			//glColor4d(1,0, 0, 0.9); 
			glBindTexture(GL_TEXTURE_2D, texture[0]);

		}
		else if((*leaf).getName() == "top")
			glBindTexture(GL_TEXTURE_2D, texture[3]);
		else if ((*leaf).getName() == "side"){
			
			glBindTexture(GL_TEXTURE_2D, texture[5]);
		}
		else if ((*leaf).getName() == "back")
			glBindTexture(GL_TEXTURE_2D, texture[5]);
		else
			glBindTexture(GL_TEXTURE_2D, texture[6]);

		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat mat_shininess[] = { 50.0 };
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

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

	pos[0] = 0; 
	pos[1] = 0; 
	pos[2] = 0;
	
	scale[0] = 10;
	scale[1] = 10;
	scale[2] = 0;

	Symbol *front = new Symbol(pos,scale, "front");

	pos[0] = 10; 
	pos[1] = 0; 
	pos[2] = 0;
	
	scale[0] = 0;
	scale[1] = 10;
	scale[2] = 1;

	Symbol *side1 = new Symbol(pos,scale, "side");

	pos[0] = 0; 
	pos[1] = 0; 
	pos[2] = 0;
	
	scale[0] = 0;
	scale[1] = 10;
	scale[2] = 1;

	Symbol *side2 = new Symbol(pos,scale, "side");

	pos[0] = 0; 
	pos[1] = 10; 
	pos[2] = 0;
	
	scale[0] = 10;
	scale[1] = 0;
	scale[2] = 1;

	Symbol *top = new Symbol(pos,scale, "top");

	pos[0] = 0; 
	pos[1] = 0; 
	pos[2] = 1;
	
	scale[0] = 10;
	scale[1] = 10;
	scale[2] = 0;

	Symbol *back = new Symbol(pos,scale, "back");

	tree<Symbol> derivTree;
	tree<Symbol>::iterator root, one, two;

	root = derivTree.begin();

	one = derivTree.insert(root, *start);
	two = derivTree.append_child(one, *facade);
	derivTree.append_child(two, *front);
	derivTree.append_child(two, *side1);
	derivTree.append_child(two, *side2);
	derivTree.append_child(two, *top);
	derivTree.append_child(two, *back);
	two = derivTree.append_child(one, *sidewings);
	derivTree.append_child(two, *sidewing1);
	derivTree.append_child(two, *sidewing2);

	tree<Symbol>::leaf_iterator leaf = derivTree.begin_leaf();

	cout << "leaf nodes: " << endl;
	while (leaf != derivTree.end_leaf()){
		//if(leaf != derivTree.begin())
			cout << "			" << (*leaf).getName() << endl;
		leaf++;
	}

	Tree = derivTree;

	cout << "test, first leaf:	" << (*Tree.begin_leaf()).getName() << endl;




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
		if (start == true) start = false;
		else start = true;
		glutPostRedisplay();
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
	glutAddMenuEntry("Light",START);
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