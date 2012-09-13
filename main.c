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
    int i = 1;
    for(i; i<=verts;i++){
        float px,py,pz,nx,ny,nz;
        char c;
        fscanf(f, "%c     %f     %f     %f     %f     %f     %f", &c, &px, &py, &pz, &nx, &ny, &nz);
        
        fprintf(stdout, "%d) line code %c (%f, %f, %f), normal (%f, %f, %f)\n", i, c,px,py,pz,nx,ny,nz);
    }
    fclose(f);
    return (EXIT_SUCCESS);
}

