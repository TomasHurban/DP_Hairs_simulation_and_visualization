/* hair test */ 

void main(void)
{
	vec4 a = gl_Vertex;
	a.x = a.x * 1.3;
	a.y = a.y * 1.0; 
	a.z = a.z * 1.3;

	float xx = a.x;
	float yy = a.y;
	float zz = a.z;

	//gl_FrontColor = vec4(0.6, 0.2, 0.0, 0.8);
	//gl_FrontColor = gl_Color;

	while (xx > 1.0)
		xx = xx / 2;
	while (yy > 1.0)
		yy = yy / 2;
	while (zz > 1.0)
		zz = zz / 2;
	gl_FrontColor = vec4(xx, yy, zz, 1.0);

	gl_Position = gl_ModelViewProjectionMatrix * a;
}