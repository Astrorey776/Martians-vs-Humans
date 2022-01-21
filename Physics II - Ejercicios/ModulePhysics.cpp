#include "Globals.h"
#include "Application.h"
#include "ModulePhysics.h"
#include "math.h"


ModulePhysics::ModulePhysics(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	debug = true;
}

// Destructor
ModulePhysics::~ModulePhysics()
{
}

bool ModulePhysics::Start()
{
	LOG("Creating Physics 2D environment");
	// Create a ball
	// You should create this object in the header of the class, so that everyone within the class can access it.
	// Set physics properties of the ball

	bola.mass = 10; // kg
	bola.surface = 2; // m^2
	bola.cd = 0.4;
	bola.cl = 1.2;

	// Set initial position and velocity of the ball
    bola.y = 1.0;
	bola.x = 10.0;
	bola.vx = 0.0;
	bola.vy = 0.0;
	return true;
}


update_status ModulePhysics::PreUpdate()
{
/*  Pas 1: Calculem forces(Gravetat)
	Pas 2: Apliquem la 2a Llei de Newton: F=m*a
	Pas 3: Introduim l'integrador

	        ->Euler:
			       -> BWD -> x+= v * dt
				   -> FWD -> v+= a * dt

            ->Verlet:
			        ->Veloc -> x+= v * dt + 1/2 * a * dt^2
                            -> v+= a * dt
	Pas 4: Collisions



	Formas de hacer el campo gravitatorio:

	1-> F=-G*(m1*m2)/r^2
	2-> F=F=ct
	3->
	*/
	float fgravetat = bola.mass * gravetat;
	float fy = fgravetat; //Li sumem mes forses al futur
	float fx=0;  //Li sumem mes forses al futur

	//Caclculem l'acceleracio sobre la bola deguda a la forsa x forsa y

	 ay=fy/bola.mass;
	 ax=fx/bola.mass;

	//Apliquem metode de integracio per updatejar la pos de la bola 

	float dt = 1.0 / 60.0;

	//Posicio

	bola.x += bola.vx * dt + 0.5 * ax * dt * dt;
    bola.y += bola.vy * dt + 0.5 * ay * dt * dt;

	bola.vx += ax * dt;
	bola.vy += ay * dt;



	return UPDATE_CONTINUE;
}


update_status ModulePhysics::Update()
{

	return UPDATE_CONTINUE;
}
update_status ModulePhysics::PostUpdate()
{
	
	SDL_Rect cbola{ METERS_TO_PIXELS(bola.x),METERS_TO_PIXELS(bola.y),32,32 };
	SDL_Rect soldado1{ player1x,player1y,64,64 };
	SDL_Rect soldado2{player2x,player2y,64,64 };

	SDL_Rect lwall{ 0,0,10,800 };
	SDL_Rect rwall{ 1015,0,10,800 };
	SDL_Rect ground{ 0,715,1015,50 };
	SDL_Rect sky{ 0,0,1015,10 };

	//Show Collisions

	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_REPEAT) {
		App->renderer->DrawQuad(lwall, 0, 255, 0);
		App->renderer->DrawQuad(rwall, 0, 255, 0);
		App->renderer->DrawQuad(ground, 0, 255, 0);
		App->renderer->DrawQuad(sky, 0, 255, 0);

		App->renderer->DrawQuad(soldado2, 0, 0, 255);
		App->renderer->DrawQuad(soldado1, 0, 0, 255);
		App->renderer->DrawQuad(cbola, 200, 100, 0);
	}
	
	//Moviment Alien (No acabat)

	if (player1x <= 850 && amovementIzq==true) {
		player1x -= 1;
	}
	if (player1x >= 850) {
		player1x -= 1;
		amovementDer = false;
		amovementIzq = true;
	}
	if (player1x <= 500) {
		amovementDer = true;
		amovementIzq = false;
	}
	if (player1x <= 500 && amovementDer==true) {
		player1x += 1;
		amovementIzq = false;
	}
	App->renderer->Blit(App->scene_intro->intro, 0, 0, NULL);

	if (pantalla == true) {
		App->renderer->Blit(App->scene_intro->Launcher, player2x + 5, player2y - 7, NULL, 1.0f, Angle);
		App->renderer->Blit(App->scene_intro->soldado1T, player1x, player1y, NULL);
		App->renderer->Blit(App->scene_intro->soldado2, player2x, player2y, NULL);
		App->renderer->Blit(App->scene_intro->bola, METERS_TO_PIXELS(bola.x), METERS_TO_PIXELS(bola.y), NULL);
	}


	//Collisions bola

	if (METERS_TO_PIXELS(bola.x) + 32 >= 1015) {
		bola.vx=0;
    }
	if (METERS_TO_PIXELS(bola.x)<= 8) {
		bola.vx = 0;
	}
	if (METERS_TO_PIXELS(bola.y)<= 8) {
		bola.vy = 0;
	}
	if (METERS_TO_PIXELS(bola.y) >=685 ) {
		bola.vy = 0;
		
	}

	//Collisions player

	if (player2x<=10) {
		player2x = 10;
	}

	if (player2x >= 950) {
		player2x = 950;
	}
	
	//Lose condition

	if (player2x >= player1x) {
		App->renderer->Blit(App->scene_intro->lose, 0, 0);
	}

	//Win condition

	/*if (bola.x >= player1x && bola.y >= player1y) {
		App->renderer->Blit(App->scene_intro->win, 0, 0);
	}*/


	//Controls testing bola

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN) {
		bola.vx += bola.vx + 1;
	}

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN) {
		bola.vx -= bola.vx + 1;
	}

	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN) {
		bola.vy -= bola.vy + 2;
	}


	//Controls player
	
	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {
		player2x += 2;
	}
	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
		player2x -= 2;
	}
	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) {
		if (Angle >= -60) {
			Angle--;
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) {
		if (Angle <= 60) {
			Angle++;
		}
	}	
	if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN) {
		App->textures->Unload(App->scene_intro->intro);
		pantalla = true;
	}
	if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_REPEAT) {
		App->renderer->Blit(App->scene_intro->win, 0, 0);
		pantalla = false;
	}
	if (App->input->GetKey(SDL_SCANCODE_F3) == KEY_REPEAT) {
		App->renderer->Blit(App->scene_intro->lose, 0, 0);
		pantalla = false;
	}



	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {
		bola.x = player2x+10;
		bola.y = player2y+10;
		bola.vx += 1;
	}

	if(App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	if(!debug)
		return UPDATE_CONTINUE;
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModulePhysics::CleanUp()
{
	LOG("Destroying physics world");

	// Delete the whole physics world!

	return true;
}
