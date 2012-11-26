/* 
 * File:   main.c
 * Author: jpeak5
 *
 * Created on September 11, 2012, 6:39 PM
 */

#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <assert.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include <math.h>
#include "util3d/key.h"
#include "util3d/obj.h"
#include "util3d/plane.h"
#include "util3d/image.h"
#include "lib/shader.h"
#include "menu.h"

#define KEY_P 'p'

int      last_time;

GLdouble zoom;                                                                 \
GLdouble rotation_x;
GLdouble rotation_y;
GLdouble position_x;
GLdouble position_y;
GLdouble position_z;

GLdouble keyboard_dx;
GLdouble keyboard_dy;
GLdouble keyboard_dz;

int      click_button;                                                         \
GLdouble click_zoom;                                                           \
GLdouble click_rotation_x;
GLdouble click_rotation_y;
GLdouble click_nx;
GLdouble click_ny;

struct spotlight 
{
    float x;
    float y;
    float z;
};

struct spotlight *S;
struct spotlight *LS;
int menu;

int spot_toggle = 0;
plane *P;
obj *O;
obj *O13;
obj *Spot;

float spot_pos_x = 0.0;
float spot_pos_y = 10.0;
float spot_pos_z = 0.0;


void init_textures()
{

    unsigned int mtl_spec = obj_get_mtrl_map(O, 0, OBJ_KS); 
    unsigned int mtl_diff = obj_get_mtrl_map(O, 0, OBJ_KD); 
    unsigned int mtl_norm = obj_get_mtrl_map(O, 0, OBJ_KA);

    GLuint diff_tex = mtl_diff;
    GLuint spec_tex = mtl_spec;
    GLuint norm_tex = mtl_norm;
		/*
		 * get an image texture for the spotlight
		 */
    int w, h, c, b;
    void *p = image_read("spotlight.png", &w, &h, &c, &b);
    int i = image_internal_form(c, b);
    int e = image_external_form(c);
    int t = image_external_type(b);
    image_flip(w, h, c, b, p);
    
    GLuint spot;
    glActiveTexture(GL_TEXTURE3);
    glTexImage2D(GL_TEXTURE_2D, 0, i, w, h, 0, e, t, p);
    glBindTexture(GL_TEXTURE_2D, spot);   

    free(p);

    GLuint texture = diff_tex;
    GLboolean in_use = glIsTexture(texture);

    if(in_use){
        printf("texture %u is in use\n", texture);
    }
    else
    {
        printf("texture %u is NOT in use\n", texture);
    }

    /*
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, diff_tex);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, spec_tex);
    
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, norm_tex);
    */
    
    glActiveTexture(GL_TEXTURE0);
    
    GLint norm = glGetUniformLocation(program, "normal");
    glUniform1i(norm, 4);

    GLint spec = glGetUniformLocation(program, "specular");
    glUniform1i(spec, 1);

    GLint diff = glGetUniformLocation(program, "diffuse");
    glUniform1i(diff, 0);
    
}

void startup(char *filename)
{
    last_time   = 0;

    zoom        = 0.5;                                                         \
    rotation_x  = 0.0;
    rotation_y  = 0.9;

    position_x  = 0.0;
    position_y  = 2.0;
    position_z  = 15.0;
    	
    keyboard_dx = 0.0;
    keyboard_dy = 0.0;
    keyboard_dz = 0.0;
    

    O = obj_create(filename);
    //O13 = obj_create("obj/swept.obj");
    P = plane_create(20);

    Spot = obj_create("obj/spotlight.obj");

    init_textures();
    glBindAttribLocationARB(program, 6, "tangent");


    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_LIGHTING);
    //glEnable(GL_LIGHT0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    {
      glRotated(0.0,1.0,0.0,1.0);
      glTranslated(S->x,S->y, S->z);
        //glRotated(S->x, S->y, S->z, 0.0);
      obj_render(Spot);
    }

    
    glClearColor(0.19f, 0.17f, 0.16f, 0.0f);

}


