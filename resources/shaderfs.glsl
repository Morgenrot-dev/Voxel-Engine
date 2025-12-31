#version 460 core
out vec4 FragColor;
in vec2 TexCoord;
uniform sampler2D ourTexture;
uniform sampler2D ourTexture1;
uniform vec3 lightColor;

void main()
{
  FragColor = mix(texture(ourTexture, TexCoord), texture(ourTexture1, TexCoord), 0.2) * vec4(lightColor, 1.0);
}
