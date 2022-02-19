#include "sphere.h"
#include "ray.h"
#include "light_source.h"
#include "math.h"


float sphere_ray_light_cos(Sphere *sphere, Ray *ray, LightSource *light_source){
    Vector intersection;
    Vector normal;
    Vector from_light;
    sphere_ray_intersection(sphere, ray, &intersection);
    vector_substract(&normal, &intersection, &sphere->position);
    vector_substract(&from_light, &light_source->position, &intersection);
    return vector_cos(&normal, &from_light);
}

float sphere_get_size(Sphere *sphere){
    return (*sphere).SIZE;
}

float sphere_ray_distance(Sphere *sphere, Ray *ray){
    Vector ray_dir_vect;
    ray_direction_vector(&ray_dir_vect, ray);

    Vector particular;
    vector_substract(&particular, &sphere->position, &ray_dir_vect);

    Vector projection;
    Vector rejection;

    vector_projection(&projection, &ray_dir_vect, &particular);
    vector_substract(&rejection, &particular, &projection);

    return vector_length(&rejection);
}

void sphere_ray_reflection(Sphere *sphere, Ray *ray, Vector *intersection, Ray *output){
    output->vector_a = *intersection;

    Vector ray_dir_vector;
    Vector normal;
    Vector projection;

    ray_direction_vector(&ray_dir_vector, ray);
    vector_substract(&normal, intersection, &sphere->position);

    vector_projection(&projection, &normal, &ray_dir_vector);

    vector_substract(&output->vector_b, &ray_dir_vector, &projection);
    vector_scalar(&output->vector_b, &output->vector_b, 2);
    vector_add(&output->vector_b, &output->vector_b, &ray->vector_a);
}

int sphere_ray_intersection(Sphere *sphere, Ray *ray, Vector *output){
    float x1 = ray->vector_a.X;
    float y1 = ray->vector_a.Y;
    float z1 = ray->vector_a.Z;
    float x2 = ray->vector_b.X;
    float y2 = ray->vector_b.Y;
    float z2 = ray->vector_b.Z;
    float xc = sphere->position.X;
    float yc = sphere->position.Y;
    float zc = sphere->position.Z;

    float a = (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1) + (z2 - z1) * (z2 - z1);
    float b = -2*( (x2 - x1)*(xc - x1) + (y2 - y1) * (yc - y1) + (z2 - z1) * (zc - z1));
    float c = (xc - x1) * (xc - x1) + (yc - y1) * (yc - y1) + (zc - z1) * (zc - z1) - sphere->SIZE * sphere->SIZE;
    if (b*b < 4*a*c){
        return 0;

    }
    float t1 = (-b + sqrt(b*b - 4*a*c))/(2*a);
    float t2 = (-b - sqrt(b*b - 4*a*c))/(2*a);

    Vector return_a;
    Vector return_b;

    ray_direction_vector(&return_a, ray);
    vector_scalar(&return_a, &return_a, t1);
    vector_add(&return_a, &return_a, &ray->vector_a);

    ray_direction_vector(&return_b, ray);
    vector_scalar(&return_b, &return_b, t2);
    vector_add(&return_b, &return_b, &ray->vector_a);

    if (vector_dist(&return_a, &ray->vector_a) < vector_dist(&return_b, &ray->vector_a)){
        *output = return_a;
    }else{
        *output = return_b;
    }
    return 1;
}