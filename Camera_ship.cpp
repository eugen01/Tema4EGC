#include "Camera_ship.h"
#include "math.h"
#include "Vector3D.h"
#include <freeglut.h>

Camera_ship::Camera_ship()
{
 Position = Vector3D(10.3,0.0,0.25);
 Forward =  Vector3D(-1.0,0.0,0.0);
 Right =    Vector3D(0.0,0.0,1.0);
 Up =	    Vector3D(0.0,1.0,0.0);

}

void Camera_ship::Trans_OX(GLfloat dist)
{

	Position = Position + ( Forward * dist);

}

void Camera_ship::Trans_OY(GLfloat dist)
{

	Position = Position + ( Up * dist);

}

void Camera_ship::Trans_OZ(GLfloat dist)
{

	Position = Position + ( Right * dist);

}

void Camera_ship::Render( void )
{

	Vector3D ViewPoint = Position + Forward;

	gluLookAt(	Position.x,Position.y,Position.z,
				ViewPoint.x,ViewPoint.y,ViewPoint.z,
				Up.x,Up.y,Up.z);
}