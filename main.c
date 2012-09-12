/* 
 * File:   main.c
 * Author: jpeak5
 *
 * Created on September 11, 2012, 6:39 PM
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * 
 */
int main(int argc, char** argv) {
    int verts,triangles;
    FILE * f = fopen("mesh/icosa.mesh","r");
    fscanf(f,"%2d %2d",&verts, &triangles);
    fprintf(stdout, "hello %s", "World");
    fprintf(stdout, "got %2d verts and %2d triangles", verts, triangles);
    fclose(f);
    return (EXIT_SUCCESS);
}

