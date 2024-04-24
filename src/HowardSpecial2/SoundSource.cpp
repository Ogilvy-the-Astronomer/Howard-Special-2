#include "SoundSource.h"
#include "Sound.h"
#include "GameObject.h"
#include "Transform.h"
#include "Core.h"
#include "Camera.h"

SoundSource::SoundSource(){
	sourceId = 0;
	volume = 1.0f;
	loop = false;
	isPlaying = false;
	alGenSources(1, &sourceId); //generate source id
}
void SoundSource::Play() {
	glm::vec3 pos = GetGameObject()->GetTransform()->position;                 //get the sound source position
	glm::mat4 view = GetCore()->mainCamera->GetComponent<Camera>()->GetView(); //get the camera view
	glm::vec4 res = view * glm:: vec4(pos, 1.0f);                              //warp the position by the camera view so that the source is attenuated relative to the cameraa
	alSource3f(sourceId, AL_POSITION, res.x, res.y, res.z);                    //set the source position
	alSourcei(sourceId, AL_BUFFER, sound->GetId());                            //set the source sound
	alSourcef(sourceId, AL_GAIN, volume);
	alSourcei(sourceId, AL_LOOPING, (loop)? 1 : 0);
	alSourcePlay(sourceId);                                                    //play the sound
}

void SoundSource::Stop() {
	alSourceStop(sourceId);
}

void SoundSource::OnUpdate(float _deltaT){
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

	isPlaying = (state == AL_PLAYING);

	#ifdef _WIN32
		//Sleep(1000);
	#else
		sleep(1);
	#endif
}

void SoundSource::SetSound(std::shared_ptr<Sound> noise){
	sound = noise;
}
