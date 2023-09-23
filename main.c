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
#include "collisions.h"

sphere spheres[2];

// Returns a vector of three values correponding to the color from a direction
// Values will be between 0 and 1
vec3 render_ray(ray r) {
        double a, t1, t = INFINITY;
        vec3 norm;
        // Find the earliest collision with an object
        for (int i = 0; i < 2; i++) {
                if ((t1 = ray_sphere(r, spheres[i])) > 0 && t1 < t) {
                        t = t1;
                        norm = norm_sphere(r, t, spheres[i]);
                }
        }
        if (t != INFINITY) {
                norm =  vec_mult(diff_sphere(norm) , 0.5);
                return vec_new(norm.x/2 + 0.5, norm.y/2 + 0.5, norm.z/2 + 0.5);
        }
        a = 0.5*(vec_unit(r.dir).y + 1.0);
        return vec_new(1-0.5 * a, 1 - 0.3 * a, 1);
}

int
main(int argc, char **argv)
{

        (void) argc;
        (void) argv;       

        // Image details
        int image_width = 255;
        int image_height = 255;
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
        int pixel_samples = 20;

        // 'Camera' position
        vec3 cam_position = vec_new(0, 0, 0);
        vec3 view_center = vec_new(0, 0, view_dist);

        // Creating objects
        spheres[0] = new_sphere(vec_new(0,-100.5,2), 100);
        spheres[1] = new_sphere(vec_new(0, 0.2, 1), 0.5);
        //spheres[0] = new_sphere(vec_new(0, 0, 0.5), 0.2);
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
                                color = vec_add(color, render_ray(r_render));
                        }
                        color = vec_div(color, pixel_samples);

                        // TODO: force between 0 and 1
                        
                        image[image_height - i - 1][j][2] = (unsigned char) ( color.x * 255 );             //red
                        image[image_height - i - 1][j][1] = (unsigned char) ( color.y * 255 );              //green
                        image[image_height - i - 1][j][0] = (unsigned char) ( color.z * 255 );      //blue
                }
        }
        // Open file to write in
        display((unsigned char*) image, image_width, image_height, "bitmap.bmp");
}