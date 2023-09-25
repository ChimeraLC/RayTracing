// This file handles ray collisions with objects
#include <math.h>   
#include <stdio.h>
#include "vectors.h"
#include "rays.h"    
#include "materials.h"
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
        if (r2 > 0) return r2;
        return r1;
}

/*
 *                     Sphere Collisions
 */

//Returns the position along the ray r that it intersects the sphere centered at center of radius radius 
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
        return (vec_dot(r.dir, norm) < 0) ? norm : vec_neg(norm);
}

// Returns a diffusion vector from a sphere
vec3
diff_sphere(vec3 normal) {
        vec3 diff = vec_rand_unit();
        return (vec_dot(normal, diff) > 0) ? diff : vec_neg(diff);
}

// Returns a new sphere object
sphere
new_sphere(vec3 center, double radius, material mat) {
        sphere s_new;
        s_new.center = center;
        s_new.radius = radius;
        s_new.mat = mat;
        return s_new;
}


/*
 *                     Rectangle Collisions
 */

// Returns the earliest position t that a ray r intersects p
double
ray_rect(ray r, rect p) {
        // Find intersection point with plane
        vec3 norm = vec_cross(p.edge1, p.edge2);
        double t = norm.x * (p.corner.x - r.origin.x) +
            norm.y * (p.corner.y - r.origin.y) +
            norm.z * (p.corner.z - r.origin.z);
        t /= norm.x * r.dir.x + norm.y * r.dir.y + norm.z * r.dir.z;
        return t;
}

// Returns the normal vector to the rect
vec3
norm_rect(ray r, rect p) {
        // Normal vector from plane
        vec3 norm = vec_unit(vec_cross(p.edge1, p.edge2));
        // Return correct direction
        norm =  (vec_dot(r.dir, norm) < 0) ? norm : vec_neg(norm);
        return norm;
}

// Returns a new rect
rect
new_rect(vec3 corner, vec3 edge1, vec3 edge2, material mat) {
        rect r_new;
        r_new.corner = corner;
        r_new.edge1 = edge1;
        r_new.edge2 = edge2;
        r_new.mat = mat;
        return r_new;
}

/*
 *                     Rectangle Prism Collisions
 */

// Returns the earliest position t that a ray r intersects p
double
ray_rect_prism(ray r, rect_prism p) {
        // Find closest corner
        vec3 closest = p.corner;
        double dist_min = vec_mag2(vec_sub(r.origin, p.corner));
        // Check 7 other possible corners
        vec3 potential;
        double dist;
        int corner; // Tracking corner position relative to actual corner
        for (int i = 1; i <= 8; i++) {
                // Find corner positibilities using bit operations
                potential = p.corner;
                if (i & 0x1) {
                        potential = vec_add(potential, p.edge1);
                }
                if ((i >> 1) & 0x1) {
                        potential = vec_add(potential, p.edge2);
                }
                if ((i >> 2) & 0x1) {
                        potential = vec_add(potential, p.edge3);
                }
                // Find distance
                dist = vec_mag2(vec_sub(r.origin, potential));
                if (dist < dist_min) {
                        dist_min = dist;
                        closest = potential;
                        corner = i;
                }
        }
        (void) corner;
        (void) closest;
        return 0;
}