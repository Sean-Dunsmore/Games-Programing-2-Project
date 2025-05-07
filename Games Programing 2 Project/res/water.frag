#version 400

in vec2 tC;
in float time;
uniform sampler2D diffuse;

out vec4 FragColour;

void main()
{
	vec2 updatedTC = vec2(tC.x *10,tC.y*10 + time * 0.1);
	vec4 Color = texture2D(diffuse, updatedTC);

	Color.w = 0.8;

	FragColour = Color;
}

