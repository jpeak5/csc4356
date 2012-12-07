uniform sampler2D diffuse;
uniform sampler2D specular;
uniform sampler2D normal;
uniform sampler2D shiny;
uniform sampler2D spotlight;
varying vec3 var_L;
varying vec3 var_N;
varying float LightIntensity;
varying vec2 MCposition;
varying vec3 eyeVec;


void main()
{
    vec3 V   = vec3(0.0,0.0,1.0);                       //view vector (always in the pos Z)
    vec3 L   = var_L;                                   //incoming light vector
    vec3 N   = var_N;                                   //surface normal
    vec3 H   = normalize(L + V);                        //half-angle

    vec4 D   = texture2D(diffuse,  gl_TexCoord[0].xy);  //diffuse color
    vec4 S   = texture2D(specular, gl_TexCoord[0].xy);  //specular light color
    vec4 Z   = texture2D(shiny,    gl_TexCoord[0].xy);  //gloss map color?
    vec4 T   = texture2D(normal,   gl_TexCoord[0].xy);  //normal map

    //vec4 S   = gl_FrontMaterial.specular;
    //float n  = gl_FrontMaterial.shininess;
    float n  = 100.0;

    /*
     * kd will be used to calculate the intensity of the diffuse light
     * as perceived by the viewer.
     * The dot product of the light vector L and the surface normal N
     * if this is a right angle,   the multiplier is 0.0
     * if the angles are the same, the multiplier is 1.0 
     * a value of 1.0 corresponds to the situation where the viewer and light source
     * share the same position; in this case, the viewer experiences the full
     * intensity of the diffuse reflected color
     */
    float kd =     max(dot(N, L), 0.0);                 //lambert


    vec3 E = normalize(eyeVec);
    vec3 R = reflect(-L, N);

    float ks = pow(max(dot(N, H), 0.0), n);
    //float ks = pow(max(dot(R, E), 0.0), n);

    //D = vec4(0.0,1.0,0.0, 1.0);
    vec3  rgb = D.rgb * kd + S.rgb * ks;
    float a   = D.a;													//alpha value...1.0
		
		

    //vec4 spotColor = vec4(1.0,0.0,0.0,1.0);       //debug value
    //vec4 spotColor = texture2D(spotlight, gl_TexCoord[0].xy);
    //vec3 final_color = rgb * spotColor.rgb + color.rgb;
    gl_FragColor = vec4(rgb, a);

}
