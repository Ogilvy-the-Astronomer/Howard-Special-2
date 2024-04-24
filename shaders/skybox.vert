uniform mat4 in_Projection;
uniform mat4 in_View;

attribute vec3 in_Position;
attribute vec3 in_TexCoord;

varying vec3 ex_TexCoord;
//varying vec3 ex_FragPos;


void main(){
  gl_Position = in_Projection * in_View * vec4(in_Position, 1.0);

  ex_TexCoord = in_Position;
  //ex_FragPos = vec3(in_Model * vec4(in_Position, 1.0));
}