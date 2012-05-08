#version 120
#extension GL_ARB_geometry_shader4 : enable

uniform float color_r;
uniform float color_g;
uniform float color_b;
uniform float color_a;

float rand(vec2 n)
{
  	return 10 * fract(sin(dot(n.xy, vec2(12.9898, 78.233)))* 43758.5453);
}

void main()
{
	float diff_limit = 0.4;
	float distance = 0.1;
	float multi = 0.5;
	float dist;
	float hue_limit = 0.1;
	float hue1;
	float hue2;

	float start = gl_PositionIn[0].y;

	float diff1 = rand(vec2(984.115616, 2156.464));
	diff1 = mod(diff1, diff_limit);
	float diff2 = rand(vec2(21.564, 489.2));
	diff2 = mod(diff2, diff_limit);

	hue1 = rand(vec2(123.845, 56.46));
	hue1 = mod(hue1, hue_limit);
	hue2 = rand(vec2(218.15, 548.71));
	hue2 = mod(hue2, hue_limit);

	// original primitive
	for (int i=0; i<gl_VerticesIn; i++)
	{
		gl_Position = gl_PositionIn[i];

		// gl_FrontColor  = gl_FrontColorIn[0];
		gl_FrontColor = vec4(color_r, color_g, color_b, color_a);
		EmitVertex();
	}
	EndPrimitive();
 
	// new primitive (1)
   	for(int i=0; i<gl_VerticesIn; i++)
	{
		vec4 vertex = gl_PositionIn[i];
		
		if (vertex.y < 0)
			dist = -vertex.y * diff1 * multi;	
		else
			dist = vertex.y * diff1 * multi;	

		gl_FrontColor = vec4(color_r+hue1, color_g+hue1, color_b+hue1, color_a);

		vertex.x = vertex.x + distance + dist;
		gl_Position = vertex;
		EmitVertex();
	}
	EndPrimitive();

	// new primitive (2)
   	for(int i=0; i<gl_VerticesIn; i++)
	{
		vec4 vertex = gl_PositionIn[i];

		if (vertex.y < 0)
			dist = -vertex.y * diff2 * multi;	
		else
			dist = vertex.y * diff2 * multi;	

		gl_FrontColor = vec4(color_r+hue2, color_g+hue2, color_b+hue2, color_a);

		vertex.x = vertex.x - distance - dist;
		gl_Position = vertex;
		EmitVertex();
	}
	EndPrimitive();

	// new primitive (3)
   	for(int i=0; i<gl_VerticesIn; i++)
	{
		vec4 vertex = gl_PositionIn[i];

		if (vertex.y < 0)
			dist = -vertex.y * diff1 * multi;	
		else
			dist = vertex.y * diff1 * multi;	

		gl_FrontColor = vec4(color_r-hue2, color_g-hue2, color_b-hue2, color_a);

		vertex.x = vertex.x + (distance/2) + (dist/2);
		gl_Position = vertex;
		EmitVertex();
	}
	EndPrimitive();

	// new primitive (4)
   	for(int i=0; i<gl_VerticesIn; i++)
	{
		vec4 vertex = gl_PositionIn[i];

		if (vertex.y < 0)
			dist = -vertex.y * diff2 * multi;	
		else
			dist = vertex.y * diff2 * multi;	

		gl_FrontColor = vec4(color_r-hue1, color_g-hue1, color_b-hue1, color_a);

		vertex.x = vertex.x - (distance/2) - (dist/2);
		gl_Position = vertex;
		EmitVertex();
	}
	EndPrimitive();

}