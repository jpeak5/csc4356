/* 
 * File:   main.c
 * Author: jpeak5
 *
 * Created on September 11, 2012, 6:39 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/glut.h>
/*
 * 
 */
int main(int argc, char** argv) {
     
    int i;
    //parse command line
    for(i = 0; i < argc; i++){
    	printf("got arg [%d]: %s\n",i, argv[i]);
    }

    struct vert{
	    GLfloat v[3];
	    GLfloat n[3];
    };

    struct triangle {
	    int a;
	    int b;
	    int c;
    };

    int verts,triangles;
    FILE * f = fopen(argv[1],"r");

    fscanf(f,"%d %d\n",&verts, &triangles);
   
    struct vert v[verts];
    struct triangle t[triangles];

//    printf("looking for %d verts abd then %d triangles\n\n", verts, triangles);
//    printf("-------------------begin verts------------\n"); 
    
    i = 1;
    for(i; i <= verts; i++){
        float px,py,pz,nx,ny,nz;
        char c;
        fscanf(f, "%c     %f     %f     %f     %f     %f     %f\n", &c, &px, &py, &pz, &nx, &ny, &nz);
        v[i].v[0] = px;
	v[i].v[1] = py;
	v[i].v[2] = pz;

	v[i].n[0] = nx;
	v[i].n[1] = ny;
	v[i].n[2] = nz;
	 
//       fprintf(stdout, "%02d) %c (%f, %f, %f), normal (%f, %f, %f)\n", 
//		i, c,
//		v[i].v[0] ,v[i].v[1], v[i].v[2],
//		v[i].n[0], v[i].n[1], v[i].n[2]
//		);
    }

    i = 1;
    for(i; i<=triangles;i++){
        int t1,t2,t3;
        char c;
        fscanf(f, "%c %i %i %i\n", &c, &t1, &t2, &t3);
	
	t[i].a = t1;
	t[i].b = t2;
	t[i].c = t3;

//        fprintf(stdout, "%02d)  %c (%d, %d, %d)\n", i, c,t[i].a, t[i].b, t[i].c);
    }
    
    fclose(f);

    GLfloat glui = 123345.345345;
    fprintf(stdout, "\n\nsize of GLuint is %zu\n", sizeof glui);
    fprintf(stdout, "\n\ngot %d verts and %d triangles\n", verts, triangles);
    fprintf(stdout, "\n\nexpect size of verts array is %zu\n", verts*glui*6);
    fprintf(stdout, "\n\nsize of verts array is %zu\n", sizeof (v));

    return (EXIT_SUCCESS);
}

