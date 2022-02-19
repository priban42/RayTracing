cmake_minimum_required(VERSION 3.20)
project(RayTracing_mk1 C)

set(CMAKE_C_STANDARD 99)

set(SDL2_INCLUDE_DIR E:/Programovani/C/libs/SDL2-2.0.20/include)
set(SDL2_LIB_DIR E:/Programovani/C/libs/SDL2-2.0.20/lib/x86)

include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})

add_executable(RayTracing_mk1 main.c sphere.c sphere.h ray.c ray.h scene.c scene.h light_source.c light_source.h vector.c vector.h color.c color.h plane.h plane.c)

target_link_libraries(${PROJECT_NAME} SDL2main SDL2)