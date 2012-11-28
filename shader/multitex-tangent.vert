//Adapted from the Orange Book, v2, section 11.6
uniform float theta;
uniform float rho;
uniform float radius;

attribute vec3 tangent;


varying vec3 LightDir;
varying vec3 EyeDir;
uniform vec3 LightPosition;

void main()
{
    //hack to construct a plausible light position
    float x,y,z;
    x = radius * cos(theta) * sin(rho);
    y = radius * sin(theta) * sin(rho);
    z = radius * cos(theta);
    vec3 LightPosition = vec3(x,y,z);

    //feeble attempt at getting this arbitrary
    //light source coord into modelView space
    vec4 lp = vec4(LightPosition, 1.0);
    LightPosition = vec3(lp * gl_ModelViewMatrixTranspose);
    EyeDir = vec3(gl_ModelViewMatrix * gl_Vertex);

    gl_Position = ftransform();
    gl_TexCoord[0] = gl_MultiTexCoord0;
    
    vec3 n = normalize(gl_NormalMatrix * gl_Normal);
    vec3 t = normalize(gl_NormalMatrix * tangent);
    vec3 b = cross(n, t);
    vec3 v;
    
    v.x = dot(LightPosition, t);
    v.y = dot(LightPosition, b);
    v.z = dot(LightPosition, n);
    LightDir = normalize(v);

    v.x = dot(EyeDir, t);
    v.y = dot(EyeDir, b);
    v.z = dot(EyeDir, n);
    EyeDir = normalize(v);
}

