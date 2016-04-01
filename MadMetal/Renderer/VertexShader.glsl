#version 410 core

//
// CPSC 453 - Introduction to Computer Graphics
// Assignment 3
//
// Texture vertex shader for phong illumination
// Note: This file should not need to be modified.
//

// Per-vertex inputs
layout (location = 0) in vec4 position_attr;
layout (location = 1) in vec4 colour_attr;
layout (location = 2) in vec3 normal_attr;
layout (location = 3) in vec3 texcoords_attr;

// Matrices we'll need
uniform highp mat4 model_matrix;
uniform highp mat4 view_matrix;
uniform highp mat4 proj_matrix;
uniform highp vec3 camera_pos;

// Inputs from vertex shader
out VS_OUT
{
    vec3 N;
    vec3 V;
    vec4 C;
    vec2 uv;
	vec4 position_attr;

} vs_out;

void main()
{
    // position in world space
   vec4 worldPosition = model_matrix * position_attr;

   // normal in world space
   vs_out.N = vec3(normalize(model_matrix * vec4(normal_attr, 0)));

   // direction to camera
   vs_out.V = normalize(camera_pos - worldPosition.xyz);

   // texture coordinates to fragment shader
   vs_out.uv = texcoords_attr.xy;

   //colour
   vs_out.C = colour_attr;
   
   vs_out.position_attr = worldPosition ;

   // screen space coordinates of the vertex
   gl_Position = proj_matrix * view_matrix * worldPosition;
}