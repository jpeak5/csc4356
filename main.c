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

/*
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

    glutWireDodecahedron();
    glutSwapBuffers();
}
*/

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
    
    int num_vert;
    int num_tri;
    struct vert *verts;
    struct triangle *triangles;

};


    

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
    

    struct obj *object = malloc(sizeof(struct obj));
    object->verts = malloc(vert_count * sizeof(struct vert));
    for(i=0; i < vert_count; i++){
        GLfloat px,py,pz,nx,ny,nz;
        char c;
        fscanf(f, "%c     %f     %f     %f     %f     %f     %f\n", &c, &px, &py, &pz, &nx, &ny, &nz);
        object->verts[i].v[0] = px;
    	object->verts[i].v[1] = py;
	    object->verts[i].v[2] = pz;

    	object->verts[i].n[0] = nx;
    	object->verts[i].n[1] = ny;

        // assert(object->verts[i].n[2] != NULL);
	    object->verts[i].n[2] = nz;
    }
/*
    //object->verts = v;
    for(i=0; i<=vert_count; i++){
        printf("vert %02d: (%f, %f, %f)", i, object->verts[i].v[0], object->verts[i].v[1], object->verts[i].v[2]);
    }
*/
    for(i=1; i<=tri_count;i++){
        int t1,t2,t3;
        char c;
        fscanf(f, "%c %i %i %i\n", &c, &t1, &t2, &t3);
	
    	t[i].a = t1;
	    t[i].b = t2;
    	t[i].c = t3;

    }
    
    object->triangles = t;
    fclose(f);
    return object;
}


int main(int argc, char** argv) {
    char *filename = argv[1]; 
    struct obj *object = readFileData(filename);

    
/*
    GLfloat glui = 123345.345345;
    fprintf(stdout, "\n\nsize of GLuint is %zu\n", sizeof glui);
    fprintf(stdout, "\n\ngot %d vert_count and %d triangles\n", vert_count, tri_count);
    fprintf(stdout, "\n\nexpect size of verts array is %zu\n", vert_count*glui*6);
    //fprintf(stdout, "\n\nsize of verts array is %zu\n", sizeof (v));

    GLuint vbo[1];
    glGenBuffers(1, &vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof (v), v, GL_STATIC_DRAW);
    printf("The size of v is sizeof (v) = %d", sizeof(v));

    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(640,480);
    glutInit(&argc, argv);

    glutCreateWindow(argv[0]);
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);

    if(glewInit() == GLEW_OK)
        glutMainLoop();

    glEnable(GL_COLOR_MATERIAL);
    {
*/
        /* Enable the necessary array pointers. */
/*
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);
        {
*/
            /* Bind the array pointers to the array buffer object. */
/*
            glBindBuffer(GL_ARRAY_BUFFER, P->vbo[0]);
            {
                glVertexPointer(3, GL_FLOAT, sz * 6, (GLvoid *) (     0));
                glNormalPointer(   GL_FLOAT, sz * 6, (GLvoid *) (sz * 3));
*/
                /* Render the squares. */
/*
                glColor4f(0.8f, 0.8f, 0.8f, 1.0f);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, P->ebo[0]);
                glDrawElements(GL_TRIANGLES, nf, GL_UNSIGNED_SHORT, 0);
*/
                /* Render the lines */
/*
                glColor4f(0.9f, 0.9f, 0.9f, 1.0f);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, P->ebo[1]);
                glDrawElements(GL_TRIANGLES, nl, GL_UNSIGNED_SHORT, 0);
*/
                /* Revert all state. */
/*
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            }
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }
        glDisableClientState(GL_NORMAL_ARRAY);
        glDisableClientState(GL_VERTEX_ARRAY);
    }
    glDisable(GL_COLOR_MATERIAL);

*/
    return (EXIT_SUCCESS);
}

