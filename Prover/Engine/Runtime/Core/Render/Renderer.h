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
class Shader;
class Camera;
class UniformProperties;
class DirectionalLight;
class PointLight;
class SpotLight;

//��Ⱦ����
class RenderSetting {
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

	RenderSetting() {}

	RenderSetting(FaceCullMode fcm, WireFrameMode wfm) {
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
struct MeshRenderUnit {
	std::shared_ptr<Mesh> mesh;
	std::shared_ptr<Shader> shader;
	RenderSetting renderSet;
};
struct LineRenderUnit {
	std::shared_ptr<Line> line;
	std::shared_ptr<Shader> shader;
	RenderSetting renderSet;
};
struct PointRenderUnit {
	std::shared_ptr<Point> point;
	std::shared_ptr<Shader> shader;
	RenderSetting renderSet;
};


//������Ⱦbuffer
struct GeometryRenderBuffer {
	std::shared_ptr<unsigned int> VAO;
	std::shared_ptr<unsigned int> VBO;
	std::shared_ptr<unsigned int> EBO;
};

//��Ⱦ��
class Renderer {
public:
	Renderer();
	~Renderer();
	Renderer(const Renderer& renderer);
public:
	inline void setMainCamera(std::shared_ptr<Camera> camera) { _mainCamera = camera; };
	inline std::shared_ptr<Camera> getMainCamera() { return _mainCamera; }
public:
	//�������
	inline void addMeshRenderUnit(std::shared_ptr<MeshRenderUnit> mru) { _meshRenderUnitsAdd.push_back(mru); }
	inline void addLineRenderUnit(std::shared_ptr<LineRenderUnit> lru) { _lineRenderUnitsAdd.push_back(lru); }
	inline void addPointRenderUnit(std::shared_ptr<PointRenderUnit> pru) { _pointRenderUnitsAdd.push_back(pru); }
	inline void removeMeshRenderUnit(std::shared_ptr<MeshRenderUnit> mru) { _meshRenderUnitsRemove.push_back(mru); }
	inline void removeLineRenderUnit(std::shared_ptr<LineRenderUnit> lru) { _lineRenderUnitsRemove.push_back(lru); }
	inline void removePointRenderUnit(std::shared_ptr<PointRenderUnit> pru) { _pointRenderUnitsRemove.push_back(pru); }
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
	std::shared_ptr<GeometryRenderBuffer> setUpMeshGeometryRenderBuffer(Mesh* mesh);
	std::shared_ptr<GeometryRenderBuffer> setUpLineGeometryRenderBuffer(Line* line);
	std::shared_ptr<GeometryRenderBuffer> setUpPointGeometryRenderBuffer(Point* point);
	void deleteGeometryRenderBuffer(GeometryRenderBuffer* buffer);
	void drawMesh(std::shared_ptr<MeshRenderUnit> mru);
	void drawLine(std::shared_ptr<LineRenderUnit> lru);
	void drawPoint(std::shared_ptr<PointRenderUnit> pru);
private:
	//shaderͨ����������
	void setViewMatrix();
	void setProjectionMatrix();
	void setCameraPosition();
	void updateShaderCommonAttribute();
private:
	//������ӵ���Ⱦ��Ԫ
	std::vector<std::shared_ptr<MeshRenderUnit>> _meshRenderUnitsAdd;
	std::vector<std::shared_ptr<LineRenderUnit>> _lineRenderUnitsAdd;
	std::vector<std::shared_ptr<PointRenderUnit>> _pointRenderUnitsAdd;
	//�����Ƴ�����Ⱦ��Ԫ
	std::vector<std::shared_ptr<MeshRenderUnit>> _meshRenderUnitsRemove;
	std::vector<std::shared_ptr<LineRenderUnit>> _lineRenderUnitsRemove;
	std::vector<std::shared_ptr<PointRenderUnit>> _pointRenderUnitsRemove;
	//ʵ����Ⱦ����Ⱦ��Ԫ
	std::set<std::shared_ptr<MeshRenderUnit>> _meshRenderUnits;
	std::set<std::shared_ptr<LineRenderUnit>> _lineRenderUnits;
	std::set<std::shared_ptr<PointRenderUnit>> _pointRenderUnits;
	//ʵ����Ⱦ����
	std::unordered_map<std::shared_ptr<MeshRenderUnit>, std::shared_ptr<GeometryRenderBuffer>> _meshRenderMapping;
	std::unordered_map<std::shared_ptr<LineRenderUnit>, std::shared_ptr<GeometryRenderBuffer>> _lineRenderMapping;
	std::unordered_map<std::shared_ptr<PointRenderUnit>, std::shared_ptr<GeometryRenderBuffer>> _pointRenderMapping;
private:
	//��Ⱦ�ӿ����
	std::shared_ptr<Camera> _mainCamera;
	std::shared_ptr<UniformProperties> _uniformProperties;
};

#endif // !1