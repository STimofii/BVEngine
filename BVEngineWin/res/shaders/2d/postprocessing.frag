#version 330 core
out vec4 FragColor;

in vec2 texCoords;

uniform sampler2D screenTexture;
uniform vec2 screenResolution;
uniform float crosshairSize;
uniform float crosshairThickness;
uniform float time;

void main()
{
    vec4 color = texture(screenTexture, texCoords);    
    vec2 pixelCoords = texCoords * screenResolution;
    vec2 center = screenResolution / 2.0;
    bool isCrosshairPixel = false;
    if(crosshairSize > 0.0){
        if (abs(pixelCoords.y - center.y) < crosshairThickness &&
            abs(pixelCoords.x - center.x) < crosshairSize) {
            isCrosshairPixel = true;
        }
        if (abs(pixelCoords.x - center.x) < crosshairThickness &&
            abs(pixelCoords.y - center.y) < crosshairSize) {
            isCrosshairPixel = true;
        }
    }
    if (isCrosshairPixel) {
        FragColor = vec4(vec3(1.4) - color.rgb, color.a);
    } else {
        FragColor = color;
    }
}