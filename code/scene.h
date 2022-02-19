
#ifndef SDL_EXAMPLE_SCENE_H
#define SDL_EXAMPLE_SCENE_H

#include "ray.h"
#include "sphere.h"
#include "light_source.h"
#include "plane.h"

typedef struct {
    int width;
    int height;
    Color background_color;
    float origin_X;
    float origin_Y;
    float origin_Z;
    Ray ray;
    Sphere spheres[3];
    int sphere_count;
    LightSource light_sources[3];
    int light_source_count;
    float base_light;
    Plane planes[3];
    int plane_count;

} Scene;

void scene_init();

void scene_render_simple(Scene *scene, SDL_Renderer *renderer);
void scene_render_light(Scene *scene, SDL_Renderer *renderer);
void scene_render_raytrace(Scene *scene, SDL_Renderer *renderer);

void scene_add_plane(Scene *scene);
void scene_add_sphere(Scene *scene, float x, float y, float z, float size);
void scene_let_there_be_light(Scene *scene, float x, float y, float z);
#endif //SDL_EXAMPLE_SCENE_H
