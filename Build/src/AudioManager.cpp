#include "AudioManager.h"

GameEngine::AudioManager::AudioManager()
{
    // find the default audio device
    const ALCchar* defaultDeviceString = alcGetString(/*device*/nullptr, ALC_DEFAULT_DEVICE_SPECIFIER);
    device = alcOpenDevice(defaultDeviceString);
    if (!device)
    {
        std::cerr << "failed to get the default device for OpenAL" << std::endl;
        success = false;
    }
    else
    {
        std::cout << "OpenAL Device: " << alcGetString(device, ALC_DEVICE_SPECIFIER) << std::endl;

        // Create an OpenAL audio context from the device
        context = alcCreateContext(device, /*attrlist*/ nullptr);

        // Activate this context so that OpenAL state modifications are applied to the context
        success = alcMakeContextCurrent(context);

        if (!success)
        {
            std::cerr << "failed to make the OpenAL context the current context" << std::endl;
        }
        else
        {
            // Create a listener in 3d space (ie the player); (there always exists as listener, you just configure data on it)
            alec(alListener3f(AL_POSITION, 0.f, 0.f, 0.f));
            alec(alListener3f(AL_VELOCITY, 0.f, 0.f, 0.f));
            ALfloat forwardAndUpVectors[] = {
                /*forward = */ 1.f, 0.f, 0.f,
                /* up = */ 0.f, 1.f, 0.f
            };
            alec(alListenerfv(AL_ORIENTATION, forwardAndUpVectors));
        }
    }
}

GameEngine::AudioManager::~AudioManager()
{
}

ALCdevice* GameEngine::AudioManager::getDevice() const
{
    return device;
}

void GameEngine::AudioManager::clean()
{
    alcMakeContextCurrent(nullptr);
    alcDestroyContext(context);
    alcCloseDevice(device);
}
