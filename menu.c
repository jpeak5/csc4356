#include <stdio.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include "lib/shader.h"

#define FIXED_FUNC  1
#define PHONG       2
#define SIMPLE      3
#define BRICK       4
#define DIFFUSE     5
#define MULTITEX    6


void menu_handler(int choice)
{

    char * phong[2]     = {"shader/phong.vert", "shader/phong.frag"};
    char * simple[2]    = {"shader/simple_shdr.vert", "shader/simple_shdr.frag"}; 
    char * brick[2]     = {"shader/brick.vert", "shader/brick.frag"}; 
    char * diffuse[1]   = {"shader/diffuse.vert"}; 
    char * multitex[2]  = {"shader/multitex.vert", "shader/multitex.frag"}; 

    switch(choice)
    {
        case FIXED_FUNC:
            glUseProgram(0);
        break;

        case SIMPLE:
            reload_shaders(simple,2);
        break;

        case BRICK:
            reload_shaders(brick,2);
        break;

        case PHONG:
            reload_shaders(phong,2);
        break;

        case DIFFUSE:
            reload_shaders(diffuse,1);
        break;

        case MULTITEX:
            reload_shaders(multitex,2);
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
    glutAddMenuEntry("Use diffuse", DIFFUSE);
    glutAddMenuEntry("Use multitex", MULTITEX);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

