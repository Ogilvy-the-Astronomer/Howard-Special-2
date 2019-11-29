#include<string>
#include<vector>
#include<AL/al.h>
#include"Resource.h"
#include"NonCopyable.h"

struct Sound : private NonCopyable, public Resource {
	Sound();
	Sound(std::string path);
	~Sound();
	std::shared_ptr<Sound> load(std::string path);
	void load_ogg(const std::string & fileName, std::vector<char>& buffer, ALenum & format, ALsizei & freq);
	ALuint GetId();
private:
	ALuint bufferId;
};