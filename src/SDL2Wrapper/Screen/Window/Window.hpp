#ifndef __INK__SDL2_WINDOW_WRAPPER_STRUCT__HEADER_FILE_
#define __INK__SDL2_WINDOW_WRAPPER_STRUCT__HEADER_FILE_

#include "../../Geometry/Geometry.hpp"
#include "../../SDL2.hpp"

namespace ink {
	
	// Can be passed as an SDL_Window*, and includes functionality wrapping the usage of SDL_Window* into OO Design.
	struct Window
	{
		// Configuration struct for window on initialization
		struct Config
		{
			const char* title = "Window";
			int width_percentage = 50,
				height_percentage = 50,
				x = SDL_WINDOWPOS_UNDEFINED,
				y = SDL_WINDOWPOS_UNDEFINED;
			struct {
				bool
					FULLSCREEN = 0, FULLSCREEN_DESKTOP = 0,
					MINIMIZED = 0, MAXIMIZED = 0,

					SHOWN = 0, HIDDEN = 0,
					BORDERLESS = 0, RESIZABLE = 0,

					INPUT_GRABBED = 0, INPUT_FOCUS = 0,
					MOUSE_FOCUS = 0, MOUSE_CAPTURE = 0, ALLOW_HIGHDPI = 0,

					ALWAYS_ON_TOP = 0, SKIP_TASKBAR = 0,
					UTILITY = 0, TOOLTIP = 0, POPUP_MENU = 0,

					OPENGL = 0, VULKAN = 0, FOREIGN = 0;
			}
			Flag;
		};
		
		void init(const Config& cfg);
		
		//		Setter											Getter
		void WindowTitle(const char* new_title);	const char*	WindowTitle() const;
		void WindowPosition(int x, int y);			V2D<int>	WindowPosition() const;
		void WindowSize(int w, int h);				V2D<int>	WindowSize() const;
		
		operator SDL_Window*();
		
		~Window();
		
		private:
		SDL_Window* window;
	};
	
}

#endif