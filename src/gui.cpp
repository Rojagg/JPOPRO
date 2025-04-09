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

	//Lista Stacji
	ImGui::SetNextWindowSize(ImVec2(430, 430));
	ImGui::SetNextWindowPos(ImVec2(50, 50));
	ImGui::Begin("Lista Stacji");

	DisplayAllStations();

	ImGui::End();

	//Wyszukiwanie
	ImGui::SetNextWindowSize(ImVec2(430, 120));
	ImGui::SetNextWindowPos(ImVec2(50, 500));
	ImGui::Begin("Wyszukiwanie");
    
	static char text[256] = {0};
    static std::string text2;
    static double input = 0.0;

	ImGui::InputText("Miejscowosc", text, sizeof(text));
        text2 = text; // Aktualizujemy `text2` tylko po zmianie `text`

    ImGui::InputDouble("Zasieg", &input);

	if (ImGui::Button("Zatwierdz##A")) {
		std::thread thread1([=]() {
			double x = 0, y = 0;
			findCity(text2, x, y);
			StationInRange(input, x, y);
			});
		thread1.detach();
	}

	ImGui::End();
		
	ImGui::SetNextWindowSize(ImVec2(430, 305));
	ImGui::SetNextWindowPos(ImVec2(50, 625));
	ImGui::Begin("Wyniki");
	DisplayStationsInRange();
	ImGui::End();

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
	text14 = text13; // Aktualizujemy `text2` tylko po zmianie `text`

	ImGui::InputText("Ulica", text11, sizeof(text11));
	text12 = text11; // Aktualizujemy `text2` tylko po zmianie `text`
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

	

	ImGui::SetNextWindowSize(ImVec2(375, 250));
	ImGui::SetNextWindowPos(ImVec2(990, 50));
	ImGui::Begin("Wybór stacji");
	displaySensor();
	ImGui::End();

	ImGui::SetNextWindowSize(ImVec2(375, 125));
	ImGui::SetNextWindowPos(ImVec2(1395, 50));


	ImGui::Begin("Wybór akcji");
	displayDay();
	ImGui::End();
	std::thread prepareThread([=]() {
		PrepareData();
		});
	prepareThread.join();
	


	ImGui::SetNextWindowSize(ImVec2(700, 185));
	ImGui::SetNextWindowPos(ImVec2(1025, 650));
	ImGui::Begin("Analiza");
		Analysis();
		ImGui::End();


	ImGui::SetNextWindowSize(ImVec2(120, 80));
	ImGui::SetNextWindowPos(ImVec2(1680, 880));
	ImGui::Begin("Odswiez dane");
		if (ImGui::Button("Odswiez")) {
				getData();
			
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
