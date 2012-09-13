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
     
    int i;
    //parse command line
    for(i = 0; i < argc; i++){
    	printf("got arg [%d]: %s\n",i, argv[i]);
    }

    int verts,triangles;
    FILE * f = fopen(argv[1],"r");

    fscanf(f,"%d %d\n",&verts, &triangles);
    
    printf("looking for %d verts abd then %d triangles\n\n", verts, triangles);
    printf("-------------------begin verts------------\n"); 
    
    i = 1;
    for(i; i <= verts; i++){
        float px,py,pz,nx,ny,nz;
        char c;
        fscanf(f, "%c     %f     %f     %f     %f     %f     %f\n", &c, &px, &py, &pz, &nx, &ny, &nz);
        
        fprintf(stdout, "%02d) %c (%f, %f, %f), normal (%f, %f, %f)\n", i, c,px,py,pz,nx,ny,nz);
    }
    i = 1;

    for(i; i<=triangles;i++){
        int t1,t2,t3;
        char c;
        fscanf(f, "%c %i %i %i\n", &c, &t1, &t2, &t3);
        fprintf(stdout, "%02d)  %c (%d, %d, %d)\n", i, c,t1,t2,t3);
    }
    
    fclose(f);
    fprintf(stdout, "\n\ngot %d verts and %d triangles\n", verts, triangles);
    return (EXIT_SUCCESS);
}

