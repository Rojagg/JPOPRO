#ifndef SEARCH_H
#define SEARCH_H

#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
#include <fstream>
#include "gui.h"
#include "api.h"
#include <vector>
#include <implot.h>

using json = nlohmann::json;

bool isFileEmpty(const std::string& filename);

bool findCity(std::string& name, double& x, double& y);

void StationInRange(double range, double x, double y, bool isFind);

void DisplayAllStations();

void DisplayStationsInRange();

void DisplayStationsInRange_Spec();

void findInRange_Specific(double range);

void displaySensor();

void displayDay();

void PrepareData();

void Analysis();
#endif