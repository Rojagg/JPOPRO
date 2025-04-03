/**
 * @file Searching.cpp
 * @author Szymon Półgęsek
 * @brief This file handles all the operations on data that has been discovered by API
 * @version 0.1
 * @date 2025-04-01
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "searching.h" 



using json = nlohmann::json;
static std::vector<json> filteredStations;
static std::vector<json> filteredStations_Specific;
static std::vector<json> filteredMeasures;
std::string timeRange[2];

/**
 * @brief
 * This function checks if the file is empty
 * 
 *
 * 
 * @param filename - the name of file we checks
 */
bool isFileEmpty(const std::string& filename) {
	std::ifstream file(filename);
	return file.peek() == std::ifstream::traits_type::eof();
}

/**
 * @brief 
 * This function filtering the list of the station due to the user parameter (range) and the place in file ""../data/specific_place.json" which includes the geographical latitude and longitude of the specific
 * localization (City, Street, Number)
 * 
 * The stations which meet the conditions is being pushed to vector (filteredMeasures_Specific)
 * @param range - search radius
 */
void findInRange_Specific(double range) {
	filteredStations_Specific.clear();
	json localization;
	std::ifstream file("../data/specific_place.json");
	file >> localization;

	double x, y;
	if (localization[0].contains("lat") && localization[0].contains("lon")) {
		x = std::stod(localization[0]["lat"].get<std::string>());
		y = std::stod(localization[0]["lon"].get<std::string>());
	

		json stations;
		if (isFileEmpty("../data/data_station.json")) {
			ImGui::Text("Brak danych");
			return;
		}
		std::ifstream file2("../data/data_station.json");
		file2 >> stations;
		range = range / 111;
		
		for (json& station : stations) {
			if (station.contains("gegrLat") && station.contains("gegrLon") && station.contains("stationName")) {
				double x1 = std::stod(station["gegrLat"].get<std::string>());
				double y1 = std::stod(station["gegrLon"].get<std::string>());
				double distance = sqrt(pow(x - x1, 2) + pow(y - y1, 2));
				if (distance < range) {
					filteredStations_Specific.push_back(station);
				}
			}
		}
	}
	else{
		ImGui::Text("Bledne dane");
	}


	
}

/**
 * @brief 
 * This function gives the geographical latitide and longitude of the city given in parameter name
 * 
 * @param name - name of city
 * @param x - the value of latitue
 * @param y - the value of latitude
 */
void findCity(std::string& name, double& x, double& y) {
	json Cities;
	std::ifstream file("../data/data_cities.json");
	file >> Cities;

	for ( json city : Cities) {
		if (city.contains("Name") == false) {
			continue;
		}
		if (city["Name"].get<std::string>() == name) {
			std::cout << "found" << '\n';
			x = city["Latitude"].get<double>();
			y = city["Longitude"].get<double>();
			return;
		}
	}
	std::cout << "Not found" << '\n';

}
/**
 * @brief 
 * This function adding the places which meet the conditions into the vector - filteredStations 
 * @param range - range of searching (in km)
 * @param x - a value of Latitude
 * @param y - a value of Longitude
 */
void StationInRange(double range, double x, double y) { //SPYTAĆ CZY WYSTARCZY INFOMRACJA O MIEŚCIE CZY DOKŁADNIEJSZA
	json Stations;
	if (isFileEmpty("../data/data_station.json")) {
		ImGui::Text("Brak danych");
		return;
	}
	std::ifstream file("../data/data_station.json");
	file >> Stations;
	range = range / 111;
	std::cout << range;
	for (json station : Stations) {
		if (station.contains("gegrLat") == false || station.contains("gegrLon") == false || station.contains("stationName") == false) {
			continue;
		}
		double x1 = std::stod(station["gegrLat"].get<std::string>());
		double y1 = std::stod(station["gegrLon"].get<std::string>());
		double distance = sqrt(pow(x - x1, 2) + pow(y - y1, 2));
		
		if (distance < range) {
			filteredStations.push_back(station);
		}
	}
	file.close();

}

