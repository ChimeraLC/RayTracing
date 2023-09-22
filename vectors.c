// This file contains functions for 3 dimensional vectors

#include <math.h>
#include "vectors.h"
// Creates a new vector with the given values
vec3
vec_new(double x, double y, double z) {
        vec3 v_new;
        v_new.e[0] = x;
        v_new.e[1] = y;
        v_new.e[2] = z;
        return v_new;
}

// Returns -v
vec3
vec_neg(vec3 v) {
        vec3 v_new;
        v_new.e[0] = -v.e[0];
        v_new.e[1] = -v.e[1];
        v_new.e[2] = -v.e[2];
        return v_new;
}

// Returns v1 + v2
vec3
vec_add(vec3 v1, vec3 v2) {
        vec3 v_new;
        v_new.e[0] = v1.e[0] + v2.e[0];
        v_new.e[1] = v1.e[1] + v2.e[1];
        v_new.e[2] = v1.e[2] + v2.e[2];
        return v_new;
}

// Returns v1 - v2
vec3
vec_sub(vec3 v1, vec3 v2) {
        vec3 v_new;
        v_new.e[0] = v1.e[0] - v2.e[0];
        v_new.e[1] = v1.e[1] - v2.e[1];
        v_new.e[2] = v1.e[2] - v2.e[2];
        return v_new;
}

// returns v * c
vec3
vec_mult(vec3 v, double c) {
        vec3 v_new;
        v_new.e[0] = v.e[0] * c;
        v_new.e[1] = v.e[1] * c;
        v_new.e[2] = v.e[2] * c;
        return v_new;
}

// returns pairwise multiplication vector
vec3
vec_multv(vec3 v1, vec3 v2) {
        vec3 v_new;
        v_new.e[0] = v1.e[0] * v2.e[0];
        v_new.e[1] = v1.e[1] * v2.e[1];
        v_new.e[2] = v1.e[2] * v2.e[2];
        return v_new;
}
// returns v * c
vec3
vec_div(vec3 v, double c) {
        vec3 v_new;
        v_new.e[0] = v.e[0] / c;
        v_new.e[1] = v.e[1] / c;
        v_new.e[2] = v.e[2] / c;
        return v_new;
}

// returns magnitude squared
double
vec_mag2(vec3 v) {
        double ret = 0;
        ret += v.e[0] * v.e[0];
        ret += v.e[1] * v.e[1];
        ret += v.e[2] * v.e[2];
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
        ret += v1.e[0] * v2.e[0];
        ret += v1.e[1] * v2.e[1];
        ret += v1.e[2] * v2.e[2];
        return ret;
}

// returns cross product of v1 and v2
vec3
vec_cross(vec3 v1, vec3 v2) {
        vec3 v_new;
        v_new.e[0] = v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1];
        v_new.e[1] = v1.e[2] * v2.e[0] - v1.e[0] * v2.e[2];
        v_new.e[2] = v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0];
        return v_new;
}