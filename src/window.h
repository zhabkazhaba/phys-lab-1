#ifndef PHYS_LAB_1_WINDOW_H
#define PHYS_LAB_1_WINDOW_H
#include "imgui.h"
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include "GLFW/glfw3.h"
#include <vector>
#include <map>
#include <string>
#include "utilityFuncs.hpp"


class Window {
private:
    enum INF_TYPE {
        INF     = 0,
        SUCCESS = 1,
        ERR     = 2
    };

    const static inline ImVec4 t_colors[] = {
            ImVec4(1.0f, 1.0f, 1.0f, 1.0f), // WHITE
            ImVec4(0.0f, 1.0f, 0.0f, 1.0f), // GREEN
            ImVec4(1.0f, 0.0f, 0.0f, 1.0f)  // RED
    };

    Window();
    static Window* instancePtr;

    // Utility
    static bool check_mode;
    struct {
        float tmp1;
        float tmp2;
        float tmp3;
        float tmp4;
        float tmp5;
        float tmp_conv1;
        float tmp_conv2;
        float tmp_conv3;
        float tmp_conv4;
        int tmp_del;
        std::pair<int, float> tmp_pair1;
        std::pair<int, float> tmp_pair2;
        std::pair<int, double> tmp_pair3;
    } t;
    struct {
        std::string message;
        ImVec4 color;
    } msg;
public:
    Window(Window& o) = delete;
    ~Window();
    static Window* initializeWindow();
    int runWindow();
    void sendMessage(const std::string& message, INF_TYPE color);
};


#endif //PHYS_LAB_1_WINDOW_H
