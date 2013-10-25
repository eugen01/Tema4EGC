#include "Vector3D.h"
class Ship {

private:
	Vector3D Forward;
	Vector3D Right;	
	Vector3D Up;
	Vector3D Position;

public:
	Ship::Ship();

	void Draw();

	void TranslateForward(GLfloat dist);
	void TranslateUp(GLfloat dist);
	void TranslateRight(GLfloat dist);

	Vector3D get_position(); 

};