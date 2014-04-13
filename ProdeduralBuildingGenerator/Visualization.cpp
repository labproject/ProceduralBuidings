#include "visualization.h"
#define LIGHT 1
#define BOXES 2
#define FACADES 3
#define TEXTURES 4
#define HISTORY 5

bool light = true, boxes = true, facades = true, textures = true;
static GLfloat spin = 0.0, aspectRatio, n = 20; //N = **Koordinatensystem**
bool initGL = false;
GLuint cube, shape;
GLubyte *tex_pointer;
//movement in scene:
//static GLdouble xRef = 0.0, yRef = 60.0, zRef = 0.0, zoom = 1, horizontal = config.at("building_height")+30, vertical = -2*config.at("building_height"), angle = 0.0;
static GLdouble xRef = 0.0, yRef = 60.0, zRef = 0.0, move_z = 1, move_x = 0, move_y = -10, horizontal = 150, vertical = -300, angle = 0.0, zoom_look = 1;
GLuint	tex_wall[12], tex_window[10], tex_glass[10], tex_roof[10], tex_floor[10], tex_groundfloor[10], tex_topfloor[10], tex_env[11], tex_entrance[11], tex_door[11], tex_back[11], garage[1];
int prob_set, prob_window;
int depth = 0;
bool history = true, valid_window = true;
//GLfloat x = 4;
//Tree
tree<Symbol> Tree;

//set up light
GLfloat LightAmbient[] = {1,1,1.0,1.0};
GLfloat LightDiffuse[] = {1.0,1.0,1.0,1.0};
GLfloat lightPosition[] = {-150.0,400.0,200.0, 1.0};





void buildCube(GLfloat x){
	//build a rectangular cube, which can be scaled and rotated
	//REPEATPARAMETER
	//GLfloat x = 4; //**verhältnis**

	glBegin(GL_QUADS);

	//Top
	glNormal3d(0.0,1.0,0.0);	glTexCoord2f(x, 0.0f);	glVertex3d( 1.0, 1.0,0.0);          
	glNormal3d(0.0,1.0,0.0);	glTexCoord2f(0, 0.0f);	glVertex3d(0.0, 1.0,0.0);          
	glNormal3d(0.0,1.0,0.0);	glTexCoord2f(0, x);		glVertex3d(0.0, 1.0, 1.0);          
	glNormal3d(0.0,1.0,0.0);	glTexCoord2f(x, x);		glVertex3d( 1.0, 1.0, 1.0);

	//Bottom
	glNormal3d(0.0,-1.0,0.0);	glTexCoord2f(x, 0.0f);	glVertex3d( 1.0,0.0, 1.0);        
	glNormal3d(0.0,-1.0,0.0);	glTexCoord2f(x, x);		glVertex3d(0.0,0.0, 1.0);          
	glNormal3d(0.0,-1.0,0.0);	glTexCoord2f(0.0f, x);	glVertex3d(0.0,0.0,0.0);         
	glNormal3d(0.0,-1.0,0.0);	glTexCoord2f(0.0f,0.0f); glVertex3d( 1.0,0.0,0.0);          

	//Back
	glNormal3d(0.0,0.0,-1.0);	glTexCoord2f(0.0f, 0.0f); glVertex3d( 1.0, 1.0, 1.0);          
	glNormal3d(0.0,0.0,-1.0);	glTexCoord2f(x, 0); glVertex3d(0.0, 1.0, 1.0);         
	glNormal3d(0.0,0.0,-1.0);	glTexCoord2f(x,x); glVertex3d(0.0,0.0, 1.0);         
	glNormal3d(0.0,0.0,-1.0);	glTexCoord2f(0.0f, x); glVertex3d( 1.0,0.0, 1.0);         

	//Front
	glNormal3d(0.0,0.0,-1.0);	glTexCoord2f(x, x); glVertex3d( 1.0,0.0,0.0);        
	glNormal3d(0.0,0.0,-1.0);	glTexCoord2f(0.0f, x); glVertex3d(0.0,0.0,0.0);          
	glNormal3d(0.0,0.0,-1.0);	glTexCoord2f(0.0f, 0.0f); glVertex3d(0.0, 1.0,0.0);         
	glNormal3d(0.0,0.0,-1.0);	glTexCoord2f(x, 0.0f); glVertex3d( 1.0, 1.0,0.0);   

	//Left
	glNormal3d(-1.0,0.0,0.0);	glTexCoord2f(0, 0.0f); glVertex3d(0.0, 1.0, 1.0);          
	glNormal3d(-1.0,0.0,0.0);	glTexCoord2f(x, 0); glVertex3d(0.0, 1.0,0.0);       
	glNormal3d(-1.0,0.0,0.0);	glTexCoord2f(x, x); glVertex3d(0.0,0.0,0.0);         
	glNormal3d(-1.0,0.0,0.0);	glTexCoord2f(0.0f, x); glVertex3d(0.0,0.0, 1.0);         

	//Right
	glNormal3d(1.0,0.0,0.0);	glTexCoord2f(0.0f, 0.0f); glVertex3d( 1.0, 1.0,0.0);        
	glNormal3d(1.0,0.0,0.0);	glTexCoord2f(x, 0.0f); glVertex3d( 1.0, 1.0, 1.0);         
	glNormal3d(1.0,0.0,0.0);	glTexCoord2f(x, x); glVertex3d( 1.0,0.0, 1.0);         
	glNormal3d(1.0,0.0,0.0);	glTexCoord2f(0.0f, x); glVertex3d( 1.0,0.0,0.0);          

	glEnd();                       
}

