#version 330 core

in vec2 TexCoords;
out vec4 color;
 
uniform sampler2D text;
uniform vec4 textColor;
 
void main()
{    
   
   //color = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);
   color = textColor * vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);
}