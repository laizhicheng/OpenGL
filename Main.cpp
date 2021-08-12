#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

int main() {

	//ʵ����GLFW����
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);//mac IOS ��Ҫ��������


	//Open GLFW Window
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);//ǰ�����������ǿ�ߣ������ơ���NULL ��ָ��һ��Ҫ�ô�д
	if (window == NULL)
	{
		printf("Failed to create GLFW window");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	//Init GLFW
	glewExperimental = true;//ʵ�����ʵĹ��ܣ�����Ҫ����Ϊtrue
	if (glewInit() != GLEW_OK)//
	{
		printf("Init GLEW failde.");
		glfwTerminate();
		return -1;
	}

	//���½ǣ�0��0�� ���
	glViewport(0, 0, 800, 600);

	void framebuffer_size_callback(GLFWwindow * window, int width, int height);

	//����������֮��callback �Զ�ִ�е������ڴ�С
	void framebuffer_size_callback(GLFWwindow * window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


}

