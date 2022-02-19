#include "vector.h"
#include "math.h"
#include <stdio.h>

float sq(float a){
    return(a * a);
}

void vector_set(Vector *vector, float x, float y, float z){
    vector->X = x;
    vector->Y = y;
    vector->Z = z;
}

float vector_dist(Vector *vector_a, Vector *vector_b){
    return sqrt(sq(vector_b->X - vector_a->X) + sq(vector_b->Y - vector_a->Y) + sq(vector_b->Z - vector_a->Z));
}

float vector_length(Vector *vector){
    return sqrt(sq(vector->X) + sq(vector->Y) + sq(vector->Z));
}

float vector_dot(Vector *vector_a, Vector *vector_b){
    return (vector_a->X * vector_b->X + vector_a->Y * vector_b->Y + vector_a->Z * vector_b->Z);
}

float vector_cos(Vector *vector_a, Vector *vector_b){
    return vector_dot(vector_a, vector_b) / (vector_length(vector_a) * vector_length(vector_b));
}

void vector_projection(Vector *output, Vector *span, Vector *vect){
    float t = (vector_dot(span, vect)/ vector_dot(span, span));
    vector_scalar(output, span, t);
}

void vector_cross(Vector *output, Vector *vector_a, Vector *vector_b){
    output->X = vector_a->Y*vector_b->Z - vector_a->Z * vector_b->Y;
    output->Y = vector_a->Z*vector_b->X - vector_a->X * vector_b->Z;
    output->Z = vector_a->X*vector_b->Y - vector_a->Y * vector_b->X;
}

void vector_scalar(Vector *output, Vector *vector, float scalar){
    output->X = scalar * vector->X;
    output->Y = scalar * vector->Y;
    output->Z = scalar * vector->Z;
}

void vector_add(Vector *output, Vector *vector_a, Vector *vector_b){
    output->X = vector_a->X + vector_b->X;
    output->Y = vector_a->Y + vector_b->Y;
    output->Z = vector_a->Z + vector_b->Z;
}

void vector_substract(Vector *output, Vector *vector_a, Vector *vector_b){
    output->X = vector_a->X - vector_b->X;
    output->Y = vector_a->Y - vector_b->Y;
    output->Z = vector_a->Z - vector_b->Z;
}

void vector_print(Vector *vector){
    printf("%f %f %f\n", vector->X, vector->Y, vector->Z);
}

