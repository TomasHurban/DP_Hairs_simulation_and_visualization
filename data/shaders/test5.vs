/* hair test */ 

void main(void)
{
	vec4 a = gl_Vertex;
	a.z = sin(5.0*a.x)*0.25;

	gl_FrontColor = vec4(0.5, 0.5, 0.5, 1.0);

	gl_Position = gl_ModelViewProjectionMatrix * a;
}