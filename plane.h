#ifndef RAYTRACING_MK1_PLANE_H
#define RAYTRACING_MK1_PLANE_H
#include "vector.h"
#include "ray.h"
#include "light_source.h"
#include "color.h"

typedef struct{
    Vector vector_a;
    Vector vector_b;
    Vector vector_c;
    Vector normal;
    Color color1;
    Color color2;
    float pattern_size;
} Plane;

int plane_ray_intersects(Plane *plane, Ray *ray);
void plane_ray_intersection(Plane *plane, Ray *ray, Vector *output);
float plane_ray_light_cos(Plane *plane, Ray *ray, LightSource *light_source);
void plane_init(Plane *plane, Vector vect_a, Vector vect_b, Vector vect_c);
void plane_get_color(Plane *plane, Vector *vector, Color *output);

#endif //RAYTRACING_MK1_PLANE_H
