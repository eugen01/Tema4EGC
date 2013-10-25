#include <stdlib.h>
#include <freeglut.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include "Camera_din.h"
#include "Camera_ship.h"
#include "Camera_ast.h"
#include "Asteroid.h"
#include "Ship.h"
#include "Vector3D.h"
#include "Spot.h"

//Numarul de asteroizi prezenti pe ecran
#define ast_nr 15
int shield_hits=3;
float shield_radius = 1.0;

int mainWindow;
Ship *ship;
Camera_din *cam_d;
Camera_ship *cam_s;
Camera_ast *cam_a;

Spot *s1,*s2;

float loc=0;
int cam=1;
//parametrii scenei
float sceneH=18.0,sceneW=25.0,sceneD=18.0;

//deplasarile navei
float shipx=0,shipy=0,shipz=0;

//viteza de delasare a navei
float step =0.2;


Asteroid *ast[ast_nr];
int obiect =-1;

bool picking=false, camera_selection=false;

void spotlights()
{
	GLfloat position1[] = {10.0,0.0,0.3,1.0};
	GLfloat position2[] = {10.0,0.0,-0.3,1.0};
	
	GLfloat dir[]={-1.0,0.0,0.0};

	s1=new Spot(position1,dir,35,GL_LIGHT2);
	s2=new Spot(position2,dir,35,GL_LIGHT3);

}

void randomize_asteroid(Asteroid *aster)
{
float size = (rand() %120) + 20;

size *= 0.01;

float  posy,posz ;
int h=sceneH,d=sceneD;
posy = (rand() %h - h/2) ;
posz = (rand() %d - d/2) ;

float speed = rand() % 12 + 2 ;
speed *= 0.01;

aster->set_size(size);
aster->set_speed(speed);
aster->set_position(Vector3D(-sceneW/2,posy,posz));

}

void check_collisions()
{
	Vector3D s = ship->get_position();
	s.x+=shipx;
	s.y+=shipy;
	s.z+=shipz;

for(int i=0;i<ast_nr;i++)
{
	Vector3D a = ast[i]->get_position();

	float dist = sqrt(pow(s.x-a.x,2)+pow(s.y-a.y,2)+pow(s.z-a.z,2));

	if (dist< 1.51*ast[i]->get_size()+shield_radius)
	{randomize_asteroid(ast[i]);
	 shield_hits--;}
}

}

void draw_asteroids()
{
for (int i=0;i<ast_nr;i++)
{	
	glPushName(i);
	if((ast[i]->get_x()>=sceneW/2)||(ast[i]->get_timer() == 1))
	{ randomize_asteroid(ast[i]);
	ast[i]->Draw();
		}
	else
	{
	ast[i]->Draw();
	}
	glPopName();
}
}

void asteroid_cam(int i)
{
Vector3D shipPos,astPos,camPos;

shipPos = ship->get_position();
shipPos.x +=shipx;
shipPos.y +=shipy;
shipPos.z += shipz;

astPos = ast[i]->get_position();

Vector3D fwd = shipPos - astPos;

camPos = astPos + (fwd /5);

cam_a = new Camera_ast(camPos,fwd,i);

cam=3;
}

void cam_move ()
{
	int a = cam_a->get_index();
	Vector3D astPos,camPos;

	astPos = ast[a]->get_position();

	Vector3D fwd = Vector3D(-1.0,0.0,0.0);

	camPos = astPos + (fwd * ast[a]->get_speed()*120);

	cam_a->set_position(camPos);
	

}


void shield()
{
	glEnable(GL_BLEND);
	glPushMatrix();
	
	glTranslatef(10.8,0,0.2);
	glTranslatef(shipx,shipy,shipz);
	GLfloat material_shield []= {0.0,1.0,0.0,0.2}; 
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,material_shield);
	glutSolidSphere(shield_radius,25,25);
	
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glPopMatrix();
	//glEnable(GL_BLEND);
}

bool l = true;

