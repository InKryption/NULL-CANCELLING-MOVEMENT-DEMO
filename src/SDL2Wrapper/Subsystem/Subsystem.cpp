#include "Subsystem.hpp"

#ifdef _DEBUG
	#include <string>
#endif

namespace ink {
	
	void Subsystem::init(const Subsystem::Config& conf)
	{
		
		int SDL_InitCode = SDL_Init(conf.MAIN);
		
		#ifdef _DEBUG
			std::string __err_msg;
			if (SDL_InitCode != 0)
			__err_msg.append("SDL_InitCode: '" + std::to_string(SDL_InitCode) + "'. Message: '" + SDL_GetError() + "'.\n");
		#endif
		
		
		
		int TTF_InitCode = TTF_Init();
		
		#ifdef _DEBUG
			if (TTF_InitCode != 0)
			__err_msg.append("TTF_InitCode: '" + std::to_string(TTF_InitCode) + "'. Message: '" + SDL_GetError() + "'.\n");
		#endif
		
		
		
		auto IMG_Flags
		= IMG_INIT_JPG * conf.IMG.JPG
		| IMG_INIT_PNG * conf.IMG.PNG
		| IMG_INIT_TIF * conf.IMG.TIF
		| IMG_INIT_WEBP * conf.IMG.WEBP;
		
		int IMG_InitCode = IMG_Init(IMG_Flags);
		
		#ifdef _DEBUG
			if (IMG_InitCode != IMG_Flags)
			__err_msg.append("IMG_InitCode expected: '" + std::to_string(IMG_Flags) + "', got '"  + std::to_string(IMG_InitCode) + "'. Message: '" + SDL_GetError() + "'.\n");
		#endif
		
		
		
		auto MIX_Flags
		=	MIX_INIT_FLAC * conf.MIX.FLAC	|	MIX_INIT_MID * conf.MIX.MID		|	MIX_INIT_MOD * conf.MIX.MOD
		|	MIX_INIT_MP3 * conf.MIX.MP3		|	MIX_INIT_OGG * conf. MIX.OGG	|	MIX_INIT_OPUS * conf.MIX.OPUS;
		
		int MIX_InitCode = Mix_Init(MIX_Flags);
		
		#ifdef _DEBUG
			if (MIX_InitCode != MIX_Flags)
			__err_msg.append("MIX_InitCode expected: '" + std::to_string(MIX_Flags) + "', got '" + std::to_string(MIX_InitCode) + "'. Message: '" + SDL_GetError() + "'.\n");
			printf("%s", __err_msg.c_str());
		#endif
	}
	
	Subsystem::~Subsystem()
	{
		IMG_Quit();
		TTF_Quit();
		Mix_Quit();
		SDL_Quit();
	}
	
}