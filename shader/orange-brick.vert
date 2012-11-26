uniform vec3 lightPos;
const float SpecularContribution = 0.3;
const float DiffuseContribution = 1.0 - SpecularContribution;
varying float LightIntensity;
varying vec2 MCposition;
void main()
{

    vec4 lightPos_n = normalize(vec4(lightPos.xyz, 0.0));

    vec4 lp = gl_ModelViewMatrix * lightPos_n;

    //vec3 ecPosition = vec3(gl_ModelViewProjectionMatrixInverse * gl_Vertex); 
    vec3 ecPosition = vec3(lightPos); 

    vec3 tnorm      = normalize(gl_NormalMatrix * gl_Normal); 
    vec3 lightVec   = normalize(lp.xyz - ecPosition); 
    vec3 reflectVec = reflect(-lightVec, tnorm); 
    vec3 viewVec    = normalize(-ecPosition); 
    float diffuse   = max(dot(lightVec, tnorm), 0.0); 
    float spec      = 0.0; 

    if (diffuse > 0.0)
    {
        spec = max(dot(reflectVec, viewVec), 0.0);
        spec = pow(spec, 16.0);
    }

    LightIntensity = DiffuseContribution * diffuse +
    SpecularContribution * spec;
    MCposition  = gl_Vertex.xy; 
    gl_Position = ftransform(); 
}
    



