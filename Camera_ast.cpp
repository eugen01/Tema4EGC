#include"Camera_ast.h"
#include <freeglut.h>
#include"Vector3D.h"

Camera_ast::Camera_ast(Vector3D pos , Vector3D fwd ,int ind)
{
Position  = Vector3D (pos.x,pos.y,pos.z);
Forward  = Vector3D (fwd.x,fwd.y,fwd.z);
Up = Vector3D (0.0,1.0,0.0);
ast_index = ind;
}
void Camera_ast::set_position(Vector3D pos)
{
Position = Vector3D (pos.x,pos.y,pos.z);

}
void Camera_ast::render()
{

	Vector3D ViewPoint = Position + Forward;

	gluLookAt(	Position.x,Position.y,Position.z,
				ViewPoint.x,ViewPoint.y,ViewPoint.z,
				Up.x,Up.y,Up.z);
}

int Camera_ast::get_index()
{
return ast_index;
}