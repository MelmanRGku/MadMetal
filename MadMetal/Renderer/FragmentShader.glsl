#version 410 core

//TODO:Rewrite shader so that diffuse doesn't change as per the camera

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
uniform vec3 specular_albedo = vec3(0.7);
uniform float specular_power = 128.0;
uniform vec3 ambient = vec3(0.1, 0.1, 0.1);

// Texture Mapping
uniform sampler2D texObject;
uniform bool texValid;

void main(void)
{
    // Normalize the incoming N, L and V vectors
    vec3 N = normalize(fs_in.N);
    vec3 L = normalize(fs_in.L);
    vec3 V = normalize(fs_in.V);

    // Calculate R locally
    vec3 R = reflect(-L, N);

	vec3 h = normalize(V + normalize(L - vec3(fs_in.position_attr) ) );

    // Compute the diffuse and specular components for each fragment
    // May replace the colour value with diffuse albedo
    vec3 diffuse = max(dot(N, L), 0.7) * fs_in.C.xyz; // diffuse_albedo;

	if (texValid)
	{
		diffuse *= vec3(texture(texObject, fs_in.uv));
	}
	else
		diffuse *= vec3(1, 1, 1);




    vec3 specular = pow(max(dot(N, h), 0.0), specular_power) * specular_albedo;

	if(specular.x + specular.y + specular.z > 2.0) specular = vec3(0.5, 0.5, 0.5);
	else if (specular.x + specular.y + specular.z > 1.0) specular = vec3(0.25, 0.25, 0.25);
	else specular = vec3(0, 0, 0);

    // Write final colour to the framebuffer
	if (texValid)
	{
		float alpha = texture(texObject, fs_in.uv).w;
		gl_FragColor = vec4(diffuse + specular, alpha);

	} else {
		gl_FragColor = vec4(diffuse + specular, fs_in.C.w);

	}

	gl_FragColor = round(gl_FragColor * 8) / 8;

}
