#include "Sound.h"
#include "stb_vorbis.h"
#include "Exception.h"

Sound::Sound(){
	bufferId = 0;
	alGenBuffers(1, &bufferId);

	ALenum format = 0;
	ALsizei freq = 0;
	std::vector<char> bufferData;
	load_ogg("../src/game/models/dixie_horn.ogg", bufferData, format, freq);

	alBufferData(bufferId, format, &bufferData.at(0), static_cast<ALsizei>(bufferData.size()), freq);
}

Sound::Sound(std::string path){
	bufferId = 0;
	alGenBuffers(1, &bufferId);

	ALenum format = 0;
	ALsizei freq = 0;
	std::vector<char> bufferData;
	load_ogg(path, bufferData, format, freq);

	alBufferData(bufferId, format, &bufferData.at(0), static_cast<ALsizei>(bufferData.size()), freq);
}

Sound::~Sound(){
	
}

void Sound::load(std::string path){
	bufferId = 0;
	alGenBuffers(1, &bufferId);

	ALenum format = 0;
	ALsizei freq = 0;
	std::vector<char> bufferData;
	load_ogg(path, bufferData, format, freq);

	alBufferData(bufferId, format, &bufferData.at(0), static_cast<ALsizei>(bufferData.size()), freq);
}

void Sound::load_ogg(const std::string & fileName, std::vector<char>& buffer, ALenum & format, ALsizei & freq){
	int channels = 0;
	int sampleRate = 0;
	short* output = NULL;

	size_t samples = stb_vorbis_decode_filename(
		fileName.c_str(), &channels, &sampleRate, &output);

	if (samples == -1)
	{
		throw Exception("coudln't load sound");
	}

	// Record the sample rate required by OpenAL
	freq = sampleRate;

	// Record the format required by OpenAL
	if (channels == 1)
	{
		format = AL_FORMAT_MONO16;
	}
	else
	{
		format = AL_FORMAT_STEREO16;

		// Force format to be mono (Useful for positional audio)
		format = AL_FORMAT_MONO16;
		freq *= 2;
	}

	// Allocate enough space based on short (two chars) multipled by the number of
	// channels and length of clip
	buffer.resize(sizeof(*output) * channels * samples);
	memcpy(&buffer.at(0), output, buffer.size());

	// Clean up the read data
	free(output);
}

ALuint Sound::GetId(){
	return bufferId;
}
