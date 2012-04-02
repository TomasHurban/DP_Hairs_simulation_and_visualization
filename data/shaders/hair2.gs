
void main(void)
{
	for(int i=0 ;i<gl_VerticesIn; i++) 
	{
		vec4 position1 = gl_FrontColorIn[i];
		//vec4 position2 = gl_FrontColorIn[i];
		//vec4 position3 = gl_FrontColorIn[i];

		gl_FrontColor = gl_FrontColorIn[i];
		position1.x = position1.x * 1.2;
		gl_Position = position1;
		EmitVertex();

		/*gl_FrontColor = gl_FrontColorIn[i];
		position2.x = position2.x * 0.8;
		gl_Position = position2;
		EmitVertex();

		gl_FrontColor = gl_FrontColorIn[i];
		position3.x = position3.x * 1;
		gl_Position = position3;
		EmitVertex();*/
	}

	EndPrimitive();
}