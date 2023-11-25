#include "../Common/Core.glsl"

uniform vec3 ambientColor;
uniform vec3 diffuseColor;
uniform vec3 specularColor;
uniform vec3 maxAmbient;
uniform vec3 maxDiffuse;
uniform vec3 maxSpecular;
uniform sampler2D ambinetTex;
uniform sampler2D diffuseTex;
uniform sampler2D specularTex;
uniform sampler2D normalTex;
uniform float shininess;
uniform bool useTexture;

in vec3 fragPos;
in vec3 normal;
in vec3 tangent;
in vec3 color;
in vec2 texCoord;
in vec3 eyePos;

//将切线空间的法线转到世界空间
vec3 calculateNormal()
{
	vec3 T=normalize(tangent);
	vec3 N=normalize(normal);
	T=normalize(T-dot(T,N)*N);
	vec3 B=normalize(cross(T,N));
	mat3 TBN=mat3(T,B,N);
	vec3 tangentSpaceNormal=texture(normalTex,texCoord).xyz;
	tangentSpaceNormal=tangentSpaceNormal*2.0f-1.0f;
	return normalize(TBN*tangentSpaceNormal);
}

//计算平行光光照
vec3 calculateDirectionalLight(DirectionalLight light,vec3 normal,vec3 ambinetColor,vec3 diffuseColor,vec3 specularColor)
{
	vec3 eyeDir=normalize(fragPos-eyePos);
	float diffuse=max(dot(-light.lightDir,normal),0.0);
	float specular=pow(max(dot(reflect(light.lightDir,normal),-eyeDir),0.0),shininess);
	vec3 ambientResult=maxAmbient*light.lightColor*ambinetColor;
	vec3 diffuseResult=diffuse*maxDiffuse*light.lightColor*diffuseColor;
	vec3 specularResult=specular*maxSpecular*light.lightColor*specularColor;
	return vec3(ambientResult+diffuseResult+specularResult);
}

//计算点光光照
vec3 calculatePointLightColor(PointLight light,vec3 normal,vec3 ambinetColor,vec3 diffuseColor,vec3 specularColor)
{
	vec3 lightDir=normalize(fragPos-light.lightPos);
	vec3 eyeDir=normalize(fragPos-eyePos);
	float dist=distance(fragPos,light.lightPos);
	float ratio=1.0f/(light.constant+dist*light.linear+dist*dist*light.quadratic);
	vec3 ambientResult=maxAmbient*ambinetColor*light.lightColor;
	vec3 diffuseResult=max(dot(-lightDir,normal),0.0f)*maxDiffuse*diffuseColor*light.lightColor*ratio;
	vec3 specularResult=pow(max(dot(reflect(lightDir,normal),-eyeDir),0.0f),32.0f)*maxSpecular*specularColor*light.lightColor*ratio;
	return vec3(ambientResult+diffuseResult+specularResult);
}

//计算聚光
vec3 calculateSpotLight(SpotLight light,vec3 normal,vec3 ambinetColor,vec3 diffuseColor,vec3 specularColor)
{
	vec3 lightDir=normalize(fragPos-light.lightPos);
	vec3 eyeDir=normalize(fragPos-eyePos);
	float range;
	float currentCos=dot(lightDir,light.lightDir);
	if(currentCos<light.outerCos){
		range=0.f;
	}
	if(currentCos>light.innerCos){
		range=1.f;
	}
	if(light.outerCos<currentCos&&currentCos<light.innerCos){
		range=(currentCos-light.outerCos)/(light.innerCos-light.outerCos);
	}
	float diffuse=max(dot(-lightDir,normal),0.0f);
	float specular=pow(max(dot(reflect(lightDir,normal),-eyeDir),0.0),shininess);
	vec3 ambientResult=maxAmbient*light.lightColor*ambinetColor;
	vec3 diffuseResult= range*diffuse*maxDiffuse*light.lightColor*diffuseColor;
	vec3 specularResult=range*specular*maxSpecular*light.lightColor*specularColor;
	return vec3(ambientResult+diffuseResult+specularResult+range);
}
void main()
{
	maxAmbient;
	maxDiffuse;
	maxSpecular;
	shininess;
	vec3 nReal;
	vec3 ambientReal;
	vec3 diffuseReal;
	vec3 specularReal;
	if(useTexture){
		nReal=calculateNormal();
		ambientReal=texture(ambinetTex,texCoord).xyz;
		diffuseReal=texture(diffuseTex,texCoord).xyz;
		specularReal=texture(specularTex,texCoord).xyz;
	}else{
		nReal=normal;
		ambientReal=ambientColor;
		diffuseReal=diffuseColor;
		specularReal=specularColor;
	}
	vec3 directionalResult;
	vec3 pointLightResult;
	vec3 spotLightResult;
	for(uint i=0;i<g_DirectionalLightCount;++i){
		directionalResult+=calculateDirectionalLight(g_DirectionalLight[i],normal,ambientReal,diffuseReal,specularReal);
	}
	for(uint i=0;i<g_PointLightCount;++i){
		pointLightResult+=calculatePointLightColor(g_PointLight[i],normal,ambientReal,diffuseReal,specularReal);
	}
	for(uint i=0;i<g_SpotLightCount;++i){
		spotLightResult+=calculateSpotLight(g_SpotLight[i],normal,ambientReal,diffuseReal,specularReal);
	}

	//todo 处理高动态范围

	gl_FragColor=vec4(directionalResult+pointLightResult+spotLightResult,1.f);
}