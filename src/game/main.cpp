#include <iostream>
#include <HowardSpecial2/HowardSpecial2.h>

int main(){
	std::shared_ptr<Core> core = core->Initialize();
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	core->mainCamera = core->AddObject();
	core->mainCamera->AddComponent<Transform>();
	core->mainCamera->AddComponent<Camera>();
	core->mainCamera->AddComponent<SoundSource>();
	core->mainCamera->GetComponent<SoundSource>()->SetSound(core->resources->load<Sound>("../src/game/models/dixie_horn.ogg"));

	std::shared_ptr<GameObject> object = core->AddObject();
	object->AddComponent<Transform>();
	//object->AddComponent<Renderer>("../src/game/models/fighter.obj", "../src/game/textures/fighter.png");
	object->AddComponent<Renderer>();
	object->GetComponent<Renderer>()->SetMesh(core->resources->load<Mesh>("../src/game/models/fighter.obj"));
	object->GetComponent<Renderer>()->SetTexture(core->resources->load<Texture>("../src/game/textures/fighter.png"));
	object->GetComponent<Transform>()->position.z = -5.0f;

	const Uint8 *state = SDL_GetKeyboardState(NULL);
	bool quit = false;
	while (!quit)
	{
		state = SDL_GetKeyboardState(NULL);
		if (state[SDL_SCANCODE_W]) core->mainCamera->GetComponent<Transform>()->position -= core->mainCamera->GetComponent<Transform>()->forward;
		if (state[SDL_SCANCODE_S]) core->mainCamera->GetComponent<Transform>()->position += core->mainCamera->GetComponent<Transform>()->forward;
		if (state[SDL_SCANCODE_A]) core->mainCamera->GetComponent<Transform>()->position -= core->mainCamera->GetComponent<Transform>()->right;
		if (state[SDL_SCANCODE_D]) core->mainCamera->GetComponent<Transform>()->position += core->mainCamera->GetComponent<Transform>()->right;
		if (state[SDL_SCANCODE_SPACE]) core->mainCamera->GetComponent<Transform>()->position.y += 0.5f;
		if (state[SDL_SCANCODE_LCTRL]) core->mainCamera->GetComponent<Transform>()->position.y -= 0.5f;

		if (state[SDL_SCANCODE_RIGHT]) core->mainCamera->GetComponent<Transform>()->rotation.y -= 0.05f;
		if (state[SDL_SCANCODE_LEFT]) core->mainCamera->GetComponent<Transform>()->rotation.y += 0.05f;
		if (state[SDL_SCANCODE_UP]) core->mainCamera->GetComponent<Transform>()->rotation.x += 0.05f;
		if (state[SDL_SCANCODE_DOWN]) core->mainCamera->GetComponent<Transform>()->rotation.x -= 0.05f;

		if (state[SDL_SCANCODE_P]) core->mainCamera->GetComponent<SoundSource>()->Play();
		SDL_Event event = { 0 };

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT) //end the game if hit escape or close the window then exit the game
			{
				quit = true;
			}
			if (event.type == SDL_KEYDOWN)
			{
				if (event.key.keysym.sym == SDLK_ESCAPE) {
					quit = true;
				}
			}
		}
		//core->Update();
		core->Display();
	}

	core->Stop();
	return 0;
}