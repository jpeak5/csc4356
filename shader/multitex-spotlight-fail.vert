//Adapted from the Orange Book, v2, section 10.3
uniform float theta;
uniform float rho;
uniform float radius;

varying float D;
varying vec3  S;

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

    vec3 ep         = vec3(gl_ModelViewMatrix * gl_Vertex);     //eye position
    vec3 norm       = normalize(gl_NormalMatrix * gl_Normal);   //vertex mormal
    vec3 lV         = normalize(LightPosition - ep);            //light vector
    vec3 refV       = reflect(-lV, norm);                       //reflection vector
    vec3 vV         = normalize(-ep);                           //view vector

    float spec  = clamp(dot(refV, vV), 0.0, 1.0);
    spec        = pow(spec, 8.0);
    S           = vec3(spec);
    D           = max(dot(lV, norm), 0.0);
    TexCoord    = gl_MultiTexCoord0.st;
    gl_Position = ftransform();
}

