attribute vec3 in_Position;
attribute vec2 in_TexCoord;

uniform mat4 in_Projection;
uniform mat4 in_Model;

varying vec2 ex_TexCoord;

void main()
{
    ex_TexCoord = in_TexCoord;
    gl_Position = in_Projection * in_Model * vec4(in_Position.x, in_Position.y, 0.0, 1.0);
}