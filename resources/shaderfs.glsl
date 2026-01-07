#version 460 core
out vec4 FragColor;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;
uniform sampler2D ourTexture;
uniform sampler2D ourTexture1;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;
void main()
{
  float specularStrength = 0.5;
  
  vec3 norm = normalize(Normal);
  vec3 viewDir = normalize(viewPos - FragPos);

  vec3 lightDir = normalize(lightPos - FragPos);
  vec3 reflectDir = reflect(-lightDir, norm);

  float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
  vec3 specular = specularStrength * spec * lightColor;
  float diff = max(dot(norm, lightDir), 0.0);
  vec3 diffuse = diff * lightColor;
  float ambientStrength = 0.1;
  vec3 ambient = ambientStrength * lightColor;
  FragColor = mix(texture(ourTexture, TexCoord), texture(ourTexture1, TexCoord), 0.2) * vec4(ambient + diffuse + specular, 1.0);
}
