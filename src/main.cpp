# include <iostream>
# include "initialization.h"
# include <GLFW/glfw3.h>
int main() {
    /*
    if (!glfwInit())
        return 1;

    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    GLFWwindow* window = glfwCreateWindow(1280, 720, "Linark", NULL, NULL);
    if (window == NULL)
        return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    while (!glfwWindowShouldClose(window))
    {
        
        glfwPollEvents();

       
        // Rendering
       
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        

        glfwSwapBuffers(window);
    }
    */
    AES obj("aarushi chauhan");
    auto [cipher,size] = obj.encrypt();
    cipher = obj.decrypt(cipher,size);
    std::cout << cipher << std::endl;
    delete[] cipher;
    return 0;   // caching and gui
}