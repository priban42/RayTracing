#ifndef SDL_EXAMPLE_RAY_H
#define SDL_EXAMPLE_RAY_H
#include "vector.h"

typedef struct{
    Vector vector_a;
    Vector vector_b;
} Ray;

void ray_direction_vector(Vector *output, Ray *ray);

#endif
