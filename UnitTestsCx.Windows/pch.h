#pragma once

#include "targetver.h"

#include "CppUnitTest.h"

#include <collection.h>
#include <sstream>
#include <iomanip>
#include <ppltasks.h>
#include <algorithm>

#include <robuffer.h>

#include "Await.h"

namespace WSS = Windows::Storage::Streams;

//
// Error handling
//

// Exception-based error handling
#define CHK(statement)  {HRESULT _hr = (statement); if (FAILED(_hr)) { throw ref new Platform::COMException(_hr); };}
#define CHKNULL(p)  {if ((p) == nullptr) { throw ref new Platform::NullReferenceException(L#p); };}
#define CHKOOM(p)  {if ((p) == nullptr) { throw ref new Platform::OutOfMemoryException(L#p); };}

//
// IBuffer data access
//

inline unsigned char* GetData(WSS::IBuffer^ buffer)
{
    unsigned char* bytes = nullptr;
    Microsoft::WRL::ComPtr<WSS::IBufferByteAccess> bufferAccess;
    CHK(((IUnknown*)buffer)->QueryInterface(IID_PPV_ARGS(&bufferAccess)));
    CHK(bufferAccess->Buffer(&bytes));
    return bytes;
}

namespace Microsoft { namespace VisualStudio { namespace CppUnitTestFramework {

    template<> static std::wstring ToString<__int64>(const __int64& t) { RETURN_WIDE_STRING(t); }

    template<> static std::wstring ToString<MediaCaptureReader::MediaSample2DFormat>(const MediaCaptureReader::MediaSample2DFormat& t) 
    { 
        switch (t)
        {
        case MediaCaptureReader::MediaSample2DFormat::Bgra8: return L"Bgra8";
        case MediaCaptureReader::MediaSample2DFormat::Nv12: return L"Nv12";
        case MediaCaptureReader::MediaSample2DFormat::Unknown: return L"Unknown";
        case MediaCaptureReader::MediaSample2DFormat::Yuy2: return L"Yuy2";
        case MediaCaptureReader::MediaSample2DFormat::Yv12: return L"Yv12";
        default: return L"Unknown MediaSample2DFormat";
        }
    }

} } }

class Log : public std::wostringstream
{
public:
    Log()
    {
    }

    ~Log()
    {
        *this << std::endl;
        ::Microsoft::VisualStudio::CppUnitTestFramework::Logger::WriteMessage(this->str().c_str());
    }
};
