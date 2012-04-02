#version 120
#extension GL_ARB_geometry_shader4 : enable

void main()
{
	// original vertex
	for (int i=0; i<gl_VerticesIn; i++)
	{
		gl_Position = gl_PositionIn[i] *2;
		EmitVertex();
	}
   
	EndPrimitive();
 
	// new vertex
   	for(int i=0; i<gl_VerticesIn; i++)
	{
		vec4 vertex = gl_PositionIn[i];
		float tmpx = vertex.x;
		vertex.x = tmpx + 2;
		gl_Position = vertex;
		EmitVertex();
	}
	
	EndPrimitive();

	// new vertex
   	for(int i=0; i<gl_VerticesIn; i++)
	{
		vec4 vertex2 = gl_PositionIn[i];
		vertex2.x = vertex2.x + 5;
		gl_Position = vertex2;
		EmitVertex();
	}
	
	EndPrimitive();
}