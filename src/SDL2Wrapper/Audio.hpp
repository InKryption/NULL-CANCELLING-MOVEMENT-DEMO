#ifndef __INK__SDL2_AUDIO_WRAPPER_STRUCT__HEADER_FILE_
#define __INK__SDL2_AUDIO_WRAPPER_STRUCT__HEADER_FILE_

#include "SDL2.hpp"

namespace ink {
	
	// Convenience struct to call Mix_OpenAudio or Mix_OpenAudioDevice, and call Mix_CloseAudio upon its destruction implicitly.
	struct Audio {
		
		// Open the mixer with a certain audio format
		Audio(int frequency = MIX_DEFAULT_FREQUENCY, Uint16 format = MIX_DEFAULT_FORMAT, int channels = MIX_DEFAULT_CHANNELS, int chunksize = 1024)
		{ Mix_OpenAudio(frequency, format, channels, chunksize); }
		
		// Open the mixer with specific device and certain audio format
		Audio(int frequency, Uint16 format, int channels, int chunksize, const char *device, int allowed_changes)
		{ Mix_OpenAudioDevice(frequency, format, channels, chunksize, device, allowed_changes); }
		
		// Close the mixer early, halting all playing audio
		static void close()
		{ Mix_CloseAudio(); }
		
		// Close the mixer automatically, halting all playing audio
		~Audio()
		{ close(); }
	};
	
}

#endif