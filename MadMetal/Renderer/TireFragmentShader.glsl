#version 410 core
//This is the shader for MeowMix's tire. It works as follows: The texture coordinate is altered such that the new coordinate fs_in.uv.y, equals the origional + the distance traveled % pi * the dimension of the wheel

// Input from vertex shader
in VS_OUT
{
    vec3 N;
    vec3 L;
    vec3 V;
    vec4 C;
    vec2 uv;
	vec4 position_attr;
} fs_in;

// Material properties
uniform vec3 diffuse_albedo = vec3(0.5, 0.2, 0.7);
uniform vec3 ambient = vec3(0.1, 0.1, 0.1);
uniform float distanceTraveled = 0;

// Texture Mapping
uniform sampler2D texObject;
uniform bool texValid;

void main(void)
{
    // Normalize the incoming N, L and V vectors
    vec3 N = normalize(fs_in.N);
    vec3 L = normalize(fs_in.L);
    vec3 V = normalize(fs_in.V);

    // Compute the diffuse and specular components for each fragment
    // May replace the colour value with diffuse albedo
    vec3 diffuse = max(dot(N, L), 0.7) * fs_in.C.xyz; // diffuse_albedo;

	fs_in.uv.y = fs_in.uv.y + distanceTraveled % (3.14159 * 10.0)

	if (texValid)
	{
		diffuse *= vec3(texture(texObject, fs_in.uv));
	}
	else
		diffuse *= vec3(1, 1, 1);

    float iambi = 0.1;
    float idiff = clamp(dot(L,N),0.0,1.0);

    float intensity = iambi + idiff;

    // quantize intensity for cel shading
    float shadeIntensity = ceil(intensity * 5)/ 5;

    // Write final colour to the framebuffer
	if (texValid)
	{
		float alpha = texture(texObject, fs_in.uv).w;
		gl_FragColor = texture(texObject, fs_in.uv);

	} else {
		gl_FragColor = vec4(ambient + diffuse * shadeIntensity, fs_in.C.w);
	}
		

}
