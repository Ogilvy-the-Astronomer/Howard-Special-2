uniform sampler2D in_Texture;
uniform vec3 in_Emissive;
uniform vec3 in_Ambient;
uniform vec3 in_LightPos;
uniform mat4 in_View;

varying vec2 ex_TexCoord;
varying vec3 ex_FragPos;
varying vec3 ex_Normal;

void main()
{
  vec4 tex = texture2D(in_Texture, ex_TexCoord);
  if(tex.w < 1){
    discard;
  }

  vec3 norm = normalize(ex_Normal);
  vec3 lightDir = normalize(in_LightPos - ex_FragPos);

  float diff = max(dot(norm, lightDir), 0.0);
  vec3 diffuse = diff * vec3(1,1,1);

  vec3 viewPos = vec3(inverse(in_View) * vec4(0,0,0,1));
  vec3 viewDir = normalize(viewPos - ex_FragPos);
  vec3 reflectDir = reflect(-lightDir, norm);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64);
  vec3 specular = spec * vec3(1,1,1);

  vec3 lighting = in_Emissive + in_Ambient + diffuse + specular;

  gl_FragColor = vec4(lighting,1) * tex;
}