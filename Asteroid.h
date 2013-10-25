#include<freeglut.h>
#include "Vector3D.h"
class Asteroid {

private:
	float size;
	float speed;
	Vector3D position;
	int timer; 
public:

	Asteroid();

	Asteroid(float,Vector3D);

	void Draw();
	float get_speed();
	void set_speed(float s);
	float get_size();
	void set_size(float s);
	
	void set_position(Vector3D);
	Vector3D get_position();
	float get_x();

	void start_timer();
	int get_timer();

};