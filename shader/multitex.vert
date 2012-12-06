varying vec3 var_L;
varying vec3 var_N;
varying vec3 lightPos;
attribute vec3 tangent;



void main()
{
    vec3 vert = vec3(gl_ModelViewMatrix * gl_Vertex);
    var_L = normalize(gl_LightSource[0].position.xyz - vert);
    var_N = normalize(gl_NormalMatrix * gl_Normal);

    gl_TexCoord[0] = gl_MultiTexCoord0;
    gl_Position = ftransform();
}
