#include <avbin.h>
#include <string>

#include <memory>
#include "Texture.h"
#include "Timer.h"


class MovieState
{

public:

    struct MovieFrame{

        std::shared_ptr<unsigned char> image;
        double timeStamp;

        MovieFrame():image(0),timeStamp(0){}

        MovieFrame( std::shared_ptr<unsigned char> frame, float timeIn):
        image(frame),timeStamp(timeIn){}

        operator bool(){return image.get();}

    };



    bool playing;

    Timer movieTimer;
    Texture texture;

    MovieFrame currentFrame;

    ///resolution
    int movieWidth;
    int movieHeight;

    double duration;

    AVbinFile* file;
    AVbinFileInfo fileinfo;
    AVbinStream* video_stream;

    int video_stream_index;

    bool openVideoStream();

    MovieState(const std::string& filename);

    MovieState(){}///\todo nu;; init

    MovieFrame getFrame();

    operator bool();

    void cleanup();

    void begin();

    ~MovieState();

    void update(); ///check timer and get next frame if needed


};
