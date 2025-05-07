#version 400

in vec2 tC;

uniform sampler2D diffuse1;
uniform sampler2D diffuse2;
uniform float counter;

out vec4 FragColour;

void main()
{
	vec3 tex1 = texture2D(diffuse1, tC).rgb;
	vec3 tex2 = texture2D(diffuse2, tC).rgb;

	float factor = abs(sin(counter));

	vec3 color = mix(tex1,tex2,factor);

	FragColour = vec4(color, 1.0);
}
