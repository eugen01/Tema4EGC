#include"Asteroid.h"
#include "Vector3D.h"

Asteroid::Asteroid() 
{

size = 1;
}

Asteroid::Asteroid (float x,Vector3D pos)
{
	position = Vector3D(pos.x,pos.y,pos.z);
	size = x;
	timer = -1;
}

void Asteroid::Draw()
{
	position.x+=speed;
	GLfloat material_ast []= {0.6,0.4,0.0,1.0};
	if (timer != -1)
	{ material_ast[0] = 1.0;
	  material_ast[1] = 0.0;
	  timer--;
	}
	if (timer == 0)
	{timer = -1;}

	glPushMatrix();
	
	glTranslatef(position.x,position.y,position.z);
	 
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,material_ast);
	glScalef(size,size,size);
	glutSolidDodecahedron();
	GLfloat material_cont []= {0.6,0.4,0.0,1.0}; 
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,material_ast);
	glScalef(1.01,1.01,1.01);
	glutWireDodecahedron();
	glPopMatrix();

}

float Asteroid::get_speed()
{return speed;}
float Asteroid::get_size()
{return size;}

void Asteroid::set_speed(float x)
{this->speed = x;}
void Asteroid::set_size(float x)
{this->size =x; }

void Asteroid::set_position(Vector3D pos)
{
position = Vector3D(pos.x,pos.y,pos.z);
}
float Asteroid::get_x()
{return position.x;}

void Asteroid::start_timer()
{
timer = 10;
}
int Asteroid::get_timer()
{
return timer;
}
Vector3D Asteroid::get_position()
{
return position;
}