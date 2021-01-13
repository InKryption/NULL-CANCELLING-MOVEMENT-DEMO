#ifndef __INK_2D_VECTOR_STRUCT__HEADER_FILE_
#define __INK_2D_VECTOR_STRUCT__HEADER_FILE_

#include "../SDL2.hpp"
#include <math.h>

#ifdef _DEBUG
	#include <type_traits>
	#include <string>
#endif

namespace ink {
	
	// A mathematical 2D Vector type. Can also be used in place of SDL_Point & SDL_FPoint (when templated appropriately).
	template<typename T>
	class V2D
	{
		public:
		T x, y;
		
		// Magnitude cubed
		T mag_squared() const { return x * x + y * y; }
		
		// Linear Magnitude of the vector
		T magnitude() const { return static_cast<T>( std::sqrt(mag_squared()) ); }
		
		// Returns the scalar result of the multiplication between this vector and the other vector 
		T dot(const V2D& other) const { return x * other.x + y * other.y; }
		
		// Returns magnitude of the vector perpendicular to this vector and the other vector
		T cross(const V2D& other) const { return x * other.y - y * other.x; }
		
		// Returns perpendicular vector
		V2D cross() const { return V2D(y, -x); }
		
		V2D(T x = T(0), T y = T(0)): x(x), y(y) {}
		V2D(const V2D& other): x(other.x), y(other.y) {}
		V2D& operator=(const V2D& other) = default;
		
		V2D operator+(const V2D& other) const			{ 	return V2D( x + other.x, y + other.y );			}
		V2D& operator+=(const V2D& other)				{ 	x += other.x; y += other.y; return *this;		}
		
		V2D operator-(const V2D& other) const			{ 	return V2D( x - other.x, y - other.y );			}
		V2D& operator-=(const V2D& other)				{ 	x -= other.x; y -= other.y; return *this;		}
		
		V2D operator*(const T& rhs) const				{ 	return V2D( x * rhs, y * rhs );					}
		V2D& operator*=(const T& rhs)					{ 	x *= rhs; y *= rhs; return *this;				}
		
		V2D operator*(const V2D& other) const			{ 	return V2D( x * other.x, y * other.y );			}
		V2D& operator*=(const V2D& other)				{ 	x *= other.x; y *= other.y; return *this;		}
		
		V2D operator/(const T& rhs) const				{ 	return V2D<T>( x / rhs, y / rhs );				}
		V2D& operator/=(const T& rhs)					{ 	x /= rhs; y /= rhs; return *this;			}
		
		V2D operator/(const V2D& other) const			{ 	return V2D( x / other.x, y / other.y );			}
		V2D& operator/=(const V2D& other)				{ 	x /= other.x; y /= other.y; return *this;		}
		
		bool operator==(const V2D& other) const			{ 	return x == other.x && y == other.y;			}
		bool operator!=(const V2D& other) const			{ 	return x != other.x || y != other.y;			}
		
		template<typename t>
		V2D<t> as_V2D() const
		{
			return { static_cast<t>(x), static_cast<t>(y) };
		}
		
		operator SDL_Point() const
		{
			return { static_cast<int>(x), static_cast<int>(y) };
		}
		
		operator SDL_FPoint() const
		{
			return { static_cast<float>(x), static_cast<float>(y) };
		}
		
		operator const SDL_Point*() const
		{
			#ifdef _DEBUG
				static_assert( std::is_same<int, T>::value , "V2D must be templated with type int to convert implicitly to SDL_Point.\n" );
			#endif
			return static_cast<const SDL_Point*>( static_cast<const void*>(this) );
		}
		
		operator const SDL_FPoint*() const
		{
			#ifdef _DEBUG
				static_assert( std::is_same<float, T>::value , "V2D must be templated with type float to convert implicitly to SDL_FPoint.\n" );
			#endif
			return static_cast<const SDL_FPoint*>( static_cast<const void*>(this) );
		}
		
		#ifdef _DEBUG
		std::string str()
		{
			return '(' + std::to_string(x) + ',' + std::to_string(y) + ')';
		}
		#endif
	};
	
}

template<typename T, typename t>
inline ink::V2D<T> operator*(const t& lhs, const ink::V2D<T>& rhs)
{
	return ink::V2D<T>( static_cast<T>(lhs * rhs.x), static_cast<T>(lhs * rhs.y) );
}

template<typename T, typename t>
inline ink::V2D<T> operator/(const t& lhs, const ink::V2D<T>& rhs)
{
	return ink::V2D<T>( static_cast<T>(lhs / rhs.x), static_cast<T>(lhs / rhs.y) );
}



#endif