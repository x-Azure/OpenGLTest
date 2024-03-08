project(OpenGLTest)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} _${PROJECT_NAME} ${glfw3_LIBRARIES} imgui GLEW::glew)