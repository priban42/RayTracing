#ifndef SDL_EXAMPLE_SPHERE_H
#define SDL_EXAMPLE_SPHERE_H
#include "vector.h"
#include "ray.h"
#include "light_source.h"
#include "color.h"

typedef struct{
    Vector position;
    float SIZE;
    Color color;
    float REFLECTIVITY;
} Sphere;

float sphere_get_size(Sphere *sphere);
float sphere_ray_distance(Sphere *sphere, Ray *ray);
void sphere_ray_reflection(Sphere *sphere, Ray *ray, Vector *intersection, Ray *output);
int sphere_ray_intersection(Sphere *sphere, Ray *ray, Vector *output);
float sphere_ray_light_cos(Sphere *sphere, Ray *ray, LightSource *light_source);
#endif //SDL_EXAMPLE_SPHERE_H
