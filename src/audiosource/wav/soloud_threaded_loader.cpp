#include "soloud_threaded_loader.h"
#include "soloud_wav.h"
#include "soloud_log.h"

#include <memory>
#include <string>

using namespace SoLoud;
static ThreadedAssetLoader* s_LoaderInstance{nullptr};

class LoadPCMAudioDataTask : public Thread::PoolTask
{
public:
    LoadPCMAudioDataTask() = default;
    ~LoadPCMAudioDataTask() = default;
    void work() final
    {
        SOLOUD_ERRORCODE errorCode = m_TargetWav->internalLoad(m_TargetFilepath.c_str());
        LogMessage(LogSeverity::Trace, LogCategory::PCMLoader, "Load PCM \"%s\" complete with ErrorCode %s", m_TargetFilepath.c_str(), getErrorString(errorCode));

        //This is awful design that needs to be changed as this is easy
        //thing that could become painful in the future.
        delete this;
    }

    Wav* m_TargetWav{nullptr};
    std::string m_TargetFilepath;
};

/*static*/ bool ThreadedAssetLoader::Initialize()
{
    if(s_LoaderInstance != nullptr)
        return false;

    s_LoaderInstance = new ThreadedAssetLoader();
    return true;
}

/*static*/ bool ThreadedAssetLoader::Destroy()
{
    if(s_LoaderInstance == nullptr)
        return false;

    delete s_LoaderInstance;
    s_LoaderInstance = nullptr;
    return true;
}

/*static*/ ThreadedAssetLoader* ThreadedAssetLoader::GetInstance()
{
    return s_LoaderInstance;
}

ThreadedAssetLoader::ThreadedAssetLoader()
{
    m_ThreadPool.init(c_NumberOfThreadsInPool, "SLWavLoader");
}

bool ThreadedAssetLoader::AddWavToLoad(Wav* targetWave, const char* filepath)
{
    LoadPCMAudioDataTask* newTask = new LoadPCMAudioDataTask();
    newTask->m_TargetWav = targetWave;
    newTask->m_TargetFilepath = filepath;

    LogMessage(LogSeverity::Trace, LogCategory::PCMLoader, "Added new PCM to load \"%s\"", filepath);
    m_ThreadPool.addWork(newTask);

    return true;
}
