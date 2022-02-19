#include "sphere.h"
#include "ray.h"
#include "light_source.h"
#include "math.h"
#include "plane.h"

void plane_init(Plane *plane, Vector vect_a, Vector vect_b, Vector vect_c){
    plane->vector_a = vect_a;
    plane->vector_b = vect_b;
    plane->vector_c = vect_c;
    Vector dirA;
    Vector dirB;
    vector_substract(&dirA, &vect_a, &vect_b);
    vector_substract(&dirB, &vect_a, &vect_c);
    vector_cross(&plane->normal, &dirA, &dirB);
    color_set(&plane->color1, 0, 0.5, 0);
    color_set(&plane->color2, 0.5, 0, 0);
    plane->pattern_size = 200;
}

float plane_ray_light_cos(Plane *plane, Ray *ray, LightSource *light_source){
    Vector intersection;
    Vector from_light;
    plane_ray_intersection(plane, ray, &intersection);

    vector_substract(&from_light, &light_source->position, &intersection);
    return vector_cos(&plane->normal, &from_light);
}

void plane_get_color(Plane *plane, Vector *vector, Color *output){
    int tile = ((int)(vector->X/plane->pattern_size + 10000)%2 +  (int)(vector->Z/plane->pattern_size + 10000)%2)%2;
    if (tile == 0){
        *output = plane->color1;
    }else{
        *output = plane->color2;
    }
}

int plane_ray_intersects(Plane *plane, Ray *ray){
    Vector ray_dir_vector;
    ray_direction_vector(&ray_dir_vector, ray);
    if (vector_cos(&plane->normal, &ray_dir_vector) < 0){
        return 1;
    }
    return 0;
    //if (vector_cos(&plane->normal, &ray_dir_vector) )
}

void plane_ray_intersection(Plane *plane, Ray *ray, Vector *output){
    Vector ray_dir_vector;
    ray_direction_vector(&ray_dir_vector, ray);

    float D = vector_dot(&plane->normal, &plane->vector_a);

    float t = (D - vector_dot(&ray->vector_a, &plane->normal))/ vector_dot(&ray_dir_vector, &plane->normal);

    vector_scalar(output, &ray_dir_vector, t);
    vector_add(output, output, &ray->vector_a);
}