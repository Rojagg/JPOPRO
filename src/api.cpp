/**
 * @file api.cpp
 * @author Szymon Półgęsek
 * @brief This file handles the communication with API
 * @version 0.1
 * @date 2025-03-31
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "api.h"
/**
 * @brief 
 * This function is important for below functions
 * It is WriteFunction that calculates the size of incoming data from API, and convert them into the table of chars
 * @param contents - pointer to downloaded data buffer
 * @param size - size of one element
 * @param amount - amount of elements
 * @param output - pointer to place where the received will be stored
 * @return size_t - total number of processed bytes
 */
size_t write_callback(void* contents, size_t size, size_t amount, std::string* output) {
	size_t totalsize = size * amount; //calculate the size of data
	output->append((char*)contents, totalsize); //add data on the end of string output
	return totalsize; //return totalsize
}

/**
 * @brief Get the Localization based on specific data(city, street, number) and forrward it into file: "../data/specific_place.json"
 * 
 * @param city 
 * @param street 
 * @param number 
 */


void getLocalization(std::string city, std::string street, std::string number) {
	
	CURL* curl;
	CURLcode result;
	std::string response;
	std::string localization = street + "%20" + number + "%20" + city;
	std::string apiUrl = "https://nominatim.openstreetmap.org/search?q=" + localization + "&format=json&limit=1";

	curl = curl_easy_init(); //return pointer to curl session
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, apiUrl.c_str());	//set url
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);//write function
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response); //the localization of received data
		curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0");
		
		result = curl_easy_perform(curl); //api request with options above
		if (result != CURLE_OK) std::cout << "Cannot download data";
		else {
			
			std::ofstream file("../data/specific_place.json");
			if (file.is_open()) {
				file << response;
				file.close();
				std::cout << "Data download";
			}
			
			
		}

	}
	
	curl_easy_cleanup(curl); //end of curl session - clear option, release resources
}
/**
 * @brief 
 * This function get the information about avery avaiable station from API and forward it into file "../data/data_station.json"
 * 
 * @return int 
 */
int getData() {
	
	CURL* curl; //Dane dotyczące połączenia
	CURLcode result; //Jaka odpowiedz serwera(w sensie błędy itp.)
	std::string response; //Dane od serwera


	curl = curl_easy_init();
	if (curl) {   //Sprawdzamy czy nie został zwrócony nullptr
		curl_easy_setopt(curl, CURLOPT_URL, "https://api.gios.gov.pl/pjp-api/rest/station/findAll"); //Wybieramy źródło
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback); //Wybieramy funkcję do zapisywania danych
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response); //Wybieramy miejsce do zapisywania danych

		result = curl_easy_perform(curl); //Zapytanie HTTP get
		if (result == CURLE_OK) {
			std::ofstream file("../data/data_station.json");

			if (file.is_open()) {
				file << response;
				file.close();
				std::cout << "Data downloaded" << '\n';
			}
			else {
				std::cout << "Cannot open file" << '\n';
			}

		}
		else {
			std::cout << "cannot download data" << '\n';
		}


		curl_easy_cleanup(curl);

		return 0;
	}
	else {
		return 1;
	}
}
/**
 * @brief 
 * This function get the detailed information about single station from API and forward it into file "../data/single_station.json"
 * 
 * @return int 
 */
void getStationData(int id) {
	
	CURL* curl;
	CURLcode result;
	std::string response;
	std::string url = "https://api.gios.gov.pl/pjp-api/rest/station/sensors/" + std::to_string(id);
	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str() ); //Wybieramy źródło
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback); //Wybieramy funkcję do zapisywania danych
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response); //Wybieramy miejsce do zapisywania danych
	}
	result = curl_easy_perform(curl);
	if (result == CURLE_OK) {
		std::ofstream file("../data/single_station.json");
		if (file.is_open()) {
			file << response;
			file.close();
			std::cout << "Data downloaded" << '\n';
		}
		else {
			std::cout << "Cannot open file" << '\n';
		}
	}
	else {
		std::cout << "cannot download data" << '\n';
	}

	curl_easy_cleanup(curl);
}
/**
 * @brief 
 * This function get the detailed information about single sensor from API and forward it into file "../data/single_sensor.json"
 * 
 * @return int 
 */
void getSensorData(int id) {
	
	CURL* curl;
	CURLcode result;
	std::string response;
	std::string url = "https://api.gios.gov.pl/pjp-api/rest/data/getData/" + std::to_string(id);
	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str()); //Wybieramy źródło
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback); //Wybieramy funkcję do zapisywania danych
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response); //Wybieramy miejsce do zapisywania danych
	}
	result = curl_easy_perform(curl);
	if (result == CURLE_OK) {
		std::ofstream file("../data/single_sensor.json");
		if (file.is_open()) {
			file << response;
			file.close();
			std::cout << "Data downloaded" << '\n';
		}
		else {
			std::cout << "Cannot open file" << '\n';
		}
	}
	else {
		std::cout << "cannot download data" << '\n';
	}

	curl_easy_cleanup(curl);
}



