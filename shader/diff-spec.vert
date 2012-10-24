void main()
{
    vec3  V   = vec3(0.0, 0.0, 1.0);
    vec3  L   = normalize(gl_LightSource[0].position.xyz);
    vec3  N   = normalize(gl_NormalMatrix * gl_Normal);
    vec3  H   = normalize(L + V);

    vec4  D   = gl_FrontMaterial.diffuse;
    vec4  S   = gl_FrontMaterial.specular;
    float n   = gl_FrontMaterial.shininess;

    float kd  =     max(dot(N, L), 0.0); 
    float ks  = pow(max(dot(N, H), 0.0), n);

    vec3  rgb = D.rgb * kd + S.rgb * ks;
    float a   = D.a; 

    gl_FrontColor = vec4(rgb, a); 
    gl_Position   = ftransform(); 
}
