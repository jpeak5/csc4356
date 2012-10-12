void main()
{
    gl_FrontColor = gl_FrontMaterial.diffuse;
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}

