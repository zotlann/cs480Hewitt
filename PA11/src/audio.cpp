#include "audio.h"

void MyAudioCallback(void* userData, Uint8* stream, int streamLength);
Audio::Audio(){}
Audio::~Audio(){}
bool Audio::Initialize()
{
    return true; //REMOVE THIS
    SDL_Init(SDL_INIT_AUDIO);
    filePath = "../assets/audio/coolMusic.wav";
    if(SDL_LoadWAV(filePath, &wavSpec, &wavStart, &wavLength) == NULL)
    {
        std::cerr << "Wrong audio file path." << std::endl;
        return false;
    }
    adata.position = wavStart;
    adata.length = wavLength;
    wavSpec.callback = MyAudioCallback;
    wavSpec.userdata = &adata;
    audioDevice = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, SDL_AUDIO_ALLOW_ANY_CHANGE);
    if(audioDevice == 0)
    {
        std::cerr << "Error: " << SDL_GetError() << std::endl;
        return false;
    }
    //starts track
    SDL_PauseAudioDevice(audioDevice, 0);

    /*while(adata.length > 0)
    {
        SDL_Delay(100);
    }
    SDL_CloseAudioDevice(audioDevice);
    SDL_FreeWAV(wavStart);*/
    //TODO: figure out how to loop this track
    //SDL_Quit();
    if(adata.length <= 0)
    {
        SDL_CloseAudioDevice(audioDevice);
        SDL_FreeWAV(wavStart);
    }

    isFinished = false;
    return true;
}

void Audio::Update()
{
    if(adata.length <= 0 && !isFinished)
    {
        isFinished = true;
        SDL_CloseAudioDevice(audioDevice);
        SDL_FreeWAV(wavStart);
        printf("Track finished\n");
    }
}

void MyAudioCallback(void* userData, Uint8* stream, int streamLength)
{
    AudioData* audioTemp = (AudioData*)userData;

    if (audioTemp->length == 0)
    {
        return;
    }

    Uint32 length = (Uint32)streamLength;
    length = (length > audioTemp->length ? audioTemp->length : length);

    SDL_memcpy(stream, audioTemp->position, length);

    audioTemp->position += length;
    audioTemp->length -= length;
}
