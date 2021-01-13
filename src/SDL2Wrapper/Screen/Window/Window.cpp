#include "Window.hpp"

namespace ink {
	
	void Window::
	init(const Window::Config& cfg)
	{
		Uint32 win_flags
		= cfg.Flag.ALLOW_HIGHDPI		* SDL_WINDOW_ALLOW_HIGHDPI
		| cfg.Flag.ALWAYS_ON_TOP		* SDL_WINDOW_ALWAYS_ON_TOP
		| cfg.Flag.BORDERLESS			* SDL_WINDOW_BORDERLESS
		| cfg.Flag.FOREIGN				* SDL_WINDOW_FOREIGN
		| cfg.Flag.FULLSCREEN			* SDL_WINDOW_FULLSCREEN
		| cfg.Flag.FULLSCREEN_DESKTOP	* SDL_WINDOW_FULLSCREEN_DESKTOP
		| cfg.Flag.HIDDEN				* SDL_WINDOW_HIDDEN
		| cfg.Flag.INPUT_FOCUS			* SDL_WINDOW_INPUT_FOCUS
		| cfg.Flag.INPUT_GRABBED		* SDL_WINDOW_INPUT_GRABBED
		| cfg.Flag.MAXIMIZED			* SDL_WINDOW_MAXIMIZED
		| cfg.Flag.MINIMIZED			* SDL_WINDOW_MINIMIZED
		| cfg.Flag.MOUSE_CAPTURE		* SDL_WINDOW_MOUSE_CAPTURE
		| cfg.Flag.MOUSE_FOCUS			* SDL_WINDOW_MOUSE_FOCUS
		| cfg.Flag.OPENGL				* SDL_WINDOW_OPENGL
		| cfg.Flag.POPUP_MENU			* SDL_WINDOW_POPUP_MENU
		| cfg.Flag.RESIZABLE			* SDL_WINDOW_RESIZABLE
		| cfg.Flag.SHOWN				* SDL_WINDOW_SHOWN
		| cfg.Flag.SKIP_TASKBAR			* SDL_WINDOW_SKIP_TASKBAR
		| cfg.Flag.TOOLTIP				* SDL_WINDOW_TOOLTIP
		| cfg.Flag.UTILITY				* SDL_WINDOW_UTILITY
		| cfg.Flag.VULKAN				* SDL_WINDOW_VULKAN
		;
		
		
		SDL_DisplayMode _display_mode;
		SDL_GetCurrentDisplayMode(0, &_display_mode);
		window = SDL_CreateWindow(cfg.title, cfg.x, cfg.y,  cfg.width_percentage * _display_mode.w / 100, cfg.height_percentage * _display_mode.h / 100, win_flags);
		
		#ifdef _DEBUG
		if (!window) printf("Problem creating window. Error Message: '%s'\n", SDL_GetError());
		#endif
		
	}
	
	V2D<int> Window::
	WindowSize() const
	{
		V2D<int> out;
		SDL_GetWindowSize(window, &out.x, &out.y);
		return out;
	}
	
	V2D<int> Window::
	WindowPosition() const
	{
		V2D<int> out;
		SDL_GetWindowPosition(window, &out.x, &out.y);
		return out;
	}
	
	const char* Window::
	WindowTitle() const
	{ return SDL_GetWindowTitle(window); }
	
	void Window::
	WindowSize(int w, int h)
	{ SDL_SetWindowSize(window, w, h); }
	
	void Window::
	WindowPosition(int x, int y)
	{ SDL_SetWindowPosition(window, x, y); }
	
	void Window::
	WindowTitle(const char* new_title)
	{ SDL_SetWindowTitle(window, new_title); }
	
	Window::
	operator SDL_Window*()
	{ return window; }
	
	Window::
	~Window()
	{ SDL_DestroyWindow(window); }
	
}