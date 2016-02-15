#version 410 core

//
// CPSC 453 - Introduction to Computer Graphics
// Assignment 3
//
// Texture fragment shader for phong illumination
// Note: This file should not need to be modified.
//

// Input from vertex shader
in VS_OUT
{
    vec3 N;
    vec3 L;
    vec3 V;
    vec3 C;
    vec2 uv;
} fs_in;

// Material properties
uniform vec3 diffuse_albedo = vec3(0.5, 0.2, 0.7);
uniform vec3 specular_albedo = vec3(0.7);
uniform float specular_power = 128.0;
uniform vec3 ambient = vec3(0.1, 0.1, 0.1);

// Texture Mapping
uniform sampler2D texObject;
uniform bool texValid;

// calculate specular component of lighting
float specularSimple(vec3 L,vec3 N,vec3 H){
   if(dot(N,L)>0){
      return pow(clamp(dot(H,N),0.0,1.0),64.0);
   }
   return 0.0;
}

void main(void)
{
    // Normalize the incoming N, L and V vectors
    vec3 N = normalize(fs_in.N);
    vec3 L = normalize(fs_in.L);
    vec3 V = normalize(fs_in.V);

    // Calculate R locally
    vec3 R = reflect(-L, N);

    // Compute the diffuse and specular components for each fragment
    // May replace the colour value with diffuse albedo
    vec3 diffuse = max(dot(N, L), 0.0) * fs_in.C; // diffuse_albedo;
	if (texValid)
		diffuse *= vec3(texture(texObject, fs_in.uv));
	else
		diffuse *= vec3(1, 1, 1);
    vec3 specular = pow(max(dot(R, V), 0.0), specular_power) * specular_albedo;

    // calculate total intensity of lighting
    vec3 halfVector = normalize( L + V );

    float iambi = 0.1;
    float idiff = clamp(dot(L,N),0.0,1.0);
    float ispec = specularSimple(L, N, halfVector);
    float intensity = iambi + idiff + ispec;

    // quantize intensity for cel shading
    float shadeIntensity = ceil(intensity * 5)/ 5;

    // Write final colour to the framebuffer
    gl_FragColor = vec4(ambient + diffuse * shadeIntensity + specular * shadeIntensity, 1.0);
}
