#ifndef __GLOBAL_H_INCLUDED__
#define __GLOBAL_H_INCLUDED__

class Global
{
public:
	//VARIABLES
	float windowWidth;
	float windowHeight;

	float buildingWidth;  //X
	float buildingHeight; //Y
	float buildingDepth;  //Z
	//...

	//MEMBERFUNCTIONS	
	float rand(float,float);

private:
	//CONSTRUCTORS
	Global();
	//...

};
//please do not write below this comment, thanks
#endif