#version 410 core

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
uniform float diffuse_albedo = .7f;
uniform float specular_albedo = 1;
uniform float specular_power = 128.0;
uniform float ambient = 0.3f;
uniform float distanceTraveled = 0.0f;

// Texture Mapping
uniform sampler2D texObject;
uniform bool texValid;

// returns intensity of reflected ambient lighting
float ambientLighting()
{
   return ambient;
}

// returns intensity of diffuse reflection
float diffuseLighting(in vec3 N, in vec3 L)
{
   // calculation as for Lambertian reflection
   float diffuseTerm = clamp(dot(N, L), 0, 1) ;
   return diffuse_albedo * diffuseTerm;
}

// returns intensity of specular reflection
float specularLighting(in vec3 N, in vec3 L, in vec3 V)
{
   float specularTerm = 0;

   // calculate specular reflection only if
   // the surface is oriented to the light source
   if(dot(N, L) > 0)
   {
      // half vector
      vec3 H = normalize(L + V);
      specularTerm = pow(dot(N, H), specular_power);
   }
   return specular_albedo * specularTerm;
}

void main(void)
{
   // normalize vectors after interpolation
   vec3 L = fs_in.L;
   vec3 V = fs_in.V;
   vec3 N = fs_in.N;

   vec2 uvtest;

   // get Blinn-Phong reflectance components
   float Iamb = ambientLighting();
   float Idif = diffuseLighting(N, L);
   float Ispe = specularLighting(N, L, V);

   // diffuse color of the object from texture
   vec3 diffuseColor;
   float hello = 0;
   if (!texValid)
	 diffuseColor = vec3(fs_in.C);
   else
   	 uvtest = fs_in.uv;
	 uvtest.y = mod((uvtest.y - mod(distanceTraveled / 5.0, 21.991148575128552669238503682957) / 21.991148575128552669238503682957), 1.0); 
	 diffuseColor = texture(texObject, uvtest).rgb;

   // combination of all components and diffuse color of the object
   vec4 resultingColor;
   resultingColor.xyz = diffuseColor * (Iamb + Idif + Ispe);

   if (!texValid)
	 resultingColor.a = fs_in.C.w;
   else
	 resultingColor.a = texture(texObject, fs_in.uv).w;

   gl_FragColor = resultingColor;

   //gl_FragColor = round(gl_FragColor * 8) / 8;

} 