/**
 * @brief 
 * This Function displays all stations included in "../data_station.json"
 * Users can select the station by name, and other fucntion retrieves its data
 */
void DisplayAllStations() {
	json Stations;
	if (isFileEmpty("../data/data_station.json")) {
		ImGui::Text("Brak danych");
		return;
	}
	std::ifstream file("../data/data_station.json");
	file >> Stations;
	for (auto& station : Stations) {
		if (ImGui::Selectable(station["stationName"].get<std::string>().c_str())) {
			getStationData(station["id"].get<int>());
		}
	}

}

/**
 * @brief 
 * This Function displays all stations included in vector (filteredStations_Specific)
 * Users can select the station by name, and other function retrieves its data
 */
void DisplayStationsInRange_Spec() {

	if (filteredStations_Specific.empty()) {
		ImGui::Text("Brak stacji o danych kryteriach");
		return;
	}
	for (auto& station : filteredStations_Specific) {
		if (ImGui::Selectable(station["stationName"].get<std::string>().c_str())) {
			getStationData(station["id"].get<int>());
		}
		//ImGui::Text("ID: %d", station["id"].get<int>());
		//ImGui::Text("Nazwa: %s", station["stationName"].get<std::string>().c_str());
		//std::cout << station["stationName"].get<std::string>() << '\n';
	}
}
/**
 * @brief 
 * This Function displays all stations included in vector (filteredStations)
 * Users can select the station by name, and other fucntion retrieves its data
 */
void DisplayStationsInRange() {
	
	if (filteredStations.empty()) {
		ImGui::Text("Brak stacji o danych kryteriach");
		return;
	}
	for (auto& station : filteredStations) {
		if (ImGui::Selectable(station["stationName"].get<std::string>().c_str())) {
			getStationData(station["id"].get<int>());
		}
		//ImGui::Text("ID: %d", station["id"].get<int>());
		//ImGui::Text("Nazwa: %s", station["stationName"].get<std::string>().c_str());
		//std::cout << station["stationName"].get<std::string>() << '\n';
	}
}
/**
 * @brief 
 * This function displays all sensors included in "../data_single_station.json"
 * Users cam select the sensor by name and another fucntion retrieves its data
 */
void displaySensor() {
	json Sensors;
	if (isFileEmpty("../data/single_station.json")) {
		ImGui::Text("Brak danych");
		return;
	}
	std::ifstream file("../data/single_station.json");
	file >> Sensors;
	for (auto &Sensor : Sensors) {
		if (ImGui::Selectable(Sensor["param"]["paramName"].get<std::string>().c_str())) {
			getSensorData(Sensor["id"].get<int>());
		}
	}
}
/**
 * @brief 
 * This function displays all times of measures available in "../data/single_sensor.json"
 * 
 * Users can set the range of days that the program uses for analysis and making graph
 */
void displayDay() {
	json Measures;
	std::ifstream file("../data/single_sensor.json");
	if (!file) return;
	file >> Measures;

	static std::string range[2] = {"",""};
	
	// Sprawdzenie czy Measures posiada poprawną strukturę
	if (!Measures.contains("values") || !Measures["values"].is_array()) {
		ImGui::Text("Nieprawidłowy format danych!");
		return;
	}

	// Iteracja po `values`
	int i = 0;
	for (auto& measure : Measures["values"]) {
		if (!measure.contains("date")) continue;  // Pominięcie błędnych wpisów
		
		std::string date = measure["date"].get<std::string>();
		std::string button = measure["date"].get<std::string>() + "##" + std::to_string(i);

		if (ImGui::Button(button.c_str())) {
			if (range[0].empty()) range[0] = date;
			else if (range[1].empty()) range[1] = date;
		}
		i++;
	}
	ImGui::SetNextWindowSize(ImVec2(375, 120));
	ImGui::SetNextWindowPos(ImVec2(1395, 180));
	ImGui::Begin("Zatwierdz");
	ImGui::Text("Poczatek: %s \n Koniec: %s", range[0].c_str(), range[1].c_str());
	if (ImGui::Button("RESET")) {
		range[0] = "";
		range[1] = "";
	}
	if (ImGui::Button("Zatwierdz##C")){
		if (range[0] > range[1]) {
			timeRange[1] = range[1];
			timeRange[0] = range[0];
		}
		else {
			timeRange[0] = range[1];
			timeRange[1] = range[0];
		}
	}

	ImGui::End();

	
}
/**
 * @brief 
 * This function adds the measures which makes the condition (includes in timeRange from displayDay function) to vector(filtered_Measures)
 * 
 * After that function generates the Plot
 */
