// Shared structure definition
typedef struct vec3 {
        double e[3];
} vec3;

// Vector methods
vec3 vec_new(double x, double y, double z);
vec3 vec_neg(vec3 v);
vec3 vec_add(vec3 v1, vec3 v2);
vec3 vec_sub(vec3 v1, vec3 v2);
vec3 vec_mult(vec3 v, double c);
vec3 vec_multv(vec3 v1, vec3 v2);
vec3 vec_div(vec3 v, double c);
double vec_mag2(vec3 v);
double vec_mag(vec3 v);
vec3 vec_unit(vec3 v);
double vec_dot(vec3 v1, vec3 v2);
vec3 vec_cross(vec3 v1, vec3 v2);