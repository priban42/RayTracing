#include "color.h"

void color_set(Color *color, float R, float G, float B){
    if (0<R && R<1){
        color->R = R;
    }else{
        color->R = 0;
    }
    if (0<G && G<1){
        color->G = G;
    }else {
        color->G = 0;
    }
    if (0<B && B<1){
        color->B = B;
    }else {
        color->B = 0;
    }

}

unsigned char get_R(Color *color){
    return (unsigned char)(color->R * 255.0);
}
unsigned char get_G(Color *color){
    return (unsigned char)(color->G * 255.0);
}
unsigned char get_B(Color *color){
    return (unsigned char)(color->B * 255.0);
}

void color_combine(Color *color_a, Color *color_b, float index){
    float secondary_index = 1-index;
    color_a->R = color_a->R*secondary_index + color_b->R*index;
    color_a->G = color_a->G*secondary_index + color_b->G*index;
    color_a->B = color_a->B*secondary_index + color_b->B*index;
}

void color_eluminate(Color *color, float index, float base_light){
    index = base_light + index * (1-base_light);
    if (index > 0){
        color->R = color->R*index;
        color->G = color->G*index;
        color->B = color->B*index;
    }else{
        color->R = 0;
        color->G = 0;
        color->B = 0;
    }

}