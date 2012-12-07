uniform sampler2D diffSamp;
uniform sampler2D specular;
uniform sampler2D normal;
uniform sampler2D shiny;
uniform sampler2D spotlight;
varying vec3 var_L;
varying vec3 var_N;
varying vec3 eyeVec;


void main()
{
    vec3 V   = normalize(eyeVec);                       //view vector 
    vec3 L   = normalize(var_L);                        //incoming light vector
    vec3 H   = normalize(L + V);                        //half-angle
    vec4 D   = texture2D(diffSamp,  gl_TexCoord[0].xy);  //diffuse color
    vec4 S   = texture2D(specular, gl_TexCoord[0].xy);  //specular light color
    vec3 N   = texture2D(normal,   gl_TexCoord[0].xy).rgb;  //normal map
//    vec4 Z   = texture2D(shiny,    gl_TexCoord[0].xy);  //gloss map color?
    
    N = N*2.0 - 1.0;   //maps the range [0.0 - 1.0] => [-1.0, 1.0] 

    //vec4 S   = gl_FrontMaterial.specular;
    //float n  = gl_FrontMaterial.shininess;
    float n    = 8.0;

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
   
    vec3  R  = reflect(-L, N);

    float kd =     max(dot(N, L), 0.0);                 //lambert
    float ks = pow(max(dot(R, V), 0.0), n);//phong
    //float ks = pow(max(dot(N, H), 0.0), n);//blinn

    //D = vec4(0.0,1.0,0.0, 1.0);
    vec3  rgb = D.rgb * kd + S.rgb * ks;
    float a   = D.a;													//alpha value...1.0
		
		

    //vec4 spotColor = vec4(1.0,0.0,0.0,1.0);       //debug value
    //vec4 spotColor = texture2D(spotlight, gl_TexCoord[0].xy);
    //vec3 final_color = rgb * spotColor.rgb + color.rgb;
    
    /**
     * this gives some weirdness, 
     * static, but otherwise close
     */
    //gl_FragColor = vec4(rgb,0.5); 
    gl_FragColor = vec4(rgb,a);

}
