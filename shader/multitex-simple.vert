uniform float theta;
uniform float rho;
uniform float radius;

varying float D;
varying vec3 S;
varying vec2 TexCoord;

void main()

{

    //hack to construct a plausible light position
    float x,y,z;
    x = radius * cos(theta) * sin(rho);
    y = radius * sin(theta) * sin(rho);
    z = radius * cos(theta);

    vec3 LightPosition = vec3(x,y,z);

    vec3 ecPosition = vec3(gl_ModelViewMatrix * gl_Vertex);
    vec3 tnorm      = normalize(gl_NormalMatrix * gl_Normal);
    vec3 lightVec   = normalize(LightPosition - ecPosition);
    vec3 reflectVec = reflect(-lightVec, tnorm);
    vec3 viewVec    = normalize(-ecPosition);

    float spec  = clamp(dot(reflectVec, viewVec), 0.0, 1.0);
    spec        = pow(spec, 8.0);
    S           = vec3(spec) * vec3(1.0, 0.941, 0.898) * 0.3;
    D           = max(dot(lightVec, tnorm), 0.0);
    TexCoord    = gl_MultiTexCoord0.st;
    gl_Position = ftransform();
}

