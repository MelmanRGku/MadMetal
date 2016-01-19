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
layout (location = 1) in vec3 colour_attr;
layout (location = 2) in vec3 normal_attr;
layout (location = 3) in vec3 texcoords_attr;

// Matrices we'll need
uniform highp mat4 model_matrix;
uniform highp mat4 view_matrix;
uniform highp mat4 proj_matrix;

// Inputs from vertex shader
out VS_OUT
{
    vec3 N;
    vec3 L;
    vec3 V;
    vec3 C;
    vec2 uv;
} vs_out;

// Position of light
uniform vec3 light_pos = vec3(100.0, 100.0, 100.0);

void main(void)
{
    // Calculate model-view matrix
    mat4 mv_matrix = view_matrix * model_matrix;

    // Calculate view-space coordinate
    vec4 P = mv_matrix * position_attr;

    // Calculate normal in view-space
    vs_out.N = mat3(mv_matrix) * normal_attr;

    // Calculate light vector
    vs_out.L = light_pos - P.xyz;

    // Calculate view vector
    vs_out.V = -P.xyz;

    // Store the colour attribute
    vs_out.C = colour_attr;

    // Pass along the texture coordinates
    vs_out.uv = texcoords_attr.st;

    // Calculate the clip-space position of each vertex
    gl_Position = proj_matrix * P;
}
