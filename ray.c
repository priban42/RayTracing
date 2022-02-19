#include <stdio.h>
#include <math.h>
#include "Ray.h"
#include "vector.h"

void ray_direction_vector(Vector *output, Ray *ray){
    vector_substract(output, &ray->vector_b, &ray->vector_a);
}


