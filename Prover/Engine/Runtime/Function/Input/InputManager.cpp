#include "Input/InputManager.h"

const std::map<InputKey, unsigned int> InputKeyGlfwMapping
{
	/* The unknown key */
	std::pair<InputKey,unsigned int>(InputKey::UNKNOWN            ,GLFW_KEY_UNKNOWN),

	/* Printable keys */
	std::pair<InputKey,unsigned int>(InputKey::SPACE              ,GLFW_KEY_SPACE),
	std::pair<InputKey,unsigned int>(InputKey::APOSTROPHE         ,GLFW_KEY_APOSTROPHE), /* ' */
	std::pair<InputKey,unsigned int>(InputKey::COMMA              ,GLFW_KEY_COMMA), /* , */
	std::pair<InputKey,unsigned int>(InputKey::MINUS              ,GLFW_KEY_MINUS), /* - */
	std::pair<InputKey,unsigned int>(InputKey::PERIOD             ,GLFW_KEY_PERIOD), /* . */
	std::pair<InputKey,unsigned int>(InputKey::SLASH              ,GLFW_KEY_SLASH), /* / */
	std::pair<InputKey,unsigned int>(InputKey::NUM_0              ,GLFW_KEY_0),
	std::pair<InputKey,unsigned int>(InputKey::NUM_1              ,GLFW_KEY_1),
	std::pair<InputKey,unsigned int>(InputKey::NUM_2              ,GLFW_KEY_2),
	std::pair<InputKey,unsigned int>(InputKey::NUM_3              ,GLFW_KEY_3),
	std::pair<InputKey,unsigned int>(InputKey::NUM_4              ,GLFW_KEY_4),
	std::pair<InputKey,unsigned int>(InputKey::NUM_5              ,GLFW_KEY_5),
	std::pair<InputKey,unsigned int>(InputKey::NUM_6              ,GLFW_KEY_6),
	std::pair<InputKey,unsigned int>(InputKey::NUM_7              ,GLFW_KEY_7),
	std::pair<InputKey,unsigned int>(InputKey::NUM_8              ,GLFW_KEY_8),
	std::pair<InputKey,unsigned int>(InputKey::NUM_9              ,GLFW_KEY_9),
	std::pair<InputKey,unsigned int>(InputKey::SEMICOLON          ,GLFW_KEY_SEMICOLON), /* ; */
	std::pair<InputKey,unsigned int>(InputKey::EQUAL              ,GLFW_KEY_EQUAL), /* = */
	std::pair<InputKey,unsigned int>(InputKey::A                  ,GLFW_KEY_A),
	std::pair<InputKey,unsigned int>(InputKey::B                  ,GLFW_KEY_B),
	std::pair<InputKey,unsigned int>(InputKey::C                  ,GLFW_KEY_C),
	std::pair<InputKey,unsigned int>(InputKey::D                  ,GLFW_KEY_D),
	std::pair<InputKey,unsigned int>(InputKey::E                  ,GLFW_KEY_E),
	std::pair<InputKey,unsigned int>(InputKey::F                  ,GLFW_KEY_F),
	std::pair<InputKey,unsigned int>(InputKey::G                  ,GLFW_KEY_G),
	std::pair<InputKey,unsigned int>(InputKey::H                  ,GLFW_KEY_H),
	std::pair<InputKey,unsigned int>(InputKey::I                  ,GLFW_KEY_I),
	std::pair<InputKey,unsigned int>(InputKey::J                  ,GLFW_KEY_J),
	std::pair<InputKey,unsigned int>(InputKey::K                  ,GLFW_KEY_K),
	std::pair<InputKey,unsigned int>(InputKey::L                  ,GLFW_KEY_L),
	std::pair<InputKey,unsigned int>(InputKey::M                  ,GLFW_KEY_M),
	std::pair<InputKey,unsigned int>(InputKey::N                  ,GLFW_KEY_N),
	std::pair<InputKey,unsigned int>(InputKey::O                  ,GLFW_KEY_O),
	std::pair<InputKey,unsigned int>(InputKey::P                  ,GLFW_KEY_P),
	std::pair<InputKey,unsigned int>(InputKey::Q                  ,GLFW_KEY_Q),
	std::pair<InputKey,unsigned int>(InputKey::R                  ,GLFW_KEY_R),
	std::pair<InputKey,unsigned int>(InputKey::S                  ,GLFW_KEY_S),
	std::pair<InputKey,unsigned int>(InputKey::T                  ,GLFW_KEY_T),
	std::pair<InputKey,unsigned int>(InputKey::U                  ,GLFW_KEY_U),
	std::pair<InputKey,unsigned int>(InputKey::V                  ,GLFW_KEY_V),
	std::pair<InputKey,unsigned int>(InputKey::W                  ,GLFW_KEY_W),
	std::pair<InputKey,unsigned int>(InputKey::X                  ,GLFW_KEY_X),
	std::pair<InputKey,unsigned int>(InputKey::Y                  ,GLFW_KEY_Y),
	std::pair<InputKey,unsigned int>(InputKey::Z                  ,GLFW_KEY_Z),
	std::pair<InputKey,unsigned int>(InputKey::LEFT_BRACKET       ,GLFW_KEY_LEFT_BRACKET), /* [ */
	std::pair<InputKey,unsigned int>(InputKey::BACKSLASH          ,GLFW_KEY_BACKSLASH), /* \ */
	std::pair<InputKey,unsigned int>(InputKey::RIGHT_BRACKET      ,GLFW_KEY_RIGHT_BRACKET), /* ] */
	std::pair<InputKey,unsigned int>(InputKey::GRAVE_ACCENT       ,GLFW_KEY_GRAVE_ACCENT), /* ` */
	std::pair<InputKey,unsigned int>(InputKey::WORLD_1            ,GLFW_KEY_WORLD_1), /* non-US #1 */
	std::pair<InputKey,unsigned int>(InputKey::WORLD_2            ,GLFW_KEY_WORLD_2), /* non-US #2 */

	/* Function keys */
	std::pair<InputKey,unsigned int>(InputKey::ESCAPE             ,GLFW_KEY_ESCAPE),
	std::pair<InputKey,unsigned int>(InputKey::ENTER              ,GLFW_KEY_ENTER),
	std::pair<InputKey,unsigned int>(InputKey::TAB                ,GLFW_KEY_TAB),
	std::pair<InputKey,unsigned int>(InputKey::BACKSPACE          ,GLFW_KEY_BACKSPACE),
	std::pair<InputKey,unsigned int>(InputKey::INSERT             ,GLFW_KEY_INSERT),
	std::pair<InputKey,unsigned int>(InputKey::DELETE             ,GLFW_KEY_DELETE),
	std::pair<InputKey,unsigned int>(InputKey::RIGHT              ,GLFW_KEY_RIGHT),
	std::pair<InputKey,unsigned int>(InputKey::LEFT               ,GLFW_KEY_LEFT),
	std::pair<InputKey,unsigned int>(InputKey::DOWN               ,GLFW_KEY_DOWN),
	std::pair<InputKey,unsigned int>(InputKey::UP                 ,GLFW_KEY_UP),
	std::pair<InputKey,unsigned int>(InputKey::PAGE_UP            ,GLFW_KEY_PAGE_UP),
	std::pair<InputKey,unsigned int>(InputKey::PAGE_DOWN          ,GLFW_KEY_PAGE_DOWN),
	std::pair<InputKey,unsigned int>(InputKey::HOME               ,GLFW_KEY_HOME),
	std::pair<InputKey,unsigned int>(InputKey::END                ,GLFW_KEY_END),
	std::pair<InputKey,unsigned int>(InputKey::CAPS_LOCK          ,GLFW_KEY_CAPS_LOCK),
	std::pair<InputKey,unsigned int>(InputKey::SCROLL_LOCK        ,GLFW_KEY_SCROLL_LOCK),
	std::pair<InputKey,unsigned int>(InputKey::NUM_LOCK           ,GLFW_KEY_NUM_LOCK),
	std::pair<InputKey,unsigned int>(InputKey::PRINT_SCREEN       ,GLFW_KEY_PRINT_SCREEN),
	std::pair<InputKey,unsigned int>(InputKey::PAUSE              ,GLFW_KEY_PAUSE),
	std::pair<InputKey,unsigned int>(InputKey::F1                 ,GLFW_KEY_F1),
	std::pair<InputKey,unsigned int>(InputKey::F2                 ,GLFW_KEY_F2),
	std::pair<InputKey,unsigned int>(InputKey::F3                 ,GLFW_KEY_F3),
	std::pair<InputKey,unsigned int>(InputKey::F4                 ,GLFW_KEY_F4),
	std::pair<InputKey,unsigned int>(InputKey::F5                 ,GLFW_KEY_F5),
	std::pair<InputKey,unsigned int>(InputKey::F6                 ,GLFW_KEY_F6),
	std::pair<InputKey,unsigned int>(InputKey::F7                 ,GLFW_KEY_F7),
	std::pair<InputKey,unsigned int>(InputKey::F8                 ,GLFW_KEY_F8),
	std::pair<InputKey,unsigned int>(InputKey::F9                 ,GLFW_KEY_F9),
	std::pair<InputKey,unsigned int>(InputKey::F10                ,GLFW_KEY_F10),
	std::pair<InputKey,unsigned int>(InputKey::F11                ,GLFW_KEY_F11),
	std::pair<InputKey,unsigned int>(InputKey::F12                ,GLFW_KEY_F12),
	std::pair<InputKey,unsigned int>(InputKey::F13                ,GLFW_KEY_F13),
	std::pair<InputKey,unsigned int>(InputKey::F14                ,GLFW_KEY_F14),
	std::pair<InputKey,unsigned int>(InputKey::F15                ,GLFW_KEY_F15),
	std::pair<InputKey,unsigned int>(InputKey::F16                ,GLFW_KEY_F16),
	std::pair<InputKey,unsigned int>(InputKey::F17                ,GLFW_KEY_F17),
	std::pair<InputKey,unsigned int>(InputKey::F18                ,GLFW_KEY_F18),
	std::pair<InputKey,unsigned int>(InputKey::F19                ,GLFW_KEY_F19),
	std::pair<InputKey,unsigned int>(InputKey::F20                ,GLFW_KEY_F20),
	std::pair<InputKey,unsigned int>(InputKey::F21                ,GLFW_KEY_F21),
	std::pair<InputKey,unsigned int>(InputKey::F22                ,GLFW_KEY_F22),
	std::pair<InputKey,unsigned int>(InputKey::F23                ,GLFW_KEY_F23),
	std::pair<InputKey,unsigned int>(InputKey::F24                ,GLFW_KEY_F24),
	std::pair<InputKey,unsigned int>(InputKey::F25                ,GLFW_KEY_F25),
	std::pair<InputKey,unsigned int>(InputKey::KP_0               ,GLFW_KEY_KP_0),
	std::pair<InputKey,unsigned int>(InputKey::KP_1               ,GLFW_KEY_KP_1),
	std::pair<InputKey,unsigned int>(InputKey::KP_2               ,GLFW_KEY_KP_2),
	std::pair<InputKey,unsigned int>(InputKey::KP_3               ,GLFW_KEY_KP_3),
	std::pair<InputKey,unsigned int>(InputKey::KP_4               ,GLFW_KEY_KP_4),
	std::pair<InputKey,unsigned int>(InputKey::KP_5               ,GLFW_KEY_KP_5),
	std::pair<InputKey,unsigned int>(InputKey::KP_6               ,GLFW_KEY_KP_6),
	std::pair<InputKey,unsigned int>(InputKey::KP_7               ,GLFW_KEY_KP_7),
	std::pair<InputKey,unsigned int>(InputKey::KP_8               ,GLFW_KEY_KP_8),
	std::pair<InputKey,unsigned int>(InputKey::KP_9               ,GLFW_KEY_KP_9),
	std::pair<InputKey,unsigned int>(InputKey::KP_DECIMAL         ,GLFW_KEY_KP_DECIMAL),
	std::pair<InputKey,unsigned int>(InputKey::KP_DIVIDE          ,GLFW_KEY_KP_DIVIDE),
	std::pair<InputKey,unsigned int>(InputKey::KP_MULTIPLY        ,GLFW_KEY_KP_MULTIPLY),
	std::pair<InputKey,unsigned int>(InputKey::KP_SUBTRACT        ,GLFW_KEY_KP_SUBTRACT),
	std::pair<InputKey,unsigned int>(InputKey::KP_ADD             ,GLFW_KEY_KP_ADD),
	std::pair<InputKey,unsigned int>(InputKey::KP_ENTER           ,GLFW_KEY_KP_ENTER),
	std::pair<InputKey,unsigned int>(InputKey::KP_EQUAL           ,GLFW_KEY_KP_EQUAL),
	std::pair<InputKey,unsigned int>(InputKey::LEFT_SHIFT         ,GLFW_KEY_LEFT_SHIFT),
	std::pair<InputKey,unsigned int>(InputKey::LEFT_CONTROL       ,GLFW_KEY_LEFT_CONTROL),
	std::pair<InputKey,unsigned int>(InputKey::LEFT_ALT           ,GLFW_KEY_LEFT_ALT),
	std::pair<InputKey,unsigned int>(InputKey::LEFT_SUPER         ,GLFW_KEY_LEFT_SUPER),
	std::pair<InputKey,unsigned int>(InputKey::RIGHT_SHIFT        ,GLFW_KEY_RIGHT_SHIFT),
	std::pair<InputKey,unsigned int>(InputKey::RIGHT_CONTROL      ,GLFW_KEY_RIGHT_CONTROL),
	std::pair<InputKey,unsigned int>(InputKey::RIGHT_ALT          ,GLFW_KEY_RIGHT_ALT),
	std::pair<InputKey,unsigned int>(InputKey::RIGHT_SUPER        ,GLFW_KEY_RIGHT_SUPER),
	std::pair<InputKey,unsigned int>(InputKey::MENU               ,GLFW_KEY_MENU),

	/* Mouse buttons */
	std::pair<InputKey,unsigned int>(InputKey::MOUSE_BUTTON_1     ,GLFW_MOUSE_BUTTON_1),
	std::pair<InputKey,unsigned int>(InputKey::MOUSE_BUTTON_2     ,GLFW_MOUSE_BUTTON_2),
	std::pair<InputKey,unsigned int>(InputKey::MOUSE_BUTTON_3     ,GLFW_MOUSE_BUTTON_3),
	std::pair<InputKey,unsigned int>(InputKey::MOUSE_BUTTON_4     ,GLFW_MOUSE_BUTTON_4),
	std::pair<InputKey,unsigned int>(InputKey::MOUSE_BUTTON_5     ,GLFW_MOUSE_BUTTON_5),
	std::pair<InputKey,unsigned int>(InputKey::MOUSE_BUTTON_6     ,GLFW_MOUSE_BUTTON_6),
	std::pair<InputKey,unsigned int>(InputKey::MOUSE_BUTTON_7     ,GLFW_MOUSE_BUTTON_7),
	std::pair<InputKey,unsigned int>(InputKey::MOUSE_BUTTON_8     ,GLFW_MOUSE_BUTTON_8),
	std::pair<InputKey,unsigned int>(InputKey::MOUSE_BUTTON_LAST  ,GLFW_MOUSE_BUTTON_LAST),
	std::pair<InputKey,unsigned int>(InputKey::MOUSE_BUTTON_LEFT  ,GLFW_MOUSE_BUTTON_LEFT),
	std::pair<InputKey,unsigned int>(InputKey::MOUSE_BUTTON_RIGHT ,GLFW_MOUSE_BUTTON_RIGHT),
	std::pair<InputKey,unsigned int>(InputKey::MOUSE_BUTTON_MIDDLE,GLFW_MOUSE_BUTTON_MIDDLE)
};

