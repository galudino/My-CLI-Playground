/*!
    \file       source.cpp
    \brief      Source file

    \author
    \date
 */

#include "header.hpp"
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

int helloWindow() {
    GLFWwindow *window = nullptr;

    if (!glfwInit()) {
        return EXIT_FAILURE;
    }
    
    if (!(window = glfwCreateWindow(640, 480, "Hello, world!", nullptr, nullptr))) {
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window)) {
        /*
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_TRIANGLES);
        glVertex2f(3, 5);
        glEnd();

        glfwSwapBuffers(window);
        */
        glfwPollEvents();
    }

    glfwTerminate();
    return EXIT_SUCCESS;
}
