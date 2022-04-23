#pragma once
#include <AL/al.h>
#include <AL/alc.h>
#include <dr_wav.h>
#include <iostream>
#include <vector>
#include <map>

namespace GameEngine {
	#define OpenAL_ErrorCheck(message)\
	{\
		ALenum error = alGetError();\
		if( error != AL_NO_ERROR)\
		{\
			std::cerr << "OpenAL Error: " << error << " with call for " << #message << std::endl;\
		}\
	}

	#define alec(FUNCTION_CALL)\
	FUNCTION_CALL;\
	OpenAL_ErrorCheck(FUNCTION_CALL)

	struct ReadWavData
	{
		std::string name = "";
		unsigned int channels = 0;
		unsigned int sampleRate = 0;
		drwav_uint64 totalPCMFrameCount = 0;
		std::vector<uint16_t> pcmData;
		drwav_uint64 getTotalSamples() { return totalPCMFrameCount * channels; }
	};

	class AudioManager {
	private:
		ALCdevice* device;
		//std::vector<>;
		std::map<std::string, ReadWavData> audios;

	public:
		ALCcontext* context;
		bool success;

		AudioManager();
		~AudioManager();

		ALCdevice* getDevice() const;
		void clean();

		void readStereoData(std::string filename);
		void readMonoData(std::string filename);
	};



}