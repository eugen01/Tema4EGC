
#include <freeglut.h>
#include "Vector3D.h"

class Camera_ship
{

private:
	Vector3D Forward;
	Vector3D Right;	
	Vector3D Up;
	Vector3D Position;

public:

	Camera_ship();

	void Render();
	
	void Trans_OX(GLfloat dist);
	void Trans_OY(GLfloat dist);
	void Trans_OZ(GLfloat dist);

};