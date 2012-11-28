//Adapted from the Orange Book, v2, section 11.6
uniform sampler2D diffSamp;
uniform sampler2D spotSamp;
uniform sampler2D specular;
uniform sampler2D normal;


varying vec3 LightDir;
varying vec3 EyeDir;
//uniform vec3 SurfaceColor; // = (0.7, 0.6, 0.18)
//uniform float BumpDensity; // = 16.0
//uniform float BumpSize; // = 0.15
//uniform float SpecularFactor; // = 0.5
void main()
{
    vec3 litColor;

    vec3 pN = (texture2D(normal, gl_TexCoord[0].xy).xyz); //perturbed normal
    vec3 diffuse = (texture2D(diffSamp, gl_TexCoord[0].xy).rgb);
    float f = 4.0; //arbitrary value
    vec3 normDelta = pN;// * f;
    litColor = diffuse * max(dot(normDelta, LightDir), 0.0);
    vec3 reflectDir = reflect(LightDir, normDelta);
    float spec = max(dot(EyeDir, reflectDir), 0.0);
    spec = pow(spec, 6.0);
    spec = 0.5*spec; //0.5 is arbitrary but could be set by a gloss map
    litColor = min(litColor + spec, vec3(1.0));
    gl_FragColor = vec4(litColor, 1.0);
}

