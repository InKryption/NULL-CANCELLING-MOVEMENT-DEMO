#ifndef __SDL2_INCLUDES__HEADER_FILE_
#define __SDL2_INCLUDES__HEADER_FILE_

// Since I installed the package in WSL,
// it registered as actually being in linux, and
// thus defining __linux__ as '1', making it
// try to include "endian.h", which, I don't have.
#undef __linux__
// Make SDL not define main as SDL_main
#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>


#include <memory>
namespace SDL {
	
	typedef bool FunctionFlag;
	
	#pragma region Memory Free Functions
	
	inline void Destroy(SDL_Window* win)				{ SDL_DestroyWindow(win); }
	inline void Destroy(SDL_Renderer* ren)				{ SDL_DestroyRenderer(ren); }
	inline void Destroy(SDL_Surface* sur)				{ SDL_FreeSurface(sur); }
	inline void Destroy(SDL_Texture* tex)				{ SDL_DestroyTexture(tex); }
	
	inline void Destroy(SDL_cond* con)					{ SDL_DestroyCond(con); }
	inline void Destroy(SDL_semaphore* sem)				{ SDL_DestroySemaphore(sem); }
	inline void Destroy(SDL_mutex* mut)					{ SDL_DestroyMutex(mut); }
	inline void Destroy(SDL_MetalView view)				{ SDL_Metal_DestroyView(view); }
	
	#pragma endregion
	
	struct Deleter { template<typename T> inline void operator()(T sdl) { Destroy(sdl); } };
	
}

#endif