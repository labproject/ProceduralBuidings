#include "visualization.h"
#define START 1
#define BOXES 2
#define FACADES 3
#define TEXTURES 4
#define HISTORY 5

bool start = false, boxes = true, facades = true, textures = true;
static GLfloat spin = 0.0, aspectRatio, n = 20; //N = **Koordinatensystem**
GLuint cube, shape;
//movement in scene:
//static GLdouble xRef = 0.0, yRef = 60.0, zRef = 0.0, zoom = 1, horizontal = config.at("building_height")+30, vertical = -2*config.at("building_height"), angle = 0.0;
static GLdouble xRef = 0.0, yRef = 60.0, zRef = 0.0, zoom = 1, horizontal = 150, vertical = -300, angle = 0.0;
GLuint	tex_wall[12], tex_window[10], tex_glass[10], tex_roof[10], tex_floor[10], tex_groundfloor[10], tex_topfloor[10], tex_env[11];
int prob1, prob2, prob3, prob4, prob5, prob6;
int depth = 0;
bool history = false;
//Tree
tree<Symbol> Tree;

//set up light
GLfloat LightAmbient[]= { 0.8,0.8, 0.8, 0.1 };    
GLfloat LightDiffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f }; 	
GLfloat LightPosition[]= { 0.0f, 120.0f, -120, 1.0f }; 


