// Main file that runs the raytracing functionality and calculations
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

#include "bmpwriter.h"
#include "vectors.h"
#include "rays.h"
#include "materials.h"
#include "collisions.h"

// Constants definitions
#define MIN_DIST 0.01   // Minimum distance required for an intersection

// Default material
material default_mat;

int sphere_count = 3;
sphere spheres[3];


// Returns a vector of three values correponding to the color from a direction
// Values will be between 0 and 1
vec3 render_ray(ray r, int bounces) {
        // Preventing recursion that is too deep
        if (bounces == 0) {
                return vec_new(0, 0, 0);
        }
        double a, t, t_close = INFINITY;
        vec3 norm;
        material mat = default_mat;
        // Chekc collisions with all objects
        for (int i = 0; i < sphere_count; i++) {
                // Find the earliest collision with an object that's not self
                if ((t = ray_sphere(r, spheres[i])) > MIN_DIST && t < t_close) {
                        t_close = t;
                        norm = norm_sphere(r, t_close, spheres[i]);
                        // Save bounce material
                        mat = spheres[i].mat;
                }
        }
        if (t_close != INFINITY) {
                // Diffraction direction based on material
                vec3 diff = mat.diff(r, norm);
                // Render diffusion ray with one less bounce
                norm =  vec_mult(render_ray(ray_new(ray_at(r, t_close), diff),
                         bounces - 1), mat.refl);
                return norm;
        }
        // Otherwise, return color of background
        a = 0.5*(vec_unit(r.dir).y + 1.0);
        return vec_new(1-0.5 * a, 1 - 0.3 * a, 1);
}

int
main(int argc, char **argv)
{

        (void) argc;
        (void) argv;       

        // Image details
        int image_width = 800;
        int image_height = 400;
        double aspect_ratio = 1; (void) aspect_ratio;
        unsigned char image[image_height][image_width][3];

        // Calculate viewport (-w/2, -h/2, -d) to (w/2, h/2, d)
        double view_height = 2;
        double view_width = view_height * ((double) image_width / image_height);
        double view_dist = 1;   // Distance between camera and viewport

        // Vector representations
        vec3 view_horizontal = vec_new(view_width, 0, 0);
        vec3 view_vertical = vec_new(0, -view_height, 0);

        // Pixel sizes
        vec3 pixel_horizontal = vec_div(view_horizontal, image_width);
        vec3 pixel_vertical = vec_div(view_vertical, image_height);

        // 'Camera' position
        vec3 cam_position = vec_new(0, 0, 0);
        vec3 view_center = vec_new(0, 0, view_dist);

        // Rendering options
        int pixel_samples = 30; // Number of samples for each ray
        int render_bounces = 10;  // Number of recursive render calls per ray

        // Creating objects
        default_mat = mat_basic(0.5);
        spheres[0] = new_sphere(vec_new(0,-100.5,1), 100, mat_basic(0.8));
        spheres[1] = new_sphere(vec_new(0, 0, 1), 0.5, mat_metal(0.5));
        spheres[2] = new_sphere(vec_new(1, 0, 1), 0.5, mat_basic(0.5));
        //spheres[0] = new_sphere(vec_new(0, 0, 1), 0.2, 0.5);
        

        // Iterate through pixels
        int i, j;
        for (i = 0; i < image_height; i++) {
                printf("\rScanlines remaining: %d ", image_height - i);
                for (j = 0; j < image_width; j++) {
                        // Find desired view position
                        vec3 pixel_point = vec_copy(cam_position);
                        pixel_point = vec_add(pixel_point, view_center);
                        pixel_point = vec_add(vec_neg(vec_div(view_horizontal, 2)), pixel_point);
                        pixel_point = vec_add(vec_neg(vec_div(view_vertical, 2)), pixel_point);

                        // Add pixel offset
                        pixel_point = vec_add(vec_mult(pixel_vertical, i + 0.5), pixel_point);
                        pixel_point = vec_add(vec_mult(pixel_horizontal, j + 0.5), pixel_point);

                        // Create corresponding ray (pointing from cam to pixel)
                        vec3 color = vec_new(0, 0, 0);
                        for (int k = 0; k < pixel_samples; k++) {
                                // Generate a random point nearby
                                vec3 pixel_spray = vec_copy(pixel_point);
                                pixel_spray = vec_add(pixel_spray, vec_mult(pixel_horizontal, (double)rand() / RAND_MAX - 0.5));
                                pixel_spray = vec_add(pixel_spray, vec_mult(pixel_vertical, (double)rand() / RAND_MAX - 0.5));
                                ray r_render = ray_new(cam_position, vec_unit(vec_sub(pixel_spray, cam_position)));
                                color = vec_add(color, render_ray(r_render, render_bounces));
                        }
                        color = vec_div(color, pixel_samples);

                        // TODO: force between 0 and 1
                        
                        image[image_height - i - 1][j][2] = (unsigned char) ( sqrt(color.x) * 255 );             //red
                        image[image_height - i - 1][j][1] = (unsigned char) ( sqrt(color.y) * 255 );              //green
                        image[image_height - i - 1][j][0] = (unsigned char) ( sqrt(color.z) * 255 );      //blue
                }
        }
        printf("\rRender complete         "); 
        // Open file to write in
        display((unsigned char*) image, image_width, image_height, "bitmap.bmp");
}