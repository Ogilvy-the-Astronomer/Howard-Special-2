uniform sampler2D in_Texture;
uniform mat4 in_View;

varying vec2 ex_TexCoord;
varying vec3 ex_FragPos;
varying vec3 ex_Normal;

varying vec4 ex_FragPosLightSpace;
uniform sampler2D in_ShadowMap;

struct PointLight{
  vec3 pos;

  vec3 emissive;
  vec3 ambient;
  vec3 specular;
  vec3 diffuse;

  float constant;
  float linear;
  float quadratic;
};
#define NO_POINT_LIGHTS 1
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

vec3 CalcPointLights(PointLight light, vec3 norm);
vec3 CalcDirLights(DirectionalLight light, vec3 norm);

float ShadowCalculation(vec4 fragPosLightSpace, vec3 lightDir);

void main(){
  vec4 tex = texture2D(in_Texture, ex_TexCoord);
  if(tex.w < 1){
    discard;
  }

  vec3 norm = normalize(ex_Normal);
  vec3 lighting = vec3(0,0,0);
  for(int i = 0; i < NO_POINT_LIGHTS; i++){
    lighting += CalcPointLights(lights[i], norm);
  }
  for(int i = 0; i < NO_DIR_LIGHTS; i++){
    lighting += CalcDirLights(dlights[i], norm);
  }

  gl_FragColor = vec4(lighting,1) * tex;
}

vec3 CalcPointLights(PointLight light, vec3 norm){
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
  float shadow = ShadowCalculation(ex_FragPosLightSpace, lightDir);
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


float ShadowCalculation(vec4 fragPosLightSpace, vec3 lightDir){
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(in_ShadowMap, projCoords.xy).r; 
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // check whether current frag pos is in shadow
    float bias = max(0.05 * (1.0 - dot(ex_Normal, lightDir)), 0.005); ;
    if(currentDepth - bias > closestDepth){
    return 0.1;
    }
    else return 1;
}
