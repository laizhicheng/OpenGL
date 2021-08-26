#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Shader.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

float vertices[] = {
	//位置                 //颜色
	 0.5f, -0.5f, 0.0f,   1.0f,0.0f,0.0f,  // 右上角
	-0.5f, -0.5f, 0.0f,   0.0f,1.0f,0.0f,  // 右下角
	 0.0f,  0.5f, 0.0f,   0.0f,0.0f,1.0f,  // 左下角
};

//shader program
//顶点着色器
//将顶点着色器的源代码硬编码在代码文件顶部的C风格字符串中：
const char* vertexShaderSource = "#version 330 core   \n   "
"layout (location = 0) in vec3 aPos; // 位置变量的属性位置值为 0                 \n   "
"layout (location = 1) in vec3 color;// 颜色变量的属性位置值为 1                  \n   "
"out vec3 ourColor;                                \n   "
"void main(){                                         \n   "
"	gl_Position = vec4(aPos, 1.0);\n"
"	ourColor = color;  \n"// 将ourColor设置为我们从顶点数据那里得到的输入颜色
"} \n   ";

//片段着色器
const char* fragmentShaderSource = "#version 330 core    \n"
"in vec3 ourColor;                                    \n"
"out vec4 FragColor;                                     \n"
"void main()                                             \n"
"{                                                       \n"
"    FragColor = vec4(ourColor,1.0f);                            \n"
"}                                                       \n";



int main()
{
	Shader* testShader = new Shader("vertexSource.vs", "fragmentSource.fs");

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

	//窗口大小左下角（0，0） 宽高
	//glViewport(0, 0, 800, 600);

	//裁切前后朝向面
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);


//vertex shader编译顶点着色器---------------------------------------------------------------------------------------
	unsigned int vertexShader;//储存顶点着色器为 unsigned int，用vertexShader创建着色器。
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//下一步我们把这个着色器源码附加到着色器对象上
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);//编译

	//check for shader compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

//fragment shader编译片段着色器---------------------------------------------------------------------------------------
	//创建一个片段着色器对象
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	//check for shader compile errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
//着色器程序
	//创建程序对象
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	//链接着色器
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//1.生成并绑定BAO
	unsigned int VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO); //glGenBuffers函数和一个缓冲ID=VBO对象

	glBindVertexArray(VAO);
	//生成VBO对象,把顶点数组复制到缓冲中供OpenGL使用。

	glBindBuffer(GL_ARRAY_BUFFER, VBO);//通过glbindbuffer把vbo缓冲绑定在gl_array_buffer上
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

//设置顶点属性指针:
	//位置属性
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//颜色属性
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);






	//渲染循环
	while (!glfwWindowShouldClose(window))//函数每次循环都要检查一次GLFW是否被要求关闭窗口
	{
		//---输入：检查输入指令----------------------
		processInput(window);


		//---渲染-----------------------------------------------
				//清理屏幕(用下面自定义颜色清理屏幕)
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);





		//更新uniform颜色
		//GLfloat timeValue = glfwGetTime();
		//GLfloat greenValue = sin(timeValue) * 0.5f + 0.5f;
		//GLint vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		//glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);



		//draw the triangle
		glUseProgram(shaderProgram);//激活着色器
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		//swap the screen buffers
		glfwSwapBuffers(window);//交换buffer
		glfwPollEvents();//检查是否有触发事件（键盘输入，鼠标）
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);


	//
	glfwTerminate();
	return 0;

}





//escape输入
// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

//窗口初始化（先在前面声明方法）
// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}