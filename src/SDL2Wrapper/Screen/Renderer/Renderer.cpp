#include "Renderer.hpp"

namespace ink {
	
	void Renderer::
	init(SDL_Window* window, const Config& rend_config)
	{
		
		Uint32 rend_flags
		= rend_config.Flag.ACCELERATED		* SDL_RENDERER_ACCELERATED
		| rend_config.Flag.PRESENTVSYNC		* SDL_RENDERER_PRESENTVSYNC
		| rend_config.Flag.SOFTWARE			* SDL_RENDERER_PRESENTVSYNC
		| rend_config.Flag.TARGETTEXTURE	* SDL_RENDERER_TARGETTEXTURE
		;
		
		renderer = SDL_CreateRenderer(window, rend_config.driver_index, rend_flags);
		
		#ifdef _DEBUG
		if (!renderer) printf("Problem creating renderer. Error Message: '%s'\n", SDL_GetError());
		#endif
	}
	
	
	
	SDL_Texture* Renderer::
	CreateTexture(const char* image_path)
	{ return IMG_LoadTexture(renderer, image_path); }
	
	SDL_Texture* Renderer::
	CreateTexture(SDL_Surface* surface)
	{ return SDL_CreateTextureFromSurface(renderer, surface); }
	
	SDL_Texture* Renderer::
	CreateTexture(Uint32 format, int access, int w, int h)
	{ return SDL_CreateTexture(renderer, format, access, w, h); }
	
	
	
	void Renderer::
	SetDrawTarget(SDL_Texture* texture)
	{ SDL_SetRenderTarget(renderer, texture); }
	
	void Renderer::
	SetDrawBlendMode(SDL_BlendMode blendMode)
	{ SDL_SetRenderDrawBlendMode(renderer, blendMode); }
	
	void Renderer::
	SetDrawColor(Uint32 R, Uint32 G, Uint32 B, Uint32 A)
	{ SDL_SetRenderDrawColor(renderer, R, G, B, A); }
	
	void Renderer::
	SetDrawColor(const Color& clr)
	{ SDL_SetRenderDrawColor(renderer, clr.r, clr.g, clr.b, clr.a); }
	
	void Renderer::
	Clear() { SDL_RenderClear(renderer); }
	
	
	
	
	void Renderer::
	DrawTexture(SDL_Texture* texture, DrawSheet<int> drawSheet)
	{ SDL_RenderCopyEx(renderer, texture, drawSheet.src, drawSheet.dst, drawSheet.rotation, drawSheet.center, drawSheet.flip); }
	
	void Renderer::
	DrawTexture(SDL_Texture* texture, DrawSheet<float> drawSheet)
	{ SDL_RenderCopyExF(renderer, texture, drawSheet.src, drawSheet.dst, drawSheet.rotation, drawSheet.center, drawSheet.flip); }
	
	void Renderer::
	DrawTexture(SDL_Texture *texture, Rect<int> dst)
	{ SDL_RenderCopy(renderer, texture, NULL, dst); }
	
	void Renderer::
	DrawTexture(SDL_Texture *texture, Rect<float> dst)
	{ SDL_RenderCopyF(renderer, texture, NULL, dst); }
	
	void Renderer::
	DrawTexture(SDL_Texture* texture, Rect<int> dst, Rect<int> src)
	{ SDL_RenderCopy(renderer, texture, src, dst); }
	
	void Renderer::
	DrawTexture(SDL_Texture *texture, Rect<float> dst, Rect<int> src)
	{ SDL_RenderCopyF(renderer, texture, src, dst); }
	
	void Renderer::
	DrawTexture(SDL_Texture *texture, Rect<int> dst, double rotation, V2D<int> center, SDL_RendererFlip flip)
	{ SDL_RenderCopyEx(renderer, texture, NULL, dst, rotation, center, flip); }
	
	void Renderer::
	DrawTexture(SDL_Texture *texture, Rect<float> dst, double rotation, V2D<float> center, SDL_RendererFlip flip)
	{ SDL_RenderCopyExF(renderer, texture, NULL, dst, rotation, center, flip); }
	
	void Renderer::
	DrawTexture(SDL_Texture *texture, Rect<int> dst, Rect<int> src, double rotation, V2D<int> center, SDL_RendererFlip flip)
	{ SDL_RenderCopyEx(renderer, texture, src, dst, rotation, center, flip); }
	
