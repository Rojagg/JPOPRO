/**
 * @file gui.cpp
 * @author Szymon Półgęsek
 * @brief This file handles the GUI with using ImGui
 * @version 0.1
 * @date 2025-04-01
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "gui.h"

void Gui::Init(GLFWwindow* window, const char* glsl_version)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImPlot::CreateContext();
	ImGuiIO& io = ImGui::GetIO();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);
	ImGui::StyleColorsLight();
}
/**
 * @brief 
 * Upadtes the GUI and handles user interaction
 */
void Gui::Update()
{

	//List of Stations
	ImGui::SetNextWindowSize(ImVec2(430, 430));
	ImGui::SetNextWindowPos(ImVec2(50, 50));
	ImGui::Begin("Lista Stacji");

	DisplayAllStations();

	ImGui::End();

	//Searching by localization (not detailed)
	ImGui::SetNextWindowSize(ImVec2(430, 120));
	ImGui::SetNextWindowPos(ImVec2(50, 500));
	ImGui::Begin("Wyszukiwanie");
    
	static char text[256] = {0};
    static std::string text2;
    static double input = 0.0;

	ImGui::InputText("Miejscowosc", text, sizeof(text));
        text2 = text; 

    ImGui::InputDouble("Zasieg", &input);

	if (ImGui::Button("Zatwierdz##A")) {
		std::thread thread1([=]() {
			double x = 0, y = 0;
			bool find = findCity(text2, x, y);
			StationInRange(input, x, y, find);
			});
		thread1.detach(); //the threads works independently (in bg), the main thread not waiting for this thread
	}

	ImGui::End();
		
	ImGui::SetNextWindowSize(ImVec2(430, 305));
	ImGui::SetNextWindowPos(ImVec2(50, 625));
	ImGui::Begin("Wyniki");
	DisplayStationsInRange();
	ImGui::End();



	//Searching by localizatoin (detailed)
	ImGui::SetNextWindowSize(ImVec2(430, 150));
	ImGui::SetNextWindowPos(ImVec2(500, 50));
	ImGui::Begin("Wyszukiwanie po dokładnej lokalizacji");
	static char text11[256] = { 0 };
	static std::string text12;
	static double input1 = 0.0;
	static int input12;

	static char text13[256] = { 0 };
	static std::string text14;

	ImGui::InputText("Miejscowosc", text13, sizeof(text13));
	text14 = text13; 

	ImGui::InputText("Ulica", text11, sizeof(text11));
	text12 = text11; 
	ImGui::InputInt("Numer mieszkania", &input12);
	ImGui::InputDouble("Zasieg", &input1);
	

	if (ImGui::Button("Zatwierdz##B")) {
		std::thread thread2([=]() {
			getLocalization(text14, text12, std::to_string(input12));
			findInRange_Specific(input1);
			});
		thread2.detach();
		
	}
	ImGui::End();
	ImGui::SetNextWindowSize(ImVec2(430, 725));
	ImGui::SetNextWindowPos(ImVec2(500, 205));
	ImGui::Begin("Wyniki2");
	
		DisplayStationsInRange_Spec();
	
	ImGui::End();

	
	//Choose the measure parameter
	ImGui::SetNextWindowSize(ImVec2(375, 250));
	ImGui::SetNextWindowPos(ImVec2(990, 50));
	ImGui::Begin("Wybór parametru");
	displaySensor();
	ImGui::End();

	ImGui::SetNextWindowSize(ImVec2(375, 125));
	ImGui::SetNextWindowPos(ImVec2(1395, 50));

	//Choose the time range
	ImGui::Begin("Wybór akcji");
	displayDay();
	ImGui::End();
	std::thread prepareThread([=]() {
		PrepareData();
		});
	prepareThread.join();
	

	//Display analysis of data
	ImGui::SetNextWindowSize(ImVec2(700, 185));
	ImGui::SetNextWindowPos(ImVec2(1025, 650));
	ImGui::Begin("Analiza");
		Analysis();
		ImGui::End();

	
	//Status of connection with server 
	ImGui::SetNextWindowSize(ImVec2(330, 80));
	ImGui::SetNextWindowPos(ImVec2(1240, 845));
	ImGui::Begin("Odswiez dane");
	static bool test = getDataWithResponse();
		if (ImGui::Button("Odswiez")) {
			
				test = getDataWithResponse();
				
				
		}
		if (test) {
			ImGui::Text("Nawiazano polaczenie z serwerem");
		}
		else {
			ImGui::Text("Brak polaczenie z serwerem - dane archwialne");
		}

		
		ImGui::End();
	
	

	
}

void Gui::Render()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Gui::Shutdown()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImPlot::DestroyContext();
	ImGui::DestroyContext();
	
}

void Gui::NewFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}
