

typedef struct material {
        double refl;            // Reflectivity
        vec3 (*diff) (ray r, vec3 norm);        // Diffusion equation
} material;

// Functions to produce each material
material mat_basic(double refl);
material mat_metal(double refl);