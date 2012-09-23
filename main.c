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


static void reshape(int w, int h)
{
    GLdouble x = 0.5 * (GLdouble) w / (GLdouble) h;
    GLdouble y = 0.5;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-x, x, -y, y, 1.0, 10.0);

    glViewport(0, 0, w, h);
}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslated(0.0, 0.0, -5.0);

    glutSolidTeapot(1.0);
    glutSwapBuffers();
}

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

    
    for(i=1; i <= verts; i++){
        float px,py,pz,nx,ny,nz;
        char c;
        fscanf(f, "%c     %f     %f     %f     %f     %f     %f\n", &c, &px, &py, &pz, &nx, &ny, &nz);
        v[i].v[0] = px;
    	v[i].v[1] = py;
	    v[i].v[2] = pz;

    	v[i].n[0] = nx;
    	v[i].n[1] = ny;
	    v[i].n[2] = nz;
	 
    }

    for(i=1; i<=triangles;i++){
        int t1,t2,t3;
        char c;
        fscanf(f, "%c %i %i %i\n", &c, &t1, &t2, &t3);
	
	t[i].a = t1;
	t[i].b = t2;
	t[i].c = t3;

    }
    
    fclose(f);

    GLfloat glui = 123345.345345;
    fprintf(stdout, "\n\nsize of GLuint is %zu\n", sizeof glui);
    fprintf(stdout, "\n\ngot %d verts and %d triangles\n", verts, triangles);
    fprintf(stdout, "\n\nexpect size of verts array is %zu\n", verts*glui*6);
    fprintf(stdout, "\n\nsize of verts array is %zu\n", sizeof (v));

    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(640,480);
    glutInit(&argc, argv);

    glutCreateWindow(argv[0]);
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);

    if(glewInit() == GLEW_OK)
        glutMainLoop();

    return (EXIT_SUCCESS);
}

