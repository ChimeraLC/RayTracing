// Struct representing vectors
typedef struct ray {
        vec3 origin;
        vec3 dir;
} ray;

ray ray_new(vec3 origin, vec3 dir);
vec3 ray_at(ray r, double t);
