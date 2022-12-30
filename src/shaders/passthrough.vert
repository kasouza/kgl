#version 330 core

layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec2 a_uv;

// uniform mat4 matrix;
// uniform float aspect_ratio;

out vec2 tex_coords;

void main()
{
    gl_Position = vec4(a_pos, 1.0);
	tex_coords = a_uv;
}
