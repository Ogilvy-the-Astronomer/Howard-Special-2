#include "SoundSource.h"
#include "Sound.h"
#include "GameObject.h"
#include "Transform.h"
#include "Core.h"
#include "Camera.h"

SoundSource::SoundSource(){
	sourceId = 0;
	alGenSources(1, &sourceId); //generate source od
}
void SoundSource::Play() {
	glm::vec3 pos = GetGameObject()->GetTransform()->position;                 //get the sound source position
	glm::mat4 view = GetCore()->mainCamera->GetComponent<Camera>()->GetView(); //get the camera view
	glm::vec4 res = view * glm:: vec4(pos, 1.0f);                              //warp the position by the camera view so that the source is attenuated relative to the cameraa
	alSource3f(sourceId, AL_POSITION, res.x, res.y, res.z);                    //set the source position
	alSourcei(sourceId, AL_BUFFER, sound->GetId());                            //set the source sound
	alSourcePlay(sourceId);                                                    //play the sound
}

void SoundSource::OnUpdate(){
 //Wait for sound to finish
 	glm::vec3 pos = GetGameObject()->GetTransform()->position;
	glm::mat4 view = GetCore()->mainCamera->GetComponent<Camera>()->GetView();
	glm::vec4 res = view * glm::vec4(pos, 1.0f);
	alSource3f(sourceId, AL_POSITION, res.x, res.y, res.z);

	ALint state = 0;
	alGetSourcei(sourceId, AL_SOURCE_STATE, &state); //get the source state

	if (state == AL_STOPPED){ 
		//break;
	}

	#ifdef _WIN32
		//Sleep(1000);
	#else
		sleep(1);
	#endif
}

void SoundSource::SetSound(std::shared_ptr<Sound> noise){
	sound = noise;
}
