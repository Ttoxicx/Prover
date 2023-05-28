#ifndef _RENDERER_H_
#define _RENDERER_H_
#include <set>
#include <vector>
#include <unordered_map>
#include <glm/glm.hpp>

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
	Mesh* mesh;
	Shader* shader;
	RenderSetting renderSet;
};
struct LineRenderUnit {
	Line* line;
	Shader* shader;
	RenderSetting renderSet;
};
struct PointRenderUnit {
	Point* point;
	Shader* shader;
	RenderSetting renderSet;
};


//������Ⱦbuffer
struct GeometryRenderBuffer {
	unsigned int* VAO;
	unsigned int* VBO;
	unsigned int* EBO;
};


//��Ⱦ��
class Renderer {
public:
	Renderer() {}
	~Renderer() {}
	Renderer(const Renderer& renderer) {}
public:
	void setMainCamera(Camera* camera) { _mainCamera = camera; };
public:
	//�������
	inline void addMeshRenderUnit(MeshRenderUnit* mru) { _meshRenderUnitsAdd.push_back(mru); }
	inline void addLineRenderUnit(LineRenderUnit* lru) { _lineRenderUnitsAdd.push_back(lru); }
	inline void addPointRenderUnit(PointRenderUnit* pru) { _pointRenderUnitsAdd.push_back(pru); }
	inline void removeMeshRenderUnit(MeshRenderUnit* mru) { _meshRenderUnitsRemove.push_back(mru); }
	inline void removeLineRenderUnit(LineRenderUnit* lru) { _lineRenderUnitsRemove.push_back(lru); }
	inline void removePointRenderUnit(PointRenderUnit* pru) { _pointRenderUnitsRemove.push_back(pru); }
private:
	//��Ⱦ���ݴ���
	GeometryRenderBuffer* setUpMeshGeometryRenderBuffer(Mesh* mesh);
	GeometryRenderBuffer* setUpLineGeometryRenderBuffer(Line* line);
	GeometryRenderBuffer* setUpPointGeometryRenderBuffer(Point* point);
	void deleteGeometryRenderBuffer(GeometryRenderBuffer* buffer);
	void drawMesh(MeshRenderUnit* mru);
	void drawLine(LineRenderUnit* lru);
	void drawPoint(PointRenderUnit* pru);
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
	std::vector<MeshRenderUnit*> _meshRenderUnitsAdd;
	std::vector<LineRenderUnit*> _lineRenderUnitsAdd;
	std::vector<PointRenderUnit*> _pointRenderUnitsAdd;
	//�����Ƴ�����Ⱦ��Ԫ
	std::vector<MeshRenderUnit*> _meshRenderUnitsRemove;
	std::vector<LineRenderUnit*> _lineRenderUnitsRemove;
	std::vector<PointRenderUnit*> _pointRenderUnitsRemove;
	//ʵ����Ⱦ����Ⱦ��Ԫ
	std::set<MeshRenderUnit*> _meshRenderUnits;
	std::set<LineRenderUnit*> _lineRenderUnits;
	std::set<PointRenderUnit*> _pointRenderUnits;
	//ʵ����Ⱦ����
	std::unordered_map<MeshRenderUnit*, GeometryRenderBuffer*> _meshRenderMapping;
	std::unordered_map<LineRenderUnit*, GeometryRenderBuffer*> _lineRenderMapping;
	std::unordered_map<PointRenderUnit*, GeometryRenderBuffer*> _pointRenderMapping;
private:
	//��Ⱦ�ӿ����
	Camera* _mainCamera = nullptr;
};

#endif // !1