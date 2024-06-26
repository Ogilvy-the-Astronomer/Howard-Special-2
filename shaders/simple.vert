uniform mat4 in_Projection;
uniform mat4 in_Model;
uniform mat4 in_View;

attribute vec3 in_Position;

void main(){
  gl_Position = in_Projection * in_View * in_Model * vec4(in_Position, 1.0);
}