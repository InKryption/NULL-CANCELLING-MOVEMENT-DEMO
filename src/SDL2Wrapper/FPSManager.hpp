#ifndef __INK__FPS_MANAGER_STRUCT__HEADER_FILE_
#define __INK__FPS_MANAGER_STRUCT__HEADER_FILE_

#include "SDL2.hpp"

namespace ink {
	
	struct FPSManager
	{
		
		FPSManager(Uint32 FPS = 60):
		delta(1000 / FPS) {}
		
		// Place at beginning of loop
		void CaptureStartFrame()
		{
			start = SDL_GetTicks();
		}
		
		// Place at end of loop
		void CaptureEndFrame()
		{
			diff = SDL_GetTicks() - start;
			SDL_Delay( (delta > diff) * (delta - diff) );
		}
		
		void SetFPS(Uint32 new_fps)
		{
			delta = 1000 / new_fps;
		}
		
		Uint32 GetFPS()
		{
			return 1000 / delta;
		}
		
		private:
		Uint32 delta, start = 0, diff = 0;
	};
	
}

#endif