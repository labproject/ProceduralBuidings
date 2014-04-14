#ifndef __VISUALIZATION_H_INCLUDED__
#define __VISUALIZATION_H_INCLUDED__

#include	<iostream>
#include	<string>
#include	<time.h>
#include	"symbol.h"
#include	<GL/freeglut.h>
#include	"SOIL.h"
#include	"tree.hh"
#include	"Global.h"
#include	<sstream>
using namespace std;




void buildCube(GLfloat);
void buildShape(int, GLfloat);
GLint loadTextures();
void display();
void reshape(GLsizei w, GLsizei h);
void init();
GLvoid keyboard( GLubyte key, GLint x, GLint y );
GLvoid specialkeys( GLint key, GLint x, GLint y );
GLvoid mousewheel(GLint wheel, GLint direction, GLint x, GLint y);
GLvoid mouse(GLint button, GLint state, GLint x, GLint y);
void menuEvents(int);
void set_textures(int);
void createMenu();
void visualization(int argc, char **argv, tree<Symbol>);





//please do not write below this comment, thanks
#endif