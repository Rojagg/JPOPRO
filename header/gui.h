#ifndef GUI_H
#define GUI_H
#include <iostream>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include "api.h"
#include "searching.h"
#include <implot.h>

class Gui {
public:
	void Init(GLFWwindow* window, const char* glsl_version);
	virtual void Update();
	void Render();
	void Shutdown();
	void NewFrame();
	
};

#endif
//ą
