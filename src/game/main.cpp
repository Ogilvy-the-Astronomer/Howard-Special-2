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

	core->mainCamera = core->AddObject("Camera"); //create the main camera
	core->mainCamera->AddComponent<Transform>(); //assign position, camera, and sound source components to it
	core->mainCamera->AddComponent<Camera>();
	core->mainCamera->AddComponent<PlayerController>();

	std::shared_ptr<GameObject> player = core->AddObject("Player");
	player->AddComponent<Transform>();
	player->AddComponent<Renderer>();
	player->GetComponent<Renderer>()->SetMesh(core->resources->load<Mesh>("../src/game/models/cube.obj"));
	player->GetTransform()->scale.y = 5.0f;
	player->GetComponent<Renderer>()->SetTexture(core->resources->load<Texture>("../src/game/textures/Bricks.png"));
	player->GetComponent<Renderer>()->SetShader(core->resources->load<ShaderProgram>("../shaders/default"));
	player->AddComponent<BoxCollider>(glm::vec3(1.0f, 1.0f, 1.0f));
	player->AddComponent<SoundSource>();
	player->GetComponent<SoundSource>()->SetSound(core->resources->load<Sound>("../src/game/sounds/walk.ogg"));
	//core->mainCamera->GetComponent<SoundSource>()->volume = 2.25f;
	core->mainCamera->GetComponent<PlayerController>()->rb = player->AddComponent<Rigidbody>();
	core->mainCamera->GetComponent<PlayerController>()->audioSource = player->GetComponent<SoundSource>();
	core->mainCamera->GetComponent<PlayerController>()->rb->friction = 1.0f;
	player->GetTransform()->position.y = 5.0f;


	//create the game world 
	std::shared_ptr<GameObject> object;

	object = core->AddObject("Light"); //add a directional light
	object->AddComponent<Transform>();
	object->AddComponent<DirectionalLight>();
	object->GetComponent<DirectionalLight>()->SetAll(glm::vec3(0.0f));
	object->GetComponent<DirectionalLight>()->ambient = (glm::vec3(1.2f));
	object->GetTransform()->rotation = glm::vec3(glm::radians(40.0f), glm::radians(40.0f), glm::radians(40.0f));
	object->GetTransform()->position.y += 15.0f;

	std::shared_ptr<GameObject> middle = object = core->AddObject();
	object->AddComponent<Transform>();
	//object->AddComponent<Renderer>();
	//object->GetComponent<Renderer>()->SetMesh(core->resources->load<Mesh>("../src/game/models/cube.obj"));
	//object->GetComponent<Renderer>()->SetTexture(core->resources->load<Texture>("../src/game/textures/dice.png"));
	//object->GetComponent<Renderer>()->SetShader(core->resources->load<ShaderProgram>("../shaders/default"));
	object->GetTransform()->position = glm::vec3(5.0f, 10.0f, 0.0f);
	object->GetTransform()->scale.x = 2.0f;

	object = core->AddObject();
	object->AddComponent<Transform>();
	object->AddComponent<Renderer>();
	object->GetComponent<Renderer>()->SetMesh(core->resources->load<Mesh>("../src/game/models/cube.obj"));
	object->GetComponent<Renderer>()->SetTexture(core->resources->load<Texture>("../src/game/textures/grass.png"));
	object->GetComponent<Renderer>()->SetShader(core->resources->load<ShaderProgram>("../shaders/default"));
	object->AddComponent<BoxCollider>();
	object->AddComponent<MeshCollider>();
	object->GetTransform()->position = glm::vec3(0.0f, -1.6f, 0.0f);
	object->GetTransform()->scale = glm::vec3(200.0f, 3.0f, 200.0f);

	object = core->AddObject("Terrain");
	object->AddComponent<Transform>();
	object->AddComponent<Renderer>();
	object->GetComponent<Renderer>()->SetMesh(core->resources->load<Mesh>("../src/game/models/mountains.obj"));
	object->GetComponent<Renderer>()->SetTexture(core->resources->load<Texture>("../src/game/textures/grass2.png"));
	object->GetComponent<Renderer>()->SetShader(core->resources->load<ShaderProgram>("../shaders/default"));
	object->GetTransform()->position = glm::vec3(0.0f, -1.5f, 0.0f);
	object->GetTransform()->scale = glm::vec3(200.0f, 200.0f, 200.0f);

	object = core->AddObject("Wall");
	object->AddComponent<Transform>();
	object->AddComponent<Renderer>();
	object->GetComponent<Renderer>()->SetMesh(core->resources->load<Mesh>("../src/game/models/cube.obj"));
	object->GetComponent<Renderer>()->SetTexture(core->resources->load<Texture>("../src/game/textures/bricks.png"));
	object->GetComponent<Renderer>()->SetShader(core->resources->load<ShaderProgram>("../shaders/default"));
	object->AddComponent<BoxCollider>();
	object->AddComponent<MeshCollider>();
	object->GetTransform()->position = glm::vec3(0.0f, 1.0f, 2.0f);
	object->GetTransform()->scale = glm::vec3(20.0f, 1.0f, 1.0f);
	object->GetTransform()->rotation = glm::vec3(0, 45.0f, 0.0f);

	object = core->AddObject("Wall 2");
	object->AddComponent<Transform>();
	object->AddComponent<Renderer>();
	object->GetComponent<Renderer>()->SetMesh(core->resources->load<Mesh>("../src/game/models/cube.obj"));
	object->GetComponent<Renderer>()->SetTexture(core->resources->load<Texture>("../src/game/textures/bricks.png"));
	object->GetComponent<Renderer>()->SetShader(core->resources->load<ShaderProgram>("../shaders/default"));
	object->AddComponent<BoxCollider>();
	object->AddComponent<MeshCollider>();
	object->GetTransform()->position = glm::vec3(2.0f, 1.0f, 1.0f);
	object->GetTransform()->scale = glm::vec3(1.0f, 20.0f, 2.0f);

	object = core->AddObject("Castle");
	object->AddComponent<Transform>();
	object->AddComponent<Renderer>();
	object->GetComponent<Renderer>()->SetMesh(core->resources->load<Mesh>("../src/game/models/castle2.obj"));
	object->GetComponent<Renderer>()->SetTexture(core->resources->load<Texture>("../src/game/textures/castle.png"));
	object->GetComponent<Renderer>()->SetShader(core->resources->load<ShaderProgram>("../shaders/default"));
	object->GetTransform()->position = glm::vec3(45.0f, 1.1f, 0.0f);
	object->GetTransform()->scale = glm::vec3(5.0f, 5.0f, 5.0f);


	/*
	object = core->AddObject("Dalek");
	object->AddComponent<Transform>();
	object->AddComponent<Renderer>();
	object->GetComponent<Renderer>()->SetMesh(core->resources->load<Mesh>("../src/game/models/dalek.obj"));
	object->GetComponent<Renderer>()->SetTexture(core->resources->load<Texture>("../src/game/textures/Bricks.png"));
	object->GetComponent<Renderer>()->SetShader(core->resources->load<ShaderProgram>("../shaders/default"));
	object->AddComponent<BoxCollider>();
	object->GetTransform()->position = glm::vec3(-10.0f, 2.0f, 0.0f);
	object->GetTransform()->scale = glm::vec3(1.0f, 1.0f, 1.0f);
	*/

	object = core->AddObject("Scarecrow");
	object->AddComponent<Transform>();
	object->AddComponent<Renderer>();
	object->GetComponent<Renderer>()->SetMesh(core->resources->load<Mesh>("../src/game/models/scarecrow2.obj"));
	object->GetComponent<Renderer>()->SetTexture(core->resources->load<Texture>("../src/game/textures/ScarecrowTex.png"));
	object->GetComponent<Renderer>()->SetShader(core->resources->load<ShaderProgram>("../shaders/default"));
	object->GetComponent<Renderer>()->material->specular = glm::vec3(2.0f);
	object->AddComponent<BoxCollider>();
	object->GetComponent<BoxCollider>()->offset = glm::vec3(0.0f, 1.5f, 0.0f);
	object->GetComponent<BoxCollider>()->dimensions = glm::vec3(5.0f, 5.5f, 5.0f);
	object->AddComponent<Rigidbody>();
	object->GetComponent<Rigidbody>()->friction = 0.02f;
	object->GetTransform()->position = glm::vec3(2.0f, 4.0f, 0.0f);
	object->GetTransform()->scale = glm::vec3(0.4f, 0.4f, 0.4f);


	object = core->AddObject();
	object->AddComponent<Transform>();
	std::shared_ptr<TextRenderer> tr = object->AddComponent<TextRenderer>();
	object->GetTransform()->scale = glm::vec3(0.05f);
	object->GetTransform()->position = glm::vec3(-0.85f, 0.85f, 0.0f);
	tr->SetText("Test");

	object = core->AddObject();
	object->AddComponent<Transform>();
	std::shared_ptr<TextRenderer> tr2 = object->AddComponent<TextRenderer>();
	object->GetTransform()->scale = glm::vec3(0.05f);
	object->GetTransform()->position = glm::vec3(-0.85f, 0.75f, 0.0f);
	tr2->SetText("Test");

	object = core->AddObject();
	object->AddComponent<Transform>();
	object->AddComponent<SoundSource>();
	object->GetComponent<SoundSource>()->SetSound(core->resources->load<Sound>("../src/game/sounds/birds.ogg"));
	object->GetComponent<SoundSource>()->loop = true;
	object->GetComponent<SoundSource>()->volume = 0.3f;
	object->GetComponent<SoundSource>()->Play();
	object->AddComponent<PointLight>();
	object->GetComponent<PointLight>()->SetAll(glm::vec3(3.0f));
	object->GetComponent<PointLight>()->emissive = glm::vec3(0.0f);
	//object->AddComponent<Renderer>();
	//object->GetComponent<Renderer>()->SetMesh(core->resources->load<Mesh>("../src/game/models/cube.obj"));
	//object->GetComponent<Renderer>()->SetTexture(core->resources->load<Texture>("../src/game/textures/bricks.png"));
	//object->GetComponent<Renderer>()->SetShader(core->resources->load<ShaderProgram>("../shaders/default"));
	object->GetTransform()->position = glm::vec3(0.0f, 0.0f, 0.0f);

	bool quit = false;
	float rot = 0, rotX = 0, rotY = 0;
	core->Start();
	while (!quit) {
		if (kb->GetKey(SDL_SCANCODE_ESCAPE)) quit = true;
		if (kb->GetKeyDown(SDL_SCANCODE_P)) object->GetComponent<SoundSource>()->Play(); //debug sound
		rot+=0.001f;
		rotX = glm::cos((rot)) * 15.0f;
		rotY = glm::sin((rot)) * 15.0f;
		object->GetTransform()->position = glm::vec3(rotX, 15.0f, rotY);
		tr->SetText("FPS: " + std::to_string((int)core->fps));
		tr2->SetText(std::to_string(player->GetTransform()->position.y));
		core->Display(); //display objects to screen
	}

	core->Stop(); //shut down the program

	return 0;
}