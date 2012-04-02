#version 120
#extension GL_ARB_geometry_shader4 : enable

void main()
{
	float distance = 0.1;

	// original vertex
	for (int i=0; i<gl_VerticesIn; i++)
	{
		gl_Position = gl_PositionIn[i];
		gl_FrontColor  = gl_FrontColorIn[0];
		EmitVertex();
	}
	EndPrimitive();
 
	// new vertex
   	/*for(int i=0; i<gl_VerticesIn; i++)
	{
		vec4 vertex = gl_PositionIn[i];
		vertex.z = vertex.z + distance;
		gl_Position = vertex;
		EmitVertex();
	}
	EndPrimitive();
	
	// new vertex
   	for(int i=0; i<gl_VerticesIn; i++)
	{
		vec4 vertex = gl_PositionIn[i];
		vertex.z = vertex.z - distance;
		gl_Position = vertex;
		EmitVertex();
	}
	EndPrimitive();*/

	// new vertex
   	for(int i=0; i<gl_VerticesIn; i++)
	{
		vec4 vertex = gl_PositionIn[i];
		vertex.x = vertex.x + distance;
		gl_Position = vertex;
		EmitVertex();
	}
	EndPrimitive();

	// new vertex
   	for(int i=0; i<gl_VerticesIn; i++)
	{
		vec4 vertex = gl_PositionIn[i];
		vertex.x = vertex.x - distance;
		gl_Position = vertex;
		EmitVertex();
	}
	EndPrimitive();
}