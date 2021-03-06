//Adapted from the Orange Book, v2, section 10.3
uniform sampler2D diffSamp;
uniform sampler2D spotSamp;
uniform sampler2D specular;
uniform sampler2D normal;
//uniform sampler2D EarthCloudGloss;

varying float D;
varying vec3  S;
varying vec2  TexCoord;

void main()
{
    vec3 diffuse = (texture2D(diffSamp, TexCoord).rgb * D);// + S * clouds.g) * (1.0 - clouds.r) +  clouds.r * D;
    vec3 color = diffuse;
    

    gl_FragColor = vec4(color, 1.0);
}

