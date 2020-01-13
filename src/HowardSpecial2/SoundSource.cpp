#include "SoundSource.h"
#include "Sound.h"
#include "GameObject.h"
#include "Transform.h"
#include "Core.h"
#include "Camera.h"

SoundSource::SoundSource(){
	sourceId = 0;
	alGenSources(1, &sourceId);
}
void SoundSource::Play() {
	glm::vec3 pos = GetGameObject()->GetTransform()->position;
	glm::mat4 view = GetCore()->mainCamera->GetComponent<Camera>()->GetView();
	glm::vec4 res = view * glm:: vec4(pos, 1.0f);
	alSource3f(sourceId, AL_POSITION, res.x, res.y, res.z);
	alSourcei(sourceId, AL_BUFFER, sound->GetId());
	alSourcePlay(sourceId);
}

void SoundSource::OnUpdate(){
 //Wait for sound to finish
	glm::vec3 pos = GetGameObject()->GetTransform()->position;
	glm::mat4 view = GetCore()->mainCamera->GetComponent<Camera>()->GetView();
	glm::vec4 res = view * glm::vec4(pos, 1.0f);
	alSource3f(sourceId, AL_POSITION, res.x, res.y, res.z);

	ALint state = 0;
	alGetSourcei(sourceId, AL_SOURCE_STATE, &state);

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