void buildShape(int i, GLfloat x){
	//build a rectangular, which can be scaled and rotated

	if (i==0)
	{	
		glBegin(GL_QUADS);
	 	glNormal3d(1.0,0.0,0.0); glTexCoord2d(x,x);		glVertex3d(0.0,0.0,0.0); //2
		glNormal3d(1.0,0.0,0.0);glTexCoord2d(x,0);		glVertex3d(0.0,1.0,0.0);  //1
		glNormal3d(1.0,0.0,0.0);glTexCoord2d(0,0);		glVertex3d(0.0,1.0,1.0);   //4
		glNormal3d(1.0,0.0,0.0);glTexCoord2d(0,x);		glVertex3d(0.0,0.0,1.0); //3
		glEnd();  
	}
	if (i==1)
	{
		glBegin(GL_QUADS);
		glTexCoord2d(x,x);	glNormal3d(0.0,1.0,0.0);	glVertex3d(1.0,0.0,0.0);   
		glTexCoord2d(0,x);	glNormal3d(0.0,1.0,0.0);	glVertex3d(0.0,0.0,0.0);
		glTexCoord2d(0,0);	glNormal3d(0.0,1.0,0.0);	glVertex3d(0.0,0.0,1.0);
		glTexCoord2d(x,0);	glNormal3d(0.0,1.0,0.0);	glVertex3d(1.0,0.0,1.0);   
		glEnd();  
	}
	if (i==2)
	{
		glBegin(GL_QUADS);
		glNormal3d(0.0,0.0,-1.0);glTexCoord2d(x,x);		glVertex3d(1.0,0.0,0.0);        
		glNormal3d(0.0,0.0,-1.0);glTexCoord2d(0,x);		glVertex3d(0.0,0.0,0.0);
		glNormal3d(0.0,0.0,-1.0);glTexCoord2d(0,0);		glVertex3d(0.0,1.0,0.0);         
		glNormal3d(0.0,0.0,-1.0);glTexCoord2d(x,0);		glVertex3d(1.0,1.0,0.0); 
		glEnd();  
	}
	                     
}

