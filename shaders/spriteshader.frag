attribute vec2 ex_TexCoord;

uniform sampler2D in_Texture;

void main(){
    vec4 tex = texture2D(in_Texture, ex_TexCoord); //load the texture at the current coordinate
    if(tex.w < 1){ //if there is transparency discard the fragment
      discard;
    }
    gl_FragColor = texture2D(in_Texture, ex_TexCoord);
}