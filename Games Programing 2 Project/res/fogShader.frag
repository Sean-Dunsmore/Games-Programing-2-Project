#version 400
out vec4 FragColor;
in vec3 v_norm;
in vec4 v_pos; 
in vec2 tC;

uniform vec3 fogColor;

uniform float maxDist; //fog max distance
uniform float minDist; //fog min distance

uniform int rimType;

uniform sampler2D diffuse;

vec3 rim1(vec3 color, vec3 N, vec3 V)
{

float rimFactor = max(0.0, 1.0 - dot(N,V));
float rimIntensity = 0.0;

vec3 rimColor = vec3(1.0,0.0,0.0);

if (rimFactor > 0.95)
	rimIntensity = 1.0; //All Rim
else if (rimFactor > 0.8)
	rimIntensity = 0.5; //Some rim
else
	rimIntensity = 0.0; //No rim

vec3 finalColor = color + rimColor * rimIntensity;
return finalColor;

}

vec3 rim2(vec3 color, vec3 N, vec3 V)
{

float rimFactor = 1.0 -max(0.0, dot(N,V));
float rimIntensity = pow(rimFactor,4.0);

vec3 rimColor = vec3(0.0,1.0,0.0);

vec3 finalColor = color + rimColor * rimIntensity;
return finalColor;

}

vec3 rim3(vec3 color, vec3 N, vec3 V)
{

float rimFactor = 1.0 -max(0.0, dot(N,V));
float rimIntensity = smoothstep(0.2,0.8,rimFactor);

vec3 rimColor = vec3(0.0,0.0,1.0);

vec3 finalColor = color + rimColor * rimIntensity;
return finalColor;

}

void main() 
{

vec3 tex = texture2D(diffuse, tC).rgb;

float dist = abs( v_pos.z );
float fogFactor = (maxDist - dist)/(maxDist - minDist);
fogFactor = clamp( fogFactor, 0.0, 1.0 );
vec3 lightColor =  tex * vec3(0.8,0.8,0.8);
vec3 color = mix( fogColor, lightColor, 1-fogFactor);

vec3 v_direction = -vec3(v_pos);

vec3 N = normalize(v_norm);
vec3 V = normalize(v_direction);

//FragColor = vec4(color,1.0);

//FragColor = vec4(rim3(color,N,V), 1.0);

if (rimType == 1)
	FragColor = vec4(rim1(color,N,V), 1.0);
else if (rimType == 2)
	FragColor = vec4(rim2(color,N,V), 1.0);
else
	FragColor = vec4(rim3(color,N,V), 1.0);
}
