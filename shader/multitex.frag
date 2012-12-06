uniform sampler2D diffuse;
uniform sampler2D specular;
uniform sampler2D normal;
uniform sampler2D shiny;
uniform sampler2D spotlight;
varying vec3 var_L;
varying vec3 var_N;
varying float LightIntensity;
varying vec2 MCposition;


void main()
{
    vec3 V   = vec3(0.0,0.0,1.0);
    vec3 L   = normalize(var_L);
    vec3 N   = var_N;
    vec3 H   = normalize(L + V);

    vec4 D   = texture2D(diffuse, gl_TexCoord[0].xy);
    vec4 S   = texture2D(specular, gl_TexCoord[2].xy);
    vec4 Z   = texture2D(shiny, gl_TexCoord[3].xy);
    vec4 T   = texture2D(normal, gl_TexCoord[1].xy);

    //vec4 S   = gl_FrontMaterial.specular;
    float n  = gl_FrontMaterial.shininess*0.03;

    float kd =     max(dot(N, L), 0.0);
    float ks = pow(max(dot(N, H), 0.0), n);

    vec3  rgb = D.rgb * kd + S.rgb * ks;
    float a   = D.a;													//alpha value...1.0
		
    vec4 color = vec4(mix(D.rgb,S.rgb,1.0), a);		//choose whether diffuse or specular
		

    //vec4 spotColor = vec4(1.0,0.0,0.0,1.0);       //debug value
    vec4 spotColor = texture2D(spotlight, gl_TexCoord[0].xy);
    vec3 final_color = rgb * spotColor.rgb + color.rgb;
    gl_FragColor = vec4(final_color, a);

}
