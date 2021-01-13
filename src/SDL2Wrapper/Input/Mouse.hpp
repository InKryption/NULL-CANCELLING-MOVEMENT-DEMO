#ifndef __INK__SDL2_MOUSE_WRAPPER_STRUCT__HEADER_FILE_
#define __INK__SDL2_MOUSE_WRAPPER_STRUCT__HEADER_FILE_

#include "../Geometry/Rect.hpp"

namespace ink {
	
	// Mouse state.
	struct Mouse:
	public V2D<int>
	{
		
		Mouse(): V2D<int>(0, 0) { Update(); }
		
		enum class Button {
			LEFT,	// Right Mouse Button
			MIDDLE,	// Middle Mouse Button
			RIGHT	// Right Mouse Button
		};
		
		bool Released(const Button& b = Button::LEFT)
		{ return (b == Button::LEFT) * LRelease + (b == Button::MIDDLE) * MRelease + (b == Button::RIGHT) * RRelease; }
		
		bool Pressed(const Button& b = Button::LEFT)
		{ return (b == Button::LEFT) * LPress + (b == Button::MIDDLE) * MPress + (b == Button::RIGHT) * RPress; }
		
		bool Held(const Button& b = Button::LEFT)
		{ return (b == Button::LEFT) * LHold + (b == Button::MIDDLE) * MHold + (b == Button::RIGHT) * RHold; }
		
		void Update() {
			auto mState = SDL_GetMouseState(&x, &y);
			bool
				pLHold = this->LHold,
				pMHold = this->MHold,
				pRHold = this->RHold;
			
			LHold = mState & SDL_BUTTON_LMASK;
			MHold = mState & SDL_BUTTON_MMASK;
			RHold = mState & SDL_BUTTON_RMASK;
			
			LRelease = !LHold && pLHold;
			MRelease = !MHold && pMHold;
			RRelease = !RHold && pRHold;
			
			LPress = LHold && !pLHold;
			MPress = MHold && !pMHold;
			RPress = RHold && !pRHold;
		}
		
		private:
		bool
		LRelease = 0, MRelease = 0, RRelease = 0,
		LPress = 0, MPress = 0, RPress = 0,
		LHold = 0, MHold = 0, RHold = 0;
		
	};
	
}

#endif