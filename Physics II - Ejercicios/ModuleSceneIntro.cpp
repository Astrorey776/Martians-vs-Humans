#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"



ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	fondo = App->textures->Load("Ejercicio/Assets/Marte.png");
	soldado1T = App->textures->Load("Ejercicio/Assets/Alien.png");
	soldado2 = App->textures->Load("Ejercicio/Assets/Soldado2.png");
	bola = App->textures->Load("Ejercicio/Assets/Misil.png");
	Launcher = App->textures->Load("Ejercicio/Assets/Arma2.png");
	win = App->textures->Load("Ejercicio/Assets/Win_Screen.png");
	lose = App->textures->Load("Ejercicio/Assets/Lose_screen.png");
	intro = App->textures->Load("Ejercicio/Assets/Intro_screen.png");

	LOG("Loading Intro assets");
	bool ret = true;

	App->renderer->camera.x = App->renderer->camera.y = 0;

	return ret;
}


// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	App->renderer->Blit(fondo, 0, 0, NULL);
	return UPDATE_CONTINUE;
}
