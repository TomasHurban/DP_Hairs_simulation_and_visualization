/* test GLSL - uniform */ 

uniform float coef;

void main(void)
{
	vec4 a = gl_Vertex;
	a.x = a.x * coef;
	a.y = a.y * coef;
	a.z = a.z * coef;

	gl_Position = gl_ModelViewProjectionMatrix * a;
}