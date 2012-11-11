#include <GL/glew.h>
#include <GL/glut.h>
#define FIXED_FUNC 1


void menu_handler(int choice)
{
    switch(choice)
    {
        case FIXED_FUNC:
        glUseProgram(0);
        break;

    }
}

void init_menu()
{
    int menu;

    menu = glutCreateMenu(menu_handler);

    glutAddMenuEntry("Revert to Fixed Function", FIXED_FUNC);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

