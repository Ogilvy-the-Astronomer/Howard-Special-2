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
	object->GetComponent<Renderer>()->SetMesh(core->resources->load<Mesh>("../src/game/models/rocks.obj"));
	object->GetComponent<Renderer>()->SetTexture(core->resources->load<Texture>("../src/game/textures/rocks.png"));
	object->GetComponent<Transform>()->scale = glm::vec3(1.0f);
	//object->GetComponent<Transform>()->position.z = 100.0f;


	
	object = core->AddObject();
	object->AddComponent<Transform>();
	object->AddComponent<Renderer>();
	object->GetComponent<Renderer>()->SetMesh(core->resources->load<Mesh>("../src/game/models/campsite.obj"));
	object->GetComponent<Renderer>()->SetTexture(core->resources->load<Texture>("../src/game/textures/campsite.png"));
	object->GetComponent<Transform>()->position.z = 70.0f;
	object->GetComponent<Transform>()->scale = glm::vec3(2.0f);

	/*
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
*/
	object = core->AddObject();
	object->AddComponent<Transform>();
	object->AddComponent<DirectionalLight>();
	//object->GetComponent<DirectionalLight>()->diffuse = glm::vec3(0.1f, 0.1f, 0.1f);
	object->GetComponent<DirectionalLight>()->ambient = glm::vec3(0.5f, 0.5f, 0.5f);
	//object->GetComponent<DirectionalLight>()->specular = glm::vec3(0.1f, 0.1f, 0.1f);
	object->GetComponent<Transform>()->rotation = glm::vec3(glm::radians(40.0f), glm::radians(40.0f), glm::radians(40.0f));

	
	std::shared_ptr<GameObject> object2;
	object2 = core->AddObject();
	object2->AddComponent<Transform>();
	object2->AddComponent<Renderer>();
	object2->GetComponent<Renderer>()->SetMesh(core->resources->load<Mesh>("../src/game/models/cube.obj"));
	object2->GetComponent<Renderer>()->SetTexture(core->resources->load<Texture>("../src/game/textures/dice.png"));
	object2->AddComponent<PointLight>();
	object2->GetComponent<PointLight>()->diffuse = glm::vec3(10.0f, 10.0f, 10.0f);
	//object2->GetComponent<PointLight>()->specular = glm::vec3(0.3f, 0.3f, 0.3f);
	object2->GetComponent<Transform>()->position = glm::vec3(0.0f, 1.0f, 70.0f);
   

	
	object = core->AddObject();
	object->AddComponent<Transform>();
	//object->AddComponent<Renderer>();
	//object->GetComponent<Renderer>()->SetMesh(core->resources->load<Mesh>("../src/game/models/cube.obj"));
	//object->GetComponent<Renderer>()->SetTexture(core->resources->load<Texture>("../src/game/textures/dice.png"));
	object->AddComponent<PointLight>();
	object->GetComponent<PointLight>()->diffuse = glm::vec3(5.0f, 5.0f, 5.0f);
	object->GetComponent<PointLight>()->linear = 0.022f;
	object->GetComponent<PointLight>()->quadratic = 0.0019f;
	//object->GetComponent<PointLight>()->specular = glm::vec3(0.3f, 0.3f, 0.3f);
	object->GetComponent<Transform>()->position = glm::vec3(0.0f, 0.0f, 0.0f);
	

	core->lights = core->GetComponents<PointLight>();
	core->renderers = core->GetComponents<Renderer>();

	const Uint8 *state = SDL_GetKeyboardState(NULL);
	bool quit = false;

	float spinPos = 6.2f;
	float spinCounter = -1;
	while (!quit)
	{
		state = SDL_GetKeyboardState(NULL);
		if (state[SDL_SCANCODE_I]) object2->GetComponent<Transform>()->position.z += 0.2f;
		if (state[SDL_SCANCODE_K]) object2->GetComponent<Transform>()->position.z -= 0.2f;
		if (state[SDL_SCANCODE_J]) object2->GetComponent<Transform>()->position.x -= 0.2f;
		if (state[SDL_SCANCODE_L]) object2->GetComponent<Transform>()->position.x += 0.2f;
		if (state[SDL_SCANCODE_U]) object2->GetComponent<Transform>()->position.y -= 0.2f;
		if (state[SDL_SCANCODE_H]) object2->GetComponent<Transform>()->position.y += 0.2f;


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
		
		if (spinPos > 6.28f && spinPos < 6.3f || spinPos > 1.55f && spinPos < 1.57f) {
			if (spinCounter < 300) {
				spinCounter++;
			}
			else{
				spinCounter = -1;
				
			}
		}
		if (spinCounter < 0) spinPos += 0.02f;

		if (spinPos > 6.3f) {
			spinPos = 0;
		}
		
		object->GetComponent<Transform>()->position = glm::vec3(glm::sin(spinPos) * 15.0f ,0.0f, glm::cos(spinPos) * 15.0f );

		core->Display();
	}

	core->Stop();

	return 0;
}