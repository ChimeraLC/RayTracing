// This file handles ray collisions with objects
#include <math.h>       
#include "vectors.h"
#include "rays.h"
#include "collisions.h"

/*
Solves the quadratic equation with the given values, returning the smallest nonegative answer
Assumes a, b, c are valid coefficients
*/
double
solve(double a, double b, double c) {
        // Calculate discriminant
        double disc = b * b - 4 * a * c;
        if (disc < 0) {
                return -1;
        }
        // Solve for two roots
        double r1, r2;
        r1 = (-b + sqrt(disc)) / (2 * a);
        r2 = (-b - sqrt(disc)) / (2 * a);
        // Return smallest nonzero
        if (r1 > r2) return r1;
        return r2;
}

/*
Returns the position along the ray r that it intersects the sphere centered at center of radius radius
*/ 
double
ray_sphere(ray r, sphere s) {
        // Find analytic values to solve
        vec3 dist = vec_sub(r.origin, s.center);
        double a = vec_dot(r.dir, r.dir);
        double b = 2 * vec_dot(r.dir, dist);
        double c = vec_dot(dist, dist) - s.radius * s.radius;
        if (b * b - 4 * a * c < 0) {
                return -1;
        }
        return solve(a, b, c);
}

// Returns normal vector of ray r intersecting shape at t
vec3
norm_sphere(ray r, double t, sphere s) {
        // Get normal vector
        vec3 norm = vec_unit(vec_sub(ray_at(r, t), s.center));
        // Get direction of vector
        //return (vec_dot(r.dir, norm) < 0) ? norm : vec_neg(norm);
        return norm;
}

// Returns a diffusion vector from a sphere
vec3
diff_sphere(vec3 normal) {
        vec3 diff = vec_rand_unit();
        return (vec_dot(normal, diff) > 0) ? diff : vec_neg(diff);
}

// Returns a new sphere object
sphere
new_sphere(vec3 center, double radius) {
        sphere s_new;
        s_new.center = center;
        s_new.radius = radius;
        return s_new;
}
