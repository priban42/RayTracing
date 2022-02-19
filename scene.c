#include <SDL.h>
#include <stdio.h>
#include "scene.h"
#include "ray.h"
#include "sphere.h"

void scene_render_simple(Scene *scene, SDL_Renderer *renderer){
    scene->ray.vector_a.X = 0;
    scene->ray.vector_a.Y = 0;
    scene->ray.vector_a.Z = 0;
    scene->ray.vector_b.Z = 100;
    for(int y = 0; y < scene->height; y++){
        scene->ray.vector_b.Y = y - (scene->height/2);
        for(int x = 0; x < scene->width; x++){
            scene->ray.vector_b.X = x - (scene->width/2);
            for(int s = 0; s < scene->sphere_count; s++){
                if (sphere_ray_distance(&scene->spheres[s], &scene->ray) <= scene->spheres[s].SIZE){
                    SDL_SetRenderDrawColor(renderer, get_R(&scene->spheres[s].color), get_G(&scene->spheres[s].color), get_B(&scene->spheres[s].color), 0);
                    SDL_RenderDrawPoint(renderer, x, y);
                }
            }
        }
    }
}

void scene_render_light(Scene *scene, SDL_Renderer *renderer){
    SDL_SetRenderDrawColor(renderer, get_R(&scene->background_color), get_G(&scene->background_color), get_B(&scene->background_color), 255);
    SDL_RenderClear(renderer);
    scene->ray.vector_a.X = scene->origin_X;
    scene->ray.vector_a.Y = scene->origin_Y;
    scene->ray.vector_a.Z = scene->origin_Z;
    scene->ray.vector_b.Z = 0;
    Vector general_intersection;
    float pixel_brightness;
    Color pixel_color;
    for(int y = 0; y < scene->height; y++){
        scene->ray.vector_b.Y = y - (scene->height/2);
        for(int x = 0; x < scene->width; x++){
            scene->ray.vector_b.X = x - (scene->width/2);
            for(int p = 0; p < scene->plane_count; p++){
                if (plane_ray_intersects(&scene->planes[p], &scene->ray)){
                    Ray shadow_ray;
                    plane_ray_intersection(&scene->planes[p], &scene->ray, &shadow_ray.vector_a);
                    shadow_ray.vector_b = scene->light_sources[0].position;

                    pixel_color;
                    plane_get_color(&scene->planes[p], &shadow_ray.vector_a, &pixel_color);
                    if (!sphere_ray_intersection(&scene->spheres[0], &shadow_ray, &general_intersection)){
                        pixel_brightness = plane_ray_light_cos(&scene->planes[p], &scene->ray, &scene->light_sources[0]);
                        color_eluminate(&pixel_color, pixel_brightness, scene->base_light);
                    }else{

                        color_eluminate(&pixel_color, 0.1, scene->base_light);
                    }
                    SDL_SetRenderDrawColor(renderer, get_R(&pixel_color), get_G(&pixel_color), get_B(&pixel_color), 0);
                    SDL_RenderDrawPoint(renderer, x, y);
                }
            }

            for(int s = 0; s < scene->sphere_count; s++){
                if (sphere_ray_intersection(&scene->spheres[s], &scene->ray, &general_intersection)){
                    pixel_brightness = sphere_ray_light_cos(&scene->spheres[s], &scene->ray, &scene->light_sources[0]);
                    pixel_color = scene->spheres[s].color;
                    color_eluminate(&pixel_color, pixel_brightness, scene->base_light);
                    SDL_SetRenderDrawColor(renderer, get_R(&pixel_color), get_G(&pixel_color), get_B(&pixel_color), 0);
                    SDL_RenderDrawPoint(renderer, x, y);
                }
            }
        }
    }
}

