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

//渲染设置
class RenderSetting {
public:
	//面剔除
	enum class FaceCullMode
	{
		CullFront,
		CullBack,
		Off
	};
	//线框模式
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

//各类渲染单元
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


//几何渲染buffer
struct GeometryRenderBuffer {
	unsigned int* VAO;
	unsigned int* VBO;
	unsigned int* EBO;
};


//渲染器
class Renderer {
public:
	Renderer() {}
	~Renderer() {}
	Renderer(const Renderer& renderer) {}
public:
	void setMainCamera(Camera* camera) { _mainCamera = camera; };
public:
	//场景相关
	inline void addMeshRenderUnit(MeshRenderUnit* mru) { _meshRenderUnitsAdd.push_back(mru); }
	inline void addLineRenderUnit(LineRenderUnit* lru) { _lineRenderUnitsAdd.push_back(lru); }
	inline void addPointRenderUnit(PointRenderUnit* pru) { _pointRenderUnitsAdd.push_back(pru); }
	inline void removeMeshRenderUnit(MeshRenderUnit* mru) { _meshRenderUnitsRemove.push_back(mru); }
	inline void removeLineRenderUnit(LineRenderUnit* lru) { _lineRenderUnitsRemove.push_back(lru); }
	inline void removePointRenderUnit(PointRenderUnit* pru) { _pointRenderUnitsRemove.push_back(pru); }
private:
	//渲染数据处理
	GeometryRenderBuffer* setUpMeshGeometryRenderBuffer(Mesh* mesh);
	GeometryRenderBuffer* setUpLineGeometryRenderBuffer(Line* line);
	GeometryRenderBuffer* setUpPointGeometryRenderBuffer(Point* point);
	void deleteGeometryRenderBuffer(GeometryRenderBuffer* buffer);
	void drawMesh(MeshRenderUnit* mru);
	void drawLine(LineRenderUnit* lru);
	void drawPoint(PointRenderUnit* pru);
public:
	//整体渲染相关
	void prepairToRender();
	void render();
	void prepairToEndRender();
	void postRender();
public:
	//帧缓冲相关
	//getFrameBuffer(camera,view,mode,buffertype)
private:
	//shader通用属性设置
	void setViewMatrix(Shader* shader);
	void setProjectionMatrix(Shader* shader);
	void setCameraPosition(Shader* shader);
	void updateShaderCommonAttribute(Shader* shader);
private:
	//即将添加的渲染单元
	std::vector<MeshRenderUnit*> _meshRenderUnitsAdd;
	std::vector<LineRenderUnit*> _lineRenderUnitsAdd;
	std::vector<PointRenderUnit*> _pointRenderUnitsAdd;
	//即将移除的渲染单元
	std::vector<MeshRenderUnit*> _meshRenderUnitsRemove;
	std::vector<LineRenderUnit*> _lineRenderUnitsRemove;
	std::vector<PointRenderUnit*> _pointRenderUnitsRemove;
	//实际渲染的渲染单元
	std::set<MeshRenderUnit*> _meshRenderUnits;
	std::set<LineRenderUnit*> _lineRenderUnits;
	std::set<PointRenderUnit*> _pointRenderUnits;
	//实际渲染缓冲
	std::unordered_map<MeshRenderUnit*, GeometryRenderBuffer*> _meshRenderMapping;
	std::unordered_map<LineRenderUnit*, GeometryRenderBuffer*> _lineRenderMapping;
	std::unordered_map<PointRenderUnit*, GeometryRenderBuffer*> _pointRenderMapping;
private:
	//渲染视口相关
	Camera* _mainCamera = nullptr;
};

#endif // !1