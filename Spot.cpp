#include "Spot.h"
#include <freeglut.h>

Spot::Spot(GLfloat *pos,GLfloat * dir , float an ,  int ind){

	for(int i=0;i<4;i++)
		Position[i]=pos[i];
	for(int i=0;i<3;i++)
		Direction[i]=dir[i];
	
	angle=an;
	index = ind;
}
void Spot::turn_on(){
	
	GLfloat difuse[] = {4.0,4.0,4.0,1.0};
	glLightfv(index, GL_DIFFUSE,difuse);
	
	

	glLightfv(index,GL_POSITION,Position);
	glLightfv(index,GL_SPOT_DIRECTION,Direction);
	glLightfv(index,GL_SPOT_CUTOFF,&angle);
	glLightf(index , GL_SPOT_EXPONENT, 2);
	glLightf(index,GL_CONSTANT_ATTENUATION,1);
	glLightf(index,GL_LINEAR_ATTENUATION,0.2f);
	glEnable(index);
}
void Spot::turn_off()
{
glDisable(index);
}

void Spot::Trans_OX(GLfloat dist)
{

	Position[0] +=dist;

}

void Spot::Trans_OY(GLfloat dist)
{

	Position[1] += dist;

}

void Spot::Trans_OZ(GLfloat dist)
{
	Position[2] += dist;

}