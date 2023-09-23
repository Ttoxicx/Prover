#ifndef _RENDERER_H_
#define _RENDERER_H_

#include <set>
#include <vector>
#include <unordered_map>
#include <glm/glm.hpp>
#include <memory>

class Mesh;
class Line;
class Point;
class Camera;
class DirectionalLight;
class PointLight;
class SpotLight;
class GLShader;
class GLUniformProperties;

//��Ⱦ����
class GLRenderSetting {
public:
	//���޳�
	enum class FaceCullMode
	{
		CullFront,
		CullBack,
		Off
	};
	//�߿�ģʽ
	enum class WireFrameMode 
	{
		On,
		Off
	};

	GLRenderSetting() {}

	GLRenderSetting(FaceCullMode fcm, WireFrameMode wfm) {
		_fcm = fcm;
		_wfm = wfm;
	}
public:
	inline FaceCullMode getFaceCullMode() { return _fcm; }
	inline WireFrameMode getWireFrameMode() { return _wfm; }
private:
	FaceCullMode _fcm = FaceCullMode::CullBack;
	WireFrameMode _wfm = WireFrameMode::Off;
};

//������Ⱦ��Ԫ
struct GLMeshRenderUnit {
	std::shared_ptr<Mesh> mesh;
	std::shared_ptr<GLShader> shader;
	GLRenderSetting renderSet;
};
struct GLLineRenderUnit {
	std::shared_ptr<Line> line;
	std::shared_ptr<GLShader> shader;
	GLRenderSetting renderSet;
};
struct GLPointRenderUnit {
	std::shared_ptr<Point> point;
	std::shared_ptr<GLShader> shader;
	GLRenderSetting renderSet;
};


//������Ⱦbuffer
struct GLGeometryRenderBuffer {
	std::shared_ptr<unsigned int> VAO;
	std::shared_ptr<unsigned int> VBO;
	std::shared_ptr<unsigned int> EBO;
};

//��Ⱦ��
class GLRenderer {
public:
	GLRenderer();
	~GLRenderer();
	GLRenderer(const GLRenderer& renderer);
public:
	inline void setMainCamera(std::shared_ptr<Camera> camera) { _mainCamera = camera; };
	inline std::shared_ptr<Camera> getMainCamera() { return _mainCamera; }
public:
	//�������
	inline void addMeshRenderUnit(std::shared_ptr<GLMeshRenderUnit> mru) { _meshRenderUnitsAdd.push_back(mru); }
	inline void addLineRenderUnit(std::shared_ptr<GLLineRenderUnit> lru) { _lineRenderUnitsAdd.push_back(lru); }
	inline void addPointRenderUnit(std::shared_ptr<GLPointRenderUnit> pru) { _pointRenderUnitsAdd.push_back(pru); }
	inline void removeMeshRenderUnit(std::shared_ptr<GLMeshRenderUnit> mru) { _meshRenderUnitsRemove.push_back(mru); }
	inline void removeLineRenderUnit(std::shared_ptr<GLLineRenderUnit> lru) { _lineRenderUnitsRemove.push_back(lru); }
	inline void removePointRenderUnit(std::shared_ptr<GLPointRenderUnit> pru) { _pointRenderUnitsRemove.push_back(pru); }
public:
	//������Ⱦ���
	void prepairToRender();
	void render();
	void prepairToEndRender();
	void postRender();
public:
	//֡�������
	//getFrameBuffer(camera,view,mode,buffertype)
public:
	//�������
	void addDirectionalLight(std::shared_ptr<DirectionalLight> light);
	void addPointLight(std::shared_ptr<PointLight> light);
	void addSpotLight(std::shared_ptr<SpotLight> light);
	void removeDirectionalLight(std::shared_ptr<DirectionalLight> light);
	void removePointLight(std::shared_ptr<PointLight> light);
	void removeSpotLight(std::shared_ptr<SpotLight> light);
private:
	//��Ⱦ���ݴ���
	std::shared_ptr<GLGeometryRenderBuffer> setUpMeshGeometryRenderBuffer(Mesh* mesh);
	std::shared_ptr<GLGeometryRenderBuffer> setUpLineGeometryRenderBuffer(Line* line);
	std::shared_ptr<GLGeometryRenderBuffer> setUpPointGeometryRenderBuffer(Point* point);
	void deleteGeometryRenderBuffer(GLGeometryRenderBuffer* buffer);
	void drawMesh(std::shared_ptr<GLMeshRenderUnit> mru);
	void drawLine(std::shared_ptr<GLLineRenderUnit> lru);
	void drawPoint(std::shared_ptr<GLPointRenderUnit> pru);
private:
	//shaderͨ����������
	void setViewMatrix();
	void setProjectionMatrix();
	void setCameraPosition();
	void updateShaderCommonAttribute();
private:
	//������ӵ���Ⱦ��Ԫ
	std::vector<std::shared_ptr<GLMeshRenderUnit>> _meshRenderUnitsAdd;
	std::vector<std::shared_ptr<GLLineRenderUnit>> _lineRenderUnitsAdd;
	std::vector<std::shared_ptr<GLPointRenderUnit>> _pointRenderUnitsAdd;
	//�����Ƴ�����Ⱦ��Ԫ
	std::vector<std::shared_ptr<GLMeshRenderUnit>> _meshRenderUnitsRemove;
	std::vector<std::shared_ptr<GLLineRenderUnit>> _lineRenderUnitsRemove;
	std::vector<std::shared_ptr<GLPointRenderUnit>> _pointRenderUnitsRemove;
	//ʵ����Ⱦ����Ⱦ��Ԫ
	std::set<std::shared_ptr<GLMeshRenderUnit>> _meshRenderUnits;
	std::set<std::shared_ptr<GLLineRenderUnit>> _lineRenderUnits;
	std::set<std::shared_ptr<GLPointRenderUnit>> _pointRenderUnits;
	//ʵ����Ⱦ����
	std::unordered_map<std::shared_ptr<GLMeshRenderUnit>, std::shared_ptr<GLGeometryRenderBuffer>> _meshRenderMapping;
	std::unordered_map<std::shared_ptr<GLLineRenderUnit>, std::shared_ptr<GLGeometryRenderBuffer>> _lineRenderMapping;
	std::unordered_map<std::shared_ptr<GLPointRenderUnit>, std::shared_ptr<GLGeometryRenderBuffer>> _pointRenderMapping;
private:
	//��Ⱦ�ӿ����
	std::shared_ptr<Camera> _mainCamera;
	std::shared_ptr<GLUniformProperties> _uniformProperties;
};

#endif // !1