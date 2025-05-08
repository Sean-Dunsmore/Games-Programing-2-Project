#version 400

uniform vec3 lightDir;
uniform vec3 inColor;
in vec3 normal;
in vec2 tC;
out vec4 FragColour;

void main()
{
	float intensity;
	vec4 colour;

	intensity = dot(lightDir, normal);

	if (intensity > 0.75)
		colour = vec4(inColor,1.0);
	else if (intensity > 0.5)
		colour = vec4(inColor * 0.6,1.0);
	else if	(intensity > 0.25)
		colour = vec4(inColor * 0.4,1.0);
	else
		colour = vec4(inColor * 0.2,1.0);
	
	FragColour = colour;
}