void init()
{
ship = new Ship();
	cam_d =new Camera_din();
	cam_s =new Camera_ship();

for (int i=0;i<ast_nr;i++)
{
float size = (rand() %120) + 20;

size *= 0.01;

float posx , posy,posz ;
int w=sceneW,h=sceneH,d=sceneD;
posx = (rand() %w -  w/2) ;
posy = (rand() %h - h/2) ;
posz = (rand() %d - d/2) ;

float speed = rand() % 12 + 2 ;
speed *= 0.01;

ast[i] = new Asteroid(size,Vector3D(posx,posy,posz));
ast[i]->set_speed(speed);
//ast[i]->Draw();
}
spotlights();

}

void drawScene()
{
	if(shield_hits > -1)
	{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	switch(cam)
	{case 1:{cam_d->Render();}break;
	 case 2:{cam_s->Render();}break;
	 case 3:{cam_a->render();
			 cam_move();}break;
    }
	//


	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_ALPHA_TEST);
	GLfloat star1[] = {0.5,0.5,1.0,0.2};
	GLfloat star2[] = {1.0,1.0,1.0,0.2};
	
	glLightfv(GL_LIGHT0, GL_AMBIENT, star1);
	glLightfv(GL_LIGHT1, GL_AMBIENT, star2);

	if (l){
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	s1->turn_on();
	s2->turn_on();
	}
	else
	{glDisable(GL_LIGHT0);
	glDisable(GL_LIGHT1);
	//s1->turn_off();
	//s2->turn_on();
	}


	glDepthFunc(GL_LESS);
	glPushMatrix();
	glScalef(sceneW,sceneH,sceneD);
	glutWireCube(1);
	glPopMatrix();

	
	glPushMatrix();
	
	glTranslatef(10.0,-0.5,-0.5);
	glTranslatef(shipx,shipy,shipz);
	glScalef(1.5,1.5,1.5);
	
	ship->Draw();
	glPopMatrix();
	

	draw_asteroids();
	check_collisions();
	
	if (! picking)
	if (shield_hits>0)
		shield();

	if (!camera_selection)
	{ast[obiect]->start_timer();
	obiect = -1;}
	else
	{
	if (obiect!=-1)	
	{asteroid_cam(obiect);
	camera_selection = false;
	obiect = -1;}
	}

	glutSwapBuffers();
	}
	else
	{glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glutSwapBuffers();
	}

	}

void display()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	drawScene();
}

void keyboard(unsigned char key , int x , int y)
{

	switch(key)
	{
	case 27:	//esc
			exit(0);
			break;

	case 'w': {cam_d->Trans_OZ(0.1);}break;
	
	case 's': {cam_d->Trans_OZ(-0.1);}break;

	case 'a': {cam_d->Trans_OX(-0.1);}break; 
	case 'd': {cam_d->Trans_OX(0.1);}break;
	case 'r': {cam_d->Trans_OY(0.1);}break;
	case 'f': {cam_d->Trans_OY(-0.1);}break;


	case '1':{cam=1;}break;
	case '2':{cam=2;}break;
	case '3':{camera_selection = true;}break;

	case 'k' :{
			
			if(shipx < sceneW/2 - 11)
			{shipx+=step; 
			 cam_s->Trans_OX(-step);
			 s1->Trans_OX(-step);
			 s2->Trans_OX(-step);
			}
			  
			  }break;
		
	case 'i': {
			if(shipx > -sceneW/2 - 11) 
			{shipx-=step;
			cam_s->Trans_OX(step);
			 s1->Trans_OX(step);
			 s2->Trans_OX(step);}
			  
			  }break;
		
	case 'p': {
			if(shipy < sceneH/2)   
			{shipy+=step;
			cam_s->Trans_OY(step);
			s1->Trans_OY(step);
			s2->Trans_OY(step);}
			  }break;

	case ';': {
			if(shipy > -sceneH/2)  
			{shipy-=step;
			cam_s->Trans_OY(-step);
			s1->Trans_OY(-step);
			s2->Trans_OY(-step);}
			  }break;

	case 'j' :{
			
			if(shipz < sceneD/2)
			{shipz +=step;
			cam_s->Trans_OZ(step);
			s1->Trans_OZ(step);
			s2->Trans_OZ(step);}
	
			  }break;
	case 'l' :{
			  
			if(shipz > - sceneD/2)
			{shipz -=step;
			cam_s->Trans_OZ(-step);
			s1->Trans_OZ(-step);
			s2->Trans_OZ(-step);}
			  
			  }break;
		
	case 'q' : {
			   l=!l;
			   }break;
	}

}

