#version 330

out vec4 ourColor;
out vec2 TexCoord;
  
layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 texCoord;

void main()
{
    gl_Position = vec4(position.x, position.y, position.z, 1.0);
	ourColor = color;
	TexCoord = texCoord;
}