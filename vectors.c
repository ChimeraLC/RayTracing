// This file contains functions for 3 dimensional vectors

#include <math.h>
#include <stdlib.h>
#include "vectors.h"

// Creates a new vector with the given values
vec3
vec_new(double x, double y, double z) {
        vec3 v_new;
        v_new.x = x;
        v_new.y = y;
        v_new.z = z;
        return v_new;
}

// Creates copy of a given vector
vec3
vec_copy(vec3 v) {
        vec3 v_new;
        v_new.x = v.x;
        v_new.y = v.y;
        v_new.z = v.z;
        return v_new;
}

// Produces a random vector with values between min and max
vec3
vec_rand(double min, double max) {
        return vec_new((double) rand() / RAND_MAX * (max - min) + min,
        (double) rand() / RAND_MAX * (max - min) + min,
        (double) rand() / RAND_MAX * (max - min) + min);
}

// Produces a random vector on the unit circle
vec3
vec_rand_unit() {
        // Repeat until sucess
        while (1 == 1) {
                vec3 potential = vec_rand(-1, 1);
                if (vec_mag(potential) < 1) {
                        return vec_unit(potential);
                }
        }
}

// Returns -v
vec3
vec_neg(vec3 v) {
        vec3 v_new;
        v_new.x = -v.x;
        v_new.y = -v.y;
        v_new.z = -v.z;
        return v_new;
}

// Returns v1 + v2
vec3
vec_add(vec3 v1, vec3 v2) {
        vec3 v_new;
        v_new.x = v1.x + v2.x;
        v_new.y = v1.y + v2.y;
        v_new.z = v1.z + v2.z;
        return v_new;
}

// Returns v1 - v2
vec3
vec_sub(vec3 v1, vec3 v2) {
        vec3 v_new;
        v_new.x = v1.x - v2.x;
        v_new.y = v1.y - v2.y;
        v_new.z = v1.z - v2.z;
        return v_new;
}

// returns v * c
vec3
vec_mult(vec3 v, double c) {
        vec3 v_new;
        v_new.x = v.x * c;
        v_new.y = v.y * c;
        v_new.z = v.z * c;
        return v_new;
}

// returns pairwise multiplication vector
vec3
vec_multv(vec3 v1, vec3 v2) {
        vec3 v_new;
        v_new.x = v1.x * v2.x;
        v_new.y = v1.y * v2.y;
        v_new.z = v1.z * v2.z;
        return v_new;
}
// returns v * c
vec3
vec_div(vec3 v, double c) {
        vec3 v_new;
        v_new.x = v.x / c;
        v_new.y = v.y / c;
        v_new.z = v.z / c;
        return v_new;
}

// returns magnitude squared
double
vec_mag2(vec3 v) {
        double ret = 0;
        ret += v.x * v.x;
        ret += v.y * v.y;
        ret += v.z * v.z;
        return ret;
}

// returns magnitude
double
vec_mag(vec3 v) {
        return sqrt(vec_mag2(v));
}

// returns unit vector
vec3
vec_unit(vec3 v) {
        return vec_div(v, vec_mag(v));
}

// returns dot product of v1 and v2
double
vec_dot(vec3 v1, vec3 v2) {
        double ret = 0;
        ret += v1.x * v2.x;
        ret += v1.y * v2.y;
        ret += v1.z * v2.z;
        return ret;
}

// returns cross product of v1 and v2
vec3
vec_cross(vec3 v1, vec3 v2) {
        vec3 v_new;
        v_new.x = v1.y * v2.z - v1.z * v2.y;
        v_new.y = v1.z * v2.x - v1.x * v2.z;
        v_new.z = v1.x * v2.y - v1.y * v2.x;
        return v_new;
}