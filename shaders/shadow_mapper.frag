uniform vec3 LightPos;
uniform float in_FarPlane;

varying vec4 ex_FragPos;

void main()
{             
	float dist = length (ex_FragPos.xyz - LightPos);
	dist /= in_FarPlane;
	gl_FragDepth = dist;
    //gl_FragDepth = gl_FragCoord.z;
} 