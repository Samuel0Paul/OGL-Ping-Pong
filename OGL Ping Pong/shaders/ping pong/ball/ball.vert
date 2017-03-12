#version 330 core

in vec3 position;
in vec3 color;

out vec3 vPosition;
out vec3 vColor; // Output to geometry (or fragment) shader

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	vec4 result = projection * view * model * vec4(position, 1.0f);
	gl_Position = result;
	vPosition = result.xyz;
	vColor = color;
}
