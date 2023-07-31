#include "soloud_error.h"

namespace SoLoud
{
    const char * getErrorString(SOLOUD_ERRORCODE aErrorCode)
    {
        switch (aErrorCode)
        {
            case SO_NO_ERROR: return "No error";
            case INVALID_PARAMETER: return "Some parameter is invalid";
            case FILE_NOT_FOUND: return "File not found";
            case FILE_LOAD_FAILED: return "File found, but could not be loaded";
            case DLL_NOT_FOUND: return "DLL not found, or wrong DLL";
            case OUT_OF_MEMORY: return "Out of memory";
            case NOT_IMPLEMENTED: return "Feature not implemented";
            case UNKNOWN_ERROR: return "Unknown Error";
        }
        return "Other error";
    }
} //namespace SoLoud
