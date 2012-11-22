// uniform qualified variables are changed at most once per primitive
uniform float CoolestTemp;
uniform float TempRange;
// attribute qualified variables are typically changed per vertex
attribute float VertexTemp;
// varying qualified variables communicate from the vertex shader to
// the fragment shader
varying float Temperature;
void main()
{
// compute a temperature to be interpolated per fragment,
// in the range [0.0, 1.0]
Temperature = (VertexTemp - CoolestTemp) / TempRange;
/*
The vertex position written in the application using
glVertex() can be read from the built-in variable
gl_Vertex. Use this value and the current model
view transformation matrix to tell the rasterizer where
this vertex is.
*/
gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}

