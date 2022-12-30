#version 330 core

layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec2 a_uv;

// uniform mat4 matrix;
// uniform float aspect_ratio;

uniform float window_width;
uniform float window_height;

uniform float translation_x;
uniform float translation_y;

uniform vec2 scale;

uniform float rotation;

uniform vec2 pivot;

uniform vec2 uv_1;
uniform vec2 uv_2;

out vec2 tex_coords;

void main()
{
	float cos_theta = cos(rotation);
	float sin_theta = sin(rotation);

	float x_scaled = a_pos.x * scale.x - pivot.x;
	float y_scaled = a_pos.y * scale.y - pivot.y;

	float x_rotated = x_scaled * cos_theta - y_scaled * sin_theta;
	float y_rotated = x_scaled * sin_theta + y_scaled * cos_theta;

	gl_Position = vec4((x_rotated + translation_x) / window_width * 2.0 - 1.0, (y_rotated + translation_y) / window_height * 2.0 - 1.0, 0.0, 1.0);

	tex_coords.x = (uv_1.x + ((uv_2.x - uv_1.x) * a_uv.x)) / scale.x;
	tex_coords.y = (uv_1.y + ((uv_2.y - uv_1.y) * a_uv.y)) / scale.y;
}
