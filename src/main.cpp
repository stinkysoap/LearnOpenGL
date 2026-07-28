#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
void framebuffer_size_callback(GLFWwindow* window, int width, int height);  
int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  
    GLFWwindow* window = glfwCreateWindow(800,600,"LearnOpenGL",NULL,NULL);
    if (window ==NULL){
        std::cout<< "Failed to create window \n" ; 
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout<< "Failed to init GLAD"<<std::endl;

    }
    glViewport(0,0,800,600);
    glfwSetFramebufferSizeCallback(window, (GLFWframebuffersizefun) framebuffer_size_callback);
    while(!glfwWindowShouldClose(window))
    {
    glfwSwapBuffers(window);
    glfwPollEvents();    
    }
    return 0;
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}  