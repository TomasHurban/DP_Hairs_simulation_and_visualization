varying float LightIntensity;

void main(void)
{
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	gl_TexCoord[0] = gl_MultiTexCoord0;

	vec3 transNorm = normalize(vec3(gl_NormalMatrix * gl_Normal));
	vec3 LightPos = gl_LightSource[0].position.xyz;
	vec3 ECposition = vec3(gl_ModelViewMatrix * gl_Vertex);
	LightIntensity = dot(normalize(LightPos - ECposition), transNorm);
	LightIntensity = 0.3 + abs(LightIntensity);
	LightIntensity = clamp(LightIntensity, 0.0, 1.0);
}