void PrepareData() {
	json Measures;
	std::vector<float> values;
	std::ifstream file("../data/single_sensor.json");

	if (!file) {
		std::cerr << "Nie można otworzyć pliku!" << std::endl;
		ImGui::SetNextWindowSize(ImVec2(700, 300));
		ImGui::SetNextWindowPos(ImVec2(1025, 330));
		ImGui::Begin("Wykres");

		if (ImPlot::BeginPlot("Wartości", 0, 0, ImVec2(660, 250), 0, ImPlotAxisFlags_AutoFit, ImPlotAxisFlags_AutoFit)) {
			ImPlot::PlotBars("Stężenie", values.data(), values.size());
			ImPlot::EndPlot();
		}

		ImGui::End();
		return;

	}

	file >> Measures;

	
	filteredMeasures.clear();
	bool inRange = false;

	for (const auto& measure : Measures["values"]) {
		if (!measure.contains("date") || !measure["date"].is_string()) continue;
		std::string currentDate = measure["date"].get<std::string>();

		if (currentDate == timeRange[0]) {
			inRange = true;
		}

		if (inRange) {
			if (measure.contains("value") && !measure["value"].is_null()) {
				values.push_back(measure["value"].get<float>());
				filteredMeasures.push_back(measure);
			}
			
		}

		if (currentDate == timeRange[1]) {
			break;
		}
	}

	std::reverse(values.begin(), values.end());

	ImGui::SetNextWindowSize(ImVec2(700, 300));
	ImGui::SetNextWindowPos(ImVec2(1025, 330));
	ImGui::Begin("Wykres");

	if (ImPlot::BeginPlot("Wartości",0,0, ImVec2(660, 250), 0, ImPlotAxisFlags_AutoFit, ImPlotAxisFlags_AutoFit)){
		ImPlot::PlotBars("Stężenie", values.data(), values.size());
		ImPlot::EndPlot();
	}

	ImGui::End();
}

/**
 * @brief 
 * This function analyses the data included in vector (filteredMeasured)
 * 
 * This function calculates maximal value, minimal value and average value
 * And displays them in GUI
 */
void Analysis() {
	if (filteredMeasures.empty()) return;
	json valueMin = filteredMeasures[0];
	json valueMax = filteredMeasures[0];
	float average = 0;
	int counter = 0;

	for (json& measure : filteredMeasures) {
		if (measure["value"].get<float>() > valueMax["value"].get<float>()) valueMax = measure;
		if (measure["value"].get<float>() < valueMin["value"].get<float>()) valueMin = measure;
		average += measure["value"].get<float>();
		counter++;
	}
	std::string min = "Minimal value:" + std::to_string(valueMin["value"].get<float>()) + "\n Day: " + valueMin["date"].get<std::string>();
	std::string max = "Maximal value:" + std::to_string(valueMax["value"].get<float>()) + "\n Day: " + valueMax["date"].get<std::string>();
	std::string avg = "Average value:" + std::to_string(average/counter);
	
	ImGui::Text(min.c_str());
	ImGui::Text(max.c_str());
	ImGui::Text(avg.c_str());
}



