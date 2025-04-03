/**
 * @file main.cpp
 * @author Szymon Półgesek
 * @brief Main File
 * @version 0.1
 * @date 2025-04-01
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include <api.h>
#include <filesystem>
#include "searching.h"
#include "gui.h"

/**
 * @brief Main function
 * 
 * @return int 
 */
int main() {

	//getLocalization("Poznan", "Kaliska", "1");
	

	//getSensorData(21345);
	//getStationData(11916);
	//getLocalization(std::string city, std::string street, std::string number);
		// Setup window
		if (!glfwInit())
			return 1;

		// GL 3.0 + GLSL 130
		const char* glsl_version = "#version 130";
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		// Create window with graphics context
		GLFWwindow* window = glfwCreateWindow(1820, 980, "Projekt - JPO", NULL, NULL);
		if (window == NULL)
			return 1;
		glfwMakeContextCurrent(window);
		glfwSwapInterval(1); // Enable vsync

		bool err = !gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

		if (err)
		{
			fprintf(stderr, "Failedł to initialize OpenGL loader!\n");
			return 1;
		}

		int screen_width, screen_height;
		glfwGetFramebufferSize(window, &screen_width, &screen_height);
		glViewport(0, 0, screen_width, screen_height);

		Gui myGui;
		myGui.Init(window, glsl_version);
		while (!glfwWindowShouldClose(window)) {
			glfwPollEvents();
			myGui.NewFrame();
			myGui.Update();
			myGui.Render();
			glfwSwapBuffers(window);
		}
		myGui.Shutdown();
}