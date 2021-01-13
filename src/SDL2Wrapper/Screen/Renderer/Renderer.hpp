#ifndef __INK__SDL2_RENDERER_WRAPPER_STRUCT__HEADER_FILE_
#define __INK__SDL2_RENDERER_WRAPPER_STRUCT__HEADER_FILE_

#include "../../Geometry/Geometry.hpp"
#include "../../SDL2.hpp"
#include "../Color.hpp"

namespace ink {
	
	// Can be passed as an SDL_Renderer*, and includes functionality wrapping the usage of SDL_Renderer* into OO Design.
	struct Renderer
	{
		// Configuration struct for renderer on initialization
		struct Config
		{
			int driver_index = -1;
			struct {
				bool
					ACCELERATED = 0,
					PRESENTVSYNC = 0,
					SOFTWARE = 0,
					TARGETTEXTURE = 0;
			}
			Flag;
		};
		
		void init(SDL_Window* window, const Config& cfg);
				
		SDL_Texture
		*CreateTexture(const char* image_path),
		*CreateTexture(SDL_Surface* surface),
		*CreateTexture(Uint32 format, int access, int w, int h);
		
		template<typename _arith> struct DrawSheet {
			ink::Rect<int> src;
			ink::Rect<_arith> dst;
			ink::V2D<_arith> center; double rotation;
			SDL_RendererFlip flip;
			DrawSheet(ink::Rect<_arith> dst = ink::Rect<int>(), ink::Rect<int> src = ink::Rect<int>(), double rotation = 0.0, ink::V2D<_arith> center = {0,0}, SDL_RendererFlip flip = SDL_FLIP_NONE):
			src(src), dst(dst), center(center), rotation(rotation), flip(flip) {}
		};
		
		void
		// Draw using a drawSheet
		DrawTexture(SDL_Texture *texture, DrawSheet<int> drawSheet),
		// Draw using a (floating point) drawSheet
		DrawTexture(SDL_Texture *texture, DrawSheet<float> drawSheet),
		// Draw entire source image, to destination
		DrawTexture(SDL_Texture *texture, Rect<int> dst),
		// Draw entire source image, to (floating point) destination
		DrawTexture(SDL_Texture *texture, Rect<float> dst),
		// Draw from selected source to destination
		DrawTexture(SDL_Texture *texture, Rect<int> dst, Rect<int> src),
		// Draw from selected source to (floating point) destination
		DrawTexture(SDL_Texture *texture, Rect<float> dst, Rect<int> src),
		// Draw entire source image to destination, specifying rotation and flip
		DrawTexture(SDL_Texture *texture, Rect<int> dst, double rotation, V2D<int> center = {0,0}, SDL_RendererFlip flip = SDL_FLIP_NONE),
		// Draw entire source image to (floating point) destination, specifying rotation and flip
		DrawTexture(SDL_Texture *texture, Rect<float> dst, double rotation, V2D<float> center = {0,0}, SDL_RendererFlip flip = SDL_FLIP_NONE),
		// Draw from selected source to destination, specifying rotation and flip
		DrawTexture(SDL_Texture *texture, Rect<int> dst, Rect<int> src, double rotation, V2D<int> center = {0,0}, SDL_RendererFlip flip = SDL_FLIP_NONE),
		// Draw from selected source to (floating point) destination, specifying rotation and flip
		DrawTexture(SDL_Texture *texture, Rect<float> dst, Rect<int> src, double rotation, V2D<float> center = {0,0}, SDL_RendererFlip flip = SDL_FLIP_NONE);
		
		void
		DrawRect(Rect<int> rect) const,
		DrawRect(Rect<int> rect, bool fill),
		DrawRect(Rect<float> rect) const,
		DrawRect(Rect<float> rect, bool fill),
		DrawRect(const Rect<int>* rectArray, int rectCount),
		DrawRect(const Rect<int>* rectArray, int rectCount, bool fill),
		DrawRect(const Rect<float>* rectArray, int rectCount),
		DrawRect(const Rect<float>* rectArray, int rectCount, bool fill);
		
		void
		DrawLine(int x1, int y1, int x2, int y2),
		DrawLine(float x1, float y1, float x2, float y2),
		DrawLine(V2D<int> pos1, V2D<int> pos2),
		DrawLine(V2D<float> pos1, V2D<float> pos2),
		DrawLine(const V2D<int>* positionsArray, int positionsCount),
		DrawLine(const V2D<float>* positionsArray, int positionsCount);
		
		void
		DrawPoint(int x, int y),
		DrawPoint(float x, float y),
		DrawPoint(V2D<int> point),
		DrawPoint(V2D<float> point),
		DrawPoint(const V2D<int>* pointArray, int pointCount),
		DrawPoint(const V2D<float>* pointArray, int pointCount);
		
		void
		SetDrawTarget(SDL_Texture* texture),
		SetDrawBlendMode(SDL_BlendMode blendMode),
		SetDrawColor(const Color& clr),
		SetDrawColor(Uint32 R, Uint32 G, Uint32 B, Uint32 A);
		
		void
		RenderPresent(),
		Clear();
		
		operator SDL_Renderer*();
		
		~Renderer();
		
		private:
		SDL_Renderer* renderer;
	};
	
}

#endif