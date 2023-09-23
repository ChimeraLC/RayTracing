// This file contains information on all of the different materials
#include "vectors.h"
#include "rays.h"
#include "materials.h"
#include "collisions.h"
// Create a basic material
// Lambertian reflection
vec3
diff_lamb(ray r, vec3 norm) {
        (void) r;       // R is unused for this diffusion
        vec3 diff = vec_add(norm, vec_rand_unit());     // Select outwards vector
        // Prevent zero vectors
        if (vec_mag(diff) < 0.001) {
                return norm;
        }
        return diff;
}

// Metallic reflection
vec3
diff_metal(ray r, vec3 norm) {
        // Calculate reflection
        vec3 diff = r.dir;
        vec3 proj = vec_mult(norm, 2 * vec_dot(r.dir, norm));
        diff = vec_sub(diff, proj);
        return diff;
}

// Create a basic lambertian mateiral
material
mat_basic(double refl) {
        material m_new;
        m_new.refl = refl;
        m_new.diff = diff_lamb;
        return m_new;
}

// Create matalic material
material
mat_metal(double refl) {
        material m_new;
        m_new.refl = refl;
        m_new.diff = diff_metal;
        return m_new;
}
