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
const float DiffuseContribution = 1.0 - SpecularContribution;


void main()
{
    vec3 ecPosition = vec3(gl_ModelViewMatrix * gl_Vertex);

    //hack to construct a plausible light position
    float x,y,z;
    x = radius * cos(theta) * sin(rho);
    y = radius * sin(theta) * sin(rho);
    z = radius * cos(theta);

    var_L = normalize(gl_LightSource[0].position.xyz);
    var_N = normalize(gl_NormalMatrix * gl_Normal);
    vec3 lightVec = normalize(var_L - ecPosition);

    vec3 reflectVec = reflect(-lightVec, var_N);
    vec3 viewVec = normalize(-ecPosition);

    float diffuse = max(dot(lightVec, var_N), 0.0);
    float spec = 0.0;
    if (diffuse > 0.0)
    {
        spec = max(dot(reflectVec, viewVec), 0.0);
        spec = pow(spec, 16.0);
    }

    LightIntensity = DiffuseContribution * diffuse + SpecularContribution * spec;
    MCposition = gl_Vertex.xy;

    gl_TexCoord[0] = gl_MultiTexCoord0;
    gl_Position = ftransform();
}
