#include "Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>

//using namespace std;
//定义


Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	//1.file B
	std::ifstream vertexFile;
	std::ifstream fragmentFile;
	//2.string B
	std::stringstream vertexSStream;
	std::stringstream fragmentSStream;

	//打开文件
	vertexFile.open(vertexPath);
	fragmentFile.open(fragmentPath);
	//保证ifstream对象可以抛出异常
	vertexFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragmentFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		if (!vertexFile.is_open() || fragmentFile.is_open())
		{
			throw std::exception("open file error");
		}

		//3.读取文件的缓冲内容到数据流中
		vertexSStream << vertexFile.rdbuf();
		fragmentSStream << fragmentFile.rdbuf();

		//4,灰色string（读取内存数据）转成string
		vertexString = vertexSStream.str();
		fragmentString = fragmentSStream.str();
		//5,char*
		vertexSource = vertexString.c_str();
		fragmentSource = fragmentString.c_str();

		printf(vertexSource);
		printf(fragmentSource);

	}
	catch (const std::exception& ex)
	{
		printf(ex.what());
			
	}

}

void Shader::test()
{

}