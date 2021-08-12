#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

int main() {

	//实例化GLFW窗口
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);//mac IOS 需要加上这条


	//Open GLFW Window
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);//前面两个参数是宽高，“名称”，NULL 空指针一定要用大写
	if (window == NULL)
	{
		printf("Failed to create GLFW window");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	//Init GLFW
	glewExperimental = true;//实验性质的功能，还是要设置为true
	if (glewInit() != GLEW_OK)//
	{
		printf("Init GLEW failde.");
		glfwTerminate();
		return -1;
	}

	//左下角（0，0） 宽高
	glViewport(0, 0, 800, 600);

	void framebuffer_size_callback(GLFWwindow * window, int width, int height);

	//调整过窗口之后callback 自动执行调整窗口大小
	void framebuffer_size_callback(GLFWwindow * window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


}

