void main()
{
    vec3 V = vec3(0.0, 0.0, 1.0); // View vector 
    vec3 L = normalize(gl_LightSource[0].position.xyz); // Light vector  
    vec3 N = normalize(gl_NormalMatrix * gl_Normal); // Normal vector 

    vec4 D = gl_FrontMaterial.diffuse; // Diffuse color 

    float kd = max(dot(N, L), 0.0); 
    vec3 rgb = D.rgb * kd; // RGB channels
    float a = D.a; // Alpha channel
    gl_FrontColor = vec4(rgb, a); 
    gl_Position = ftransform(); 
}

