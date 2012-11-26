uniform sampler2D diffuse;
uniform sampler2D specular;
uniform vec3 lightPos;
//uniform sampler2D normal;
varying vec3 var_L;
varying vec3 var_N;
varying float LightIntensity;
varying vec2 MCposition;


void main()
{
    vec3 V   = vec3(0.0,0.0,1.0);
    vec3 L   = normalize(lightPos);
    vec3 N   = var_N;
    vec3 H   = normalize(L + V);

    //vec4 D   = vec4(0.0,0.0,0.0,0.0);
    vec4 D   = texture2D(diffuse, gl_TexCoord[0].xy);
    vec4 S   = texture2D(specular, gl_TexCoord[0].xy);
  //  vec4 T   = texture2D(normal, gl_TexCoord[0].xy);
    //vec4 S   = gl_FrontMaterial.specular;
    float n  = gl_FrontMaterial.shininess;//*dot(S,S);

    float kd = max(dot(N, L), 0.0);
    float ks = pow(max(dot(N, H), 0.0), n);

    vec3 rgb = D.rgb * kd;// + S.rgb * ks;
    vec3  dc = D.rgb + kd;									//diffuse color
    vec3  sc = D.rgb + ks;									//specular color
    float a  = D.a;													//alpha value...1.0
		
    vec4 color = vec4(mix(dc,sc,1.0), a);		//choose whether diffuse or specular
		
    gl_FragColor = color;	
    //gl_FragColor = vec4(rgb, a);

}