void processhits (GLint hits, GLuint buffer[])
{
   int i;
   GLuint names, *ptr, minZ,*ptrNames, numberOfNames;

   // pointer la inceputul bufferului ce contine hit recordurile
   ptr = (GLuint *) buffer;
   // se doreste selectarea obiectului cel mai aproape de observator
   minZ = 0xffffffff;
   for (i = 0; i < hits; i++) 
   {
      // numarul de nume numele asociate din stiva de nume
      names = *ptr;
	  ptr++;
	  // Z-ul asociat hitului - se retine 
	  if (*ptr < minZ) {
		  numberOfNames = names;
		  minZ = *ptr;
		  // primul nume asociat obiectului
		  ptrNames = ptr+2;
	  }
	  
	  // salt la urmatorul hitrecord
	  ptr += names+2;
  }

  // identificatorul asociat obiectului
  ptr = ptrNames;
  
  obiect = *ptr;
     
}

void pick(int x, int y)
{
	// buffer de selectie
	GLuint buffer[1024];

	// numar hituri
	GLint nhits;

	// coordonate viewport curent
	GLint	viewport[4];

	// se obtin coordonatele viewportului curent
	glGetIntegerv(GL_VIEWPORT, viewport);
	// se initializeaza si se seteaza bufferul de selectie
	memset(buffer,0x0,1024);
	glSelectBuffer(1024, buffer);
	
	// intrarea in modul de selectie
	glRenderMode(GL_SELECT);

	// salvare matrice de proiectie curenta
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	// se va randa doar intr-o zona din jurul cursorului mouseului de [1,1]
	glGetIntegerv(GL_VIEWPORT,viewport);
	gluPickMatrix(x,viewport[3]-y,1.0f,1.0f,viewport);

	gluPerspective(45,(viewport[2]-viewport[0])/(GLfloat) (viewport[3]-viewport[1]),0.1,1000);
	glMatrixMode(GL_MODELVIEW);

	// se "deseneaza" scena : de fapt nu se va desena nimic in framebuffer ci se va folosi bufferul de selectie
	picking = true;
	drawScene();
	picking = false;
	// restaurare matrice de proiectie initiala
	glMatrixMode(GL_PROJECTION);						
	glPopMatrix();				

	glMatrixMode(GL_MODELVIEW);
	// restaurarea modului de randare uzual si obtinerea numarului de hituri
	nhits=glRenderMode(GL_RENDER);	
	
	// procesare hituri
	if(nhits != 0)
		processhits(nhits,buffer);
	else
		obiect=-1;

				
}


void mouse(int buton, int stare, int x, int y)
{
	switch(buton)
	{
	// Am apasat click stanga : porneste animatia si realizeaza picking
	case GLUT_LEFT_BUTTON:
		if(stare == GLUT_DOWN)
		{
			// in aceasta variabila se va intoarce obiectul la care s-a executat pick
			obiect = -1;

			pick(x,y);
		}
		break;

	}
}

void reshape(int w , int h)
{

	glViewport(0,0,w,h);

	//set proiectie
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45,(float)w/(float)h,0.2,100);


}




void idle()
{
glutPostRedisplay();
}
int main(int argc , char** argv)
{

	glutInit(&argc,argv);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	
	int w = 1000 , h= 600;

	glutInitWindowSize(w,h);

	glutInitWindowPosition(100,100);

	mainWindow = glutCreateWindow("Tema4");

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutIdleFunc(idle);

	glClearColor(0.0,0.0,0.0,1.0);
	

	init();
	glutMainLoop();
	return 0;
}