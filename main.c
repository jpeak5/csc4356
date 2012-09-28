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

GLdouble rotation_x;
GLdouble rotation_y;
GLdouble position_z;
GLdouble scale;

int      click_button;
GLdouble click_rotation_x;
GLdouble click_rotation_y;
GLdouble click_scale;                                                          \
GLdouble click_nx;
GLdouble click_ny;


shape *S;

void startup(char *filename)
{
    rotation_x = 0.0;                                                          \
    rotation_y = 0.0;                                                          \
    position_z = 5.0;                                                          \
    scale      = 1.0;

    S = shape_create(filename);

    glEnable(GL_NORMALIZE);                                                    \
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
}

static void reshape(int w, int h)
{
    GLdouble tb = 0.5;
    GLdouble lr = 0.5 * (GLdouble) w / (GLdouble) h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-lr, lr, -tb, tb, 1.0, 100.0);

    glViewport(0, 0, w, h);
}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //glEnable(GL_DEPTH_TEST);
    //glEnable(GL_LIGHTING);
    //glEnable(GL_LIGHT0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslated(0.0, 0.0, -position_z);
    glRotated(rotation_x, 1.0, 0.0, 0.0);
    glRotated(rotation_y, 0.0, 1.0, 0.0);
    glScaled(scale, scale, scale);                                             \

    shape_render(S);
    glutSwapBuffers();
}

void motion(int x, int y)
{
    GLdouble nx = (GLdouble) x / glutGet(GLUT_WINDOW_WIDTH);
    GLdouble ny = (GLdouble) y / glutGet(GLUT_WINDOW_HEIGHT);

    GLdouble dx = nx - click_nx;
    GLdouble dy = ny - click_ny;

    if (click_button == GLUT_LEFT_BUTTON)
    {
        rotation_x = click_rotation_x +  90.0 * dy;
        rotation_y = click_rotation_y + 180.0 * dx;

        if (rotation_x >   90.0) rotation_x  =  90.0;
        if (rotation_x <  -90.0) rotation_x  = -90.0;
        if (rotation_y >  180.0) rotation_y -= 360.0;
        if (rotation_y < -180.0) rotation_y += 360.0;
    }
    if (click_button == GLUT_RIGHT_BUTTON)
    {
        scale = click_scale - dy;                                              \
    }

    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
    click_nx = (GLdouble) x / glutGet(GLUT_WINDOW_WIDTH);
    click_ny = (GLdouble) y / glutGet(GLUT_WINDOW_HEIGHT);

    click_button     = button;
    click_rotation_x = rotation_x;
    click_rotation_y = rotation_y;
    click_scale      = scale;
}
    

/*----------------------------------------------------------------------------*/
int main(int argc, char** argv) {

    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(640, 480);
    glutInit(&argc, argv);

    glutCreateWindow(argv[0]);

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMotionFunc(motion);
    glutMouseFunc(mouse);

    char *filename = argv[1]; 

    if (glewInit() == GLEW_OK)
    {
        startup(filename);
        glutMainLoop();
    }

    return (EXIT_SUCCESS);
}

