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
    Window();
    static Window* instancePtr;

    // Utility
    static bool check_mode;
public:
    Window(Window& o) = delete;
    ~Window();
    static Window* initializeWindow();
    int runWindow();
};


#endif //PHYS_LAB_1_WINDOW_H
