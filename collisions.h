// Struct representing a sphere
typedef struct sphere {
        vec3 center;
        double radius;
        material mat;
} sphere;

// Sphere functions
double ray_sphere(ray r, sphere s);
vec3 norm_sphere(ray r, double t, sphere s);
vec3 diff_sphere(vec3 normal);
sphere new_sphere(vec3 center, double radius, material mat);