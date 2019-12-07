#include "audio.h"

void MyAudioCallback(void* userData, Uint8* stream, int streamLength);
Audio::Audio(){}
Audio::~Audio(){}
bool Audio::Initialize()
{
    return true; //REMOVE THIS
    SDL_Init(SDL_INIT_AUDIO);
    SDL_AudioSpec wavSpec;
    Uint8* wavStart;
    Uint32 wavLength;
    char* filePath = "../assets/audio/coolMusic.wav";
    if(SDL_LoadWAV(filePath, &wavSpec, &wavStart, &wavLength) == NULL)
    {
        std::cerr << "Wrong audio file path." << std::endl;
        return false;
    }
    adata.position = wavStart;
    adata.length = wavLength;
    wavSpec.callback = MyAudioCallback;
    wavSpec.userdata = &adata;
    SDL_AudioDeviceID audioDevice;
    audioDevice = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, SDL_AUDIO_ALLOW_ANY_CHANGE);
    if(audioDevice == 0)
    {
        std::cerr << "Error: " << SDL_GetError() << std::endl;
        return false;
    }
    SDL_PauseAudioDevice(audioDevice, 0);
    while(adata.length > 0)
    {
        SDL_Delay(100);
    }
    SDL_CloseAudioDevice(audioDevice);
    SDL_FreeWAV(wavStart);
    //SDL_Quit();

    std::cout << "Audio!" << std::endl;
    return true;
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
/*
int main(int argc, char** argv)
{
    SDL_Init(SDL_INIT_AUDIO);

    SDL_AudioSpec wavSpec;
    Uint8* wavStart;
    Uint32 wavLength;
    char* filePath = "ADD YOUR FILE PATH HERE";

    if(SDL_LoadWAV(filePath, &wavSpec, &wavStart, &wavLength) == NULL)
    {
        cerr << "Error: file could not be loaded as an audio file." << endl;
    }

    AudioData audio;
    audio.position = wavStart;
    audio.length = wavLength;

    wavSpec.callback = audioCallback;
    wavSpec.userdata = &audio;

    SDL_AudioDeviceID audioDevice;
    audioDevice = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, SDL_AUDIO_ALLOW_ANY_CHANGE);

    if (audioDevice == 0)
    {
        cerr << "Error: " << SDL_GetError() << endl;
        return 1;
    }

    SDL_PauseAudioDevice(audioDevice, 0);

    while (audio.length > 0)
    {
        SDL_Delay(100);
    }

    SDL_CloseAudioDevice(audioDevice);
    SDL_FreeWAV(wavStart);
    SDL_Quit();

    return 0;
}
*/