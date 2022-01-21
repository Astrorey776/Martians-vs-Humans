#pragma once
#include "Module.h"
#include "Globals.h"

#define PIXELS_PER_METER 50.0f // if touched change METER_PER_PIXEL too
#define METER_PER_PIXEL 0.02f // this is 1 / PIXELS_PER_METER !


#define METERS_TO_PIXELS(m) ((int) floor(PIXELS_PER_METER * m))
#define PIXEL_TO_METERS(p)  ((float) METER_PER_PIXEL * p)



class Ball
{
public:
	// Position
	// You could also use an array/vector
	double x;
	double y;

	// Velocity
	double vx;
	double vy;

	// Mass
	double mass;

	// Aerodynamics stuff
	double surface; // Effective wet surface
	double cl; // Lift coefficient
	double cd; // Drag coefficient

	float Ax;
	float Ay;

	// Has physics enabled?
	bool physics_enabled = true;
};

class ModulePhysics : public Module
{
public:
	ModulePhysics(Application* app, bool start_enabled = true);
	~ModulePhysics(); 

	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

	Ball bola;

	int player1x = 800;
	int player1y = 650;

	float ax = 0;
	float ay = 0;

	float Angle;

	bool pantalla = false;


	int player2x = 150;
	int player2y = 650;

	bool amovementIzq = true;
	bool amovementDer = false;

	float massa = 0;
	float gravetat = 9.81;
	int bolay;

private:

	bool debug;
};