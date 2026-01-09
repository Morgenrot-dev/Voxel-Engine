#version 460 core
out vec4 FragColor;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

struct Material {
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  float shininess;
};

struct MaterialMap {
  sampler2D diffuse;
  sampler2D specular;
  float shininess;
};

struct Light {
  vec3 position;
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};

struct DiffuseResult {
  vec3 diffuseColor;
  float diff;
};

uniform Material material;
uniform Light light;

uniform MaterialMap materialMap;

uniform vec3 viewPos;

DiffuseResult diffuse_calculation(vec3 normal, vec3 lightDir, vec3 lightDiffuse, vec3 textureDiffuse)
{
  float diff = max(dot(normal, lightDir), 0.0);
  DiffuseResult result;
  result.diffuseColor = lightDiffuse * diff * textureDiffuse;
  result.diff = diff;
  return result;
}

vec3 specular_calculation(vec3 viewDir, vec3 reflectionDir, float shininess, vec3 textureColor, vec3 lightSpec)
{
  float specular = pow(max(dot(viewDir, reflectionDir), 0.0), shininess);
  return textureColor * specular * lightSpec;
}

vec3 ambient_calculation(vec3 lightAmbient, vec3 textureColor)
{
  return lightAmbient * textureColor;
}

void main()
{
  vec3 norm = normalize(Normal);
  vec3 viewDir = normalize(viewPos - FragPos);
  vec3 lightDir = normalize(light.position - FragPos);
  vec3 reflectDir = reflect(-lightDir, norm);
 
  vec4 diffuseTex = texture(materialMap.diffuse, TexCoord);
  vec4 specularTex = texture(materialMap.specular, TexCoord);

  DiffuseResult result;
  result = diffuse_calculation(norm, lightDir, light.diffuse, vec3(diffuseTex));
  vec3 specular_value = vec3(0,0,0);
  if(result.diff > 0.0)
  {
    specular_value = specular_calculation(viewDir, reflectDir, materialMap.shininess, vec3(specularTex), light.specular);
  }
  vec4 textureMix = mix(diffuseTex, specularTex, 0.2);
  vec3 ambient = ambient_calculation(light.ambient, vec3(textureMix));
  vec3 result_color = ambient + result.diffuseColor + specular_value;
  //vec3 result = vec3(mix(texture(ourTexture, TexCoord), texture(ourTexture1, TexCoord), 0.2)) * (ambient + diffuse + specular);
  FragColor = vec4(result_color, 1.0);
}


