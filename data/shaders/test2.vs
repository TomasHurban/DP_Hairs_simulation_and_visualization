/* test GLSL - zmeni farbu objektu na zelenu */ 

void main(void)
{
	gl_FrontColor = vec4(0.0, 0.5, 0.0, 1.0);
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}