std::shared_ptr<InputManager> InputManager::getInstance()
{
	if (_inputmanager == nullptr) {
		_inputmanager = std::make_shared<InputManager>();
	}
	return _inputmanager;
}

void InputManager::handleKeyInput(GLFWwindow* window)
{
	for (auto value : _keyMappingPress) {
		if (glfwGetKey(window, value.first) == GLFW_PRESS) {
			for (auto fun : value.second) {
				fun();
			}
		}
	}
	for (auto value : _keyMappingRelease) {
		if (glfwGetKey(window, value.first) == GLFW_RELEASE) {
			for (auto fun : value.second) {
				fun();
			}
		}
	}
	for (auto value : _keyMappingRepeat) {
		if (glfwGetKey(window, value.first) == GLFW_REPEAT) {
			for (auto fun : value.second) {
				fun();
			}
		}
	}
}

void InputManager::handleMouseXYCallBack(GLFWwindow* window, double x, double y)
{
	for (auto callback : _mouseXYCallBack) {
		callback(x, y);
	}
}

void InputManager::handleMouseSrollCallBack(GLFWwindow* window, double xval, double yval)
{
	for (auto callback : _mouseSrollCallBack) {
		callback(xval, yval);
	}
}

void InputManager::addKeyMapping(InputKey key, KeyState state, std::function<void()> callback)
{
	unsigned int glfwKey = InputKeyGlfwMapping.at(key);
	if (state == KeyState::PRESS) {
		if (_keyMappingPress.find(glfwKey) != _keyMappingPress.end()) {
			_keyMappingPress.emplace(glfwKey, std::vector<std::function<void()>>());
		}
		_keyMappingPress[glfwKey].push_back(callback);
	}
	if (state == KeyState::RELEASE) {
		if (_keyMappingRelease.find(glfwKey) != _keyMappingRelease.end()) {
			_keyMappingRelease.emplace(glfwKey, std::vector<std::function<void()>>());
		}
		_keyMappingRelease[glfwKey].push_back(callback);
	}
	if (state == KeyState::REPEAT) {
		if (_keyMappingRepeat.find(glfwKey) != _keyMappingRepeat.end()) {
			_keyMappingRepeat.emplace(glfwKey, std::vector<std::function<void()>>());
		}
		_keyMappingRepeat[glfwKey].push_back(callback);
	}
}

