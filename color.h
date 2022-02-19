#ifndef RAYTRACING_MK1_COLOR_H
#define RAYTRACING_MK1_COLOR_H
typedef struct {
    float R;
    float G;
    float B;
}Color;

unsigned char get_R(Color *color);
unsigned char get_G(Color *color);
unsigned char get_B(Color *color);
void color_set(Color *color, float R, float G, float B);
void color_combine(Color *color_a, Color *color_b, float index);
void color_eluminate(Color *color, float index, float base_light);
#endif //RAYTRACING_MK1_COLOR_H
