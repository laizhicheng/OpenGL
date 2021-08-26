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
	//λ��                 //��ɫ
	 0.5f, -0.5f, 0.0f,   1.0f,0.0f,0.0f,  // ���Ͻ�
	-0.5f, -0.5f, 0.0f,   0.0f,1.0f,0.0f,  // ���½�
	 0.0f,  0.5f, 0.0f,   0.0f,0.0f,1.0f,  // ���½�
};

//shader program
//������ɫ��
//��������ɫ����Դ����Ӳ�����ڴ����ļ�������C����ַ����У�
const char* vertexShaderSource = "#version 330 core   \n   "
"layout (location = 0) in vec3 aPos; // λ�ñ���������λ��ֵΪ 0                 \n   "
"layout (location = 1) in vec3 color;// ��ɫ����������λ��ֵΪ 1                  \n   "
"out vec3 ourColor;                                \n   "
"void main(){                                         \n   "
"	gl_Position = vec4(aPos, 1.0);\n"
"	ourColor = color;  \n"// ��ourColor����Ϊ���ǴӶ�����������õ���������ɫ
"} \n   ";

//Ƭ����ɫ��
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

	//���ڴ�С���½ǣ�0��0�� ���
	//glViewport(0, 0, 800, 600);

	//����ǰ������
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);


//vertex shader���붥����ɫ��---------------------------------------------------------------------------------------
	unsigned int vertexShader;//���涥����ɫ��Ϊ unsigned int����vertexShader������ɫ����
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//��һ�����ǰ������ɫ��Դ�븽�ӵ���ɫ��������
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);//����

	//check for shader compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

//fragment shader����Ƭ����ɫ��---------------------------------------------------------------------------------------
	//����һ��Ƭ����ɫ������
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
//��ɫ������
	//�����������
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	//������ɫ��
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//1.���ɲ���BAO
	unsigned int VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO); //glGenBuffers������һ������ID=VBO����

	glBindVertexArray(VAO);
	//����VBO����,�Ѷ������鸴�Ƶ������й�OpenGLʹ�á�

	glBindBuffer(GL_ARRAY_BUFFER, VBO);//ͨ��glbindbuffer��vbo�������gl_array_buffer��
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

//���ö�������ָ��:
	//λ������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//��ɫ����
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);






	//��Ⱦѭ��
	while (!glfwWindowShouldClose(window))//����ÿ��ѭ����Ҫ���һ��GLFW�Ƿ�Ҫ��رմ���
	{
		//---���룺�������ָ��----------------------
		processInput(window);


		//---��Ⱦ-----------------------------------------------
				//������Ļ(�������Զ�����ɫ������Ļ)
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);





		//����uniform��ɫ
		//GLfloat timeValue = glfwGetTime();
		//GLfloat greenValue = sin(timeValue) * 0.5f + 0.5f;
		//GLint vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		//glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);



		//draw the triangle
		glUseProgram(shaderProgram);//������ɫ��
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		//swap the screen buffers
		glfwSwapBuffers(window);//����buffer
		glfwPollEvents();//����Ƿ��д����¼����������룬��꣩
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);


	//
	glfwTerminate();
	return 0;

}





//escape����
// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

//���ڳ�ʼ��������ǰ������������
// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}