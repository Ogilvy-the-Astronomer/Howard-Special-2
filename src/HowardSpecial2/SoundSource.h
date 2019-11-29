#include<string>
#include<vector>
#include<AL/al.h>
#include<memory>
#include "Component.h"

struct Sound;

struct SoundSource : public Component {
	SoundSource();
	void Play();
	void OnUpdate();
	void SetSound(std::shared_ptr<Sound> noise);
	
	ALuint sourceId;
	std::shared_ptr<Sound> sound;
};