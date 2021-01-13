#ifndef __INK__SDL2_PHYSICAL_KEYBOARD_WRAPPER_STRUCT__HEADER_FILE_
#define __INK__SDL2_PHYSICAL_KEYBOARD_WRAPPER_STRUCT__HEADER_FILE_

#ifdef _DEBUG
	#include <stdio.h>
#endif
#include "../SDL2.hpp"

namespace ink {
	
	// Use operator[SDL_Scancode] to retrieve physical key state
	struct PhysicalKeyboard
	{
		// Use [SDL_Scancode] to retrieve physical key state
		public: bool operator[](const SDL_Scancode& Scancode) {
			#ifdef _DEBUG
				if (Scancode > SDL_NUM_SCANCODES || Scancode == SDL_SCANCODE_UNKNOWN)
				{
					printf("'%i' is not a valid Scancode.\n", (int)Scancode);
					return false;
				}
			#endif
			return static_cast<bool>(PhysKB[Scancode]);
		}
		private: const Uint8* const PhysKB = SDL_GetKeyboardState(NULL);
	};
	
}

#endif