void buildCube(){
	//build a rectangular cube, which can be scaled and rotated
	//REPEATPARAMETER
	GLfloat x = 2048.0f/512.0f; //**verhältnis**

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
	//initialize random seed
	srand (time(NULL));

	string filename;

	//Textures for Environment
			for(int i = 0; i < 11; i++){
				filename = "textures/ground" + to_string(static_cast<long long>(i)) + ".jpg";
//				cout << "loading " << filename << endl;
				tex_env[i] = SOIL_load_OGL_texture(filename.c_str(),SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
				if (tex_env[i] == 0 ) cout << "ERROR loading texture " << filename << endl;
			}
				
				prob1 = rand() % 11;

	//Textures for Wall
			for(int i = 0; i < 12; i++){
				filename = "textures/brick" + to_string(static_cast<long long>(i)) + ".jpg";
//				cout << "loading " << filename << endl;
				tex_wall[i] = SOIL_load_OGL_texture(filename.c_str(),SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
				if (tex_wall[i] == 0 ) cout << "ERROR loading texture " << filename << endl;
			}

			prob2 = rand() % 12;

	//Textures Glass

			for(int i = 0; i < 9; i++){
				filename = "textures/glass" + to_string(static_cast<long long>(i)) + ".jpg";
//				cout << "loading " << filename << endl;
				tex_glass[i] = SOIL_load_OGL_texture(filename.c_str(),SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
				if (tex_glass[i] == 0 ) cout << "ERROR loading texture " << i << endl;
			}

			prob3 = rand() % 9;

			prob5 = rand() % 9 + 1;
			if (prob5 == 9 ) prob5 = 0;

	//Textures for Roof

			for(int i = 0; i < 8; i++){
				filename = "textures/roof" + to_string(static_cast<long long>(i)) + ".jpg";
//				cout << "loading " << filename << endl;
				tex_roof[i] = SOIL_load_OGL_texture(filename.c_str(),SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
				if (tex_roof[i] == 0 ) cout << "ERROR loading texture " << i << endl;
			}

			prob4 = rand() % 8;

			
	//Textures for Groundfloor

			for(int i = 0; i < 4; i++){
				filename = "textures/groundfloor" + to_string(static_cast<long long>(i)) + ".jpg";
				//cout << "loading " << filename << endl;
				tex_groundfloor[i] = SOIL_load_OGL_texture(filename.c_str(),SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
				if (tex_groundfloor[i] == 0 ) cout << "ERROR loading texture " << i << endl;
			}

			prob5 = rand() % 4;

	//Textures for topfloor

			for(int i = 0; i < 7; i++){
				filename = "textures/topfloor" + to_string(static_cast<long long>(i)) + ".jpg";
				//cout << "loading " << filename << endl;
				tex_topfloor[i] = SOIL_load_OGL_texture(filename.c_str(),SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
				if (tex_topfloor[i] == 0 ) cout << "ERROR loading texture " << i << endl;
			}

			prob6 = rand() % 7;



			
			//cout << prob1 << prob2 << prob3 << prob4;

 
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
	//gluLookAt (-1.0+horizontal, 120+vertical, -20+zoom, xRef, yRef, zRef, 0.0, 1, 0); 
	gluLookAt(0,horizontal+(abs(zoom)),vertical-(zoom),xRef,yRef,zRef,0,1,0);

	//glScaled(zoom,zoom,zoom);
	glTranslated(0,-10,0);
	glRotated(angle,0,1,0);

	//draw ground
	GLfloat x = 2048.0f/512.0f;//test size
	//glColor3d(0,0,0);
	glBindTexture(GL_TEXTURE_2D, tex_env[prob1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glBegin(GL_QUADS);
		glTexCoord2f(0, 0); glVertex3d(-200, -0.1, -200);
		glTexCoord2f(x, 0); glVertex3d(-200, -0.1, 200);          
		glTexCoord2f(x, x); glVertex3d(200, -0.1, 200);          
		glTexCoord2f(0, x); glVertex3d(200, -0.1, -200);
	glEnd();

	glTranslated(-5,0,-5);


	//Iterate over Tree
	
	tree<Symbol>::leaf_iterator leaf = Tree.begin_leaf();
	tree<Symbol>::pre_order_iterator pre = Tree.begin(); 
	Symbol *child;
	
	

	if(history){
		while(pre != Tree.end()){
			//glColor3d(1,0,0);
			if (Tree.depth(pre) == depth )
				pre.skip_children();
			if((Tree.depth(pre) < depth) && (pre.number_of_children() == 0) || (Tree.depth(pre) == depth)){
				glPushMatrix();

				if((*pre).getName() == "window" || (*pre).getName() == "floor"){
					//glColor4d(1,0, 0, 0.9); 
					glBindTexture(GL_TEXTURE_2D, tex_glass[prob3]);
				}
				else if ((*pre).getName() == "groundfloor")
					glBindTexture(GL_TEXTURE_2D, tex_groundfloor[prob5]);
				else if ((*pre).getName() == "topfloor")
					glBindTexture(GL_TEXTURE_2D, tex_topfloor[prob6]);

				else if((*pre).getName() == "roof"){
					//glColor4d(0.7,0, 0, 0.9); 
					glBindTexture(GL_TEXTURE_2D, tex_roof[prob4]);
				}
				else if ((*pre).getName() == "side"){
			
					glBindTexture(GL_TEXTURE_2D, tex_wall[prob5]);
				}
				else if ((*pre).getName() == "back")
					glBindTexture(GL_TEXTURE_2D, tex_wall[prob2]);
				else
					glBindTexture(GL_TEXTURE_2D, tex_wall[prob2]);

		
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
				//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
				//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
				GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
				GLfloat mat_shininess[] = { 50.0 };
				glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
				glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
				glTranslated((*pre).position[0], (*pre).position[1], (*pre).position[2]);
				glScaled((*pre).scale[0], (*pre).scale[1], (*pre).scale[2]);

				glCallList(cube);
				glPopMatrix();
			}

			pre++;
		}
	}
	else{		



		while (leaf != Tree.end_leaf()){

			if((*leaf).drawable){
			
				glPushMatrix();
		
				//coloooors red, blue, green, yellow

				if((*leaf).getName() == "red")
					glColor3d(1,0,0);
			else if((*leaf).getName() == "blue")
					glColor3d(0,0,1);
			else if((*leaf).getName() == "green")
					glColor3d(0,1,0);
			else if((*leaf).getName() == "yellow")
				glColor3d(1,1,0);
			else {
				glColor3d(1,1,1);
			}


				//cout << node.name << endl;
				if((*leaf).getName() == "front" || (*leaf).getName() == "floor"){
					//glColor4d(1,0, 0, 0.9); 
					glBindTexture(GL_TEXTURE_2D, tex_glass[prob3]);
				}
				else if ((*leaf).getName() == "groundfloor")
					glBindTexture(GL_TEXTURE_2D, tex_groundfloor[prob5]);
				else if ((*leaf).getName() == "topfloor")
					glBindTexture(GL_TEXTURE_2D, tex_topfloor[prob6]);

				else if((*leaf).getName() == "roof"){
					//glColor4d(0.7,0, 0, 0.9); 
					glBindTexture(GL_TEXTURE_2D, tex_roof[prob4]);
				}
				else if ((*leaf).getName() == "side"){
			
					glBindTexture(GL_TEXTURE_2D, tex_wall[prob5]);
				}
				else if ((*leaf).getName() == "back")
					glBindTexture(GL_TEXTURE_2D, tex_wall[prob2]);
				else
					glBindTexture(GL_TEXTURE_2D, tex_wall[prob2]);

		
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
			}

			leaf++;
		}
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
		glOrtho(-n, n, -n / aspectRatio, n / aspectRatio, 20, -20); 
	else
		glOrtho(-n * aspectRatio, n * aspectRatio, -n, n, 20, -20);

	
	gluPerspective(2, aspectRatio, 1, 10);

 
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

	case 49: // decrement depth
		depth --;
		if(depth < 0)
			depth = 0;
		glutPostRedisplay();
		break;

	case 50: //increment depth
		depth++;
		//cout << Tree.max_depth() << endl;
		if(depth > Tree.max_depth())
			depth = Tree.max_depth();
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
        angle += 5;
		if (angle > 360) angle = 0;
		
		glutPostRedisplay();
         break;

    case GLUT_KEY_RIGHT:    //move right
        // xRef += 0.5;
         //if (xRef > 15.0) xRef = 15.0;
		angle -= 5;
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
        zoom += 4.0;
		
 
    }
    else if (direction==+1)
    {
        zoom -= 4.0;
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
	case HISTORY:
		if(history) history = false;
		else history = true;
		glutPostRedisplay();
		break;
	}
}


void createMenu(){
	int menu;
	menu = glutCreateMenu(menuEvents);

	//add entries to menu
	glutAddMenuEntry("Light",START);
	glutAddMenuEntry("Enable History", HISTORY);
	//attach menu to right mouse button
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void visualization(int argc, char **argv, tree<Symbol> devTree){

	cout<<"-----------------------"<<endl<<"VISUALIZATION"<<endl<<"-----------------------"<<endl<<endl<<endl;
	
	//DEBUG
	//map<string,float> *karte = &config;
	//cout<<"Building Height: "<<karte->at("building_height")<<endl;

	tree<Symbol>::leaf_iterator leaf = Tree.begin_leaf();
	
	glutInit(&argc, argv); // Initialize GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE);
	glEnable(GLUT_MULTISAMPLE);
	glutInitWindowSize(1280, 720); // Set the width and height of the window
	glutInitWindowPosition(0, 0); // Set the position of the window
	glutCreateWindow("Buildings"); // Set the title for the window

	init();
	Tree = devTree;
	createMenu();
	glutReshapeFunc(reshape);
	glutDisplayFunc(display); 
	//glutIdleFunc(display);
    glutKeyboardFunc( keyboard );
    glutSpecialFunc( specialkeys );
	glutMouseWheelFunc(mousewheel);

	glutMainLoop(); 
}