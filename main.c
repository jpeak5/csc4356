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
    GLdouble mv_location[4];
    GLdouble obj_anchor[4];
    float x;
    float y;
    float z;
    float rotation_x;
    float rotation_y;
    float radius;
    int num_verts;
    obj *Spot;

};

struct spotlight *S;

int menu;

plane *P;
obj *O;
obj *O13;


float spot_pos_x;
float spot_pos_y;
float spot_pos_z;


void init_textures()
{

    /*
    unsigned int mtl_spec = obj_get_mtrl_map(O, 0, OBJ_KS); 
    unsigned int mtl_diff = obj_get_mtrl_map(O, 0, OBJ_KD); 
    unsigned int mtl_norm = obj_get_mtrl_map(O, 0, OBJ_KA);
    */
    /*
    GLuint diff_tex = mtl_diff;
    GLuint spec_tex = mtl_spec;
    GLuint norm_tex = mtl_norm;
	*/
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
    glGenTextures(1, &spot);

    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_2D, spot);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, i, w, h, 0, e, t, p);


    free(p);

    /*
    GLuint texture = diff_tex;
    GLboolean in_use = glIsTexture(texture);

    if(in_use){
        printf("texture %u is in use\n", texture);
    }
    else
    {
        printf("texture %u is NOT in use\n", texture);
    }
    */
    
    /*
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, diff_tex);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, spec_tex);
    
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, norm_tex);
    */
    
    glActiveTexture(GL_TEXTURE0);
    
    GLint spotlight = glGetUniformLocation(program, "spotSamp");
    glUniform1i(spotlight, 4);

    GLint shine = glGetUniformLocation(program, "shiny");
    glUniform1i(shine, 3);

    GLint spec = glGetUniformLocation(program, "specular");
    glUniform1i(spec, 2);

    GLint norm = glGetUniformLocation(program, "normal");
    glUniform1i(norm, 1);

    GLint diff = glGetUniformLocation(program, "diffSamp");
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

    //create our spotlight
    S->Spot = obj_create("obj/spotlight.obj");

    S->radius = 90.0;

    //knowing this will help us grab a reference vert
    S->num_verts = obj_num_vert(S->Spot);

    //set the obj anchor vector
    //for later transformation 
    //into light source eye coord
    float *a;
    obj_get_vert_v(S->Spot, S->num_verts-1, a);
    a[3] = 0.0;
    S->obj_anchor[0] = (GLdouble)a[0];
    S->obj_anchor[1] = (GLdouble)a[1];
    S->obj_anchor[2] = (GLdouble)a[2];
    S->obj_anchor[3] = (GLdouble)a[3];
    printf("the coordinate of vert %d is {%f,%f,%f, %f}", S->num_verts-1,S->obj_anchor[0], S->obj_anchor[1], S->obj_anchor[2], S->obj_anchor[3]);


    init_textures();
    glBindAttribLocationARB(program, 6, "tangent");


    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_LIGHTING);
    //glEnable(GL_LIGHT0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    {
      glRotated(S->mv_location[0],S->mv_location[1], S->mv_location[2], 1.0);
        //glRotated(S->mv_location[0], S->mv_location[1], S->mv_location[2], 0.0);
      obj_render(S->Spot);
    }

    
    glClearColor(0.19f, 0.17f, 0.16f, 0.0f);

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
    }
}

/*----------------------------------------------------------------------------*/
static void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
}

/**
 * m - a gl matrix
 * o - the vector you'd like to transfor
 * t - the transformed vector
 */
void get_eye_coords(GLdouble m[16], GLdouble *v, GLdouble *w)
{
    w[0] = v[0]*m[0] + v[1]*m[4] + v[2]* m[8]  + v[3] *m[12];
    w[0] = v[0]*m[1] + v[1]*m[5] + v[2]* m[9]  + v[3] *m[13];
    w[0] = v[0]*m[2] + v[1]*m[6] + v[2]* m[10] + v[3] *m[14];
    w[0] = v[0]*m[3] + v[1]*m[7] + v[2]* m[11] + v[3] *m[15];
    //printf("the coordinate of vector TRANSFORMED is {%f,%f,%f,%f}", w[0], w[1], w[2], w[3]);
}

void set_spot_pos(float x, float y, float z)
{


    S->mv_location[0] = x;
    S->mv_location[1] = y;
    S->mv_location[2] = z;
    
}

