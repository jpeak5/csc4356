#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include "shader.h"

GLuint program;
/*----------------------------------------------------------------------------*/
void init_shaders(char **shader)
{
    GLuint vs;
    if(shader[2])
    {
        vs = loadVertShader(shader[2]);
    }

    GLuint fs;
    if(shader[3])
    {
        fs = loadFragShader(shader[3]);
    }
    checkCompile(fs);
    checkCompile(vs);
    link_shaders(fs,vs);
    check_shader_linkage();
    glUseProgram(program);
}
/*----------------------------------------------------------------------------*/
void link_shaders(GLuint frag_shader, GLuint vert_shader)
{
    program = glCreateProgram();
    glAttachShader(program, vert_shader);
    glAttachShader(program, frag_shader);
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
        fprintf(stderr, "OpenGL Program Error:\n%s", p);
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
        fprintf(stderr, "OpenGL Shader Error:\n%s", p);
        free(p);
    }

}
/*----------------------------------------------------------------------------*/

GLuint loadVertShader(const char *vert_filename){
    GLuint vert_shader = glCreateShader(GL_VERTEX_SHADER);
    GLchar *vert_text = load(vert_filename);
    glShaderSource (vert_shader, 1, (const GLchar **) &vert_text, 0);
    glCompileShader(vert_shader);
    free(vert_text);
    return vert_shader;
}

GLuint loadFragShader(const char *frag_filename){
    GLuint frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
    GLchar *frag_text = load(frag_filename);
    glShaderSource (frag_shader, 1, (const GLchar **) &frag_text, 0);
    glCompileShader(frag_shader);
    free(frag_text);
    return frag_shader;
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

