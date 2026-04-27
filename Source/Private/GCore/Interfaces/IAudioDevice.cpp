#include "GCore/Interfaces/IAudioDevice.h"
#include <stdexcept>

static IAudioDevice* AudioDeviceInstance = nullptr;

IAudioDevice& IAudioDevice::Get()
{
	return *AudioDeviceInstance;
}

void IAudioDevice::SetInstance(IAudioDevice* InInstance)
{
	AudioDeviceInstance = InInstance;
}
