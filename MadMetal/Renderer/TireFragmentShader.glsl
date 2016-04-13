#version 410 core

#define MAX_NUM_OF_LIGHTS 70

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
uniform float distanceTraveled = 0.0f;

uniform int bitmask = 0x00000001;

uniform vec3 lightPosArray[MAX_NUM_OF_LIGHTS];

uniform vec3 lightColorArray[MAX_NUM_OF_LIGHTS];

 uniform float constArray[MAX_NUM_OF_LIGHTS];
 uniform float linearArray[MAX_NUM_OF_LIGHTS];
 uniform float quadArray[MAX_NUM_OF_LIGHTS];

 uniform float cutoffArray[MAX_NUM_OF_LIGHTS];


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

float dropoffFunction(float constant1, float constant2, float constant3, vec3 lightPosition, vec4 position, float cutoff)
{
	float dist = distance(lightPosition, position.xyz) / 4;
	if (dist > cutoff) 
		return 0;
	return 1/(constant1 + constant2 * dist + constant3 * pow(dist, 2));

}


void main(void)
{
   // normalize vectors after interpolation

   vec3 V = fs_in.V;
   vec3 N = fs_in.N;

   vec2 uvtest;

   vec3 diffuseColor;
   if (!texValid)
	 diffuseColor = vec3(fs_in.C);
   else
   	 uvtest = fs_in.uv;
	 uvtest.y = 1 - mod((uvtest.y - mod(distanceTraveled / 5.0, 21.991148575128552669238503682957) / 21.991148575128552669238503682957), 1.0); 
	 diffuseColor = texture(texObject, uvtest).rgb;

   vec3 L = vec3(0, 0, 0);
   vec4 resultingColor;
   resultingColor.xyz = diffuseColor;

   vec3 lighting = vec3(0.0, 0.0, 0.0);

   int specialValue;
   
   float Iamb = ambientLighting();

   for (int i = 0; i < MAX_NUM_OF_LIGHTS; i++)
   {

	   L = normalize(lightPosArray[i] - fs_in.position_attr.xyz);

	   // get Blinn-Phong reflectance components
	   float Idif = diffuseLighting(N, L);
	   float Ispe = specularLighting(N, L, V);


	 lighting += (Iamb + Idif + Ispe) * dropoffFunction(constArray[i], linearArray[i], quadArray[i],lightPosArray[i] , fs_in.position_attr, cutoffArray[i]) * lightColorArray[i];      

   }

   resultingColor.xyz = max(resultingColor.xyz * lighting, resultingColor.xyz * Iamb);

   if (!texValid)
	 resultingColor.a = fs_in.C.w;
   else
	 resultingColor.a = texture(texObject, fs_in.uv).w;

   gl_FragColor = resultingColor;

   //gl_FragColor = round(gl_FragColor * 8) / 8;
} 