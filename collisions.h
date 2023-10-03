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
        material mat;
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

// Sphere functionsrect_prism
double ray_rect_prism(ray r, rect_prism p);
vec3 norm_rect_prism(ray r, rect_prism p, double t);
rect_prism new_rect_prism(vec3 corner, vec3 edge1, vec3 edge2, vec3 edge3, material mat);