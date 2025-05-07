#version 400

uniform vec3 lightDir;
in vec3 normal;
in vec2 tC;
in vec3 viewDirection;
in vec3 position;
out vec4 FragColour;

uniform sampler2D sampler;
uniform vec4 ambient;
uniform vec4 diffuse;
uniform vec4 specular;
uniform int lightType;
uniform vec3 lightPos;

vec4 directionalLight()
{
	//Intensity = how aligned is the normal to the light direction, 1 = aligned 0 = not aligned
	float intensity = dot(lightDir, normal);

	//Calculate diffuse
	vec4 colour;
	colour = clamp(diffuse * intensity,0.0,1.0);

	return colour;
}

vec4 pointLight()
{
	//Vector representing direction from light to vertex
	vec3 lightVector = normalize(lightPos - position);

	//Intensity = how aligned is the normal to the light direction, 1 = aligned 0 = not aligned
	float intensity = clamp(dot(lightVector, normal),0.0,1.0);

	//Calculate diffuse
	vec4 colour;
	colour = clamp(diffuse * intensity,0.0,1.0);

	return colour;

}

vec4 spotLight()
{

	vec3 lightVector = normalize(lightPos - position);
	float spotFactor = dot(lightVector, lightDir);

	float cutOff = 0.9f;

	//Calculate diffuse
	vec4 colour = vec4(0.0,0.0,0.0,1.0);

	if (spotFactor > cutOff)
	{
	
		colour = pointLight();
        colour =  colour * (1.0 - (1.0 - spotFactor) * 1.0/(1.0 - cutOff));
	}
	else
	{
		colour = vec4(0.0,0.0,0.0,1.0);
	}

	return colour;
}

vec4 calculateLighting()
{

	vec3 lightReflect = normalize(reflect(viewDirection, normal));
	float specularIntensity = dot(viewDirection,lightReflect);

	//Calculate diffuse lighting
	vec4 colour;
	if (lightType == 0) //If directional light
	{
		colour = directionalLight();
	}
	if (lightType == 1) //If point light
	{
		colour = pointLight();
	}
	if (lightType == 2) //If spot light
	{
		colour = spotLight();
	}

	//Calculate specular
	vec4 specularColor;
	if (specularIntensity > 0)
	{
		specularColor = vec4(specular * specularIntensity * 0.5);
	}

	return clamp(colour + specularColor,0.0,1.0);

}

void main()
{
	float intensity;
	vec4 colour;

	//Calculate lighting color
	colour = calculateLighting();

	//Add ambient
	colour = clamp(colour + ambient,0.0,1.0);

	//Texture
	vec3 tex = texture2D(sampler, tC).rgb;

	//Return light * texture
	FragColour = clamp(colour,0.0,1.0) * vec4(tex,1);
}