#include "MovieState.h"
#include <stdexcept>
#include <iostream>


template <class T>
struct ArrayDeleter
{

    void operator()(T* ptr)
    {
        delete[] ptr;
    }

};



void MovieState::begin(){

    movieTimer.reset();

    currentFrame = getFrame();

    playing = currentFrame;
}


void MovieState::update(){

    if(playing){
    if(movieTimer.getDelta() > currentFrame.timeStamp){

        playing = (currentFrame = getFrame());
        if(playing){
        texture.subImage(currentFrame.image.get());
        }
    }
}

}


MovieState::MovieFrame MovieState::getFrame()
{

    AVbinPacket packet;
    packet.structure_size = sizeof(packet);

    if(!video_stream){
    if(!openVideoStream()){

        throw std::runtime_error("Unable to open stream");
    }
    }

    if(!file)throw std::runtime_error("FILE NOT OPEN");


   while (!avbin_read(file, &packet))
    {

          if (packet.stream_index == video_stream_index)
        {
            unsigned char* video_buffer =  new unsigned char[movieWidth*movieHeight*3];
            if (avbin_decode_video(video_stream, packet.data, packet.size,video_buffer)<=0){
                printf("could not read video packet\n");
                continue;
            }
           // else printf("read video frame\n");

            // do something with video_buffer
            return MovieFrame(std::shared_ptr<unsigned char>((unsigned char*)video_buffer,ArrayDeleter<unsigned char>()),packet.timestamp* 1e-6);
            //free(video_buffer);
        }

    }


    return MovieFrame(); ///empty frame


}



void MovieState::cleanup()
{
    if (video_stream)
    {
        avbin_close_stream(video_stream);
        video_stream=0;
    }

    if(file)
    {
        avbin_close_file(file);
        file=0;
    }

}





MovieState::~MovieState()
{
    cleanup();
}


bool MovieState::openVideoStream()
{

    if(video_stream_index<0)return false;

    return (video_stream = avbin_open_stream(file, video_stream_index));

}


MovieState::operator bool()
{
    return file;
}


MovieState::MovieState(const std::string& filename)
    :file(avbin_open_filename(filename.c_str() )),
    video_stream(NULL),
    video_stream_index(-1),
    playing(0)
{
    if (!file)
    {
        throw std::runtime_error("Unable to open file");
    }

    fileinfo.structure_size = sizeof(fileinfo);

    if (avbin_file_info(file, &fileinfo))
    {
        throw std::runtime_error("Unable to read file info");
    }

    std::cout<<"Number of streams: "<<fileinfo.n_streams<<std::endl;
    std::cout<<"Duration: "<<(((double)fileinfo.duration) * 1e-6)<<std::endl;
    std::cout<<"Start Time: "<<fileinfo.start_time<<std::endl;

    int stream_index;
    for (stream_index=0; stream_index<fileinfo.n_streams; stream_index++)
    {
        AVbinStreamInfo8 streaminfo;
        streaminfo.structure_size = sizeof(streaminfo);

        avbin_stream_info(file, stream_index, (AVbinStreamInfo *) &streaminfo);

        if (streaminfo.type == AVBIN_STREAM_TYPE_VIDEO)
        {

            movieWidth = streaminfo.video.width;
            movieHeight = streaminfo.video.height;
            video_stream_index = stream_index;

        }

    }

    texture = Texture(movieWidth,movieHeight, 3);
}
