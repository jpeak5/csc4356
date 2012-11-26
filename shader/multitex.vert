varying vec3 var_L;
varying vec3 var_N;
uniform vec3 lightPos;
//attribute vec3 tangent;

void main()
{
    //var_L = gl_LightSource[0].position.xyz;
    var_L = lightPos.xyz * gl_ModelViewMatrix;
    var_N = gl_NormalMatrix * gl_Normal;

		//printf("light source position = x: %f y: %f z: %f", var_L.x, var_L.y, var_L.z);
    gl_TexCoord[0] = gl_MultiTexCoord0;
    gl_Position = ftransform();
}
