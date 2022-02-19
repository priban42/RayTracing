#ifndef RAYTRACING_MK1_VECTOR_H
#define RAYTRACING_MK1_VECTOR_H

#include <stdio.h>

typedef struct{
    float X;
    float Y;
    float Z;
} Vector;

void vector_set(Vector *vector, float x, float y, float z);
float vector_dist(Vector *vector_a, Vector *vector_b);
float vector_dot(Vector *vector_a, Vector *vector_b);
float vector_length(Vector *vector);
float vector_cos(Vector *vector_a, Vector *vector_b);

void vector_projection(Vector *output, Vector *span, Vector *vect);
void vector_cross(Vector *output, Vector *vector_a, Vector *vector_b);
void vector_scalar(Vector *output, Vector * vector, float scalar);
void vector_add(Vector *output, Vector *vector_a, Vector *vector_b);
void vector_substract(Vector *output, Vector *vector_a, Vector *vector_b);
void vector_print(Vector *vector);

#endif //RAYTRACING_MK1_VECTOR_H
