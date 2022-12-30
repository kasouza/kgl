#version 330 core

in vec2 tex_coords;

uniform sampler2D tex;

out vec4 frag_color;

void main()
{
	frag_color = texture(tex, tex_coords);
	if (frag_color.a == 0.0)
		discard;
}
