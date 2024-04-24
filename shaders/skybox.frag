uniform mat4 in_View;

varying vec3 ex_TexCoord;
//varying vec3 ex_FragPos;

uniform samplerCube in_Skybox;



void main(){
    gl_FragColor = texture(in_Skybox, ex_TexCoord);
}

