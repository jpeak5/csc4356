//Adapted from the Orange Book, v2, section 11.6
uniform sampler2D diffSamp;
uniform sampler2D spotSamp;
uniform sampler2D specular;
uniform sampler2D normal;


varying vec3 Normal;
varying vec3 LightDir;
varying vec3 EyeDir;

void main()
{
    vec3 V  = EyeDir;
    vec3 L  = normalize(LightDir);
    
    vec3 N  = normalize(Normal);
    vec3 pN = (texture2D(normal, gl_TexCoord[0].xy).xyz); //perturbed normal
    vec3 pC = pN*2.0;
    pC.r = pC.r -1.0;
    pC.g = pC.g -1.0;
    pC.b = pC.b -1.0;

    vec3 D  = (texture2D(diffSamp, gl_TexCoord[0].xy).rgb);
  //vec4 D  = gl_FrontMaterial.diffuse;
    vec3 S  = (texture2D(specular, gl_TexCoord[0].xy).rgb); 

    vec3 pNorm = normalize(pN);
    vec3  reflectDir = reflect(LightDir, pNorm);
    float n = gl_FrontMaterial.shininess;

    float kd =     max(dot(pNorm, L), 0.0);
    float ks = pow(max(dot(EyeDir, reflectDir), 0.0), n); 

    vec3  rgb = D.rgb * kd + S.rgb * ks; // RGB channels
    float a   = 1.0; 
  //float a   = D.a; 

    gl_FragColor = vec4(rgb, a); 

}

