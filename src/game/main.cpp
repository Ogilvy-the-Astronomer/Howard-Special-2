#include <iostream>
#include <HowardSpecial2/HowardSpecial2.h>
#include "playerController.h"
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
	core->mainCamera->AddComponent<PlayerController>();

	std::shared_ptr<GameObject> player = core->AddObject();
	player->AddComponent<Transform>();
	player->AddComponent<Renderer>();
	player->GetComponent<Renderer>()->SetMesh(core->resources->load<Mesh>("../src/game/models/cube.obj"));
	player->GetComponent<Renderer>()->SetTexture(core->resources->load<Texture>("../src/game/textures/Bricks.png"));
	player->AddComponent<BoxCollider>(glm::vec3(1.0f, 5.0f, 1.0f));
	core->mainCamera->GetComponent<PlayerController>()->rb = player->AddComponent<Rigidbody>();
	core->mainCamera->GetComponent<PlayerController>()->rb->friction = 1.0f;


	//create the game world 
	std::shared_ptr<GameObject> object;

	object = core->AddObject(); //add a directional light
	object->AddComponent<Transform>();
	object->AddComponent<DirectionalLight>();
	object->GetComponent<DirectionalLight>()->ambient = glm::vec3(0.7f, 0.7f, 0.7f);
	object->GetTransform()->rotation = glm::vec3(glm::radians(40.0f), glm::radians(40.0f), glm::radians(40.0f));

	std::shared_ptr<GameObject> middle = object = core->AddObject();
	object->AddComponent<Transform>();
	object->AddComponent<Renderer>();
	object->GetComponent<Renderer>()->SetMesh(core->resources->load<Mesh>("../src/game/models/cube.obj"));
	object->GetComponent<Renderer>()->SetTexture(core->resources->load<Texture>("../src/game/textures/dice.png"));
	object->AddComponent<BoxCollider>();
	object->AddComponent<MeshCollider>();
	object->GetTransform()->position = glm::vec3(5.0f, 0.0f, 0.0f);
	object->GetTransform()->scale.x = 2.0f;

	object = core->AddObject();
	object->AddComponent<Transform>();
	object->AddComponent<Renderer>();
	object->GetComponent<Renderer>()->SetMesh(core->resources->load<Mesh>("../src/game/models/cube.obj"));
	object->GetComponent<Renderer>()->SetTexture(core->resources->load<Texture>("../src/game/textures/grass.png"));
	object->AddComponent<BoxCollider>();
	object->AddComponent<MeshCollider>();
	object->GetTransform()->position = glm::vec3(0.0f, -10.0f, 0.0f);
	object->GetTransform()->scale = glm::vec3(200.0f, 1.0f, 200.0f);

	for (int i = 0; i < 5; i++) {
		object = core->AddObject();
		object->AddComponent<Transform>();
		object->AddComponent<Renderer>();
		object->GetComponent<Renderer>()->SetMesh(core->resources->load<Mesh>("../src/game/models/cube.obj"));
		object->GetComponent<Renderer>()->SetTexture(core->resources->load<Texture>("../src/game/textures/bricks.png"));
		object->AddComponent<BoxCollider>();
		object->AddComponent<MeshCollider>();
		object->GetTransform()->position = glm::vec3(25.0f, -5.0f, 10.0f*i - 15.0f);
		object->GetTransform()->scale = glm::vec3(10.0f, 10.0f, 10.0f);

		object = core->AddObject();
		object->AddComponent<Transform>();
		object->AddComponent<Renderer>();
		object->GetComponent<Renderer>()->SetMesh(core->resources->load<Mesh>("../src/game/models/cube.obj"));
		object->GetComponent<Renderer>()->SetTexture(core->resources->load<Texture>("../src/game/textures/bricks.png"));
		object->AddComponent<BoxCollider>();
		object->AddComponent<MeshCollider>();
		object->GetTransform()->position = glm::vec3(-25.0f, -5.0f, 10.0f*i - 15.0f);
		object->GetTransform()->scale = glm::vec3(10.0f, 10.0f, 10.0f);

		object = core->AddObject();
		object->AddComponent<Transform>();
		object->AddComponent<Renderer>();
		object->GetComponent<Renderer>()->SetMesh(core->resources->load<Mesh>("../src/game/models/cube.obj"));
		object->GetComponent<Renderer>()->SetTexture(core->resources->load<Texture>("../src/game/textures/bricks.png"));
		object->AddComponent<BoxCollider>();
		object->AddComponent<MeshCollider>();
		object->GetTransform()->position = glm::vec3(10.0f*i - 15.0f, -5.0f, 25.0f);
		object->GetTransform()->scale = glm::vec3(10.0f, 10.0f, 10.0f);

		object = core->AddObject();
		object->AddComponent<Transform>();
		object->AddComponent<Renderer>();
		object->GetComponent<Renderer>()->SetMesh(core->resources->load<Mesh>("../src/game/models/cube.obj"));
		object->GetComponent<Renderer>()->SetTexture(core->resources->load<Texture>("../src/game/textures/bricks.png"));
		object->AddComponent<BoxCollider>();
		object->AddComponent<MeshCollider>();
		object->GetTransform()->position = glm::vec3(10.0f*i - 15.0f, -5.0f, -25.0f);
		object->GetTransform()->scale = glm::vec3(10.0f, 10.0f, 10.0f);
	}

	for (int i = 0; i < 10; i++) {
		object = core->AddObject();
		object->AddComponent<Transform>();
		object->AddComponent<Renderer>();
		object->GetComponent<Renderer>()->SetMesh(core->resources->load<Mesh>("../src/game/models/cube.obj"));
		object->GetComponent<Renderer>()->SetTexture(core->resources->load<Texture>("../src/game/textures/bricks.png"));
		object->AddComponent<BoxCollider>();
		object->AddComponent<MeshCollider>();
		object->GetTransform()->position = glm::vec3(11.0f + i, -9.5f, 0.0f);
		object->GetTransform()->scale = glm::vec3(1.0f, 1.75f*i + 1.0f, 10.0f);
	}

	object = core->AddObject();
	object->AddComponent<Transform>();
	object->AddComponent<Renderer>();
	object->GetComponent<Renderer>()->SetMesh(core->resources->load<Mesh>("../src/game/models/dalek.obj"));
	object->GetComponent<Renderer>()->SetTexture(core->resources->load<Texture>("../src/game/textures/Bricks.png"));
	object->AddComponent<BoxCollider>();
	object->GetTransform()->position = glm::vec3(-10.0f, 20.0f, 0.0f);
	object->GetTransform()->scale = glm::vec3(1.0f, 1.0f, 1.0f);

	/*
	object = core->AddObject(); 
	object->AddComponent<Transform>();
	object->AddComponent<Renderer>();
	object->GetComponent<Renderer>()->SetMesh(core->resources->load<Mesh>("../src/game/models/fighter.obj"));
	object->GetComponent<Renderer>()->SetTexture(core->resources->load<Texture>("../src/game/textures/fighter.png"));
	object->AddComponent<BoxCollider>(glm::vec3(4.0f, 2.0f, 18.0f));
	object->GetTransform()->position.x = 5.0f;
	*/

	object = core->AddObject();
	object->AddComponent<Transform>();
	std::shared_ptr<TextRenderer> tr = object->AddComponent<TextRenderer>();
	object->GetTransform()->scale = glm::vec3(0.1f);
	object->GetTransform()->position = glm::vec3(-0.85f, 0.85f, 0.0f);
	tr->SetText("Test");

	object = core->AddObject();
	object->AddComponent<Transform>();
	object->AddComponent<Renderer>();
	object->GetComponent<Renderer>()->SetMesh(core->resources->load<Mesh>("../src/game/models/cube.obj"));
	object->GetComponent<Renderer>()->SetTexture(core->resources->load<Texture>("../src/game/textures/dice.png"));
	object->AddComponent<SoundSource>();
	object->GetComponent<SoundSource>()->SetSound(core->resources->load<Sound>("../src/game/models/dixie_horn.ogg"));
	object->AddComponent<PointLight>();
	object->GetComponent<PointLight>()->diffuse = glm::vec3(5.0f, 5.0f, 5.0f);
	object->GetTransform()->position = glm::vec3(0.0f, 15.0f, 0.0f);

	bool quit = false;
	float rot = 0;
	core->Start();
	while (!quit)
	{
		if (kb->GetKey(SDL_SCANCODE_ESCAPE)) quit = true;
		if (kb->GetKeyDown(SDL_SCANCODE_P)) object->GetComponent<SoundSource>()->Play(); //debug sound
		middle->GetTransform()->rotation.y = (rot += 0.01f);
		tr->SetText("FPS: " + std::to_string(core->fps));
		core->Display(); //display objects to screen
	}

	core->Stop(); //shut down the program

	return 0;
}