#ifndef _INPUTMANAGER_H_
#define _INPUTMANAGER_H_
#include <map>
#include <vector>
#include <functional>
#include <glfw/glfw3.h>
#include <memory>
enum class KeyState
{
	RELEASE			   ,
	PRESS			   ,
	REPEAT 
};
enum class InputKey
{
	/* The unknown key */
	UNKNOWN            ,
	
	/* Printable keys */
	SPACE              ,
	APOSTROPHE         , /* ' */
	COMMA              , /* , */
	MINUS              , /* - */
	PERIOD             , /* . */
	SLASH              , /* / */
	NUM_0              ,
	NUM_1              ,
	NUM_2              ,
	NUM_3              ,
	NUM_4              ,
	NUM_5              ,
	NUM_6              ,
	NUM_7              ,
	NUM_8              ,
	NUM_9              ,
	SEMICOLON          , /* ; */
	EQUAL              , /* = */
	A                  ,
	B                  ,
	C                  ,
	D                  ,
	E                  ,
	F                  ,
	G                  ,
	H                  ,
	I                  ,
	J                  ,
	K                  ,
	L                  ,
	M                  ,
	N                  ,
	O                  ,
	P                  ,
	Q                  ,
	R                  ,
	S                  ,
	T                  ,
	U                  ,
	V                  ,
	W                  ,
	X                  ,
	Y                  ,
	Z                  ,
	LEFT_BRACKET       , /* [ */
	BACKSLASH          , /* \ */
	RIGHT_BRACKET      , /* ] */
	GRAVE_ACCENT       , /* ` */
	WORLD_1            , /* non-US #1 */
	WORLD_2            , /* non-US #2 */
	
	/* Function keys */
	ESCAPE             ,
	ENTER              ,
	TAB                ,
	BACKSPACE          ,
	INSERT             ,
	DELETE             ,
	RIGHT              ,
	LEFT               ,
	DOWN               ,
	UP                 ,
	PAGE_UP            ,
	PAGE_DOWN          ,
	HOME               ,
	END                ,
	CAPS_LOCK          ,
	SCROLL_LOCK        ,
	NUM_LOCK           ,
	PRINT_SCREEN       ,
	PAUSE              ,
	F1                 ,
	F2                 ,
	F3                 ,
	F4                 ,
	F5                 ,
	F6                 ,
	F7                 ,
	F8                 ,
	F9                 ,
	F10                ,
	F11                ,
	F12                ,
	F13                ,
	F14                ,
	F15                ,
	F16                ,
	F17                ,
	F18                ,
	F19                ,
	F20                ,
	F21                ,
	F22                ,
	F23                ,
	F24                ,
	F25                ,
	KP_0               ,
	KP_1               ,
	KP_2               ,
	KP_3               ,
	KP_4               ,
	KP_5               ,
	KP_6               ,
	KP_7               ,
	KP_8               ,
	KP_9               ,
	KP_DECIMAL         ,
	KP_DIVIDE          ,
	KP_MULTIPLY        ,
	KP_SUBTRACT        ,
	KP_ADD             ,
	KP_ENTER           ,
	KP_EQUAL           ,
	LEFT_SHIFT         ,
	LEFT_CONTROL       ,
	LEFT_ALT           ,
	LEFT_SUPER         ,
	RIGHT_SHIFT        ,
	RIGHT_CONTROL      ,
	RIGHT_ALT          ,
	RIGHT_SUPER        ,
	MENU			   ,
	
	/* Mouse buttons */
	MOUSE_BUTTON_1     ,
	MOUSE_BUTTON_2     ,
	MOUSE_BUTTON_3     ,
	MOUSE_BUTTON_4     ,
	MOUSE_BUTTON_5     ,
	MOUSE_BUTTON_6     ,
	MOUSE_BUTTON_7     ,
	MOUSE_BUTTON_8     ,
	MOUSE_BUTTON_LAST  ,
	MOUSE_BUTTON_LEFT  ,
	MOUSE_BUTTON_RIGHT ,
	MOUSE_BUTTON_MIDDLE
};

//typedef void (*KeyCallBack)();
//typedef void (*AxisCallBack)(double,double);
//typedef void (*ScrollCallBack)(double, double);
class InputManager {
public:
	InputManager() {}
	~InputManager() {
	}
public:
	static std::shared_ptr<InputManager> getInstance();
public:
	void  addKeyMapping(InputKey key, KeyState state, std::function<void()> callback);
	void  addMouseXYCallBack(std::function<void(double, double)> callback);
	void  addMouseSrollCallBack(std::function<void(double, double)> callback);
	void  removeKeyMapping(InputKey key, KeyState state, std::function<void()> callback);
	void  removeMouseXYCallBack(std::function<void(double, double)> callback);
	void  removeMouseSrollCallBack(std::function<void(double, double)> callback);
private:
	friend class Viewport;
	static void	 handleKeyInput(GLFWwindow* window);
	static void  handleMouseXYCallBack(GLFWwindow* window, double x, double y);
	static void  handleMouseSrollCallBack(GLFWwindow* window, double xval, double yval);
private:
	static std::map<unsigned int, std::vector<std::function<void()>>> _keyMappingRelease;
	static std::map<unsigned int, std::vector<std::function<void()>>> _keyMappingPress;
	static std::map<unsigned int, std::vector<std::function<void()>>> _keyMappingRepeat;
	static std::vector<std::function<void(double, double)>> _mouseXYCallBack;
	static std::vector<std::function<void(double, double)>> _mouseSrollCallBack;
private:
	static std::shared_ptr<InputManager> _inputmanager;
};

#endif // !_INPUTMANAGER_H_
