#ifndef __SDL_PROJECT6__GEOMETRY_RECT_STRUCT__HEADER_FILE_
#define __SDL_PROJECT6__GEOMETRY_RECT_STRUCT__HEADER_FILE_

#include "../SDL2.hpp"
#include "V2D.hpp"

#ifdef _DEBUG
	#include <type_traits>
	#include <string>
#endif

namespace ink {
	
	// A mathematical rect struct comprised of two 2D vectors (pos & size). Can also be used as an SDL_Rect & SDL_FRect (when templated appropriately).
	template<typename T>
	class Rect
	{
		public:
		V2D<T> pos, size;
		
		T& x()	{ return pos.x;		}
		T& y()	{ return pos.y;		}
		T& w()	{ return size.x;	}
		T& h()	{ return size.y;	}
		
		// Standard constructor
		Rect(T x = 0, T y = 0, T w = 1, T h = 1):
		pos(x, y), size(w, h) {}
		
		// Standard 2D Vector constructor
		Rect(const V2D<T>& pos, const V2D<T>& size):
		pos(pos), size(size) {}
		
		// Single 2D Vector constructor
		Rect(const V2D<T>& size):
		pos(0, 0), size(size) {}
		
		// Mixed constructor
		Rect(const V2D<T>& pos, T w, T h):
		pos(pos), size(w, h) {}
		
		// Mixed constructor
		Rect(T x, T y, const V2D<T>& size):
		pos(x, y), size(size) {}
		
		// Copy constructor
		Rect(const Rect& other):
		pos(other.pos), size(other.size) {}
		
		V2D<T> UpperLeft() const
		{ return pos; }
		
		V2D<T> UpperRight() const
		{ return pos + V2D<T>(w(), 0); }
		
		V2D<T> LowerLeft() const
		{ return pos + V2D<T>(0, h()); }
		
		V2D<T> LowerRight() const
		{ return pos + size; }
		
		V2D<T> Center() const
		{ return pos + size / 2; }
		
		bool operator==(const Rect<T>& other) const
		{
			return	UpperLeft() == other.UpperLeft()
			&&		LowerRight() == other.LowerRight();
		}
		
		bool operator!=(const Rect<T>& other) const
		{ return !(*this == other); }
		
		Rect<T> operator+(const Rect<T>& other) const
		{ return Rect<T>(pos + other.pos, size + other.size); }
		
		Rect<T>& operator+=(const Rect<T>& rhs)
		{
			pos+=rhs.pos; size+=rhs.size;
			return *this;
		}
		
		Rect<T> operator-(const Rect<T>& other) const
		{ return Rect<T>(pos + other.pos, size + other.size); }
		
		Rect<T>& operator-=(const Rect<T>& rhs)
		{
			pos-=rhs.pos; size-=rhs.size;
			return *this;
		}
		
		// Returns true if there is any overlap between this rect and the other rect, edges included
		bool intersects(const Rect<T>& other) const
		{ return cmp_intersection(*this, other) || cmp_intersection(other, *this); }
		
		// Returns true if the 2D Vector falls within the boundaries of the rect, edges included
		template<typename t>
		bool intersects(const V2D<t>& vec) const
		{
			bool
				x = vec.x >= pos.x && vec.x <= pos.x + size.x,
				y = vec.y >= pos.y && vec.y <= pos.y + size.y
			;
			
			return x && y;
		}
		
		#ifdef _DEBUG
		std::string str()
		{ return '(' + std::to_string(x()) + ',' + std::to_string(y()) + ',' + std::to_string(w()) + ',' + std::to_string(h()) + ')'; }
		#endif
		
		template<typename arithmetic>
		operator Rect<arithmetic>()
		{ return { static_cast<arithmetic>(pos.x), static_cast<arithmetic>(pos.y), static_cast<arithmetic>(size.x), static_cast<arithmetic>(size.y) }; }
		
		operator SDL_Rect()
		{ return { static_cast<int>(pos.x), static_cast<int>(pos.y), static_cast<int>(size.x), static_cast<int>(size.y) }; }
		
		operator SDL_FRect()
		{ return { static_cast<float>(pos.x), static_cast<float>(pos.y), static_cast<float>(size.x), static_cast<float>(size.y) }; }
		
		operator const SDL_Rect*() const
		{
			#ifdef _DEBUG
				static_assert( std::is_same<int, T>::value , "Rect must be templated with type int to convert implicitly to SDL_Rect.\n" );
			#endif
			return static_cast<const SDL_Rect*>(static_cast<const void*>(this));
		}
		
		operator const SDL_FRect*() const
		{
			#ifdef _DEBUG
				static_assert( std::is_same<float, T>::value , "Rect must be templated with type float to convert implicitly to SDL_FRect.\n" );
			#endif
			return static_cast<const SDL_FRect*>(static_cast<const void*>(this));
		}
		
		private:
		static bool cmp_intersection(const Rect<int>& r1, const Rect<int>& r2) {
			bool
				xoIntersect = r1.pos.x >= r2.pos.x && r1.pos.x <= r2.pos.x + r2.size.x,
				xeIntersect = r1.pos.x + r1.size.x >= r2.pos.x && r1.pos.x + r1.size.x <= r2.pos.x + r2.size.x,
				yoIntersect = r1.pos.y >= r2.pos.y && r1.pos.y <= r2.pos.y + r2.size.y,
				yeIntersect = r1.pos.y + r1.size.y >= r2.pos.y && r1.pos.y + r1.size.y <= r2.pos.y + r2.size.y
			;
			
			bool
				borderIntersect = (xoIntersect || xeIntersect ) && ( yoIntersect || yeIntersect),
				crossIntersect1 = r1.pos.x <= r2.pos.x && r1.pos.x + r1.size.x >= r2.pos.x + r2.size.x && (yoIntersect || yeIntersect),
				crossIntersect2 = r1.pos.y <= r2.pos.y && r1.pos.y + r1.size.y >= r2.pos.y + r2.size.y && (xoIntersect || xeIntersect)
			; 
			
			return borderIntersect || crossIntersect1 || crossIntersect2;
		};
		
	};
	
}

#endif