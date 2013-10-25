#include <freeglut.h>
#include "Vector3D.h"

class Camera_ast {

private:
	Vector3D Position;
	Vector3D Forward;
	Vector3D Up;
	Vector3D Right;
	int ast_index;

public:
	Camera_ast (Vector3D,Vector3D,int);
	
	void render ();
	void set_position(Vector3D);
	int get_index();
	

};