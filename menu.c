#include <stdio.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include "lib/shader.h"

#define FIXED_FUNC  1
#define PHONG       2
#define SIMPLE      3
#define BRICK       4


void menu_handler(int choice)
{

    char * phong[2]     = {"shader/phong.vert", "shader/phong.frag"};
    char * simple[2]    = {"shader/simple_shdr.vert", "shader/simple_shdr.frag"}; 
    char * brick[2]     = {"shader/brick.vert", "shader/brick.frag"}; 

    switch(choice)
    {
        case FIXED_FUNC:
            glUseProgram(0);
        break;

        case SIMPLE:
            reload_shaders(simple);
        break;

        case BRICK:
            reload_shaders(brick);
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
    glutAddMenuEntry("Use Brick", BRICK);
    glutAddMenuEntry("Use Phong", PHONG);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

