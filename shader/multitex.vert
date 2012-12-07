varying vec3 var_L;
varying vec3 var_N;
varying vec3 lightPos;
attribute vec3 tangent;
varying vec3 eyeVec;



void main()
{
    vec3 vert = vec3(gl_ModelViewMatrix * gl_Vertex);
    var_L = normalize(gl_LightSource[0].position.xyz - vert);
    
    vec3 N = normalize(gl_NormalMatrix * gl_Normal);
    vec3 T = normalize(gl_NormalMatrix * tangent);
    vec3 B = normalize(cross(N, T));
    
    
    eyeVec = -vert;

    gl_TexCoord[0] = gl_MultiTexCoord0;
    gl_Position = ftransform();
}
