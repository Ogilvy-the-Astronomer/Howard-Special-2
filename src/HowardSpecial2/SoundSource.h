#include<string>
#include<vector>
#include<AL/al.h>
#include<memory>
#include "Component.h"

struct Sound;
/**
 * a sound source component for playing sounds
 */
struct SoundSource : public Component {
	SoundSource();
	void Play(); ///< play the sound
	void OnUpdate(); 
	void SetSound(std::shared_ptr<Sound> noise); ///< set the sound
private:
	ALuint sourceId; ///<source id
	std::shared_ptr<Sound> sound; ///< pointer to the sound to be played
};