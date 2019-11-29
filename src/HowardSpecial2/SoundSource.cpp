#include "SoundSource.h"
#include "Sound.h"

SoundSource::SoundSource(){
	sourceId = 0;
	alGenSources(1, &sourceId);
}
void SoundSource::Play() {
	alSource3f(sourceId, AL_POSITION, 0.0f, 0.0f, 0.0f);
	alSourcei(sourceId, AL_BUFFER, sound->GetId());
	alSourcePlay(sourceId);
}

void SoundSource::OnUpdate(){
 //Wait for sound to finish

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
