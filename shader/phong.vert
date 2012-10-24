varying vec3 var_L;
varying vec3 var_N;

void main()
{
    var_L = gl_LightSource[0].position.xyz; // Light vector
    var_N = gl_NormalMatrix * gl_Normal;    // Normal vector 

    gl_Position = ftransform();             // Vertex position 
}

