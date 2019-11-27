#include<string>
#include<vector>
#include<AL/al.h>
#include "Component.h"


struct SoundSource : public Component {
	SoundSource();
	void Play();
	void load_ogg(const std::string & fileName, std::vector<char>& buffer, ALenum & format, ALsizei & freq);
	void OnUpdate();
	
	ALuint bufferId;
	ALuint sourceId;
};