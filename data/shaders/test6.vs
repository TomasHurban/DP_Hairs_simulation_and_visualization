/* test GLSL - zmensi objekt*/ 

void main(void)
{
	vec4 a = gl_Vertex;
	a.x = a.x * 1.0;
	a.y = a.y * 1.0; 
	a.z = a.z * 1.0;

	gl_Position = gl_ModelViewProjectionMatrix * a;
}