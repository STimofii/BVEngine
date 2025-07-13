#version 330 core

in vec2 v_uv;
out vec4 f_color;

uniform sampler2D u_texture0;

void main(){
	//texture(u_texture0, v_uv)
	f_color = vec4(1, 0, 0, 1);
}