#include <stdio.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include "lib/shader.h"

#define FIXED_FUNC  1
#define PHONG       2
#define SIMPLE      3


void menu_handler(int choice)
{
    char * shaders[2];

    char * phong[2]     = {"shader/phong.vert", "shader/phong.frag"};
    char * simple[2]    = {"shader/simple_shdr.vert", "shader/simple_shdr.frag"}; 

    switch(choice)
    {
        case FIXED_FUNC:
            glUseProgram(0);
        break;

        case SIMPLE:
            reload_shaders(simple);
        break;

        case PHONG:
            reload_shaders(phong);
        break;
    }
}

void init_menu()
{
    glutCreateMenu(menu_handler);

    glutAddMenuEntry("Revert to Fixed Function", FIXED_FUNC);
    glutAddMenuEntry("Use simple shader", SIMPLE);
    glutAddMenuEntry("Use Phong", PHONG);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

