#include<string>
#include<vector>
#include<AL/al.h>
#include"Resource.h"
#include"NonCopyable.h"
/**
 * sound resource
 */
struct Sound : private NonCopyable, public Resource {
	Sound();
	Sound(std::string path); ///< constructor that loads sound from path
	~Sound();
	void load(std::string path); ///< function that loads sound from path
	void load_ogg(const std::string & fileName, std::vector<char>& buffer, ALenum & format, ALsizei & freq); ///< loads an off file and saves it to buffer
	ALuint GetId();
private:
	ALuint bufferId; ///< sound id
};