#pragma once
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

#include "soloud_thread.h"

#include <cstdint>

namespace SoLoud
{
//Forward Declarations
class Wav;


/*!
 * \brief The ThreadedAssetLoader class enables us
 * to asynchronous load assets for playback without blocking our main thread.
 * Features such as load completion can also come from here. This API is only for
 * internal library use
 */
class ThreadedAssetLoader
{
public:
    //TODO - In the future Soloud could have a context based system
    //allowing for multiple instances and break us out of the singleton pattern
    static bool Initialize();
    static bool Destroy();
    static ThreadedAssetLoader* GetInstance();

    bool AddWavToLoad(Wav* targetWave, const char* filepath);


    ~ThreadedAssetLoader() = default;

protected:
    ThreadedAssetLoader();
    static constexpr size_t c_NumberOfThreadsInPool = 5;
    SoLoud::Thread::Pool m_ThreadPool;

};
}
