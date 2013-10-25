#include "Camera_din.h"
#include "math.h"
#include "Vector3D.h"
#include <freeglut.h>

Camera_din::Camera_din()
{
 Position = Vector3D(0.0,0.0,30.0);
 Forward =  Vector3D(0.0,0.0,-1.0);
 Right =    Vector3D(1.0,0.0,0.0);
 Up =	    Vector3D(0.0,1.0,0.0);

}

void Camera_din::Trans_OX(GLfloat dist)
{

	Position = Position + ( Right * dist);

}

void Camera_din::Trans_OY(GLfloat dist)
{

	Position = Position + ( Up * dist);

}

void Camera_din::Trans_OZ(GLfloat dist)
{

	Position = Position + ( Forward * dist);

}

void Camera_din::Render( void )
{

	Vector3D ViewPoint = Position + Forward;

	gluLookAt(	Position.x,Position.y,Position.z,
				ViewPoint.x,ViewPoint.y,ViewPoint.z,
				Up.x,Up.y,Up.z);
}