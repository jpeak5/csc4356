// uniform qualified variables are changed at most once per primitive
// by the application, and vec3 declares a vector of three
// floating-point numbers
uniform vec3 CoolestColor;
uniform vec3 HottestColor;
// Temperature contains the now interpolated per-fragment
// value of temperature set by the vertex shader
varying float Temperature;
void main()
{
// get a color between coolest and hottest colors, using
// the mix() built-in function
vec3 color = mix(CoolestColor, HottestColor, Temperature);
// make a vector of 4 floating-point numbers by appending an
// alpha of 1.0, and set this fragment's color
gl_FragColor = vec4(color, 1.0);
}

