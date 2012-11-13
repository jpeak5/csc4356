void init_shaders(char **shader);
void init_shader_vars();
void reload_shaders(char **shaders);
void link_shaders(GLuint frag_shader, GLuint vert_shader);
void check_shader_linkage();
void checkCompile(GLuint shader);
GLuint loadVertShader(const char *vert_filename);
GLuint loadFragShader(const char *frag_filename);
char *load(const char *name);
