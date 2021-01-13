#ifndef __SDL__SCREEN_STRUCT__HEADER_FILE_
#define __SDL__SCREEN_STRUCT__HEADER_FILE_

#include "Window/Window.hpp"
#include "Renderer/Renderer.hpp"

namespace ink {
	
	struct Screen:
	public Window,
	public Renderer
	{
		
		void init(const Window::Config& wCfg, const Renderer::Config& rCfg)
		{
			this->Window::init(wCfg);
			this->Renderer::init(*this, rCfg);
		}
		
		Screen() {}
		~Screen()
		{
			this->Window::~Window();
			this->Renderer::~Renderer();
		}
	};
	
}

#endif