#ifndef AUDIO_H
#define AUDIO_H

#include <iostream>
#include <SDL2/SDL.h>

struct AudioData{
    Uint8* position;
    Uint32 length;
};
class Audio{
    public:
        Audio();
        ~Audio();
        bool Initialize();
        friend void MyAudioCallback(void* userData, Uint8* stream, int streamLength);
    private:
        AudioData adata;
};


#endif //AUDIO_H