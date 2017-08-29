#ifndef _RAY_H_
#define _RAY_H_
#include "vector3.h" // necessário para acessar vector3
using namespace utility;
class Ray {
    private:
        point3 O; // the origin of the ray.
        vector3 D; // The ray's direction.
    public: 

        //=== Alias
        typedef float real_type;

        //=== Constructor
        Ray( point3 o_=point3(), vector3 d_=vector3() )
            : O( o_ )
            , D( d_ )
        { /* empty */ }

        //=== Getters
        inline vector3 get_direction( void ) const { return D; }
        inline point3 get_origin( void ) const { return O; }

        //Get a point3 for the point given an "instant" t_
        point3 point_at( real_type t_ )  const
        {
            return O + t_ * D; // parametric equation of the ray.
        }
};
#endif