GLint loadTextures()                                    
{
	//initialize random seed
	srand (time(NULL));

	string filename;
	int number_textures = 5;


	//probability for choosing a texture set and windowset:
	prob_set = rand() % 5;
	prob_window = rand() % 5;

	//cout << prob_set << "  " << prob_window << endl;
	//Textures for Environment

	for(int i = 0; i < number_textures; i++){
		filename = "textures/ground" + to_string(static_cast<long long>(i)) + ".jpg";
		tex_env[i] = SOIL_load_OGL_texture(filename.c_str(),SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_MIPMAPS);
		if (tex_env[i] == 0 ) cout << "ERROR loading texture " << filename << endl;
	}



	//Textures for Wall
	for(int i = 0; i < number_textures; i++){
		filename = "textures/brick" + to_string(static_cast<long long>(i)) + ".jpg";
		tex_wall[i] = SOIL_load_OGL_texture(filename.c_str(),SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_MIPMAPS);
		if (tex_wall[i] == 0 ) cout << "ERROR loading texture " << filename << endl;
	}


	//Textures for Roof

	for(int i = 0; i < number_textures; i++){
		filename = "textures/roof" + to_string(static_cast<long long>(i)) + ".jpg";
		tex_roof[i] = SOIL_load_OGL_texture(filename.c_str(),SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_MIPMAPS);
		if (tex_roof[i] == 0 ) cout << "ERROR loading texture " << filename << endl;
	}

	
	//Textures for Groundfloor

	for(int i = 0; i < number_textures; i++){
		filename = "textures/groundfloor" + to_string(static_cast<long long>(i)) + ".jpg";
		tex_groundfloor[i] = SOIL_load_OGL_texture(filename.c_str(),SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_MIPMAPS);
		if (tex_groundfloor[i] == 0 ) cout << "ERROR loading texture " << filename << endl;
	}
	
	//Textures for topfloor

	for(int i = 0; i < number_textures; i++){
		filename = "textures/topfloor" + to_string(static_cast<long long>(i)) + ".jpg";
		tex_topfloor[i] = SOIL_load_OGL_texture(filename.c_str(),SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_MIPMAPS);
		if (tex_topfloor[i] == 0 ) cout << "ERROR loading texture " << filename << endl;
	}

	
	//Tex window
	for(int i = 0; i < 8; i++){
		filename = "textures/window" + to_string(static_cast<long long>(i)) + ".jpg";
		tex_window[i] = SOIL_load_OGL_texture(filename.c_str(),SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_MIPMAPS);
		if (tex_window[i] == 0 ) cout << "ERROR loading texture " << filename << endl;
	}


	//Tex door
	for(int i = 0; i < number_textures; i++){
		filename = "textures/door" + to_string(static_cast<long long>(i)) + ".jpg";
		tex_door[i] = SOIL_load_OGL_texture(filename.c_str(),SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_MIPMAPS);
		if (tex_door[i] == 0 ) cout << "ERROR loading texture " << filename << endl;
	}

	//Tex back
	for(int i = 0; i < number_textures; i++){
		filename = "textures/back" + to_string(static_cast<long long>(i)) + ".jpg";
		tex_back[i] = SOIL_load_OGL_texture(filename.c_str(),SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_MIPMAPS);
		if (tex_back[i] == 0 ) cout << "ERROR loading texture " << filename << endl;
	}
	
	//Tex garage
		filename = "textures/garage.jpg";
		garage[0] = SOIL_load_OGL_texture(filename.c_str(),SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_MIPMAPS);
		if (garage[0] == 0 ) cout << "ERROR loading texture " << filename << endl;
	



	return true;                                        
}

