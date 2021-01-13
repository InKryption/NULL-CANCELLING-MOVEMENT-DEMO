#ifndef __INK__SDL2_COLOR_STRUCT_WRAPPER__HEADER_FILE_
#define __INK__SDL2_COLOR_STRUCT_WRAPPER__HEADER_FILE_

#include "../SDL2.hpp"

namespace ink {
		
	class Color:
	public SDL_Color
	{
		public:
		operator SDL_Color()	{ return *this; }
		operator SDL_Color*()	{ return this; }
		
		Color(Uint8 R = 0, Uint8 G = 0, Uint8 B = 0, Uint8 A = 255):
		SDL_Color{R, G, B, A} {}
		
		Color(const SDL_Color& clr):
		SDL_Color{clr.r, clr.g, clr.b, clr.a} {}
		
		Color& operator+=(const Color& other)
		{ r+=other.r; g+=other.g; b+=other.b; a+=other.a; return *this; }
		
		Color operator+(const Color& other) const
		{ return Color(*this) += other; }
		
		Color& operator-=(const Color& other)
		{ r-=other.r; g-=other.g; b-=other.b; a-=other.a; return *this; }
		
		Color operator-(const Color& other) const
		{ return Color(*this) -= other; }
		
		bool operator==(const Color& other) const
		{ return r == other.r && g == other.g && b == other.b && a == other.a; }
		
		bool operator!=(const Color& other) const
		{ return !(*this == other); }
		
		Color operator*(Uint8 rhs) const
		{ return Color(r*rhs,g*rhs,b*rhs,a*rhs); }
		
		Color operator/(Uint8 rhs) const
		{ return Color(r/rhs, g/rhs, b/rhs, a/rhs); }
		
		#ifdef _DEBUG
			// Returns the color in string form in the format "(R,G,B,A)"
			std::string str()
			{ return '(' + std::to_string(r) + ',' + std::to_string(g) + ',' + std::to_string(b) + ',' + std::to_string(a) + ')'; }
		#endif
		
	};
	
}

#endif