void set_spot_pos(int x, int y)
{
        S->x = -10.0;
        S->y = 10.0;
        S->z = 2.0;
        printf("\nincoming mouse coords x: %d, y: %d\nSetting spot values x: %f, y: %f\n",x,y,S->x,S->y);
        LS = S;
    
}
/*----------------------------------------------------------------------------*/

void keyboardup(unsigned char key, int x, int y)
{
    switch (key)
    {
        case KEY_L: keyboard_dx += 1.0; break;
        case KEY_R: keyboard_dx -= 1.0; break;
        case KEY_D: keyboard_dy += 1.0; break;
        case KEY_U: keyboard_dy -= 1.0; break;
        case KEY_F: keyboard_dz += 1.0; break;
        case KEY_B: keyboard_dz -= 1.0; break;
        case KEY_X: 
                    glUseProgram(0);
                    break;
    }
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case KEY_L: keyboard_dx -= 1.0; break;
        case KEY_R: keyboard_dx += 1.0; break;
        case KEY_D: keyboard_dy -= 1.0; break;
        case KEY_U: keyboard_dy += 1.0; break;
        case KEY_F: keyboard_dz -= 1.0; break;
        case KEY_B: keyboard_dz += 1.0; break;
        case KEY_P: 
                spot_toggle = (spot_toggle == 1) ? 0 : 1;
                printf("spot toggle value set to %d", spot_toggle);
    }
}

/*----------------------------------------------------------------------------*/
static void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
}

static void display(void)
{
    GLdouble tb = zoom;                                                        \
    GLdouble lr = zoom * glutGet(GLUT_WINDOW_WIDTH)                            \
                       / glutGet(GLUT_WINDOW_HEIGHT);                          \

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);                                               \
    glLoadIdentity();                                                          \
    glFrustum(-lr, lr, -tb, tb, 1.0, 100.0);                                   \

    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    GLuint lightLoc = glGetUniformLocation(program, "lightPos");
    glUniform3f(lightLoc, S->x, S->y, S->z);

    glRotated(rotation_x, -1.0, 0.0, 0.0);
    glRotated(rotation_y, 0.0, 1.0, 0.0);
    glTranslated(-position_x, -position_y+1.0, -position_z);
		
    init_shader_vars();
	


        glPushMatrix();
        {
          glRotated(0.0,1.0,0.0,1.0);
          glTranslated(S->x,S->y, S->z);
            //glRotated(S->x, S->y, S->z, 0.0);
          obj_render(Spot);
        }
        glPopMatrix();
        glPushMatrix();
        {
            //glDisable(GL_LIGHTING);
            //plane_render(P);
            glTranslated(0.0, 1.0, 0.0);
            //obj_render(O13);
            obj_render(O);

            //glEnable(GL_LIGHTING);
        }
        glPopMatrix();

    glutSwapBuffers();
}

/*----------------------------------------------------------------------------*/

