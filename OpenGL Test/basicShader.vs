#version 330

out vec4 ourColor;
  
layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;

void main()
{
    gl_Position = vec4(position.x, position.y, position.z, 1.0);
	ourColor = color;
}