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


void init_textures()
{

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
    
    glActiveTexture(GL_TEXTURE0);
   
    
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

    P = plane_create(20);

    //create our spotlight
    S->Spot = obj_create("obj/spotlight.obj");

    S->radius = 40.0;

    //knowing this will help us grab a reference vert
    S->num_verts = obj_num_vert(S->Spot);

    //set the obj anchor vector
    //for later transformation 
    //into light source eye coord
    float *a;
    obj_get_vert_v(S->Spot, S->num_verts-1, a);
    a[3] = 0.0;

    init_textures();
    

    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
    GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat lmodel_ambient[] = { 0.01, 0.01, 0.01, 1.0 };


    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);
    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 2.0);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 1.0);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.5);

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 45.0);
    GLfloat spot_direction[] = { 0.0, -1.0, 0.0 };
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);


    glEnable(GL_LIGHTING) ;
    glEnable(GL_LIGHT0) ;
    glEnable(GL_DEPTH_TEST) ;

    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    {
        glTranslated(0.0,5.0,0.0);
        obj_render(S->Spot);
        GLfloat light_position[] = { 0.0, 1.0, 0.0, 1.0 };
        glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    }

    
    glClearColor(0.1f, 0.1f, 0.1f, 0.0f);

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




void set_spot()
{



    glPushMatrix();
    {

        glScalef(0.2,0.2,0.2);
        glRotated(S->rotation_x,0.0,1.0,0.0);
        glRotated(S->rotation_y,1.0,0.0,0.0);
        glTranslated(0.0, 6.0, S->radius);
        obj_render(S->Spot);
        /**
         * clues from the Red Book, 6ed.
         */
        glRotated(S->rotation_x,0.0,1.0,0.0);
        glRotated(S->rotation_y,1.0,0.0,0.0);
        glTranslated(0.0, 6.0, S->radius);
        GLfloat light_position[] = { 0.0, 1.0, 0.0, 1.0 };
        glLightfv(GL_LIGHT0, GL_POSITION, light_position);


        //get the current matrix, and use it
        //to determine the eye coordinates of
        //any point in the Spot object..
        //printf("anchor coord %d is {%f,%f,%f,%f}\n", S->num_verts-1, S->obj_anchor[0], S->obj_anchor[1], S->obj_anchor[2], S->obj_anchor[3]);

        double m[16];
        glGetDoublev(GL_MODELVIEW, m);




    }
    glPopMatrix();

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
            obj_render(O);
            set_spot();
            glScalef(0.2,0.2,0.2);
            
            
          
            GLdouble m[16];
          glGetDoublev(GL_MODELVIEW, m);
          GLdouble e[4];


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
        float ya = 0.9; // y acceleration 
        S->rotation_x = click_rotation_x + 360.0 * dx * zoom * xa;
        S->rotation_y = click_rotation_y + 360.0 * dy * zoom * ya;
                                                            
        if (S->rotation_x >  360.0) S->rotation_x  =  360.0;
        if (S->rotation_x < -360.0) S->rotation_x  = -360.0;
        if (S->rotation_y >  360.0) S->rotation_y -=  360.0;
        if (S->rotation_y < -360.0) S->rotation_y +=  360.0;

//        printf("function inputs are x: %d, y: %d\n",x,y);
//        printf("intermediate vars are cl_rot_x: %f cl_rot_y: %f\n", click_rotation_x, click_rotation_y);
//        printf("more intermediate vars are rot_x: %f rot_y: %f\n", rotation_x, rotation_y);
//        printf("even more intermediate vars are dx: %f dy: %f zoom: %f\n", dx, dy, zoom);
//        printf("function outputs are S->rotation_x: %f, S->rotation_y: %f\n",S->rotation_x,S->rotation_y);


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

