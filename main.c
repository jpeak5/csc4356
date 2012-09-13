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
    fscanf(f,"%d %d",&verts, &triangles);
    int i = 1;
    
        int t1,t2,t3;
        char c;
        fscanf(f, "%c %d %d %d", &c, &t1, &t2, &t3);
        fprintf(stdout, "%d) line code %c (%d, %d, %d)\n", i, c,t1,t2,t3);
    
    for(i; i <= verts; i++){
        float px,py,pz,nx,ny,nz;
        char c;
        fscanf(f, "%c     %f     %f     %f     %f     %f     %f", &c, &px, &py, &pz, &nx, &ny, &nz);
        
        fprintf(stdout, "%d) line code %c (%f, %f, %f), normal (%f, %f, %f)\n", i, c,px,py,pz,nx,ny,nz);
    }
    i = 1;

    /**This is not working!!!
    for(i; i<=triangles;i++){
        int t1,t2,t3;
        char c;
    */
        fscanf(f, "%c %d %d %d", &c, &t1, &t2, &t3);
        fprintf(stdout, "%d) line code %c (%d, %d, %d)\n", i, c,t1,t2,t3);
    /*
    }
    */
    
    fclose(f);
    fprintf(stdout, "\n\ngot %d verts and %d triangles\n", verts, triangles);
    return (EXIT_SUCCESS);
}

