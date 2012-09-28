#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include "shape.h"


/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/

/* The following data give the vertices of the standard unit cube.  These     */
/* may be stored in a vertex array or buffer object and used directly with    */
/* a call to glDrawArrays(GL_QUADS, 0, 24). The vertex ordering and texture   */
/* coordinates provided give face orientations in line with the definition    */
/* of GL_TEXTURE_CUBE_MAP.                                                    */


struct vert{
    GLfloat v[3];
    GLfloat n[3];
};

struct triangle {
    GLushort t[3];
};

struct shape{
    
    GLuint vbo[1];
    //this might be a problem;
    GLuint ebo[1];
    int num_vert;
    int num_tri;
    struct vert *verts;
    struct triangle *triangles;

};


static void init_vbo(struct shape *S)
{
    size_t vbo_sz = sizeof(struct vert) * S->num_vert;
    printf("size of vbo @vbo init time= %zu\n", vbo_sz);

    glBindBuffer(GL_ARRAY_BUFFER,         S->vbo[0]);
    glBufferData(GL_ARRAY_BUFFER,         vbo_sz, S->verts, GL_STATIC_DRAW);



    size_t ebo_sz = sizeof(struct triangle) * S->num_tri;
    printf("size of ebo @ebo init time= %zu\n", ebo_sz);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, S->ebo[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, ebo_sz, S->triangles, GL_STATIC_DRAW);
}

/*----------------------------------------------------------------------------*/



/* Allocate and initialize a new shape object. There must be a current OpenGL  */
/* context at the time.                                                       */

shape *shape_create(char * arg1)
{
    shape *S;
    S = malloc(sizeof(shape));

    //printf("param 1 to readFileData = %s\n", arg1);
    int i,vert_count,tri_count;
    
    FILE * f = fopen((char *)arg1,"r");

    printf("reading file %s\n", arg1);
    fscanf(f,"%d %d\n",&vert_count, &tri_count);
//    struct vert v[vert_count];
    printf("scanning %d verts and %d triangles\n", vert_count, tri_count);
    S->num_vert = (int)vert_count;
    //declaratino + initializtion
    //this call to malloc() means that this thing
    //we are declaring will persist beyond the scope of the 
    //function call...
    
    S->verts = malloc(vert_count * sizeof(struct vert));
    printf("sizeof S->verts at allocation time = %zu\n", vert_count * sizeof(struct vert));
    
    for(i=0; i < vert_count; i++){
        
        GLfloat px,py,pz,nx,ny,nz;
        
        char c;
        fscanf(f, "%c     %f     %f     %f     %f     %f     %f\n", &c, &px, &py, &pz, &nx, &ny, &nz);

        S->verts[i].v[0] = px;
    	S->verts[i].v[1] = py;
	    S->verts[i].v[2] = pz;

    	S->verts[i].n[0] = nx;
    	S->verts[i].n[1] = ny;
	    S->verts[i].n[2] = nz;
    }
    
    //for(i=0; i<vert_count; i++){
    //    printf("vert %02d: (%f, %f, %f)\n", i, S->verts[i].v[0], S->verts[i].v[1], S->verts[i].v[2]);
    //}

    S->triangles = malloc(tri_count * sizeof(struct triangle));
    S->num_tri = tri_count;
    printf("size of S->triangles at allocation time = %zu\n", sizeof(struct triangle)*S->num_tri);

    for(i=0; i<tri_count;i++){
        int t1,t2,t3;
        char c;
        fscanf(f, "%c %i %i %i\n", &c, &t1, &t2, &t3);
	
    	S->triangles[i].t[0] = t1;
	    S->triangles[i].t[1] = t2;
    	S->triangles[i].t[2] = t3;
        
        printf("got triangle with points %d %d %d\n", S->triangles[i].t[0], S->triangles[i].t[1], S->triangles[i].t[2]);

    }
    
    fclose(f);

        glGenBuffers (1, S->vbo);
        glGenBuffers (1, S->ebo);

        init_vbo(S);
    return S;
}

/* Release the given cube structure and all resources held by it.             */

void shape_delete(shape *S)
{
    assert(S);

    glDeleteBuffers (1, S->ebo);
    glDeleteBuffers (1, S->vbo);

    free(S);
}

/*----------------------------------------------------------------------------*/

/* Render the given cube structure.                                           */

void shape_render(shape *S)
{
    printf("begin shape_render(*S)\n");
    const size_t sz = sizeof (GLfloat);

    assert(S);

    /* Enable the necessary array pointers. */

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    {
        /* Bind the array pointers to the array buffer object. */

        glBindBuffer(GL_ARRAY_BUFFER,         S->vbo[0]);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, S->ebo[0]);
        {

            glVertexPointer(  3, GL_FLOAT, sz * 6, (GLvoid *) (     0));
            glNormalPointer(     GL_FLOAT, sz * 6, (GLvoid *) (sz * 3));
            glDrawElements(GL_TRIANGLES, 3* S->num_tri, GL_UNSIGNED_SHORT, 0);

        }
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ARRAY_BUFFER,         0);
    }
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}

/*----------------------------------------------------------------------------*/
