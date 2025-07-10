#version 330 core

layout (location = 0) in vec4 vertex;
out vec2 TexCoords;
 
uniform mat4 projection;
uniform vec3 text_position;
uniform vec2 char_position;
uniform float scale;
 
void main()
{
    gl_Position = projection * vec4(((vertex.xy+char_position.xy) * scale) + text_position.xy, text_position.z, 1.0);
    TexCoords = vertex.zw;
}  