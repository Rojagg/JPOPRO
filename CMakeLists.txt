cmake_minimum_required(VERSION 3.10)
add_compile_options(/utf-8)

project(Aplikacja)


find_package(CURL REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(implot CONFIG REQUIRED)
find_package(GTest REQUIRED)



add_executable(Aplikacja  "src/api.cpp" "src/main.cpp" "src/Searching.cpp" "header/api.h" "header/searching.h" "src/gui.cpp")
#add_executable(Aplikacja   "header/gui.h" "src/gui.cpp")

target_link_libraries(Aplikacja PRIVATE 
  CURL::libcurl
  nlohmann_json::nlohmann_json
  glad::glad
  glfw
  imgui::imgui
  implot::implot
  GTest::gtest
)






target_include_directories(Aplikacja PRIVATE 
  ${CMAKE_SOURCE_DIR}/header
)

enable_testing()

add_executable(test_1 tests/test.cpp 
"src/api.cpp" "src/Searching.cpp" "header/api.h" "header/searching.h" "src/gui.cpp")

target_link_libraries(test_1 PRIVATE GTest::gtest
 CURL::libcurl
  nlohmann_json::nlohmann_json
  glad::glad
  glfw
  imgui::imgui
  implot::implot
  GTest::gtest
)

target_include_directories(test_1 PRIVATE 
  ${CMAKE_SOURCE_DIR}/header
)

add_test(NAME test1 COMMAND test_1)