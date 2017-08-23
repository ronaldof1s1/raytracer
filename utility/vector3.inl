#include "vector3.h"
namespace utility {
    //
    //=== Member function implementation.
    //
    inline void vector3::make_unit_vector( void )
    {
        /**
         * +---> unit vector.
         * |
         *
         * ^     1
         * v = _____ * v
         *     ||v||
         *
         * ||v|| = sqrt( v dot v )
         *
         *      1
         * k =_____
         *    ||v||
         */
        auto v_dot_v = e[X]*e[X] + e[Y]*e[Y] + e[Z]*e[Z] ;
        // make sure we divide by zero here.
        assert( fabs( v_dot_v - 0.f ) > 0.000001 );
        value_type k = 1.f/ sqrt( v_dot_v );
        e[X] *= k;
        e[Y] *= k;
        e[Z] *= k;
    }
    //
    //=== Non-member function implementation: operator overloading.
    //
    inline std::istream& operator>>( std::istream& is, vector3 & v )
    {
        is >> v.e[vector3::field_t::X]
            >> v.e[vector3::field_t::Y]
            >> v.e[vector3::field_t::Z];
        return is;
    }
    inline std::ostream& operator<<( std::ostream& os, const vector3 & v )
    {
        os << std::fixed << std::setprecision( 2 )
            << "{ "
            << v.e[vector3::field_t::X]
            << " "
            << v.e[vector3::field_t::Y]
            << " "
            << v.e[vector3::field_t::Z]
            << " }";
        return os;
    }

    // vectorial sum
    inline vector3 operator+( const vector3 & v1, const vector3 & v2 )
    {
        return vector3( v1.e[vector3::X] + v2.e[vector3::X],
                v1.e[vector3::Y] + v2.e[vector3::Y],
                v1.e[vector3::Z] + v2.e[vector3::Z] );
    }
    inline vector3 operator-( const vector3 & v1, const vector3 & v2 )
    {
        return vector3( v1.e[vector3::X] - v2.e[vector3::X],
                v1.e[vector3::Y] - v2.e[vector3::Y],
                v1.e[vector3::Z] - v2.e[vector3::Z] );
    }

    inline vector3 operator*( const vector3 & v1, const vector3 & v2 )
    {
        return vector3( v1.e[vector3::X] * v2.e[vector3::X],
                v1.e[vector3::Y] * v2.e[vector3::Y],
                v1.e[vector3::Z] * v2.e[vector3::Z] );
    }
    inline vector3 operator/( const vector3 & v1, const vector3 & v2 )
    {
        return vector3( v1.e[vector3::X] / v2.e[vector3::X],
                v1.e[vector3::Y] / v2.e[vector3::Y],
                v1.e[vector3::Z] / v2.e[vector3::Z] );
    }

    // Scalar Multiplication
    inline vector3 operator*( const vector3 & v, vector3::value_type t )
    {
        return vector3( v.e[vector3::X] * t,
                v.e[vector3::Y] * t,
                v.e[vector3::Z] * t );
    }
    inline vector3 operator*( vector3::value_type t, const vector3 & v )
    {
        return vector3( v.e[vector3::X] * t,
                v.e[vector3::Y] * t,
                v.e[vector3::Z] * t );
    }
    inline vector3 operator/( const vector3 & v, vector3::value_type t )
    {
        return vector3( v.e[vector3::X] / t,
                v.e[vector3::Y] / t,
                v.e[vector3::Z] / t );
    } 

    //inner (dot) product
    inline vector3::value_type dot( const vector3 & v1, const vector3 & v2 )
    {
        return v1.e[vector3::X] * v2.e[vector3::X] +
            v1.e[vector3::Y] * v2.e[vector3::Y] +
            v1.e[vector3::Z] * v2.e[vector3::Z] ;
    }

    //cross or vectorial product
    inline vector3 cross( const vector3 & v1, const vector3 & v2 )
    {
        return vector3(    v1.e[vector3::Y] * v2.e[vector3::Z] - v1.e[vector3::Z] * v2.e[vector3::Y]  ,
                -( v1.e[vector3::X] * v2.e[vector3::Z] - v1.e[vector3::Z] * v2.e[vector3::X] ),
                v1.e[vector3::X] * v2.e[vector3::Y] - v1.e[vector3::Y] * v2.e[vector3::X]    );
    }
    inline vector3& vector3::operator+=( const vector3 & v )
    {
        e[X] += v.e[X];
        e[Y] += v.e[Y];
        e[Z] += v.e[Z];
        return *this;
    }
    inline vector3& vector3::operator-=( const vector3 & v )
    {
        e[X] -= v.e[X];
        e[Y] -= v.e[Y];
        e[Z] -= v.e[Z];
        return *this;
    }
    inline vector3& vector3::operator*=( const vector3 & v )
    {
        e[X] *= v.e[X];
        e[Y] *= v.e[Y];
        e[Z] *= v.e[Z];
        return *this;
    }
    inline vector3& vector3::operator/=( const vector3 & v )
    {
        e[X] /= v.e[X];
        e[Y] /= v.e[Y];
        e[Z] /= v.e[Z];
        return *this;
    }
    inline vector3& vector3::operator*=( const value_type t )
    {
        e[X] *= t;
        e[Y] *= t;
        e[Z] *= t;
        return *this;
    }
    inline vector3& vector3::operator/=( const value_type t )
    {
        assert( fabs( t - 0.f ) > 0.000001 );
        value_type k = 1.f/t;
        e[X] *= k;
        e[Y] *= k;
        e[Z] *= k;
        return *this;
    }
    inline static vector3 unit_vector( const vector3 & v )
    {
        return v / v.length() ;
    }
} // namespace utility
