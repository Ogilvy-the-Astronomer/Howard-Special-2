#include<string>
#include<vector>
#include<AL/al.h>
struct SoundBuffer {
	VertexBuffer();
	void load_ogg(const std::string & fileName, std::vector<char>& buffer, ALenum & format, ALsizei & freq);
	
};