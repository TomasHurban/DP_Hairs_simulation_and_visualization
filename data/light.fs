varying float LightIntensity;

void main(void)
{
	vec4 color = gl_Color * LightIntensity;
	gl_FragColor = vec4(color.rgb, 1.0);
}