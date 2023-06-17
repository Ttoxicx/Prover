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
	Renderer() {}
	~Renderer() {}
	Renderer(const Renderer& renderer) {}
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
private:
	//��Ⱦ���ݴ���
	std::shared_ptr<GeometryRenderBuffer> setUpMeshGeometryRenderBuffer(Mesh* mesh);
	std::shared_ptr<GeometryRenderBuffer> setUpLineGeometryRenderBuffer(Line* line);
	std::shared_ptr<GeometryRenderBuffer> setUpPointGeometryRenderBuffer(Point* point);
	void deleteGeometryRenderBuffer(GeometryRenderBuffer* buffer);
	void drawMesh(std::shared_ptr<MeshRenderUnit> mru);
	void drawLine(std::shared_ptr<LineRenderUnit> lru);
	void drawPoint(std::shared_ptr<PointRenderUnit> pru);
public:
	//������Ⱦ���
	void prepairToRender();
	void render();
	void prepairToEndRender();
	void postRender();
public:
	//֡�������
	//getFrameBuffer(camera,view,mode,buffertype)
private:
	//shaderͨ����������
	void setViewMatrix(Shader* shader);
	void setProjectionMatrix(Shader* shader);
	void setCameraPosition(Shader* shader);
	void updateShaderCommonAttribute(Shader* shader);
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
};

#endif // !1