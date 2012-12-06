varying vec3 var_L;
varying vec3 var_N;
varying vec4 var_I;
uniform float theta;
uniform float rho;
uniform float radius;
varying float LightIntensity;
varying vec2 MCposition;
varying vec3 lightPos;
//attribute vec3 tangent;
const float SpecularContribution = 0.3;
const float DiffuseContribution = 0.5 - SpecularContribution;


void main()
{
    vec3 eye_coord = vec3(gl_ModelViewMatrix * gl_Vertex);

    var_L = normalize(gl_LightSource[0].position.xyz);
    var_N = normalize(gl_NormalMatrix * gl_Normal);
    vec3 light_dir = normalize(var_L - eye_coord);


    gl_TexCoord[0] = gl_MultiTexCoord0;
    gl_Position = ftransform();
}
