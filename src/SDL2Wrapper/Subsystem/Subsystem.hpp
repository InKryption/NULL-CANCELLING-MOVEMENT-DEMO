#ifndef __SDL_PROJECT6__SDL_HELPER_FUNCTION__SUBSYSTEM_INIT__HEADER_FILE_
#define __SDL_PROJECT6__SDL_HELPER_FUNCTION__SUBSYSTEM_INIT__HEADER_FILE_

#include "../SDL2.hpp"

namespace ink {
	
	// Struct which simplifies the initialization of SDL Subsystems
	// - alongside that of the SDL extensions -, and automatically
	// deinitializes all of the SDL subsystems on destruction.
	struct Subsystem {
		
		struct Config {
			int MAIN = SDL_INIT_EVERYTHING;
			
			struct {
				bool
				JPG = 0, TIF = 0,
				WEBP = 0, PNG = 0;
			} IMG;
			
			struct {
				bool
				FLAC = 0, MID = 0, MOD = 0,
				MP3 = 0, OGG = 0, OPUS = 0;
			} MIX;
		};
		
		void init(const Config& conf);
		~Subsystem();
	};
	
}

#endif