#include <iostream>
#include <HowardSpecial2/HowardSpecial2.h>
/* References
van Waard, M. (2019) ‘A2:Code and Report - Open GL Game’, 3D Graphics Programming. Bournemouth University. Unpublished assignment.
De Vries, J., 2020. LearnOpenGL - Multiple lights [online]. Learnopengl.com. Available from: https://learnopengl.com/Lighting/Multiple-lights [Accessed 10 Jan 2020].
De Vries, J., 2020. LearnOpenGL - Light casters [online]. Learnopengl.com. Available from: https://learnopengl.com/Lighting/Light-casters [Accessed 10 Jan 2020].
De Vries, J., 2020. LearnOpenGL - Cubemaps [online]. Learnopengl.com. Available from: https://learnopengl.com/Advanced-OpenGL/Cubemaps [Accessed 10 Jan 2020].
De Vries, J., 2020. LearnOpenGL - Framebuffers [online]. Learnopengl.com. Available from: https://learnopengl.com/Advanced-OpenGL/Framebuffers [Accessed 10 Jan 2020].
De Vries, J., 2020. LearnOpenGL - Point Shadows [online]. Learnopengl.com. Available from: https://learnopengl.com/Advanced-Lighting/Shadows/Point-Shadows [Accessed 10 Jan 2020].
plasmacel., 2017. How to render depth linearly in modern OpenGL with gl_FragCoord.z in fragment shader? [online]. Stack Overflow. Available from: https://stackoverflow.com/questions/7777913/how-to-render-depth-linearly-in-modern-opengl-with-gl-fragcoord-z-in-fragment-sh/45710371 [Accessed 10 Jan 2020].
Anon., 2012. Tutorial 16 : Shadow mapping [online]. Opengl-tutorial.org. Available from: http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-16-shadow-mapping/ [Accessed 10 Jan 2020].
*/

