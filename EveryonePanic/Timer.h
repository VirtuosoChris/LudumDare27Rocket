#ifndef VIRTUOSO_TIMER_H_INCLUDED
#define VIRTUOSO_TIMER_H_INCLUDED

#include <chrono>

class Timer{


public:

    std::chrono::high_resolution_clock::time_point lastTime;

    Timer(){
        reset();
    }

    void reset(){
        lastTime = std::chrono::high_resolution_clock::now();
    }


    double getDelta(){

         std::chrono::high_resolution_clock::time_point currentTime =  std::chrono::high_resolution_clock::now();

         std::chrono::duration<double> time_span =  std::chrono::duration_cast< std::chrono::duration<double>>(currentTime - lastTime);

        return time_span.count();

       // lastTime = currentTime;

    }

};

#endif
