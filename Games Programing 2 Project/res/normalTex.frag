#version 330

in vec2 tC;
in vec3 normal;

out vec4 fragmentColor;

uniform sampler2D diffuse;

void main()
{

    vec3 tex = texture2D(diffuse, tC).rgb;
    vec3 color = vec3(1.0f,1.0f,1.0f) * normal;
   
    fragmentColor = vec4(color * tex, 1.0);
}