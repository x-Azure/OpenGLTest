project(OpenGLTest)
file(GLOB_RECURSE imguiSrc src/imgui/*.cpp)

add_library(imgui ${imguiSrc})
target_link_libraries(imgui glfw)
target_include_directories(imgui PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")