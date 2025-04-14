#ifndef API_H
#define API_H
#include <iostream>
#include <curl/curl.h>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>
#include <imgui.h>

using json = nlohmann::json;

// Deklaracja funkcji callback do zapisywania danych
size_t write_callback(void* contents, size_t size, size_t amount, std::string* output);

// Deklaracja funkcji do pobierania danych z API
int getData();
bool getDataWithResponse();
void getSensorData(int id);
void getStationData(int id);
void getLocalization(std::string city, std::string street, std::string number);

#endif // API_HANDLER_H