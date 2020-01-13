uniform sampler2D in_Texture;
uniform mat4 in_View;
uniform float in_FarPlane;
uniform float in_NearPlane;

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
  vec4 tex = texture2D(in_Texture, ex_TexCoord); //load the texture at the current coordinate
  if(tex.w < 1){ //if there is transparency discard the fragment
    discard;
  }

  vec3 norm = normalize(ex_Normal); //normalize the fragment normal
  vec3 lighting = vec3(0,0,0);
  float shadow = 0;
  for(int i = 0; i < NO_POINT_LIGHTS; i++){ //go through every point light and calculate the light and shadow values on this fragment
    lighting += CalcPointLights(lights[i], norm, in_ShadowMaps[i]);
	shadow += ShadowCalculation(ex_FragPos, in_ShadowMaps[i], lights[i].pos);
  }
  lighting += shadow;
  for(int i = 0; i < NO_DIR_LIGHTS; i++){ //do the same for directional lights
    lighting += CalcDirLights(dlights[i], norm);
  }
  gl_FragColor = vec4(lighting,1) * tex; //set the fragment colour to the light value multiplied by the texture value
}

vec3 CalcPointLights(PointLight light, vec3 norm, samplerCube shadowMap){
  vec3 lightDir = normalize(light.pos - ex_FragPos); //get the direction of the light from the current fragment position

  float diff = max(dot(norm, lightDir), 0.0);
  light.diffuse = diff * light.diffuse; //get the diffuse value at this fragment

  vec3 viewPos = vec3(inverse(in_View) * vec4(0,0,0,1));
  vec3 viewDir = normalize(viewPos - ex_FragPos);
  vec3 reflectDir = reflect(-lightDir, norm);

  float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64);
  light.specular = spec * light.specular;

  float distance = length(light.pos - ex_FragPos);
  float attentuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance)); //change the light value based on it's distance from the fragment

  vec3 lighting = light.emissive + ((light.ambient + light.diffuse + light.specular) * attentuation); //calculate the light value at this fragment
  
  return lighting;
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

vec3 sampleOffsetDirections[20] = vec3[] //list of offsets for use in softening the shadow edges
(
   vec3( 1,  1,  1), vec3( 1, -1,  1), vec3(-1, -1,  1), vec3(-1,  1,  1), 
   vec3( 1,  1, -1), vec3( 1, -1, -1), vec3(-1, -1, -1), vec3(-1,  1, -1),
   vec3( 1,  1,  0), vec3( 1, -1,  0), vec3(-1, -1,  0), vec3(-1,  1,  0),
   vec3( 1,  0,  1), vec3(-1,  0,  1), vec3( 1,  0, -1), vec3(-1,  0, -1),
   vec3( 0,  1,  1), vec3( 0, -1,  1), vec3( 0, -1, -1), vec3( 0,  1, -1)
);  

float ShadowCalculation(vec3 fragPos, samplerCube shadowMap, vec3 lightPos){
  vec3 fragToLight = (fragPos - lightPos); //get the direction to sample the shadowmap from
  float currentDepth = length(fragToLight); //get the depth of the current fragment
  int samples  = 20;
  float diskRadius = 0.15; //shadow softening radius
  float bias = 0.001; 
  float shadow = 0;

  for(int i = 0; i < samples; ++i){ 
    float shadowDepth = texture(shadowMap, fragToLight + sampleOffsetDirections[i] * diskRadius).r; //get the shadow depth from the shadow map, offset by current sample offset value
	float z = shadowDepth;// * 2.0 - 1.0; 
    float linearShadowDepth = (2.0 * in_NearPlane * in_FarPlane) / (in_FarPlane + in_NearPlane - z * (in_FarPlane - in_NearPlane)); //change the value of the depth map depth to the same range as the current depth
    if(currentDepth - bias > linearShadowDepth){//if the current depth is more than the shadow map depth, the fragment is behind an object from the lights perspective and thus is in shadow
      shadow -= 1.0;
	}
  }
  shadow /= float(samples); //soften the shadow
  
  return shadow;
}
