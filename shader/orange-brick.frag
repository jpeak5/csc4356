uniform vec3 mortar_color; 
uniform vec3 brick_color;
uniform vec2 brick_size;
uniform vec2 brick_pct;
uniform vec3 test_color;

varying vec3 lp;
varying vec2 MCposition;
varying float LightIntensity;


void main()
{
    vec3 color;
    vec2 position, useBrick;
    position = MCposition / brick_size;
    if (fract(position.y * 0.5) > 0.5)
    position.x += 0.5;
    position = fract(position);
    useBrick = step(position, brick_pct);
    color = mix(mortar_color, brick_color, useBrick.x * useBrick.y);
    color *= LightIntensity;
    gl_FragColor = vec4(color, 1.0);
}

