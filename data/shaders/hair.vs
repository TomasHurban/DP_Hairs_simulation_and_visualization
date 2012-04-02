void main(void)
{
	vec4 a = gl_Vertex;

	float xx = a.x;
	float yy = a.y;
	float zz = a.z;

	gl_FrontColor = vec4(0.3, 0.1, 0.0, 0.8);
	//gl_FrontColor = gl_Color;

	/*while (xx > 1.0)
		xx = xx / 2;
	while (yy > 1.0)
		yy = yy / 2;
	while (zz > 1.0)
		zz = zz / 2;*/

	/*while (xx > 1.0)
		xx = 1.0/xx;
	while (yy > 1.0)
		yy = 1.0/yy;
	while (zz > 1.0)
		zz = 1.0/zz;
	gl_FrontColor = vec4(xx, yy, zz, 1.0);*/

	gl_Position = gl_ModelViewProjectionMatrix * a;
}