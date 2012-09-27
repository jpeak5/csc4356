/* 
 * File:   main.c
 * Author: jpeak5
 *
 * Created on September 11, 2012, 6:39 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
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

//    glutWireDodecahedron();
//    see cube_render
    glutSwapBuffers();
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

struct obj{
    
    GLuint vbo[1];
    int num_vert;
    int num_tri;
    struct vert *verts;
    struct triangle *triangles;

};

struct obj *O;

void fireTheExplosiveBolts(void)
{
    /*
     * borrowed from one of 
     * the 'viewing' demos
     *
    rotation_x = 0.0;
    rotation_y = 0.0;
    position_z = 5.0;
    scale      = 1.0;                                                          \
    
    C = cube_create();
    
    *
    *
    */

}
    

struct obj *readFileData(char *arg1){
    
    assert(arg1 != NULL);

    printf("param 1 to readFileData = %s\n", arg1);
    int i,vert_count,tri_count;
    
    FILE * f = fopen((char *)arg1,"r");

    printf("reading file %s\n", arg1);
    fscanf(f,"%d %d\n",&vert_count, &tri_count);
//    struct vert v[vert_count];
    struct triangle t[tri_count];
    printf("scanning %d verts and %d triangles\n", vert_count, tri_count);
    
    //declaratino + initializtion
    //this call to malloc() means that this thing
    //we are declaring will persist beyond the scope of the 
    //function call...
    O = malloc(sizeof(struct obj));
    
    O->verts = malloc(vert_count * sizeof(struct vert));

    for(i=0; i < vert_count; i++){
        
        GLfloat px,py,pz,nx,ny,nz;
        
        char c;
        fscanf(f, "%c     %f     %f     %f     %f     %f     %f\n", &c, &px, &py, &pz, &nx, &ny, &nz);

        O->verts[i].v[0] = px;
    	O->verts[i].v[1] = py;
	    O->verts[i].v[2] = pz;

    	O->verts[i].n[0] = nx;
    	O->verts[i].n[1] = ny;
	    O->verts[i].n[2] = nz;
    }
    
    for(i=0; i<vert_count; i++){
        printf("vert %02d: (%f, %f, %f)\n", i, O->verts[i].v[0], O->verts[i].v[1], O->verts[i].v[2]);
    }

    O->triangles = malloc(tri_count * sizeof(struct triangle));
    for(i=0; i<=tri_count;i++){
        int t1,t2,t3;
        char c;
        fscanf(f, "%c %i %i %i\n", &c, &t1, &t2, &t3);
	
    	O->triangles[i].a = t1;
	    O->triangles[i].b = t2;
    	O->triangles[i].c = t3;

    }
    
    fclose(f);

    glEnable(GL_NORMALIZE);                                                    \
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    return O;
}


int main(int argc, char** argv) {

    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(640, 480);
    glutInit(&argc, argv);

    glutCreateWindow(argv[0]);
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    //glutMotionFunc(motion);
    //glutMouseFunc(mouse);

    char *filename = argv[1]; 
    O = readFileData(filename);

    glEnable(GL_NORMALIZE);                                                    \
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

    fireTheExplosiveBolts();
    glutMainLoop();

    return (EXIT_SUCCESS);
}