void display() {
	if(!valid_window)
		 return;


	glColor3d(1,1,1);

	if(light){
		glEnable(GL_LIGHT0); 

		glEnable(GL_LIGHTING);
	}
	else{
		glDisable(GL_LIGHT0);

		glDisable(GL_LIGHTING);
	}
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1,1,1, 1.0);

	glLoadIdentity();
 
	gluLookAt(0,horizontal+(abs(zoom_look)),vertical-(zoom_look),xRef,yRef,zRef,0,1,0);


	glTranslated(move_x,move_y,move_z);
	glRotated(angle,0,1,0);

	//draw ground
	GLfloat x = 1;//2048.0f/512.0f;//test size

	glBindTexture(GL_TEXTURE_2D, tex_env[prob_set]);

	//load texture in storage for mipmapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glBegin(GL_QUADS);
		glNormal3d(0,1,0);	glTexCoord2f(0, 0); glVertex3d(-200, -0.1, -200);
		glNormal3d(0,1,0);	glTexCoord2f(x, 0); glVertex3d(-200, -0.1, 200);          
		glNormal3d(0,1,0);	glTexCoord2f(x, x); glVertex3d(200, -0.1, 200);          
		glNormal3d(0,1,0);	glTexCoord2f(0, x); glVertex3d(200, -0.1, -200);
	glEnd();

	glTranslated(-5,0,-5);



	//Iterate over Tree

	tree<Symbol>::leaf_iterator leaf = Tree.begin_leaf();
	tree<Symbol>::pre_order_iterator pre = Tree.begin(); 
	Symbol *child;


	//draw whole tree only if history == false, otherwise draw up to certain treelevel given by parameter depth
	
	if(history){
		while(pre != Tree.end()){
			
			if (Tree.depth(pre) == depth )
				pre.skip_children();
			if((Tree.depth(pre) < depth) && (pre.number_of_children() == 0) || (Tree.depth(pre) == depth)){
				glPushMatrix();

				glColor3d(1,1,1);

				//Objects with wall texture
				//if((*pre).getName() == "start" || (*pre).getName() == "complex" || (*pre).getName() == "facades" || (*pre).getName() == "sidewing" || (*pre).getName() == "back" || (*pre).getName() == "side" || (*pre).getName() == "floors"
				//							   ||(*pre).getName() == "wall" || (*pre).getName() == "tile"){
				//	glBindTexture(GL_TEXTURE_2D, tex_wall[prob_set]);
				//}

				//Objects with roof texture
				if((*pre).getName() == "roof"){
					glBindTexture(GL_TEXTURE_2D, tex_roof[prob_set]);
				}
				
				//Back side
				else if ((*pre).getName() == "back"){
					x=4;
					glBindTexture(GL_TEXTURE_2D, tex_back[prob_set]);
					
				}
				//Objects with floor textures
				else if ((*pre).getName() == "groundfloor" || (*pre).getName() == "groundlevel"){
					x=1;
					glBindTexture(GL_TEXTURE_2D, tex_groundfloor[0]);
				}	
				else if ((*pre).getName() == "groundfloor2" || (*pre).getName() == "groundlevel"){
					x=1;
					glBindTexture(GL_TEXTURE_2D, tex_groundfloor[1]);
				}
				else if ((*pre).getName() == "topfloor")
					glBindTexture(GL_TEXTURE_2D, tex_topfloor[prob_set]);

				//Objects like windows, doors, entrance
				else if ((*pre).getName() == "window"){
							prob_window = 1+((int)rand())%8;
					string tmp  = static_cast<ostringstream*>( &(ostringstream() << prob_window) )->str();
					(*pre).name.append(tmp);
					glBindTexture(GL_TEXTURE_2D, tex_window[prob_window]);
				}
					else if ((*pre).getName() == "window1"){
					glBindTexture(GL_TEXTURE_2D, tex_window[0]);
				}	else if ((*pre).getName() == "window2"){
					glBindTexture(GL_TEXTURE_2D, tex_window[1]);
				}	else if ((*pre).getName() == "window3"){
					glBindTexture(GL_TEXTURE_2D, tex_window[2]);
				}	else if ((*pre).getName() == "window4"){
					glBindTexture(GL_TEXTURE_2D, tex_window[3]);
				}	else if ((*pre).getName() == "window5"){
					glBindTexture(GL_TEXTURE_2D, tex_window[4]);
				}	else if ((*pre).getName() == "window6"){
					glBindTexture(GL_TEXTURE_2D, tex_window[5]);
				}	else if ((*pre).getName() == "window7"){
					glBindTexture(GL_TEXTURE_2D, tex_window[6]);
				}	else if ((*pre).getName() == "window8"){
					glBindTexture(GL_TEXTURE_2D, tex_window[7]);
				}

				else if ((*pre).getName() == "door"){
					x = 1;
					glBindTexture(GL_TEXTURE_2D, tex_door[prob_set]);
	
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
				}
					else if ((*pre).getName() == "garage")
					glBindTexture(GL_TEXTURE_2D, garage[0]);


				
				//DEBUG COLORS
				else if ((*pre).getName() == "red")
					glColor3d(1,0,0);
				else if ((*pre).getName() == "blue")
					glColor3d(0,0,1);
				else if ((*pre).getName() == "green")
					glColor3d(0,1,0);
				else if ((*pre).getName() == "yellow")
					glColor3d(1,1,0);
				else
					glBindTexture(GL_TEXTURE_2D, tex_wall[prob_set]);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
				
				glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
				GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
				GLfloat mat_shininess[] = { 120.0 };
				glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
				glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
				glTranslated((*pre).position[0], (*pre).position[1], (*pre).position[2]);
				glScaled((*pre).scale[0], (*pre).scale[1], (*pre).scale[2]);

				
				if((*pre).scale[0]==0)
					buildShape(0,x);
				else if((*pre).scale[1]==0)
					buildShape(1,x);
				else if((*pre).scale[2]==0)
					buildShape(2,x);
				//glCallList(cube);
				if((*pre).scale[2]!=0&&(*pre).scale[1]!=0&&(*pre).scale[0]!=0){
					buildCube(x);
				}
				glPopMatrix();
			}

			pre++;
		}
	}
	else{		



		while (leaf != Tree.end_leaf()){

			if((*leaf).drawable){

				glPushMatrix();
				glColor3d(1,1,1);
				//Objects with roof texture
				if((*leaf).getName() == "roof"){
					glBindTexture(GL_TEXTURE_2D, tex_roof[prob_set]);
				}
				
				//Objects with floor textures
				else if ((*leaf).getName() == "groundfloor" || (*leaf).getName() == "groundlevel"){
					x=1;
					glBindTexture(GL_TEXTURE_2D, tex_groundfloor[0]);
				}	
				else if ((*leaf).getName() == "groundfloor2" || (*leaf).getName() == "groundlevel"){
					x=1;
					glBindTexture(GL_TEXTURE_2D, tex_groundfloor[1]);
				}
				else if ((*leaf).getName() == "topfloor")
					glBindTexture(GL_TEXTURE_2D, tex_topfloor[prob_set]);
			
				//Objects like windows, doors, entrance
				else if ((*leaf).getName() == "window"){
					prob_window = 1+((int)rand())%8;
					string tmp  = static_cast<ostringstream*>( &(ostringstream() << prob_window) )->str();
					(*leaf).name.append(tmp);
					glBindTexture(GL_TEXTURE_2D, tex_window[prob_window]);
				}
				
					else if ((*leaf).getName() == "window1"){
					glBindTexture(GL_TEXTURE_2D, tex_window[0]);
				}	else if ((*leaf).getName() == "window2"){
					glBindTexture(GL_TEXTURE_2D, tex_window[1]);
				}	else if ((*leaf).getName() == "window3"){
					glBindTexture(GL_TEXTURE_2D, tex_window[2]);
				}	else if ((*leaf).getName() == "window4"){
					glBindTexture(GL_TEXTURE_2D, tex_window[3]);
				}	else if ((*leaf).getName() == "window5"){
					glBindTexture(GL_TEXTURE_2D, tex_window[4]);
				}	else if ((*leaf).getName() == "window6"){
					glBindTexture(GL_TEXTURE_2D, tex_window[5]);
				}	else if ((*leaf).getName() == "window7"){
					glBindTexture(GL_TEXTURE_2D, tex_window[6]);
				}	else if ((*leaf).getName() == "window8"){
					glBindTexture(GL_TEXTURE_2D, tex_window[7]);
				}

				else if ((*leaf).getName() == "door"){
					x = 1;
					glBindTexture(GL_TEXTURE_2D, tex_door[prob_set]);
	
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
				}
			
				else if ((*leaf).getName() == "back"){
					x=4;
					glBindTexture(GL_TEXTURE_2D, tex_back[prob_set]);

				}
				else if ((*leaf).getName() == "garage")
					glBindTexture(GL_TEXTURE_2D, garage[0]);


				//DEBUG COLORS
				else if ((*leaf).getName() == "red")
					glColor3d(1,0,0);
				else if ((*leaf).getName() == "blue")
					glColor3d(0,0,1);
				else if ((*leaf).getName() == "green")
					glColor3d(0,1,0);
				else if ((*leaf).getName() == "yellow")
					glColor3d(1,1,0);
				else{
					glBindTexture(GL_TEXTURE_2D, tex_wall[prob_set]);
				}


				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
				
				glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
				GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
				GLfloat mat_shininess[] = { 120.0 };
				glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
				glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

				glTranslated((*leaf).position[0], (*leaf).position[1], (*leaf).position[2]);
				glScaled((*leaf).scale[0], (*leaf).scale[1], (*leaf).scale[2]);
		
				
				if((*leaf).scale[0]==0)
					buildShape(0,x);
				if((*leaf).scale[1]==0)
					buildShape(1,x);
				if((*leaf).scale[2]==0)
					buildShape(2,x);
				//glCallList(cube);
				if((*leaf).scale[2]!=0&&(*pre).scale[1]!=0&&(*pre).scale[0]!=0){
					buildCube(x);
				}
				
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
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT0,GL_AMBIENT,LightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT0, GL_POSITION,lightPosition); 
	glEnable(GL_NORMALIZE);

	
	loadTextures();

	//cube = glGenLists (1);
	//glNewList(cube, GL_COMPILE);
	//buildCube();
	//glEndList();

	//shape = glGenLists(1);
	//glNewList(shape, GL_COMPILE);
	//buildShape();
	//glEndList();
}

GLvoid keyboard( GLubyte key, GLint x, GLint y )
{
	switch (key) { 
	case 27:    
				valid_window = false;
				glutDestroyWindow(glutGetWindow());
				break;

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

	case 115: //change view
		zoom_look += 4.0;
		glutPostRedisplay();
		break;

	case 120: //change view
		zoom_look -= 4.0;
		glutPostRedisplay();
		break;

	case 100: //move in x up
		move_x += 4.0;
		glutPostRedisplay();
		break;

	case 99: //move in x down
		move_x -= 4.0;
		glutPostRedisplay();
		break;

	case 118: //move in y up
		move_y += 4.0;
		glutPostRedisplay();
		break;

	case 102: //move in y down
		move_y -= 4.0;
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
		yRef += 5;
		// if (yRef > 15.0) yRef = 15.0;
		glutPostRedisplay();
		break;

	case GLUT_KEY_DOWN:     //move down
		yRef -= 5;
		//if (yRef < -15.0) yRef = -15.0;
		glutPostRedisplay();
		break;
	}
}

GLvoid mousewheel(GLint wheel, GLint direction, GLint x, GLint y)
{

	if (direction==-1)
	{
		move_z += 4.0;


	}
	else if (direction==+1)
	{
		move_z -= 4.0;
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
	case LIGHT:
		if (light == true) light = false;
		else light = true;
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

void set_textures(int opt){
	switch(opt){
	case 0:
		prob_set = 0;
		prob_window = 0;
		glutPostRedisplay();
		break;
	case 1:
		prob_set = 1;
		prob_window = 1;
		glutPostRedisplay();
		break;
	case 2:
		prob_set = 2;
		prob_window = 2;
		glutPostRedisplay();
		break;
	case 3:
		prob_set = 3;
		prob_window = 3;
		glutPostRedisplay();
		break;
	case 4:
		prob_set = 4;
		prob_window = 4;
		glutPostRedisplay();
		break;
	case 5:
		prob_set = 5;
		prob_window = 5;
		glutPostRedisplay();
		break;
	}
}

void createMenu(){
	int menu, submenu;
	string tex_name;

	submenu = glutCreateMenu(set_textures);
	for (int i = 0; i < 5; i++){
		tex_name = "Set " + to_string(static_cast<long long>(i+1));
		glutAddMenuEntry(tex_name.c_str(), i);
	}

	//add entries to menu
	menu = glutCreateMenu(menuEvents);
	glutAddMenuEntry("Light",LIGHT);
	glutAddMenuEntry("Enable History", HISTORY);
	glutAddSubMenu("Change texture set", submenu);



	//attach menu to right mouse button
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void visualization(int argc, char **argv, tree<Symbol> devTree){
	valid_window = true;
	depth = devTree.max_depth();
	int mainWindow;
	cout<<"-----------------------"<<endl<<"VISUALIZATION"<<endl<<"-----------------------"<<endl<<endl<<endl;

	cout << "Shortcuts:  " << endl;
	cout << "move along x:		d - c " << endl;
	cout << "move along y:		f - v " << endl;
	cout << "move along z:		mousewheel up - down " << endl;
	//DEBUG
	//map<string,float> *karte = &config;
	//cout<<"Building Height: "<<karte->at("building_height")<<endl;

	tree<Symbol>::leaf_iterator leaf = Tree.begin_leaf();

	if(!initGL){
		initGL = true;
		glutInit(&argc, argv); // Initialize GLUT only once
	}
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE);
	glEnable(GLUT_MULTISAMPLE);
	glutInitWindowSize(1280, 720); // Set the width and height of the window
	glutInitWindowPosition(0, 0); // Set the position of the window
	mainWindow = glutCreateWindow("Buildings"); // Set the title for the window

	init();
	Tree = devTree;
	createMenu();
	glutReshapeFunc(reshape);
	glutDisplayFunc(display); 
	//glutIdleFunc(display);
	glutKeyboardFunc( keyboard );
	glutSpecialFunc( specialkeys );
	glutMouseWheelFunc(mousewheel);

	while(valid_window){
		 glutMainLoopEvent();
		display();
	}

	
}