int main(){	
	std::shared_ptr<Core> core = core->Initialize();//initialze the core
	std::shared_ptr<Keyboard> kb = core->keyboard;

	core->mainCamera = core->AddObject(); //create the main camera
	core->mainCamera->AddComponent<Transform>(); //assign position, camera, and sound source components to it
	core->mainCamera->AddComponent<Camera>();


	//create the game world 
	std::shared_ptr<GameObject> object;
	/*
	object = core->AddObject(); //create the campsite object
	object->AddComponent<Transform>();
	object->AddComponent<Renderer>();
	object->GetComponent<Renderer>()->SetMesh(core->resources->load<Mesh>("../src/game/models/campsite.obj"));
	object->GetComponent<Renderer>()->SetTexture(core->resources->load<Texture>("../src/game/textures/campsite.png"));
	object->GetTransform()->scale = glm::vec3(4.0f);
	*/
	object = core->AddObject(); //create the campsite object
	object->AddComponent<Transform>();
	object->AddComponent<Renderer>();
	object->GetComponent<Renderer>()->SetMesh(core->resources->load<Mesh>("../src/game/models/fighter.obj"));
	object->GetComponent<Renderer>()->SetTexture(core->resources->load<Texture>("../src/game/textures/fighter.png"));
	object->AddComponent<BoxCollider>(glm::vec3(0.5f, 0.5f, 0.5f));
	object->GetTransform()->position.x = 20.0f;

	object = core->AddObject(); //add a directional light
	object->AddComponent<Transform>();
	object->AddComponent<DirectionalLight>();
	object->GetComponent<DirectionalLight>()->ambient = glm::vec3(0.2f, 0.2f, 0.2f);
	object->GetTransform()->rotation = glm::vec3(glm::radians(40.0f), glm::radians(40.0f), glm::radians(40.0f));

	object = core->AddObject();
	object->AddComponent<Transform>();
	object->AddComponent<Renderer>();
	object->GetComponent<Renderer>()->SetMesh(core->resources->load<Mesh>("../src/game/models/cube.obj"));
	object->GetComponent<Renderer>()->SetTexture(core->resources->load<Texture>("../src/game/textures/dice.png"));
	object->AddComponent<SoundSource>();
	object->GetComponent<SoundSource>()->SetSound(core->resources->load<Sound>("../src/game/models/dixie_horn.ogg"));
	object->AddComponent<PointLight>();
	object->GetComponent<PointLight>()->diffuse = glm::vec3(5.0f, 5.0f, 5.0f);
	object->AddComponent<BoxCollider>(glm::vec3(0.5f, 0.5f, 0.5f));
	object->GetTransform()->position = glm::vec3(0.0f, 5.0f, 0.0f);

	bool quit = false;
	core->Start();
	while (!quit)
	{
		if (kb->GetKey(SDL_SCANCODE_ESCAPE)) quit = true;

		if (kb->GetKey(SDL_SCANCODE_I)) object->GetTransform()->position.z += 0.2f;
		if (kb->GetKey(SDL_SCANCODE_K)) object->GetTransform()->position.z -= 0.2f;
		if (kb->GetKey(SDL_SCANCODE_J)) object->GetTransform()->position.x -= 0.2f;
		if (kb->GetKey(SDL_SCANCODE_L)) object->GetTransform()->position.x += 0.2f;
		if (kb->GetKey(SDL_SCANCODE_U)) object->GetTransform()->position.y += 0.2f;
		if (kb->GetKey(SDL_SCANCODE_H)) object->GetTransform()->position.y -= 0.2f;
		//controls for camera movement
		
		if (kb->GetKey(SDL_SCANCODE_W)) core->mainCamera->GetTransform()->position -= core->mainCamera->GetTransform()->forward * 0.5f;
		if (kb->GetKey(SDL_SCANCODE_S)) core->mainCamera->GetTransform()->position += core->mainCamera->GetTransform()->forward * 0.5f;
		if (kb->GetKey(SDL_SCANCODE_A)) core->mainCamera->GetTransform()->position -= core->mainCamera->GetTransform()->right * 0.5f;
		if (kb->GetKey(SDL_SCANCODE_D)) core->mainCamera->GetTransform()->position += core->mainCamera->GetTransform()->right * 0.5f;
		if (kb->GetKey(SDL_SCANCODE_R)) core->mainCamera->GetTransform()->position.y += 0.5f;
		if (kb->GetKey(SDL_SCANCODE_F)) core->mainCamera->GetTransform()->position.y -= 0.5f;
		
		if (kb->GetKey(SDL_SCANCODE_W)) core->mainCamera->GetTransform()->position -= core->mainCamera->GetTransform()->forward * 0.5f;
		if (kb->GetKey(SDL_SCANCODE_S)) core->mainCamera->GetTransform()->position += core->mainCamera->GetTransform()->forward * 0.5f;
		if (kb->GetKey(SDL_SCANCODE_A)) core->mainCamera->GetTransform()->position -= core->mainCamera->GetTransform()->right * 0.5f;
		if (kb->GetKey(SDL_SCANCODE_D)) core->mainCamera->GetTransform()->position += core->mainCamera->GetTransform()->right * 0.5f;
		if (kb->GetKey(SDL_SCANCODE_R)) core->mainCamera->GetTransform()->position.y += 0.5f;
		if (kb->GetKey(SDL_SCANCODE_F)) core->mainCamera->GetTransform()->position.y -= 0.5f;
		//controls for camera rotation
		if (kb->GetKey(SDL_SCANCODE_RIGHT)) core->mainCamera->GetTransform()->rotation.y -= 0.05f;
		if (kb->GetKey(SDL_SCANCODE_LEFT)) core->mainCamera->GetTransform()->rotation.y += 0.05f;
		if (kb->GetKey(SDL_SCANCODE_UP)) core->mainCamera->GetTransform()->rotation.x += 0.05f;
		if (kb->GetKey(SDL_SCANCODE_DOWN)) core->mainCamera->GetTransform()->rotation.x -= 0.05f;
		
		if (kb->GetKeyDown(SDL_SCANCODE_P)) object->GetComponent<SoundSource>()->Play(); //debug sound

		core->Display(); //display objects to screen
	}

	core->Stop(); //shut down the program

	return 0;
}