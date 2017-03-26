#version 330

out vec4 ourColor;
out vec2 TexCoord;
  
layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 texCoord;

uniform mat4 transform;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0f);
	ourColor = color;
	TexCoord = vec2(texCoord.x, 1.0 - texCoord.y);
}