	void Renderer::
	DrawTexture(SDL_Texture *texture, Rect<float> dst, Rect<int> src, double rotation, V2D<float> center, SDL_RendererFlip flip)
	{ SDL_RenderCopyExF(renderer, texture, src, dst, rotation, center, flip); }
	
	
	
	void Renderer::
	DrawRect(Rect<int> rect) const { SDL_RenderDrawRect(renderer, rect); }
	
	void Renderer::
	DrawRect(Rect<float> rect) const { SDL_RenderDrawRectF(renderer, rect); }
	
	void Renderer::
	DrawRect(const Rect<int>* rectArray, int rectCount)
	{ SDL_RenderDrawRects(renderer, static_cast<const SDL_Rect*>(static_cast<const void*>(rectArray)), rectCount); }
	
	void Renderer::
	DrawRect(const Rect<float>* rectArray, int rectCount)
	{ SDL_RenderDrawRectsF(renderer, static_cast<const SDL_FRect*>(static_cast<const void*>(rectArray)), rectCount); }
	
	
	
	void Renderer::
	DrawRect(Rect<int> rect, bool fill)
	{ SDL_RenderFillRect(renderer, rect); }
	
	void Renderer::
	DrawRect(Rect<float> rect, bool)
	{ SDL_RenderFillRectF(renderer, rect); }
	
	void Renderer::
	DrawRect(const Rect<int>* rectArray, int rectCount, bool fill)
	{ SDL_RenderFillRects(renderer, static_cast<const SDL_Rect*>(static_cast<const void*>(rectArray)), rectCount); }
	
	void Renderer::
	DrawRect(const Rect<float>* rectArray, int rectCount, bool fill)
	{ SDL_RenderFillRectsF(renderer, static_cast<const SDL_FRect*>(static_cast<const void*>(rectArray)), rectCount); }
	
	
	
	void Renderer::
	DrawLine(int x1, int y1, int x2, int y2)
	{ SDL_RenderDrawLine(renderer, x1, y1, x2, y2); }
	
	void Renderer::
	DrawLine(float x1, float y1, float x2, float y2)
	{ SDL_RenderDrawLineF(renderer, x1, y1, x2, y2); }
	
	void Renderer::
	DrawLine(V2D<int> pos1, V2D<int> pos2)
	{ SDL_RenderDrawLine(renderer, pos1.x, pos1.y, pos2.x, pos2.y); }
	
	void Renderer::
	DrawLine(V2D<float> pos1, V2D<float> pos2)
	{ SDL_RenderDrawLine(renderer, pos1.x, pos1.y, pos2.x, pos2.y); }
	
	void Renderer::
	DrawLine(const V2D<int>* positionsArray, int positionsCount) 
	{ SDL_RenderDrawLines(renderer, static_cast<const SDL_Point*>(static_cast<const void*>(positionsArray)), positionsCount); }
	
	void Renderer::
	DrawLine(const V2D<float>* positionsArray, int positionsCount)
	{ SDL_RenderDrawLinesF(renderer, static_cast<const SDL_FPoint*>(static_cast<const void*>(positionsArray)), positionsCount); }
	
	
	
	void Renderer::
	DrawPoint(int x, int y)
	{ SDL_RenderDrawPoint(renderer, x, y); }
	
	void Renderer::
	DrawPoint(float x, float y)
	{ SDL_RenderDrawPointF(renderer, x, y); }
	
	void Renderer::
	DrawPoint(V2D<int> point)
	{ SDL_RenderDrawPoint(renderer, point.x, point.y); }
	
	void Renderer::
	DrawPoint(V2D<float> point)
	{ SDL_RenderDrawPointF(renderer, point.x, point.y); }
	
	void Renderer::
	DrawPoint(const V2D<int>* pointArray, int pointCount)
	{ SDL_RenderDrawPoints(renderer, static_cast<const SDL_Point*>(static_cast<const void*>(pointArray)), pointCount); }
	
	void Renderer::
	DrawPoint(const V2D<float>* pointArray, int pointCount)
	{ SDL_RenderDrawPointsF(renderer, static_cast<const SDL_FPoint*>(static_cast<const void*>(pointArray)), pointCount); }
	
	
	
	void Renderer::
	RenderPresent() { SDL_RenderPresent(renderer); }
	
	Renderer::
	operator SDL_Renderer*() { return renderer; }
	
	
	Renderer::~Renderer()
	{ SDL_DestroyRenderer(renderer); }
	
}