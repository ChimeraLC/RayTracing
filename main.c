// Main file that runs the raytracing functionality and calculations
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "bmpwriter.h"
#include "vectors.h"

// Struct representing vectors
typedef struct ray {
        vec3 origin;
        vec3 dir;
} ray;

int
main(int argc, char **argv)
{

        (void) argc;
        (void) argv;       

        // Image details
        int image_width = 255;
        int image_height = 255;
        double aspect_ratio = 1;
        unsigned char image[image_height][image_width][3];

        // Calculate viewport
        double view_height = 2;
        double vew_width = view_height * ((double) image_width / image_height);

        // 'Camera' position
        vec3 cam_position = vec_new(0, 0, 0);

        int i, j;
        for (i = 0; i < image_height; i++) {
                printf("\rScanlines remaining: %d ", image_height - j);
                for (j = 0; j < image_width; j++) {
                image[i][j][2] = (unsigned char) ( i * 255 / image_height );             //red
                image[i][j][1] = (unsigned char) ( j * 255 / image_width );              //green
                image[i][j][0] = (unsigned char) ( (i+j) * 255 / (image_height + image_width) );      //blue
                }
        }
        // Open file to write in
        display((unsigned char*) image, image_width, image_height, "bitmap.bmp");
}