attribute vec2 ex_TexCoord;

uniform sampler2D depthMap;
uniform float near_plane;
uniform float far_plane;

// required when using a perspective projection matrix
float LinearizeDepth(float depth)
{
    float z = depth * 2.0 - 1.0; // Back to NDC 
    return (2.0 * near_plane * far_plane) / (far_plane + near_plane - z * (far_plane - near_plane));	
}

void main()
{             
    const float offset = 1.0 / 300.0;
    vec2 offsets[9] = vec2[](
        vec2(-offset,  offset), // top-left
        vec2( 0.0f,    offset), // top-center
        vec2( offset,  offset), // top-right
        vec2(-offset,  0.0f),   // center-left
        vec2( 0.0f,    0.0f),   // center-center
        vec2( offset,  0.0f),   // center-right
        vec2(-offset, -offset), // bottom-left
        vec2( 0.0f,   -offset), // bottom-center
        vec2( offset, -offset)  // bottom-right    
    );

    float kernel[9] = float[](
        -1, -1, -1,
        -1,  9, -1,
        -1, -1, -1
    );

    vec3 sampleTex[9];
    for(int i = 0; i < 9; i++)
    {
        sampleTex[i] = vec3(texture(depthMap, ex_TexCoord.st + offsets[i]));
    }
    vec3 col = vec3(0.0);
    for(int i = 0; i < 9; i++)
        col += sampleTex[i] * kernel[i];
    near_plane = 0.1;
    far_plane = 300;
    //float depthValue = texture(depthMap, ex_TexCoord).r;
    //gl_FragColor = vec4(vec3(LinearizeDepth(depthValue) / far_plane), 1.0); // perspective
    //gl_FragColor = vec4(vec3(depthValue), 1.0); // orthographic
    gl_FragColor = texture2D(depthMap, ex_TexCoord);
    //gl_FragColor = vec4(col, 1.0);
}