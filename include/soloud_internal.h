/*
SoLoud audio engine
Copyright (c) 2013-2015 Jari Komppa

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

#ifndef SOLOUD_INTERNAL_H
#define SOLOUD_INTERNAL_H

#include "soloud.h"
#include <unordered_map>

namespace SoLoud
{
    result sdl1_init(SoLoud::Soloud *aSoloud, unsigned int aFlags, unsigned int aSamplerate, unsigned int aBuffer, unsigned int aChannels);
    result sdl2_init(SoLoud::Soloud *aSoloud, unsigned int aFlags, unsigned int aSamplerate, unsigned int aBuffer, unsigned int aChannels);
    result sdl2static_init(SoLoud::Soloud *aSoloud, unsigned int aFlags, unsigned int aSamplerate, unsigned int aBuffer, unsigned int aChannels);
    result openal_init(SoLoud::Soloud *aSoloud, unsigned int aFlags, unsigned int aSamplerate, unsigned int aBuffer, unsigned int aChannels);
    result coreaudio_init(SoLoud::Soloud *aSoloud, unsigned int aFlags, unsigned int aSamplerate, unsigned int aBuffer, unsigned int aChannels);
    result opensles_init(SoLoud::Soloud *aSoloud, unsigned int aFlags, unsigned int aSamplerate, unsigned int aBuffer, unsigned int aChannels);
    result portaudio_init(SoLoud::Soloud *aSoloud, unsigned int aFlags, unsigned int aSamplerate, unsigned int aBuffer, unsigned int aChannels);
    result winmm_init(SoLoud::Soloud *aSoloud, unsigned int aFlags, unsigned int aSamplerate, unsigned int aBuffer, unsigned int aChannels);
    result xaudio2_init(SoLoud::Soloud *aSoloud, unsigned int aFlags, unsigned int aSamplerate, unsigned int aBuffer, unsigned int aChannels);
    result wasapi_init(SoLoud::Soloud *aSoloud, unsigned int aFlags, unsigned int aSamplerate, unsigned int aBuffer, unsigned int aChannels);
    result oss_init(SoLoud::Soloud *aSoloud, unsigned int aFlags, unsigned int aSamplerate, unsigned int aBuffer, unsigned int aChannels);
    result vita_homebrew_init(SoLoud::Soloud *aSoloud, unsigned int aFlags, unsigned int aSamplerate, unsigned int aBuffer, unsigned int aChannels);
    result alsa_init(SoLoud::Soloud *aSoloud, unsigned int aFlags, unsigned int aSamplerate, unsigned int aBuffer, unsigned int aChannels);
    result pipewire_init(SoLoud::Soloud *aSoloud, unsigned int aFlags, unsigned int aSamplerate, unsigned int aBuffer, unsigned int aChannels);
    result jack_init(SoLoud::Soloud *aSoloud, unsigned int aFlags, unsigned int aSamplerate, unsigned int aBuffer, unsigned int aChannels);
    result miniaudio_init(SoLoud::Soloud* aSoloud, unsigned int aFlags, unsigned int aSamplerate, unsigned int aBuffer, unsigned int aChannels);
    result nosound_init(SoLoud::Soloud* aSoloud, unsigned int aFlags, unsigned int aSamplerate, unsigned int aBuffer, unsigned int aChannels);
    result null_init(SoLoud::Soloud *aSoloud, unsigned int aFlags, unsigned int aSamplerate, unsigned int aBuffer, unsigned int aChannels);

    typedef result (SoloudBackEndInitializationFunction)(SoLoud::Soloud *aSoloud, unsigned int aFlags, unsigned int aSamplerate, unsigned int aBuffer, unsigned int aChannels);
    struct BackEndInitializationFunctionAndDefaults
    {
        unsigned int mFlags{0};
        unsigned int mSampleRate{0};
        unsigned int mBufferSize{0};
        unsigned int mChannels{0};
        SoloudBackEndInitializationFunction* mFunction{nullptr};
    };

    static const std::unordered_map<Soloud::BACKENDS, BackEndInitializationFunctionAndDefaults> scBackends =
    {
        {Soloud::SDL1,
         {
             .mFlags = Soloud::CLIP_ROUNDOFF,
             .mSampleRate = 44100,
             .mBufferSize = 2048,
             .mChannels = 2,
             .mFunction = sdl1_init
         }
        },

        {Soloud::SDL2,
         {
             .mFlags = Soloud::CLIP_ROUNDOFF,
             .mSampleRate = 44100,
             .mBufferSize = 2048,
             .mChannels = 2,
         #if WITH_SDL2_STATIC
             .mFunction = sdl2static_init
         #else
             .mFunction = sdl2_init
         #endif
         }
        },

        {Soloud::OPENAL,
         {
             .mFlags = Soloud::CLIP_ROUNDOFF,
             .mSampleRate = 44100,
             .mBufferSize = 2048,
             .mChannels = 2,
             .mFunction = openal_init
         }
        },

        {Soloud::COREAUDIO,
         {
             .mFlags = Soloud::CLIP_ROUNDOFF,
             .mSampleRate = 44100,
             .mBufferSize = 2048,
             .mChannels = 2,
             .mFunction = coreaudio_init
         }
        },

        {Soloud::OPENSLES,
         {
             .mFlags = Soloud::CLIP_ROUNDOFF,
             .mSampleRate = 44100,
             .mBufferSize = 2048,
             .mChannels = 2,
             .mFunction = opensles_init
         }
        },

        {Soloud::PORTAUDIO,
         {
             .mFlags = Soloud::CLIP_ROUNDOFF,
             .mSampleRate = 44100,
             .mBufferSize = 2048,
             .mChannels = 2,
             .mFunction = portaudio_init
         }
        },

        {Soloud::WINMM,
         {
             .mFlags = Soloud::CLIP_ROUNDOFF,
             .mSampleRate = 44100,
             .mBufferSize = 4096,
             .mChannels = 2,
             .mFunction = winmm_init
         }
        },

        {Soloud::XAUDIO2,
         {
             .mFlags = Soloud::CLIP_ROUNDOFF,
             .mSampleRate = 44100,
             .mBufferSize = 2048,
             .mChannels = 2,
             .mFunction = xaudio2_init
         }
        },

        {Soloud::WASAPI,
         {
             .mFlags = Soloud::CLIP_ROUNDOFF,
             .mSampleRate = 44100,
             .mBufferSize = 4096,
             .mChannels = 2,
             .mFunction = wasapi_init
         }
        },

        {Soloud::OSS,
         {
             .mFlags = Soloud::CLIP_ROUNDOFF,
             .mSampleRate = 44100,
             .mBufferSize = 2048,
             .mChannels = 2,
             .mFunction = oss_init
         }
        },

        {Soloud::VITA_HOMEBREW,
         {
             .mFlags = Soloud::CLIP_ROUNDOFF,
             .mSampleRate = 44100,
             .mBufferSize = 2048,
             .mChannels = 2,
             .mFunction = vita_homebrew_init
         }
        },

        {Soloud::ALSA,
         {
             .mFlags = Soloud::CLIP_ROUNDOFF,
             .mSampleRate = 44100,
             .mBufferSize = 2048,
             .mChannels = 2,
             .mFunction = alsa_init
         }
        },

        {Soloud::PIPEWIRE,
         {
             .mFlags = Soloud::CLIP_ROUNDOFF,
             .mSampleRate = 44100,
             .mBufferSize = 2048,
             .mChannels = 2,
             .mFunction = pipewire_init
         }
        },

        {Soloud::JACK,
         {
             .mFlags = Soloud::CLIP_ROUNDOFF,
             .mSampleRate = 44100,
             .mBufferSize = 2048,
             .mChannels = 2,
             .mFunction = jack_init
         }
        },

        {Soloud::MINIAUDIO,
         {
             .mFlags = Soloud::CLIP_ROUNDOFF,
             .mSampleRate = 44100,
             .mBufferSize = 2048,
             .mChannels = 2,
             .mFunction = miniaudio_init
         }
        },

        {Soloud::NOSOUND,
         {
             .mFlags = Soloud::CLIP_ROUNDOFF,
             .mSampleRate = 44100,
             .mBufferSize = 2048,
             .mChannels = 2,
             .mFunction = nosound_init
         }
        },

        {Soloud::NULLDRIVER,
         {
             .mFlags = Soloud::CLIP_ROUNDOFF,
             .mSampleRate = 44100,
             .mBufferSize = 2048,
             .mChannels = 2,
             .mFunction = null_init
         }
        },
    };

	// Interlace samples in a buffer. From 11112222 to 12121212
	void interlace_samples_float(const float *aSourceBuffer, float *aDestBuffer, unsigned int aSamples, unsigned int aChannels, unsigned int aStride);

	// Convert to 16-bit and interlace samples in a buffer. From 11112222 to 12121212
	void interlace_samples_s16(const float *aSourceBuffer, short *aDestBuffer, unsigned int aSamples, unsigned int aChannels, unsigned int aStride);
};

#define FOR_ALL_VOICES_PRE \
		handle *h_ = NULL; \
		handle th_[2] = { aVoiceHandle, 0 }; \
		lockAudioMutex_internal(); \
		h_ = voiceGroupHandleToArray_internal(aVoiceHandle); \
		if (h_ == NULL) h_ = th_; \
		while (*h_) \
		{ \
			int ch = getVoiceFromHandle_internal(*h_); \
			if (ch != -1)  \
			{

#define FOR_ALL_VOICES_POST \
			} \
			h_++; \
		} \
		unlockAudioMutex_internal();

#define FOR_ALL_VOICES_PRE_3D \
		handle *h_ = NULL; \
		handle th_[2] = { aVoiceHandle, 0 }; \
		h_ = voiceGroupHandleToArray_internal(aVoiceHandle); \
		if (h_ == NULL) h_ = th_; \
				while (*h_) \
						{ \
			int ch = (*h_ & 0xfff) - 1; \
			if (ch != -1 && m3dData[ch].mHandle == *h_)  \
						{

#define FOR_ALL_VOICES_POST_3D \
						} \
			h_++; \
						} 

#define FOR_ALL_VOICES_PRE_EXT \
		handle *h_ = NULL; \
		handle th_[2] = { aVoiceHandle, 0 }; \
		mSoloud->lockAudioMutex_internal(); \
		h_ = mSoloud->voiceGroupHandleToArray_internal(aVoiceHandle); \
		if (h_ == NULL) h_ = th_; \
		while (*h_) \
		{ \
			int ch = mSoloud->getVoiceFromHandle_internal(*h_); \
			if (ch != -1)  \
			{

#define FOR_ALL_VOICES_POST_EXT \
			} \
			h_++; \
		} \
		mSoloud->unlockAudioMutex_internal();

#define FOR_ALL_VOICES_PRE_3D_EXT \
		handle *h_ = NULL; \
		handle th_[2] = { aVoiceHandle, 0 }; \
		h_ = mSoloud->voiceGroupHandleToArray(aVoiceHandle); \
		if (h_ == NULL) h_ = th_; \
				while (*h_) \
						{ \
			int ch = (*h_ & 0xfff) - 1; \
			if (ch != -1 && mSoloud->m3dData[ch].mHandle == *h_)  \
						{

#define FOR_ALL_VOICES_POST_3D_EXT \
						} \
			h_++; \
						} 

#endif
