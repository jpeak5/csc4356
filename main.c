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
#include "shape.h"

GLdouble rotation_x;                                                           \
GLdouble rotation_y;                                                           \
GLdouble position_z;                                                           \


shape *S;

void startup(char *filename)
{
    printf("begin startup(%s)\n", filename);
    rotation_x = 0.0;                                                          \
    rotation_y = 0.0;                                                          \
    position_z = 5.0;                                                          \

    S = shape_create(filename);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
}

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
    printf("display()\n");
//    glutWireDodecahedron();
    shape_render(S);
    glutSwapBuffers();
}
    
void motion(int x, int y)                                                      \
{                                                                              \
    GLdouble nx = (GLdouble) x / glutGet(GLUT_WINDOW_WIDTH);                   \
    GLdouble ny = (GLdouble) y / glutGet(GLUT_WINDOW_HEIGHT);                  \
                                                                               \
    rotation_x =  90.0 * (2.0 * ny - 1.0);                                     \
    rotation_y = 180.0 * (2.0 * nx - 1.0);                                     \
                                                                               \
    glutPostRedisplay();                                                       \
    printf("just finished motion(%d, %d)\n", x, y);
}                                                                              \

/*----------------------------------------------------------------------------*/



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

    if (glewInit() == GLEW_OK)
    {
        startup(filename);
        glutMainLoop();
    }

    return (EXIT_SUCCESS);
}

