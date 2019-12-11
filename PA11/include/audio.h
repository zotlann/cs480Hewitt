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
        void Update();
        friend void MyAudioCallback(void* userData, Uint8* stream, int streamLength);
    private:
        SDL_AudioSpec wavSpec;
        Uint8* wavStart;
        Uint32 wavLength;
        const char* filePath; //used to be char*
        SDL_AudioDeviceID audioDevice;
        AudioData adata;
        //Uint8* aPos;
        //Uint32 aLen;
        bool isFinished;
};

#endif //AUDIO_H