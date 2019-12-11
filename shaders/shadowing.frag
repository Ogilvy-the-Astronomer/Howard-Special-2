uniform sampler2D in_Texture;
uniform mat4 in_View;
uniform float in_FarPlane;

varying vec2 ex_TexCoord;
varying vec3 ex_FragPos;
varying vec3 ex_Normal;

#define NO_POINT_LIGHTS 1
uniform samplerCube in_ShadowMaps[NO_POINT_LIGHTS];

struct PointLight{
  vec3 pos;

  vec3 emissive;
  vec3 ambient;
  vec3 specular;
  vec3 diffuse;

  float constant;
  float linear;
  float quadratic;

  mat4 view;
};

uniform PointLight lights[NO_POINT_LIGHTS];

struct DirectionalLight{
  vec3 dir;

  vec3 emissive;
  vec3 ambient;
  vec3 specular;
  vec3 diffuse;
};
#define NO_DIR_LIGHTS 1
uniform DirectionalLight dlights[NO_DIR_LIGHTS];

vec3 CalcPointLights(PointLight light, vec3 norm, samplerCube shadowMap);
vec3 CalcDirLights(DirectionalLight light, vec3 norm);

float ShadowCalculation(vec3 fragPos, samplerCube shadowMap, vec3 lightPos);

void main(){
  vec4 tex = texture2D(in_Texture, ex_TexCoord);
  if(tex.w < 1){
    discard;
  }

  vec3 norm = normalize(ex_Normal);
  vec3 lighting = vec3(0,0,0);
  for(int i = 0; i < NO_POINT_LIGHTS; i++){
    lighting += CalcPointLights(lights[i], norm, in_ShadowMaps[i]);
  }
  for(int i = 0; i < NO_DIR_LIGHTS; i++){
    lighting += CalcDirLights(dlights[i], norm);
  }

  //vec3 fragToLight = ex_FragPos - lights[0].pos;
  //float closestDepth = texture(in_ShadowMaps[0], fragToLight).r;
  //closestDepth *= in_FarPlane;
  //float currentDepth = length(fragToLight);
  //gl_FragColor = vec4(vec3(currentDepth), 1.0) + (vec4(lighting,1.0) * 0.001);
  

  gl_FragColor = vec4(lighting,1) * tex;
}

vec3 CalcPointLights(PointLight light, vec3 norm, samplerCube shadowMap){
  vec3 lightDir = normalize(light.pos - ex_FragPos);

  float diff = max(dot(norm, lightDir), 0.0);
  light.diffuse = diff * light.diffuse;

  vec3 viewPos = vec3(inverse(in_View) * vec4(0,0,0,1));
  vec3 viewDir = normalize(viewPos - ex_FragPos);
  vec3 reflectDir = reflect(-lightDir, norm);

  float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64);
  light.specular = spec * light.specular;

  float distance = length(light.pos - ex_FragPos);
  float attentuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

  vec3 lighting = light.emissive + ((light.ambient + light.diffuse + light.specular) * attentuation);
  float shadow = ShadowCalculation(ex_FragPos, shadowMap, light.pos);
  return lighting * shadow;
}

vec3 CalcDirLights(DirectionalLight light, vec3 norm){
  vec3 lightDir = normalize(-light.dir);

  float diff = max(dot(norm, lightDir), 0.0);
  light.diffuse = diff * light.diffuse;

  vec3 viewPos = vec3(inverse(in_View) * vec4(0,0,0,1));
  vec3 viewDir = normalize(viewPos - ex_FragPos);
  vec3 reflectDir = reflect(-lightDir, norm);

  float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64);
  light.specular = spec * light.specular;

  vec3 lighting = light.emissive + light.ambient + light.diffuse + light.specular;

  return lighting;
}


float ShadowCalculation(vec3 fragPos, samplerCube shadowMap, vec3 lightPos){
  vec3 fragToLight = fragPos - lightPos;
  float closestDepth = texture(shadowMap, fragToLight).r;
  closestDepth *= in_FarPlane;
  float currentDepth = length(fragToLight);
  // check whether current frag pos is in shadow
  float bias = 0.05; 
  float shadow = currentDepth -  bias > closestDepth ? 1.0 : 0.0;
  return shadow;
}
