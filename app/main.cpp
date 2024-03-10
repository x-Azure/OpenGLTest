#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <Renderer.hpp>

#include <tests/TestClearColor.hpp>
#include <tests/Test2DObject.hpp>

static void glfw_error_callback(int error, const char *description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}
void GLAPIENTRY DebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam)
{
    std::cout << "[OpenGL Error](" << type << ") " << message << std::endl;
    std::cin.get();
    exit(-1);
}
int main()
{
    // glfwSetErrorCallback(glfw_error_callback);
    GLFWwindow *window;
    if (!glfwInit())
        return -1;

    const char *glsl_version = "#version 150";
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(960, 540, "OpenGL 0.0", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK)
        return -1;
    std::cout << glGetString(GL_VERSION) << std::endl;
    glfwSwapInterval(1);
    // Enable debug output
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(DebugCallback, 0);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;     // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    glm::vec3 transate(0, 0, 0);
    glm::vec3 transate1(0, 300, 0);
    glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

    Renderer render;

    Tests::Test *currentTest = nullptr;
    Tests::TestMenu *TestMenu = new Tests::TestMenu(currentTest);
    currentTest = TestMenu;

    TestMenu->RegisterTest<Tests::TestClearColor>("Clear Color");
    TestMenu->RegisterTest<Tests::Test2DObject>("2D Obj");

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        render.Clear();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (currentTest)
        {
            currentTest->OnUpdate(0.0f);
            currentTest->OnRender();
            ImGui::Begin("Tests");
            if (currentTest != TestMenu && ImGui::Button("<-"))
            {
                delete currentTest;
                currentTest = TestMenu;
            }
            currentTest->OnImguiRender();
            ImGui::End();
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow *backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
        glfwSwapBuffers(window);
    }
    delete currentTest;
    if (currentTest != TestMenu)
        delete TestMenu;
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
}