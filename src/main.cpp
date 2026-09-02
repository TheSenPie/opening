#include <GLFW/glfw3.h>

#include <stdio.h>

int main()
{
    GLFWwindow* window;
    GLFWmonitor* monitor = NULL;

    monitor = glfwGetPrimaryMonitor();

    window = glfwCreateWindow(640, 480, "Window name", monitor, NULL);

    glfwDestroyWindow(window);
    glfwTerminate();

    printf("Hello, World\n");

    return 0;
}
