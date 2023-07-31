/*
SoLoud audio engine
Copyright (c) 2013-2018 Jari Komppa

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

   1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.

   2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.

   3. This notice may not be removed or altered from any source
   distribution.
*/

#ifndef SOLOUD_WAV_H
#define SOLOUD_WAV_H

#include "soloud.h"
#include <atomic>

struct stb_vorbis;

class LoadPCMAudioDataTask;

namespace SoLoud
{
	class Wav;
	class File;
	class MemoryFile;

	class WavInstance : public AudioSourceInstance
	{
		Wav *mParent;
		unsigned int mOffset;
	public:
		WavInstance(Wav *aParent);
        virtual unsigned int getAudio(float *aBuffer, unsigned int aSamplesToRead, unsigned int aBufferSize) final;
        virtual result rewind();
        virtual bool hasEnded();
	};

	class Wav : public AudioSource
	{
        SOLOUD_ERRORCODE internalLoad(const char *aFilename);
        SOLOUD_ERRORCODE loadwav(MemoryFile *aReader);
        SOLOUD_ERRORCODE loadogg(MemoryFile *aReader);
        SOLOUD_ERRORCODE loadmp3(MemoryFile *aReader);
        SOLOUD_ERRORCODE loadflac(MemoryFile *aReader);
        SOLOUD_ERRORCODE testAndLoadFile(MemoryFile *aReader);

        float *mData{nullptr};

        //In a multithreaded loader environment this allows files
        //that havent been loaded to still tick correctly
        std::atomic<bool> mDataIsLoaded{false};


	public:
        unsigned int mSampleCount{0};

        friend WavInstance;
        friend LoadPCMAudioDataTask;

        Wav() = default;
		virtual ~Wav();
        SOLOUD_ERRORCODE load(const char *aFilename);
        SOLOUD_ERRORCODE loadMem(const unsigned char *aMem, unsigned int aLength, bool aCopy = false, bool aTakeOwnership = true);
        SOLOUD_ERRORCODE loadFile(File &aFile);
        SOLOUD_ERRORCODE loadRawWave8(unsigned char *aMem, unsigned int aLength, float aSamplerate = 44100.0f, unsigned int aChannels = 1);
        SOLOUD_ERRORCODE loadRawWave16(short *aMem, unsigned int aLength, float aSamplerate = 44100.0f, unsigned int aChannels = 1);
        SOLOUD_ERRORCODE loadRawWave(float *aMem, unsigned int aLength, float aSamplerate = 44100.0f, unsigned int aChannels = 1, bool aCopy = false, bool aTakeOwnership = true);

		virtual AudioSourceInstance *createInstance();
		time getLength();
	};
};

#endif
