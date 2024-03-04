#include <numeric>
#include <cstdlib>
#include <complex>
#include <iostream>
#include "window.h"
#include "utilityFuncs.hpp"
#include "testList.h"

bool Window::check_mode;
Window* Window::instancePtr;

Window::Window() {
    check_mode = true;
    t.tmp1 = 0.0f;
    t.tmp2 = 0.0f;
    t.tmp3 = 0.0f;
    t.tmp4 = 0.0f;
    t.tmp5 = 0.0f;
    t.tmp_conv1 = 0.0f;
    t.tmp_conv2 = 0.0f;
    t.tmp_conv3 = 0.0f;
    t.tmp_conv4 = 0.0f;
    t.tmp_pair = std::make_pair(0, 0.0f);
    msg.message = "Welcome!";
    msg.color = colors[INF];
}

Window* Window::initializeWindow() {
    if (instancePtr != nullptr)
        return instancePtr;
    instancePtr = new Window();
    return instancePtr;
}

void Window::sendMessage(const std::string &message, INF_TYPE color) {
    msg.message = message;
    msg.color = colors[color];
}

int Window::runWindow() {
    // Initializing GLFW
    if (!glfwInit())
        return 1;

    // Creating a GLFW window
    GLFWwindow *window = glfwCreateWindow(940, 600, "PHYS-LAB-1", nullptr, nullptr);
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
    int selected1 = 0;
    int selected2 = 0;
    int selected3 = 0;
    testList testList1 = testList();

    ImVec4* colors = ImGui::GetStyle().Colors;
    colors[ImGuiCol_Text]                   = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_TextDisabled]           = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    colors[ImGuiCol_WindowBg]               = ImVec4(0.06f, 0.06f, 0.06f, 0.94f);
    colors[ImGuiCol_ChildBg]                = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_PopupBg]                = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
    colors[ImGuiCol_Border]                 = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
    colors[ImGuiCol_BorderShadow]           = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_FrameBg]                = ImVec4(0.16f, 0.45f, 0.43f, 0.54f);
    colors[ImGuiCol_FrameBgHovered]         = ImVec4(0.26f, 0.45f, 0.43f, 0.40f);
    colors[ImGuiCol_FrameBgActive]          = ImVec4(0.26f, 0.47f, 0.57f, 0.67f);
    colors[ImGuiCol_TitleBg]                = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
    colors[ImGuiCol_TitleBgActive]          = ImVec4(0.16f, 0.45f, 0.43f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed]       = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
    colors[ImGuiCol_MenuBarBg]              = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
    colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive]    = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
    colors[ImGuiCol_CheckMark]              = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colors[ImGuiCol_SliderGrab]             = ImVec4(0.24f, 0.52f, 0.88f, 1.00f);
    colors[ImGuiCol_SliderGrabActive]       = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colors[ImGuiCol_Button]                 = ImVec4(0.26f, 0.45f, 0.43f, 0.40f);
    colors[ImGuiCol_ButtonHovered]          = ImVec4(0.26f, 0.45f, 0.49f, 1.00f);
    colors[ImGuiCol_ButtonActive]           = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
    colors[ImGuiCol_Header]                 = ImVec4(0.13f, 0.45f, 0.44f, 0.31f);
    colors[ImGuiCol_HeaderHovered]          = ImVec4(0.14f, 0.45f, 0.52f, 0.80f);
    colors[ImGuiCol_HeaderActive]           = ImVec4(0.26f, 0.59f, 0.54f, 1.00f);
    colors[ImGuiCol_Separator]              = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
    colors[ImGuiCol_SeparatorHovered]       = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
    colors[ImGuiCol_SeparatorActive]        = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
    colors[ImGuiCol_ResizeGrip]             = ImVec4(0.26f, 0.59f, 0.98f, 0.20f);
    colors[ImGuiCol_ResizeGripHovered]      = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
    colors[ImGuiCol_ResizeGripActive]       = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
    colors[ImGuiCol_Tab]                    = ImVec4(0.18f, 0.45f, 0.44f, 0.86f);
    colors[ImGuiCol_TabHovered]             = ImVec4(0.21f, 0.67f, 0.59f, 0.60f);
    colors[ImGuiCol_TabActive]              = ImVec4(0.30f, 0.57f, 0.56f, 1.00f);
    colors[ImGuiCol_TabUnfocused]           = ImVec4(0.07f, 0.10f, 0.15f, 0.97f);
    colors[ImGuiCol_TabUnfocusedActive]     = ImVec4(0.14f, 0.26f, 0.42f, 1.00f);
    colors[ImGuiCol_PlotLines]              = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered]       = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
    colors[ImGuiCol_PlotHistogram]          = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered]   = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
    colors[ImGuiCol_TableHeaderBg]          = ImVec4(0.19f, 0.19f, 0.20f, 1.00f);
    colors[ImGuiCol_TableBorderStrong]      = ImVec4(0.31f, 0.31f, 0.35f, 1.00f);
    colors[ImGuiCol_TableBorderLight]       = ImVec4(0.23f, 0.23f, 0.25f, 1.00f);
    colors[ImGuiCol_TableRowBg]             = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_TableRowBgAlt]          = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
    colors[ImGuiCol_TextSelectedBg]         = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
    colors[ImGuiCol_DragDropTarget]         = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
    colors[ImGuiCol_NavHighlight]           = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colors[ImGuiCol_NavWindowingHighlight]  = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
    colors[ImGuiCol_NavWindowingDimBg]      = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
    colors[ImGuiCol_ModalWindowDimBg]       = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
    ImGuiStyle& style = ImGui::GetStyle();
    style.FrameRounding = 3.0f;
    style.WindowRounding = 3.0f;

    // Main window loop
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();


        //<----------------------->
        ImGui::SetNextWindowPos(ImVec2(50, 100));
        ImGui::SetNextWindowSize(ImVec2(300,440));
        ImGui::Begin("Input");
        if (ImGui::BeginTabBar("##tabs", ImGuiTabBarFlags_None)) {
            if (ImGui::BeginTabItem("Input")) {
                ImGui::PushItemWidth(100);

                ImGui::SeparatorText("Radius");
                ImGui::InputFloat("Enter value in ##1", &t.tmp1);
                const char* l_measuring[2] = {"m", "mm"};
                ImGui::SameLine();
                ImGui::ListBox("##listbox1", &selected1, l_measuring, IM_ARRAYSIZE(l_measuring), 2);
                if (ImGui::Button("Add to list ##1")) {
                    if (selected1 == 0)
                        testList1.setRadius(t.tmp1);
                    else if (selected1 == 1)
                        testList1.setRadius(util::convertMillimetersToMeters(t.tmp1));
                }

                ImGui::SeparatorText("Height");
                ImGui::InputFloat("Enter value in ##2", &t.tmp2);
                ImGui::SameLine();
                ImGui::ListBox("##listbox2", &selected2, l_measuring, IM_ARRAYSIZE(l_measuring), 2);
                if (ImGui::Button("Add to list ##2")) {
                    if (selected2 == 0)
                        testList1.setHeight(t.tmp2);
                    else if (selected2 == 1)
                        testList1.setHeight(util::convertMillimetersToMeters(t.tmp2));
                }

                ImGui::SeparatorText("Mass");
                ImGui::InputFloat("Enter value in ##3", &t.tmp3);
                const char* m_measuring[2] = {"kg", "g"};
                ImGui::SameLine();
                ImGui::ListBox("##listbox3", &selected3, m_measuring, IM_ARRAYSIZE(m_measuring), 2);
                if (ImGui::Button("Add to list ##3")) {
                    if (selected3 == 0)
                        testList1.setMass(t.tmp3);
                    else if (selected3 == 1)
                        testList1.setMass(util::convertGramsToKilograms(t.tmp3));
                }

                ImGui::SeparatorText("Time");
                ImGui::InputFloat("Enter value in sec", &t.tmp4);
                if (ImGui::Button("Add to list ##4")) {
                    testList1.addTimeValue(t.tmp4);
                }

                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Convert")) {
                ImGui::Text("From mm to m");
                ImGui::PushItemWidth(100);
                ImGui::InputFloat("Enter value in mm", &t.tmp_conv1);
                if (ImGui::Button("Convert ##1"))
                    t.tmp_conv2 = util::convertMillimetersToMeters(t.tmp_conv1);
                ImGui::Text("Converted value is %f m.", t.tmp_conv2);
                ImGui::Spacing();
                ImGui::Separator();

                ImGui::Text("From m to mm");
                ImGui::InputFloat("Enter value in m", &t.tmp_conv3);
                if (ImGui::Button("Convert ##2"))
                    t.tmp_conv4 = util::convertMetersToMillimeters(t.tmp_conv3);
                ImGui::Text("Converted value is %f mm.", t.tmp_conv4);

                ImGui::EndTabItem();
            }
            ImGui::EndTabBar();
        }
        /* ImGui::SeparatorText("Guide");
        ImGui::Text("Values are calculated in mm."); */
        ImGui::End();

        ImGui::SetNextWindowPos(ImVec2(350, 100));
        ImGui::SetNextWindowSize(ImVec2(300,440));
        ImGui::Begin("Display");
        if (ImGui::BeginTabBar("##tabs1", ImGuiTabBarFlags_None)) {
            if (ImGui::BeginTabItem("Table")) {
                static ImGuiTableFlags flags = ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg;
                if (ImGui::BeginTable("table1", 2, flags)) {
                    ImGui::TableSetupColumn("No.");
                    ImGui::TableSetupColumn("Time (sec)");
                    ImGui::TableHeadersRow();
                    for (int i = 0; i < testList1.getSize(); i++) {
                        ImGui::TableNextRow();
                        ImGui::TableNextColumn();
                        ImGui::Text("%d", i + 1);
                        ImGui::TableNextColumn();
                        ImGui::Text("%f", testList1.getTimes()[i]);
                        //ImGui::TableNextColumn();
                        //ImGui::Text("%f", tests[i].deviation);
                    }
                    ImGui::EndTable();
                }
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Other")) {
                ImGui::SeparatorText("Mass");
                ImGui::Text("Mass: %f kg", testList1.getMass());
                ImGui::SeparatorText("Radius");
                ImGui::Text("Radius: %f m", testList1.getRadius());
                ImGui::SeparatorText("Height");
                ImGui::Text("Height: %f m", testList1.getHeight());
                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("Plot")) {
                ImGui::SeparatorText("Time values");
                ImGui::PlotLines("sec", testList1.getTimes().data(), testList1.getSize(), 0, nullptr, testList1.getMinTime(), testList1.getMaxTime(), ImVec2(0,60));
                ImGui::EndTabItem();
            }
            ImGui::EndTabBar();
        }
        ImGui::End();

        ImGui::SetNextWindowSize(ImVec2(240,300));
        ImGui::SetNextWindowPos(ImVec2(650, 100));
        ImGui::Begin("Calculations");
        if (ImGui::BeginTabBar("##tabs2", ImGuiTabBarFlags_None)) {
            if (ImGui::BeginTabItem("Task 1")) {
                if (ImGui::Button("Calculate")) {
                    if (testList1.getSize() == 0) {
                        sendMessage("Error: No data to calculate", ERR);
                    } else {
                        t.tmp_pair = testList1.calculateImpulse();
                        if (t.tmp_pair.first == 1)
                            sendMessage("Error: No time values", ERR);
                        else if (t.tmp_pair.first == 2)
                            sendMessage("Error: Mass is 0", ERR);
                        else {
                            t.tmp5 = t.tmp_pair.second;
                            sendMessage("Calculation is done", SUCCESS);
                        }
                    }
                }
                ImGui::SeparatorText("Number of time values");
                ImGui::Text("N: %zu", testList1.getSize());
                ImGui::SeparatorText("Impulse");
                ImGui::Text("Impulse: %f", t.tmp5);
                ImGui::EndTabItem();
            }
            ImGui::EndTabBar();
        }
        ImGui::End();

        ImGui::SetNextWindowSize(ImVec2(240,140));
        ImGui::SetNextWindowPos(ImVec2(650, 400));
        ImGui::Begin("Messages");
        ImGui::TextColored(msg.color, "%s", msg.message.c_str());
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