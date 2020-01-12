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
	//enable face culling for performance and depth testing for shadow maps
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	
	
	core->mainCamera = core->AddObject(); //create the main camera
	core->mainCamera->AddComponent<Transform>(); //assign position, camera, and sound source components to it
	core->mainCamera->GetComponent<Transform>()->position.z = 20.0f;
	core->mainCamera->AddComponent<Camera>();
	core->mainCamera->AddComponent<SoundSource>();
	core->mainCamera->GetComponent<SoundSource>()->SetSound(core->resources->load<Sound>("../src/game/models/dixie_horn.ogg"));

	//create the game world 
	std::shared_ptr<GameObject> object;

	object = core->AddObject(); //create the rock shadow object
	object->AddComponent<Transform>();
	object->AddComponent<Renderer>();
	object->GetComponent<Renderer>()->SetMesh(core->resources->load<Mesh>("../src/game/models/rocks.obj"));
	object->GetComponent<Renderer>()->SetTexture(core->resources->load<Texture>("../src/game/textures/rocks.png"));

	object = core->AddObject(); //create the rock shadow object
	object->AddComponent<Transform>();
	object->AddComponent<Renderer>();
	object->GetComponent<Renderer>()->SetMesh(core->resources->load<Mesh>("../src/game/models/polys.obj"));
	object->GetComponent<Renderer>()->SetTexture(core->resources->load<Texture>("../src/game/textures/grey.png"));
	object->GetComponent<Transform>()->rotation.y = glm::radians(-90.0f)	;
	object->GetComponent<Transform>()->position.x = 120.0f;
	object->GetComponent<Transform>()->position.y = -2.0f;
	object->GetComponent<Transform>()->scale = glm::vec3(8.0f);
	
	object = core->AddObject(); //create the campsite object
	object->AddComponent<Transform>();
	object->AddComponent<Renderer>();
	object->GetComponent<Renderer>()->SetMesh(core->resources->load<Mesh>("../src/game/models/campsite.obj"));
	object->GetComponent<Renderer>()->SetTexture(core->resources->load<Texture>("../src/game/textures/campsite.png"));
	object->GetComponent<Transform>()->position.z = 120.0f;
	object->GetComponent<Transform>()->scale = glm::vec3(4.0f);

	object = core->AddObject(); //add a directional light
	object->AddComponent<Transform>();
	object->AddComponent<DirectionalLight>();
	object->GetComponent<DirectionalLight>()->ambient = glm::vec3(1.0f, 1.0f, 1.0f);
	object->GetComponent<Transform>()->rotation = glm::vec3(glm::radians(40.0f), glm::radians(40.0f), glm::radians(40.0f));

	
	std::shared_ptr<GameObject> object2; //create the 3 point light shadow casters to the scene
	object2 = core->AddObject();
	object2->AddComponent<Transform>();
	object2->AddComponent<PointLight>();
	object2->GetComponent<PointLight>()->diffuse = glm::vec3(8.0f, 5.0f, 5.0f);
	object2->GetComponent<PointLight>()->linear = 0.027f; //adjust the light attentuation to make it go further
	object2->GetComponent<PointLight>()->quadratic = 0.0028f;
	object2->GetComponent<Transform>()->position = glm::vec3(0.0f, 2.0f, 120.0f);

	std::shared_ptr<GameObject> object3;
	object3 = core->AddObject();
	object3->AddComponent<Transform>();
	object3->AddComponent<PointLight>();
	object3->GetComponent<PointLight>()->diffuse = glm::vec3(8.0f, 5.0f, 5.0f);
	object3->GetComponent<PointLight>()->linear = 0.027f;
	object3->GetComponent<PointLight>()->quadratic = 0.0028f;
	object3->GetComponent<Transform>()->position = glm::vec3(0.0f, 2.0f, 120.0f);
   
	std::shared_ptr<GameObject> object4;
	object4 = core->AddObject();
	object4->AddComponent<Transform>();
	object4->AddComponent<Renderer>();
	object4->GetComponent<Renderer>()->SetMesh(core->resources->load<Mesh>("../src/game/models/cube.obj"));
	object4->GetComponent<Renderer>()->SetTexture(core->resources->load<Texture>("../src/game/textures/dice.png"));
	object4->AddComponent<PointLight>();
	object4->GetComponent<PointLight>()->diffuse = glm::vec3(10.0f, 10.0f, 10.0f);
	object4->GetComponent<PointLight>()->specular = glm::vec3(1.0f, 1.0f, 1.0f);
	object4->GetComponent<PointLight>()->linear = 0.014f;
	object4->GetComponent<PointLight>()->quadratic = 0.0007f;
	object4->GetComponent<Transform>()->position = glm::vec3(123.0f, 23.0f, 20.0f);

	object = core->AddObject();
	object->AddComponent<Transform>();
	object->AddComponent<PointLight>();
	object->GetComponent<PointLight>()->diffuse = glm::vec3(5.0f, 5.0f, 5.0f);
	object->GetComponent<PointLight>()->linear = 0.014f;
	object->GetComponent<PointLight>()->quadratic = 0.0007f;
	object->GetComponent<Transform>()->position = glm::vec3(0.0f, 0.0f, 0.0f);
	

	core->lights = core->GetComponents<PointLight>(); //add a list of lights to the core
	core->renderers = core->GetComponents<Renderer>(); //add a list of visible objects to the core

	const Uint8 *state = SDL_GetKeyboardState(NULL); //a variable containing the status of all the keys
	bool quit = false;

	float spinPos = 6.2f; //variables for the light movements
	float spinCounter = -1;

	float spinPos2 = 0.0f;
	float spinPos3 = 0.0f;
	while (!quit)
	{
		state = SDL_GetKeyboardState(NULL); //get the keyboard state this frame
		if (state[SDL_SCANCODE_I]) object4->GetComponent<Transform>()->position.z += 0.2f;
		if (state[SDL_SCANCODE_K]) object4->GetComponent<Transform>()->position.z -= 0.2f;
		if (state[SDL_SCANCODE_J]) object4->GetComponent<Transform>()->position.x -= 0.2f;
		if (state[SDL_SCANCODE_L]) object4->GetComponent<Transform>()->position.x += 0.2f;
		if (state[SDL_SCANCODE_U]) object4->GetComponent<Transform>()->position.y -= 0.2f;
		if (state[SDL_SCANCODE_H]) object4->GetComponent<Transform>()->position.y += 0.2f;
		//controls for camera movement
		if (state[SDL_SCANCODE_W]) core->mainCamera->GetComponent<Transform>()->position -= core->mainCamera->GetComponent<Transform>()->forward * 0.5f;
		if (state[SDL_SCANCODE_S]) core->mainCamera->GetComponent<Transform>()->position += core->mainCamera->GetComponent<Transform>()->forward * 0.5f;
		if (state[SDL_SCANCODE_A]) core->mainCamera->GetComponent<Transform>()->position -= core->mainCamera->GetComponent<Transform>()->right * 0.5f;
		if (state[SDL_SCANCODE_D]) core->mainCamera->GetComponent<Transform>()->position += core->mainCamera->GetComponent<Transform>()->right * 0.5f;
		if (state[SDL_SCANCODE_R]) core->mainCamera->GetComponent<Transform>()->position.y += 0.5f;
		if (state[SDL_SCANCODE_F]) core->mainCamera->GetComponent<Transform>()->position.y -= 0.5f;
		//controls for camera rotation
		if (state[SDL_SCANCODE_RIGHT]) core->mainCamera->GetComponent<Transform>()->rotation.y -= 0.05f;
		if (state[SDL_SCANCODE_LEFT]) core->mainCamera->GetComponent<Transform>()->rotation.y += 0.05f;
		if (state[SDL_SCANCODE_UP]) core->mainCamera->GetComponent<Transform>()->rotation.x += 0.05f;
		if (state[SDL_SCANCODE_DOWN]) core->mainCamera->GetComponent<Transform>()->rotation.x -= 0.05f;
		
		if (state[SDL_SCANCODE_P]) core->mainCamera->GetComponent<SoundSource>()->Play(); //debug sound
		SDL_Event event = { 0 }; //sdl events variable

		while (SDL_PollEvent(&event)) //go through list of sdl events
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
		
		if (spinPos > 6.28f && spinPos < 6.3f || spinPos > 1.55f && spinPos < 1.57f || spinPos > 3.1f && spinPos < 3.12f || spinPos > 4.65f && spinPos < 4.67f) { //stop the light every 90 degrees
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
		
		object->GetComponent<Transform>()->position = glm::vec3(glm::sin(spinPos) * 15.0f ,0.0f, glm::cos(spinPos) * 15.0f ); //set the x and y of the light position to 15x the sin and cos of an incrementing value
		spinPos2 += 0.05f;
		object2->GetComponent<Transform>()->position = glm::vec3(glm::sin(spinPos2) * 0.7f, glm::sin(spinPos2) * 0.5f + 2.0f, glm::cos(spinPos2) * 0.7f + 120.0f); //same as above but also changing y
		spinPos3 -= 0.05f;
		object3->GetComponent<Transform>()->position = glm::vec3(glm::sin(spinPos3) * 0.7f, glm::cos(spinPos3) * 0.5f + 2.0f, glm::cos(spinPos3) * 0.7f + 120.0f); //same as above
		core->Display(); //display objects to screen
	}

	core->Stop(); //shut down the program

	return 0;
}