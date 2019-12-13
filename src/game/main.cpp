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

	std::shared_ptr<GameObject> object;

	object = core->AddObject();
	object->AddComponent<Transform>();
	object->AddComponent<Renderer>();
	object->GetComponent<Renderer>()->SetMesh(core->resources->load<Mesh>("../src/game/models/fighter.obj"));
	object->GetComponent<Renderer>()->SetTexture(core->resources->load<Texture>("../src/game/textures/fighter.png"));
	object->GetComponent<Transform>()->position.z = -5.0f;


	object = core->AddObject();
	object->AddComponent<Transform>();
	object->AddComponent<Renderer>();
	object->GetComponent<Renderer>()->SetMesh(core->resources->load<Mesh>("../src/game/models/desert.obj"));
	object->GetComponent<Renderer>()->SetTexture(core->resources->load<Texture>("../src/game/textures/alientex.png"));
	object->GetComponent<Transform>()->position.y = -5.0f;
	object->GetComponent<Transform>()->scale = glm::vec3(5, 5, 5);

	object = core->AddObject();
	object->AddComponent<Transform>();
	object->AddComponent<Renderer>();
	object->GetComponent<Renderer>()->SetMesh(core->resources->load<Mesh>("../src/game/models/desert.obj"));
	object->GetComponent<Renderer>()->SetTexture(core->resources->load<Texture>("../src/game/textures/alientex.png"));
	object->GetComponent<Transform>()->position.y = 15.0f;
	object->GetComponent<Transform>()->rotation.z = glm::radians(180.0f);
	object->GetComponent<Transform>()->scale = glm::vec3(5, 5, 5);

	object = core->AddObject();
	object->AddComponent<Transform>();
	object->AddComponent<Renderer>();
	object->GetComponent<Renderer>()->SetMesh(core->resources->load<Mesh>("../src/game/models/desert.obj"));
	object->GetComponent<Renderer>()->SetTexture(core->resources->load<Texture>("../src/game/textures/alientex.png"));
	object->GetComponent<Transform>()->position.x = 20;
	object->GetComponent<Transform>()->rotation.z = glm::radians(90.0f);
	object->GetComponent<Transform>()->scale = glm::vec3(5, 5, 5);

	object = core->AddObject();
	object->AddComponent<Transform>();
	object->AddComponent<Renderer>();
	object->GetComponent<Renderer>()->SetMesh(core->resources->load<Mesh>("../src/game/models/desert.obj"));
	object->GetComponent<Renderer>()->SetTexture(core->resources->load<Texture>("../src/game/textures/alientex.png"));
	object->GetComponent<Transform>()->position.x = -20;
	object->GetComponent<Transform>()->rotation.z = glm::radians(-90.0f);
	object->GetComponent<Transform>()->scale = glm::vec3(5, 5, 5);

	object = core->AddObject();
	object->AddComponent<Transform>();
	object->AddComponent<Renderer>();
	object->GetComponent<Renderer>()->SetMesh(core->resources->load<Mesh>("../src/game/models/desert.obj"));
	object->GetComponent<Renderer>()->SetTexture(core->resources->load<Texture>("../src/game/textures/alientex.png"));
	object->GetComponent<Transform>()->position.z = -20;
	object->GetComponent<Transform>()->rotation.x = glm::radians(90.0f);
	object->GetComponent<Transform>()->scale = glm::vec3(5, 5, 5);

	object = core->AddObject();
	object->AddComponent<Transform>();
	object->AddComponent<Renderer>();
	object->GetComponent<Renderer>()->SetMesh(core->resources->load<Mesh>("../src/game/models/desert.obj"));
	object->GetComponent<Renderer>()->SetTexture(core->resources->load<Texture>("../src/game/textures/alientex.png"));
	object->GetComponent<Transform>()->position.z = 20;
	object->GetComponent<Transform>()->rotation.x = glm::radians(-90.0f);
	object->GetComponent<Transform>()->scale = glm::vec3(5, 5, 5);

	object = core->AddObject();
	object->AddComponent<Transform>();
	object->AddComponent<DirectionalLight>();
	object->GetComponent<DirectionalLight>()->diffuse = glm::vec3(0.3f, 0.3f, 0.3f);
	object->GetComponent<DirectionalLight>()->specular = glm::vec3(0.3f, 0.3f, 0.3f);
	object->GetComponent<Transform>()->rotation = glm::vec3(glm::radians(-45.0f), glm::radians(-40.0f), 0.0f);

	object = core->AddObject();
	object->AddComponent<Transform>();
	object->AddComponent<Renderer>();
	object->GetComponent<Renderer>()->SetMesh(core->resources->load<Mesh>("../src/game/models/cube.obj"));
	object->GetComponent<Renderer>()->SetTexture(core->resources->load<Texture>("../src/game/textures/dice.png"));
	object->AddComponent<PointLight>();
	object->GetComponent<PointLight>()->diffuse = glm::vec3(10.0f, 10.0f, 10.0f);
	object->GetComponent<PointLight>()->specular = glm::vec3(0.3f, 0.3f, 0.3f);
	object->GetComponent<Transform>()->position = glm::vec3(0.0f, 7.0f, 3.5f);


	
	object = core->AddObject();
	object->AddComponent<Transform>();
	object->AddComponent<Renderer>();
	object->GetComponent<Renderer>()->SetMesh(core->resources->load<Mesh>("../src/game/models/cube.obj"));
	object->GetComponent<Renderer>()->SetTexture(core->resources->load<Texture>("../src/game/textures/dice.png"));
	object->AddComponent<PointLight>();
	object->GetComponent<PointLight>()->diffuse = glm::vec3(10.0f, 10.0f, 10.0f);
	object->GetComponent<PointLight>()->specular = glm::vec3(0.3f, 0.3f, 0.3f);
	object->GetComponent<Transform>()->position = glm::vec3(0.0f, 1.0f, 0.5f);
	

	core->lights = core->GetComponents<PointLight>();
	core->renderers = core->GetComponents<Renderer>();

	const Uint8 *state = SDL_GetKeyboardState(NULL);
	bool quit = false;
	while (!quit)
	{
		state = SDL_GetKeyboardState(NULL);
		if (state[SDL_SCANCODE_I]) object->GetComponent<Transform>()->position.z += 0.2f;
		if (state[SDL_SCANCODE_K]) object->GetComponent<Transform>()->position.z -= 0.2f;
		if (state[SDL_SCANCODE_J]) object->GetComponent<Transform>()->position.x -= 0.2f;
		if (state[SDL_SCANCODE_L]) object->GetComponent<Transform>()->position.x += 0.2f;
		if (state[SDL_SCANCODE_U]) object->GetComponent<Transform>()->position.y -= 0.2f;
		if (state[SDL_SCANCODE_H]) object->GetComponent<Transform>()->position.y += 0.2f;


		if (state[SDL_SCANCODE_W]) core->mainCamera->GetComponent<Transform>()->position -= core->mainCamera->GetComponent<Transform>()->forward * 0.2f;
		if (state[SDL_SCANCODE_S]) core->mainCamera->GetComponent<Transform>()->position += core->mainCamera->GetComponent<Transform>()->forward * 0.2f;
		if (state[SDL_SCANCODE_A]) core->mainCamera->GetComponent<Transform>()->position -= core->mainCamera->GetComponent<Transform>()->right * 0.2f;
		if (state[SDL_SCANCODE_D]) core->mainCamera->GetComponent<Transform>()->position += core->mainCamera->GetComponent<Transform>()->right * 0.2f;
		if (state[SDL_SCANCODE_R]) core->mainCamera->GetComponent<Transform>()->position.y += 0.5f;
		if (state[SDL_SCANCODE_F]) core->mainCamera->GetComponent<Transform>()->position.y -= 0.5f;

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