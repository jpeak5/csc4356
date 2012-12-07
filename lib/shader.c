#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include <time.h>
#include "shader.h"

GLuint vert_shader;
GLuint frag_shader;


GLuint uniform_time;

//brick colors
GLuint mortar_color;
GLuint test_color;
GLuint brick_color;
GLuint brick_size;
GLuint brick_frac;

/*----------------------------------------------------------------------------*/
void init_shader_vars()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);

    GLuint uniform_time = glGetUniformLocation(program, "time");
    glUniform1f(uniform_time, tv.tv_usec/100000);
    glUniform1f(uniform_time, tv.tv_usec/100000);

    //brick colors
    GLuint mortar_color =   glGetUniformLocation(program, "mortar_color");
    GLuint test_color   =   glGetUniformLocation(program, "test_color");
    GLuint brick_color  =   glGetUniformLocation(program, "brick_color");
    GLuint brick_size   =   glGetUniformLocation(program, "brick_size");
    GLuint brick_frac   =   glGetUniformLocation(program, "brick_frac");

    glUniform3f(test_color, 1.0, 1.0, 1.0);
    glUniform3f(mortar_color, 0.05, 1.0, 0.05);
    glUniform3f(brick_color, 0.1, 0.1, 0.1);
    glUniform2f(brick_size, 0.6, 0.2);
    glUniform2f(brick_frac, 0.9, 0.9);


}

/*----------------------------------------------------------------------------*/
void init_shaders(char **shader, int count)
{
    init_shader_vars();


    printf("init_shaders has been passed %d shaders in its input param\n", count);

    if(count ==1)
    {
        vert_shader = loadVertShader(shader[0]);
        checkCompile(vert_shader);
    }

    if(count ==2)
    {
        assert(shader[1] != NULL);
        printf("loading second shader");
        
        vert_shader = loadVertShader(shader[0]);
        checkCompile(vert_shader);

        frag_shader = loadFragShader(shader[1]);
        checkCompile(frag_shader);
    }

    link_shaders();

    check_shader_linkage();
    
    glUseProgram(program);
}
/*----------------------------------------------------------------------------*/
void reload_shaders(char **shaders, int count)
{
    glUseProgram(0);
    init_shaders(shaders, count);
}
/*----------------------------------------------------------------------------*/
void link_shaders()
{
    program = glCreateProgram();
glBindAttribLocationARB(program, 6, "tangent");//after prog is created
    if(vert_shader > 0)
    {
        assert(vert_shader > 0);
        glAttachShader(program, vert_shader);
    }
    
    if(frag_shader > 0)
    {
        assert(frag_shader > 0);
        glAttachShader(program, frag_shader);
    }
    
    glLinkProgram(program);
}
/*----------------------------------------------------------------------------*/
void check_shader_linkage()
{
    GLchar *p;
    GLint s, n;

    glGetProgramiv(program, GL_LINK_STATUS,&s);
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &n);

    if ((s == 0) && (p = (GLchar *) calloc(n + 1, 1)))
    {
        glGetProgramInfoLog(program, n, NULL, p);
        fprintf(stderr, "OpenGL Program LINK Error:\n%s", p);
        free(p);
    }
}
/*----------------------------------------------------------------------------*/
void checkCompile(GLuint shader)
{
    GLchar *p;
    GLint s, n;

    glGetShaderiv(shader, GL_COMPILE_STATUS, &s);
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &n);

    if ((s == 0) && (p = (GLchar *) calloc(n + 1, 1)))
    {
        glGetShaderInfoLog(shader, n, NULL, p);
        fprintf(stderr, "OpenGL Shader Compilation Error:\n%s", p);
        free(p);
    }

}
/*----------------------------------------------------------------------------*/

GLuint loadVertShader(const char *vert_filename){
    assert(vert_filename);
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    GLchar *vert_text = load(vert_filename);
    glShaderSource (vs, 1, (const GLchar **) &vert_text, 0);
    glCompileShader(vs);
    free(vert_text);
    return vs;
}

GLuint loadFragShader(const char *frag_filename){
    assert(frag_filename);
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    GLchar *frag_text = load(frag_filename);
    glShaderSource (fs, 1, (const GLchar **) &frag_text, 0);
    glCompileShader(fs);
    free(frag_text);
    return fs;
}
/*----------------------------------------------------------------------------*/
char *load(const char *name)
{
    FILE *fp = 0;
    void *p = 0;
    size_t n = 0;
    if ((fp = fopen(name, "rb")))
    {
        if (fseek(fp, 0, SEEK_END) == 0)
            if ((n = (size_t) ftell(fp)))
                if (fseek(fp, 0, SEEK_SET) == 0)
                    if ((p = calloc(n + 1, 1)))
                        fread(p, 1, n, fp);
        fclose(fp);
    }
    return p;
}

