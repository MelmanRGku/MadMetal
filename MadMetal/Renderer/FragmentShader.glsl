#version 410 core

// Input from vertex shader
in VS_OUT
{
    vec3 N;
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

uniform int bitmask = 0x00000001;

uniform vec3 lightPosArray[10];

uniform vec3 lightColorArray[10];

uniform constants
{
  float constArray[10];
};

uniform linears
{
  float linearArray[10];
};

uniform quads
{
  float quadArray[10];
};



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

// THIS CODE IS NEEDED FOR DROPPING OFF LIGHTING, IMPORTANT FOR MULTIPLE LIGHTS
//float dropoffFunction (1/k0 + k1d + k2d^2)

float dropoffFunction(float constant1, float constant2, float constant3, vec3 lightPosition, vec4 position)
{
	float dist = distance(lightPosition, position.xyz);
	return 1/(constant1 + constant2 * dist + constant3 * pow(dist, 2));

}


void main(void)
{
   // normalize vectors after interpolation

   vec3 V = fs_in.V;
   vec3 N = fs_in.N;

   vec3 diffuseColor;
   if (!texValid)
	 diffuseColor = vec3(fs_in.C);
   else
	 diffuseColor = texture(texObject, fs_in.uv).rgb;

   vec3 L = vec3(0, 0, 0);
   vec4 resultingColor;
   resultingColor.xyz = diffuseColor;

   for (int i = 0; i < 1; i++)
   {

	   L = normalize(lightPosArray[0] - fs_in.position_attr.xyz);

	   // get Blinn-Phong reflectance components
	   float Iamb = ambientLighting();
	   float Idif = diffuseLighting(N, L);
	   float Ispe = specularLighting(N, L, V);

   
	 resultingColor.xyz *= (Iamb + Idif + Ispe) * dropoffFunction(0, 0.01, 0,lightPosArray[0] , fs_in.position_attr) * lightColorArray[0];      

   }

   if (!texValid)
	 resultingColor.a = fs_in.C.w;
   else
	 resultingColor.a = texture(texObject, fs_in.uv).w;

   gl_FragColor = resultingColor;

   //gl_FragColor = round(gl_FragColor * 8) / 8;
} 