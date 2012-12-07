varying vec3 var_L;
varying vec3 var_N;
varying vec3 lightPos;
attribute vec3 tangent;
varying vec3 eyeVec;



void main()
{
    vec3 vert = vec3(gl_ModelViewMatrix * gl_Vertex);
    var_L = normalize(gl_LightSource[0].position.xyz);
    
    /**
     * build the components of a transformation matrix
     * for converting coordinates from object to tangent space
     */
    vec3 N = normalize(gl_NormalMatrix * gl_Normal);
    vec3 T = normalize(gl_NormalMatrix * tangent);
    vec3 B = normalize(cross(N, T));
    
    mat3 tbn = mat3(T,B,N);

    /**
     * Where we have previously passed the normal.
     * let us multiply it by the TBN first
     */
    var_N = normalize(tbn*N);
    var_L = normalize(tbn*var_L);

    eyeVec = normalize(-vert * tbn);

    gl_TexCoord[0] = gl_MultiTexCoord0;
    gl_Position = ftransform();
}
