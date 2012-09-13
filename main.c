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


    struct vertex{
	float x;
	float y;
	float z;
    };

    struct normal {
	float x;
	float y;
	float z;
    };

    struct triangle {
	int a;
	int b;
	int c;
    };

    int verts,triangles;
    FILE * f = fopen(argv[1],"r");

    fscanf(f,"%d %d\n",&verts, &triangles);
   
    struct vertex v[verts];
    struct normal n[verts];
    struct triangle t[triangles];

    printf("looking for %d verts abd then %d triangles\n\n", verts, triangles);
    printf("-------------------begin verts------------\n"); 
    
    i = 1;
    for(i; i <= verts; i++){
        float px,py,pz,nx,ny,nz;
        char c;
        fscanf(f, "%c     %f     %f     %f     %f     %f     %f\n", &c, &px, &py, &pz, &nx, &ny, &nz);
        v[i].x = px;
	v[i].y = py;
	v[i].z = pz;

	n[i].x = nx;
	n[i].y = ny;
	n[i].z = nz;
	 
        fprintf(stdout, "%02d) %c (%f, %f, %f), normal (%f, %f, %f)\n", 
		i, c,
		v[i].x ,v[i].y, v[i].z,
		n[i].x, n[i].y, n[i].z
		);
    }

    i = 1;
    for(i; i<=triangles;i++){
        int t1,t2,t3;
        char c;
        fscanf(f, "%c %i %i %i\n", &c, &t1, &t2, &t3);
	
	t[i].a = t1;
	t[i].b = t2;
	t[i].c = t3;

        fprintf(stdout, "%02d)  %c (%d, %d, %d)\n", i, c,t[i].a, t[i].b, t[i].c);
    }
    
    fclose(f);
    fprintf(stdout, "\n\ngot %d verts and %d triangles\n", verts, triangles);
    return (EXIT_SUCCESS);
}

