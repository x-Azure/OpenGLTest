project(OpenGLTest)

add_compile_definitions(APP_DIR="${CMAKE_CURRENT_SOURCE_DIR}")
add_executable(${PROJECT_NAME} main.cpp)
# target_include_directories(${PROJECT_NAME} PUBLIC shader)
target_link_libraries(${PROJECT_NAME} _${PROJECT_NAME} ${glfw3_LIBRARIES} imgui GLEW::glew)