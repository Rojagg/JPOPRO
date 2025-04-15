#include <iostream>
#include <Gtest/gtest.h>
#include <filesystem>
#include "searching.h"


TEST(isFileEmpty_TEST, FileDoesntExist) {
	EXPECT_TRUE(isFileEmpty("Imaginary.json"));
}

TEST(isFileEmpty_TEST, EmptyFile) {
	std::ofstream empty_file("../data/test.json");
	empty_file.close();
	EXPECT_TRUE(isFileEmpty("../data/test.json"));
	std::filesystem::remove("../data/test.json");
}

TEST(isFileEmpty_TEST, NonEmptyFile) {
	std::ofstream non_empty_file("../data/test2.json");
	non_empty_file << "FILLING";
	non_empty_file.close();
	EXPECT_FALSE(isFileEmpty("../data/test2.json"));
	std::filesystem::remove("../data/test2.json");
}



TEST(findInRange_Specific_TEST, NoFilesWithSpecificPlaceorEmptyFile) {
	if (std::filesystem::exists("../data/specific_place.json"))
		std::filesystem::remove("../data/specific_place.json");

	EXPECT_NO_THROW(findInRange_Specific(10));
	std::ofstream file("../data/specific_place.json");
	file.close();
	EXPECT_NO_THROW(findInRange_Specific(10));
	std::filesystem::remove("../data/specific_place.json");
}

TEST(findInRange_Specific_TEST, NoFilesWithStationDataAndEmptyFile) {
	if (std::filesystem::exists("../data/data_station.json"))
		std::filesystem::remove("../data/data_station.json");

	EXPECT_NO_THROW(findInRange_Specific(10));

	std::ofstream file("../data/data_station.json");
	file.close();
	EXPECT_NO_THROW(findInRange_Specific(10));
	std::filesystem::remove("../data/data_station.json");

}

TEST(findInRange_Specific_TEST, WrongDataStation) {
	if (std::filesystem::exists("../data/data_station.json"))
		std::filesystem::remove("../data/data_station.json");
	std::ofstream file("../data/data_station.json");
	file << "{ Test invalid data";
	file.close();
	EXPECT_NO_THROW(findInRange_Specific(10));

	std::filesystem::remove("../data/data_station.json");

}

TEST(findInRange_Specific_TEST, WrongDataSpecific) {
	if (std::filesystem::exists("../data/specific_place.json"))
		std::filesystem::remove("../data/specific_place.json");
	std::ofstream file("../data/specific_place.json");

	file << "{ Test invalid data";
	file.close();
	EXPECT_NO_THROW(findInRange_Specific(10));

	std::filesystem::remove("../data/specific_place.json");

}


TEST(StationInRange_TEST, NoFilesWithStationDataOREmptyFile) {
	if (std::filesystem::exists("../data/data_station.json"))
		std::filesystem::remove("../data/data_station.json");

	EXPECT_NO_THROW(StationInRange(10,1,1,1));

	std::ofstream file("../data/data_station.json");
	file.close();
	EXPECT_NO_THROW(StationInRange(10,1,1,1));
	std::filesystem::remove("../data/data_station.json");

}

TEST(StationInRange_TEST, WrongFormat) {
	if (std::filesystem::exists("../data/data_station.json"))
		std::filesystem::remove("../data/data_station.json");
	std::ofstream file("../data/data_station.json");
	file << "{ Test invalid data";
	file.close();
	EXPECT_NO_THROW(StationInRange(10,1,1,1));

	std::filesystem::remove("../data/data_station.json");

}


TEST(DisplayAllStation_TEST, NoFilesWithStationDataOrEmpty) {
	if (std::filesystem::exists("../data/data_station.json"))
		std::filesystem::remove("../data/data_station.json");

	EXPECT_NO_THROW(DisplayAllStations());

	std::ofstream file("../data/data_station.json");
	file.close();
	EXPECT_NO_THROW(DisplayAllStations());
	std::filesystem::remove("../data/data_station.json");

}

TEST(DisplayAllStation_TEST, WrongFormat) {
	if (std::filesystem::exists("../data/data_station.json"))
		std::filesystem::remove("../data/data_station.json");
	std::ofstream file("../data/data_station.json");
	file << "{ Test invalid data";
	file.close();
	EXPECT_NO_THROW(DisplayAllStations());

	std::filesystem::remove("../data/data_station.json");

}

TEST(DisplaySensor_TEST, NoFile) {
	if (std::filesystem::exists("../data/single_station.json"))
		std::filesystem::remove("../data/single_station.json");

	EXPECT_NO_THROW(displaySensor());
}

TEST(DisplaySensor_TEST, EmptyFile) {
	std::ofstream file("../data/single_station.json");
	file.close();

	EXPECT_NO_THROW(displaySensor());

	std::filesystem::remove("../data/single_station.json");
}

TEST(DisplaySensor_TEST, WrongFormat) {
	std::ofstream file("../data/single_station.json");
	file << "{ invalid json";
	file.close();

	EXPECT_NO_THROW(displaySensor());

	std::filesystem::remove("../data/single_station.json");
}

TEST(DisplayDay_TEST, NoFile) {
	if (std::filesystem::exists("../data/single_sensor.json"))
		std::filesystem::remove("../data/single_sensor.json");

	EXPECT_NO_THROW(displayDay());
}

TEST(DisplayDay_TEST, EmptyFile) {
	std::ofstream file("../data/single_sensor.json");
	file.close();

	EXPECT_NO_THROW(displayDay());

	std::filesystem::remove("../data/single_sensor.json");
}

TEST(DisplayDay_TEST, WrongFormat) {
	std::ofstream file("../data/single_sensor.json");
	file << "{ invalid json";
	file.close();

	EXPECT_NO_THROW(displayDay());

	std::filesystem::remove("../data/single_sensor.json");
}
