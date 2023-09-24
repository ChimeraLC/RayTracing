int display(unsigned char *image, int image_height);
int init_writer(int image_width, int image_height, char *filename);
int write_line(unsigned char *image);
int close_writer();