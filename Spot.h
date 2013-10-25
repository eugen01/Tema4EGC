#include <freeglut.h>
#include "Vector3D.h"

class Spot {

private : 

	GLfloat Position[4];
	GLfloat Direction[3];
	GLfloat angle;
	int index;
	
public :
	Spot(GLfloat *,GLfloat * ,float,int);

	void turn_on();
	void turn_off();

	void Trans_OX(GLfloat dist);
	void Trans_OY(GLfloat dist);
	void Trans_OZ(GLfloat dist);

};
