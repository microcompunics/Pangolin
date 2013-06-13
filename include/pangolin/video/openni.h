#ifndef PANGOLIN_OPENNI_H
#define PANGOLIN_OPENNI_H

#include <pangolin/pangolin.h>
#include <pangolin/video.h>

// OpenNI generates SO MANY warnings, we'll just disable all for this header(!)
// GCC and clang will listen to this pramga.
#pragma GCC system_header
#include <XnCppWrapper.h>

namespace pangolin
{

enum OpenNiSensorType
{
    OpenNiUnassigned = -1,
    OpenNiRgb = 0,
    OpenNiIr = 1,
    OpenNiDepth = 2,
    OpenNiIr8bit = 3,
    OpenNiIrProj = 4,
    OpenNiIr8bitProj = 5
};

//! Interface to video capture sources
struct OpenNiVideo : public VideoInterface
{
public:
    OpenNiVideo(OpenNiSensorType s1, OpenNiSensorType s2);
    ~OpenNiVideo();

    //! Implement VideoInput::Start()
    void Start();
    
    //! Implement VideoInput::Stop()
    void Stop();

    //! Implement VideoInput::SizeBytes()
    size_t SizeBytes() const;

    //! Implement VideoInput::Streams()
    const std::vector<StreamInfo>& Streams() const;
    
    //! Implement VideoInput::GrabNext()
    bool GrabNext( unsigned char* image, bool wait = true );
    
    //! Implement VideoInput::GrabNewest()
    bool GrabNewest( unsigned char* image, bool wait = true );
    
protected:
    std::vector<StreamInfo> streams;
    OpenNiSensorType sensor_type[2];
    
    xn::Context context;
    xn::DepthGenerator depthNode;
    xn::ImageGenerator imageNode;
    xn::IRGenerator irNode;
    
    size_t sizeBytes;
};

}

#endif // PANGOLIN_OPENNI_H