void scene_render_raytrace(Scene *scene, SDL_Renderer *renderer){
    SDL_SetRenderDrawColor(renderer, get_R(&scene->background_color), get_G(&scene->background_color), get_B(&scene->background_color), 255);
    SDL_RenderClear(renderer);
    scene->ray.vector_a.X = scene->origin_X;
    scene->ray.vector_a.Y = scene->origin_Y;
    scene->ray.vector_a.Z = scene->origin_Z;
    scene->ray.vector_b.Z = 0;
    Vector general_intersection;
    float pixel_brightness;
    Color pixel_color;
    for(int y = 0; y < scene->height; y++){
        scene->ray.vector_b.Y = y - (scene->height/2);
        for(int x = 0; x < scene->width; x++){
            scene->ray.vector_b.X = x - (scene->width/2);
            for(int p = 0; p < scene->plane_count; p++){
                if (plane_ray_intersects(&scene->planes[p], &scene->ray)){
                    Ray shadow_ray;
                    plane_ray_intersection(&scene->planes[p], &scene->ray, &shadow_ray.vector_a);
                    shadow_ray.vector_b = scene->light_sources[0].position;

                    pixel_color;
                    plane_get_color(&scene->planes[p], &shadow_ray.vector_a, &pixel_color);
                    if (!sphere_ray_intersection(&scene->spheres[0], &shadow_ray, &general_intersection)){
                        pixel_brightness = plane_ray_light_cos(&scene->planes[p], &scene->ray, &scene->light_sources[0]);
                        color_eluminate(&pixel_color, pixel_brightness, scene->base_light);
                    }else{
                        color_eluminate(&pixel_color, 0.1, scene->base_light);
                    }
                    SDL_SetRenderDrawColor(renderer, get_R(&pixel_color), get_G(&pixel_color), get_B(&pixel_color), 0);
                    SDL_RenderDrawPoint(renderer, x, y);
                }
            }

            for(int s = 0; s < scene->sphere_count; s++){
                if (sphere_ray_intersection(&scene->spheres[s], &scene->ray, &general_intersection)){
                    pixel_brightness = sphere_ray_light_cos(&scene->spheres[s], &scene->ray, &scene->light_sources[0]);
                    pixel_color = scene->spheres[s].color;
                    color_eluminate(&pixel_color, pixel_brightness, scene->base_light);
                    Ray bounce;
                    sphere_ray_reflection(&scene->spheres[s], &scene->ray, &general_intersection, &bounce);
                    if (plane_ray_intersects(&scene->planes[0], &bounce)){
                        plane_ray_intersection(&scene->planes[0], &bounce, &general_intersection);
                        Color bounce_color;
                        Ray shadow_ray;
                        shadow_ray.vector_a = general_intersection;
                        shadow_ray.vector_b = scene->light_sources[0].position;

                        plane_get_color(&scene->planes[0], &shadow_ray.vector_a, &bounce_color);
                        if (!sphere_ray_intersection(&scene->spheres[0], &shadow_ray, &general_intersection)){
                            pixel_brightness = plane_ray_light_cos(&scene->planes[0], &scene->ray, &scene->light_sources[0]);
                            color_eluminate(&bounce_color, pixel_brightness, scene->base_light);
                        }else{
                            color_eluminate(&bounce_color, 0.1, scene->base_light);
                        }
                        color_eluminate(&bounce_color, pixel_brightness, scene->base_light);
                        color_combine(&pixel_color, &bounce_color, 0.4);
                    }
                    SDL_SetRenderDrawColor(renderer, get_R(&pixel_color), get_G(&pixel_color), get_B(&pixel_color), 0);
                    SDL_RenderDrawPoint(renderer, x, y);
                }
            }
        }
    }
}


void scene_init(Scene *scene){
    scene->base_light = 0.3;
    scene->sphere_count = 0;
    scene->light_source_count = 0;
    scene->plane_count = 0;
    scene->origin_X = 0;
    scene->origin_Y = 0;
    scene->origin_Z = -1000;
    Color color;
    color_set(&color, 0.2, 0.2, 0.2);
    scene->background_color = color;
}

void scene_add_plane(Scene *scene){
    Plane plane;
    Vector vect_a;
    Vector vect_b;
    Vector vect_c;
    vector_set(&vect_a, 0, 300, 0);
    vector_set(&vect_b, 1, 300, 0);
    vector_set(&vect_c, 0, 300, 1);
    plane_init(&plane, vect_a, vect_b, vect_c);
    scene->planes[scene->plane_count] = plane;
    scene->plane_count ++;
}

void scene_add_sphere(Scene *scene, float x, float y, float z, float size){
    Sphere sphere;
    sphere.position.X = x;
    sphere.position.Y = y;
    sphere.position.Z = z;
    sphere.color.R = 0.8;
    sphere.color.G = 0.8;
    sphere.color.B = 0.8;
    sphere.SIZE = size;
    scene->spheres[scene->sphere_count] = sphere;
    scene->sphere_count ++;
}

void scene_let_there_be_light(Scene *scene, float x, float y, float z){
    LightSource light_source;
    light_source.position.X = x;
    light_source.position.Y = y;
    light_source.position.Z = z;
    scene->light_sources[scene->light_source_count] = light_source;
    scene->light_source_count++;
}