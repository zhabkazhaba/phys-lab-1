#include <numeric>
#include <cstdlib>
#include <complex>
#include "window.h"

bool Window::check_mode;
Window* Window::instancePtr;

Window::Window() {
    check_mode = true;
}

Window* Window::initializeWindow() {
    if (instancePtr != nullptr)
        return instancePtr;
    instancePtr = new Window();
    return instancePtr;
}

int Window::runWindow() {
    // Initializing GLFW
    if (!glfwInit())
        return 1;

    // Creating a GLFW window
    GLFWwindow *window = glfwCreateWindow(1000, 600, "PHYS-LAB-1", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);

    // Initializing ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void) io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();

    // Initializing temporary variables
    float diameter_tmp = 0.0f;
    float height_tmp = 0.0f;

    // Main window loop
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        // Initializing temporary variables
        float tmp[4] = {0.0f, 0.0f, 0.0f, 0.0f};

        ImGui::SetNextWindowSize(ImVec2(200,400));
        ImGui::Begin("Input");
        if (ImGui::CollapsingHeader("Input measurement")) {
            ImGui::InputFloat("Enter value in mm", &tmp[0]);
        }
        if (ImGui::CollapsingHeader("Value conversion")) {
            ImGui::Text("From mm to m");
            ImGui::InputFloat("Enter value in mm", &tmp[0]);
            if (ImGui::Button("Convert"))
                tmp[1] = util::convertMillimetersToMeters(tmp[0]);
            ImGui::Text("Converted value is %f m.", tmp[1]);
            ImGui::Spacing();

            ImGui::Text("From m to mm");
            ImGui::InputFloat("Enter value in m", &tmp[2]);
            if (ImGui::Button("Convert"))
                tmp[3] = util::convertMetersToMillimeters(tmp[2]);
            ImGui::Text("Converted values if %f mm.", tmp[3]);
        }
        ImGui::End();

        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}