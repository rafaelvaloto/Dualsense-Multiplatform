#include "GCore/Interfaces/IAudioDevice.h"
#include <stdexcept>

static IAudioDevice* AudioDeviceInstance = nullptr;

IAudioDevice& IAudioDevice::Get()
{
	if (!AudioDeviceInstance)
	{
		// No ambiente de testes, podemos querer retornar um mock ou falhar silenciosamente
		// Para agora, vamos assumir que ele DEVE ser configurado.
		// No CLion/Windows, podemos usar um fallback se necessário.
	}
	return *AudioDeviceInstance;
}

void IAudioDevice::SetInstance(IAudioDevice* InInstance)
{
	AudioDeviceInstance = InInstance;
}