void InputManager::addMouseXYCallBack(std::function<void(double, double)> callback)
{
	_mouseXYCallBack.push_back(callback);
}

void InputManager::addMouseSrollCallBack(std::function<void(double, double)> callback)
{
	_mouseSrollCallBack.push_back(callback);
}

void InputManager::removeKeyMapping(InputKey key, KeyState state, std::function<void()> callback)
{
	unsigned int glfwKey = InputKeyGlfwMapping.at(key);
	if (state == KeyState::PRESS) {
		if (_keyMappingPress.find(glfwKey) == _keyMappingPress.end()) return;
		auto& callbacks = _keyMappingPress[glfwKey];
		auto itr = callbacks.begin();
		for (itr; itr != callbacks.end(); ++itr) {
			if ((*itr).target<void()>() == callback.target<void()>()) {
				callbacks.erase(itr);
				break;
			}
		}
	}
	if (state == KeyState::RELEASE) {
		if (_keyMappingRelease.find(glfwKey) == _keyMappingRelease.end()) return;
		auto& callbacks = _keyMappingRelease[glfwKey];
		auto itr = callbacks.begin();
		for (itr; itr != callbacks.end(); ++itr) {
			if ((*itr).target<void()>() == callback.target<void()>()) {
				callbacks.erase(itr);
				break;
			}
		}
	}
	if (state == KeyState::REPEAT) {
		if (_keyMappingRepeat.find(glfwKey) == _keyMappingRepeat.end()) return;
		auto& callbacks = _keyMappingRepeat[glfwKey];
		auto itr = callbacks.begin();
		for (itr; itr != callbacks.end(); ++itr) {
			if ((*itr).target<void()>() == callback.target<void()>()) {
				callbacks.erase(itr);
				break;
			}
		}
	}
}

