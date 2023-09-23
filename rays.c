// Functions used for rays
#include <math.h>       
#include "vectors.h"
#include "rays.h"

// Returns a new ray
ray
ray_new(vec3 origin, vec3 dir) {
        ray r_new;
        r_new.origin = origin;
        r_new.dir = dir;
        return r_new;
}

// Returns position along ray
vec3
ray_at(ray r, double t) {
        return vec_add(r.origin, vec_mult(r.dir, t));
}