void motion(int x, int y)
{
    GLdouble nx = (GLdouble) x / glutGet(GLUT_WINDOW_WIDTH);
    GLdouble ny = (GLdouble) y / glutGet(GLUT_WINDOW_HEIGHT);

    GLdouble dx = nx - click_nx;
    GLdouble dy = ny - click_ny;

    if (click_button == GLUT_LEFT_BUTTON)                                      \
    {                                                                          \
        rotation_x = click_rotation_x +  90.0 * dy * zoom;                     \
        rotation_y = click_rotation_y + 180.0 * dx * zoom;                     \
                                                                               \
        if (rotation_x >   90.0) rotation_x  =  90.0;                          \
        if (rotation_x <  -90.0) rotation_x  = -90.0;                          \
        if (rotation_y >  180.0) rotation_y -= 360.0;                          \
        if (rotation_y < -180.0) rotation_y += 360.0;                          \
    }                                                                          \
    if (click_button == GLUT_RIGHT_BUTTON)                                     \
    {                                                                          \
        zoom = click_zoom + dy;                                                \
                                                                               \
        if (zoom < 0.01) zoom = 0.01;                                          \
    }
    if (click_button == GLUT_MIDDLE_BUTTON)
    {
        S->x = click_rotation_x +  90.0 * dy * zoom;                     \
        S->z = click_rotation_y + 180.0 * dx * zoom;                     \
                                                                               \
        if (S->x >   90.0) S->x  =  90.0;                          \
        if (S->x <  -90.0) S->x  = -90.0;                          \
        if (S->z >  180.0) S->z -= 360.0;                          \
        if (S->z < -180.0) S->z += 360.0;                          \
        
    }
    
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
    click_nx = (GLdouble) x / glutGet(GLUT_WINDOW_WIDTH);
    click_ny = (GLdouble) y / glutGet(GLUT_WINDOW_HEIGHT);

    click_button     = button;                                                 \
    click_zoom       = zoom;                                                   \
    click_rotation_x = rotation_x;
    click_rotation_y = rotation_y;

//Wheel reports as button 3(scroll up) and button 4(scroll down)
if ((button == 3) || (button == 4)) // It's a wheel event
{
    //http://stackoverflow.com/questions/14378/using-the-mouse-scrollwheel-in-glut
    // Each wheel event reports like a button click, GLUT_DOWN then GLUT_UP
    if (state == GLUT_UP) return; // Disregard redundant GLUT_UP events
    printf("Scroll %s At %d %d\n", (button == 3) ? "Up" : "Down", x, y);

    //keyboard_dz -= 1.0;
    }else{  // normal button event
    printf("Button %s At %d %d\n", (state == GLUT_DOWN) ? "Down" : "Up", x, y);
    //keyboard_dz += 1.0;
    }
}
    

/*----------------------------------------------------------------------------*/
void idle(void)
{
    GLdouble M[16], speed = 3.0;

    int curr_time = glutGet(GLUT_ELAPSED_TIME);

    GLdouble dt = (curr_time - last_time) / 1000.0;
    GLdouble kx = keyboard_dx * dt * speed;
    GLdouble ky = keyboard_dy * dt * speed;
    GLdouble kz = keyboard_dz * dt * speed;

    last_time = curr_time;

    glGetDoublev(GL_MODELVIEW_MATRIX, M);

    position_x += kx * M[ 0] + ky * M[ 1] + kz * M[ 2];
    position_y += kx * M[ 4] + ky * M[ 5] + kz * M[ 6];
    position_z += kx * M[ 8] + ky * M[ 9] + kz * M[10];

    glutPostRedisplay();
}



/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/

int main(int argc, char** argv) {
		
    S = malloc(sizeof(struct spotlight));
    LS = malloc(sizeof(struct spotlight));

    S->x = spot_pos_x;
    S->y = spot_pos_y;
    S->z = spot_pos_z;

    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(1024, 800);
    glutInit(&argc, argv);

    glutCreateWindow(argv[1]);

    glutKeyboardUpFunc(keyboardup);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMotionFunc(motion);
    glutMouseFunc(mouse);
    glutIdleFunc(idle);
    
    glutIgnoreKeyRepeat(1);

    char *filename = argv[1]; 
    char *shader[argc-2];
    int count;
    
    

    switch(argc)
    {
        case 1:
            printf("you must provide an input file. \nfail. \nexit.\n");
            return (EXIT_FAILURE);
        break;

        case 2:
            printf("Gimme some shaders!\n");
            return (EXIT_FAILURE);
        break;

        case 3:
            shader[0]   = argv[2];
            count       = 1;
        break;
    
        case 4:
            shader[0]   = argv[2];
            shader[1]   = argv[3];
            count       = 2;
        break;
    }

    if (glewInit() == GLEW_OK)
    {
        startup(filename);
        init_shaders(shader,count);
        init_menu();
        glutMainLoop();
    }

    return (EXIT_SUCCESS);
}

