#version 330 core

layout (location = 0) in vec4 vertex;
out vec2 TexCoords;
 
uniform mat4 projection;
uniform vec3 position;
uniform float scale;
 
void main()
{
    gl_Position = projection * vec4((vertex.xy+position.xy) * scale, position.z, 1.0);
    TexCoords = vertex.zw;
}  