// Struct representing a sphere
typedef struct sphere {
        vec3 center;
        double radius;
        material mat;
} sphere;

// Struct represetning a rectangle
typedef struct rect {
        vec3 corner;
        vec3 edge1;
        vec3 edge2;
        material mat;
} rect;

// Struct representing a rectangular prism
typedef struct rect_prism {
        vec3 corner;       // One of the prism corners
        vec3 edge1;             // Each of the three prism edges
        vec3 edge2;
        vec3 edge3;
} rect_prism;

// Sphere functions
double ray_sphere(ray r, sphere s);
vec3 norm_sphere(ray r, double t, sphere s);
vec3 diff_sphere(vec3 normal);
sphere new_sphere(vec3 center, double radius, material mat);

// Rect functions
double ray_rect(ray r, rect p);
vec3 norm_rect(ray r, rect p);
rect new_rect(vec3 corner, vec3 edge1, vec3 edge2, material mat);