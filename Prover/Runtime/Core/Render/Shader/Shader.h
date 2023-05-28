#ifndef _SHADER_H_
#define _SHADER_H_

#include <glm/glm.hpp>

class Shader {
public:
	Shader(const char* vscPath, const char* fscPath, const char* gscPath);
	Shader(const char* vscPath, const char* fscPath);
	Shader(const char* vscPath);
public:
	inline int isShaderBuildSuccessful() { return _buildSuccess; }
	inline unsigned int getShaderId() { return _shaderProgramId; }
	void getShaderCondition();
public:
	void setParameters1b(const char* property, bool val);
	void setParameters2b(const char* property, const glm::bvec2& vec2);
	void setParameters3b(const char* property, const glm::bvec3& vec3);
	void setParameters4b(const char* property, const glm::bvec4& vec4);
	void setParameters1i(const char* property, int val);
	void setParameters2i(const char* property, const glm::ivec2& vec2);
	void setParameters3i(const char* property, const glm::ivec3& vec3);
	void setParameters4i(const char* property, const glm::ivec4& vec4);
	void setParameters1ui(const char* property, unsigned int val);
	void setParameters2ui(const char* property, const glm::uvec2& vec2);
	void setParameters3ui(const char* property, const glm::uvec3& vec3);
	void setParameters4ui(const char* property, const glm::uvec4& vec4);
	void setParameters1f(const char* property, float val);
	void setParameters2f(const char* property, const glm::vec2& vec2);
	void setParameters3f(const char* property, const glm::vec3& vec3);
	void setParameters4f(const char* property, const glm::vec4& vec4);
	void setParameters1d(const char* property, double val);
	void setParameters2d(const char* property, const glm::dvec2& vec2);
	void setParameters3d(const char* property, const glm::dvec3& vec3);
	void setParameters4d(const char* property, const glm::dvec4& vec4);
	void setParametersMat2f(const char* property, const glm::mat2& mat2);
	void setParametersMat3f(const char* property, const glm::mat3& mat3);
	void setParametersMat4f(const char* property, const glm::mat4& mat4);
	void setParametersMat2d(const char* property, const glm::dmat2& mat2);
	void setParametersMat3d(const char* property, const glm::dmat3& mat3);
	void setParametersMat4d(const char* property, const glm::dmat4& mat4);
private:
	enum class SHADER_TYPE {
		VERT,
		FRAG,
		GEOM
	};
	enum class PROGRAM_TYPE {
		VERT_ONLY,
		VERT_FRAG,
		VERT_GEOM_FRAG
	};
	void loadandCompileSubShader(const char* path, SHADER_TYPE type);
	void createShader(PROGRAM_TYPE type);
private:
	unsigned int _shaderProgramId = 0;
	unsigned int _vertShaderId = 0;
	unsigned int _fragShaderId = 0;
	unsigned int _geomShaderId = 0;
private:
	int _buildSuccess;
	unsigned int _errorId;
};

#endif // !_SHADER_H_