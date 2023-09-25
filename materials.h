

typedef struct material {
        double refl;            // Reflectivity
        vec3 (*diff) (ray r, vec3 norm);        // Diffusion equation
        double add;             // Used differently for different materials
} material;

// Functions to produce each material
material mat_basic(double refl);
material mat_metal(double refl);