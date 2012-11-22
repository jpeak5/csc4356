void init_shaders(char **shader, int count);
void init_shader_vars();
void reload_shaders(char **shaders, int count);
void link_shaders();
void check_shader_linkage();
void checkCompile(GLuint shader);
GLuint loadVertShader(const char *vert_filename);
GLuint loadFragShader(const char *frag_filename);
char *load(const char *name);
GLuint program;

