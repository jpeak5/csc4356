uniform sampler2D ;
uniform sampler2D EarthNight;
uniform sampler2D specular;
varying float D;
varying vec3 Specular;
varying vec2 TexCoord;
void main()
{
    // Monochrome cloud cover value will be in clouds.r
    // Gloss value will be in clouds.g
    // clouds.b will be unused
    vec2 clouds = texture2D(specular, TexCoord).rg;
    vec3 daytime = (texture2D(EarthDay, TexCoord).rgb * D + Specular * clouds.g) * (1.0 - clouds.r) + clouds.r * D;
    vec3 nighttime = texture2D(EarthNight, TexCoord).rgb * (1.0 - clouds.r) * 2.0;
    vec3 color = daytime;
    if (D < 0.1)
        color = mix(nighttime, daytime, (D + 0.1) * 5.0);
    gl_FragColor = vec4(color, 1.0);
}

