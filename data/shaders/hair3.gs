
void main(void)
{
	for(int i=0 ;i<gl_VerticesIn; i++) 
	{
		gl_FrontColor = gl_FrontColorIn[i];
		gl_Position = gl_PositionIn[i];

		// Done with this vertex
		EmitVertex();
	}
	// Done with the input primitive
	EndPrimitive();
}