void set_spot()
{



    glPushMatrix();
    {

        glScalef(0.2,0.2,0.2);
        glRotated(S->rotation_x,0.0,1.0,0.0);
        glRotated(S->rotation_y,1.0,0.0,0.0);
        glTranslated(0.0, 6.0, S->radius);

        set_spot_pos(S->rotation_x, -S->rotation_y, 1.0);

        obj_render(S->Spot);

        //get the current matrix, and use it
        //to determine the eye coordinates of
        //any point in the Spot object..
        //printf("anchor coord %d is {%f,%f,%f,%f}\n", S->num_verts-1, S->obj_anchor[0], S->obj_anchor[1], S->obj_anchor[2], S->obj_anchor[3]);

        double m[16];
        glGetDoublev(GL_MODELVIEW, m);

        //debug
        int i=0;
        for(i;i<16;i++)
        {
            //printf("value of m[%d]=%f\n", i, m[i]);
        }

        S->mv_location[0] = S->obj_anchor[0]*m[0] + S->obj_anchor[1]*m[4] + S->obj_anchor[2]* m[8]  + S->obj_anchor[3] *m[12];
        S->mv_location[1] = S->obj_anchor[0]*m[1] + S->obj_anchor[1]*m[5] + S->obj_anchor[2]* m[9]  + S->obj_anchor[3] *m[13];
        S->mv_location[2] = S->obj_anchor[0]*m[2] + S->obj_anchor[1]*m[6] + S->obj_anchor[2]* m[10] + S->obj_anchor[3] *m[14];
        S->mv_location[3] = S->obj_anchor[0]*m[3] + S->obj_anchor[1]*m[7] + S->obj_anchor[2]* m[11] + S->obj_anchor[3] *m[15];
        //printf("the coordinate of vector TRANSFORMED is {%f,%f,%f,%f}\n", S->mv_location[0], S->mv_location[1], S->mv_location[2], S->mv_location[3]);
        //get_eye_coords(m,S->obj_anchor,e);

        //S->mv_location = *e;

    }
    glPopMatrix();

    //use spherical geometry to approximate the light source position
    GLuint theta = glGetUniformLocation(program,"theta");
    GLuint rho   = glGetUniformLocation(program,"rho");
    GLuint radius= glGetUniformLocation(program,"radius");

    glUniform1f(theta,  S->rotation_x);
    glUniform1f(rho,    S->rotation_y);
    glUniform1f(radius, S->radius);

    //printf("passing uniforms: theta: %f rho: %f radius: %f\n",S->rotation_x, S->rotation_y, S->radius);

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

    glRotated(rotation_x, -1.0, 0.0, 0.0);
    glRotated(rotation_y, 0.0, 1.0, 0.0);
    glTranslated(-position_x, -position_y+1.0, -position_z);
		
    
    init_shader_vars();
	


        glPushMatrix();
        {
            //glDisable(GL_LIGHTING);
            plane_render(P);
            glTranslated(0.0, 1.0, 0.0);
            //obj_render(O13);
            obj_render(O);
            set_spot();
          GLdouble m[16];
          glGetDoublev(GL_MODELVIEW, m);
          GLdouble e[4];

          //get_eye_coords(m, S->mv_location, e);

          //glEnable(GL_LIGHTING);
        }
        glPopMatrix();
        double m[16];
        glGetDoublev(GL_MODELVIEW, m);

        //debug
        int i=0;
        for(i;i<16;i++)
        {
            //printf("value of final matrix m[%d]=%f\n", i, m[i]);
        }

    glutSwapBuffers();
}

/*----------------------------------------------------------------------------*/
void passive_motion(int x, int y)
{

}

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
        float xa = 2.0; // x acceleration 
        float ya = 0.5; // y acceleration 
        S->rotation_x = click_rotation_x + 360.0 * dx * zoom * xa;
        S->rotation_y = click_rotation_y + 360.0 * dy * zoom * ya;
                                                            
        if (S->rotation_x >  360.0) S->rotation_x  =  360.0;
        if (S->rotation_x < -360.0) S->rotation_x  = -360.0;
        if (S->rotation_y >  360.0) S->rotation_y -=  360.0;
        if (S->rotation_y < -360.0) S->rotation_y +=  360.0;

        printf("function inputs are x: %d, y: %d\n",x,y);
        printf("intermediate vars are cl_rot_x: %f cl_rot_y: %f\n", click_rotation_x, click_rotation_y);
        printf("more intermediate vars are rot_x: %f rot_y: %f\n", rotation_x, rotation_y);
        printf("even more intermediate vars are dx: %f dy: %f zoom: %f\n", dx, dy, zoom);
        printf("function outputs are S->rotation_x: %f, S->rotation_y: %f\n",S->rotation_x,S->rotation_y);


    }

    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
    //get the mouse position in terms of the window
    //value will be in the range [-1.0, 1.0]
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
    //printf("Scroll %s At %d %d\n", (button == 3) ? "Up" : "Down", x, y);

    //keyboard_dz -= 1.0;
    }else{  // normal button event
    //printf("Button %s At %d %d\n", (state == GLUT_DOWN) ? "Down" : "Up", x, y);
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

    S->mv_location[0] = spot_pos_x;
    S->mv_location[1] = spot_pos_y;
    S->mv_location[2] = spot_pos_z;

    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(1024, 800);
    glutInit(&argc, argv);

    glutCreateWindow(argv[1]);

    glutPassiveMotionFunc(passive_motion);
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