void InputManager::removeMouseXYCallBack(std::function<void(double, double)> callback)
{
	auto itr = _mouseXYCallBack.begin();
	for (itr; itr != _mouseXYCallBack.end(); ++itr) {
		if ((*itr).target<void(double,double)>() == callback.target<void(double,double)>()) {
			_mouseXYCallBack.erase(itr);
			break;
		}
	}
}

void InputManager::removeMouseSrollCallBack(std::function<void(double, double)> callback)
{
	auto itr = _mouseSrollCallBack.begin();
	for (itr; itr != _mouseSrollCallBack.end(); ++itr) {
		if ((*itr).target<void(double, double)>() == callback.target<void(double, double)>()) {
			_mouseSrollCallBack.erase(itr);
			break;
		}
	}
}

std::map<unsigned int, std::vector<std::function<void()>>> InputManager::_keyMappingRelease;
std::map<unsigned int, std::vector<std::function<void()>>> InputManager::_keyMappingPress;
std::map<unsigned int, std::vector<std::function<void()>>> InputManager::_keyMappingRepeat;
std::vector<std::function<void(double, double)>> InputManager::_mouseXYCallBack;
std::vector<std::function<void(double, double)>> InputManager::_mouseSrollCallBack;

std::shared_ptr<InputManager> InputManager::_inputmanager = nullptr;