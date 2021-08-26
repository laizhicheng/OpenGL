#include "Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>

//using namespace std;
//����


Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	//1.file B
	std::ifstream vertexFile;
	std::ifstream fragmentFile;
	//2.string B
	std::stringstream vertexSStream;
	std::stringstream fragmentSStream;

	//���ļ�
	vertexFile.open(vertexPath);
	fragmentFile.open(fragmentPath);
	//��֤ifstream��������׳��쳣
	vertexFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragmentFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		if (!vertexFile.is_open() || fragmentFile.is_open())
		{
			throw std::exception("open file error");
		}

		//3.��ȡ�ļ��Ļ������ݵ���������
		vertexSStream << vertexFile.rdbuf();
		fragmentSStream << fragmentFile.rdbuf();

		//4,��ɫstring����ȡ�ڴ����ݣ�ת��string
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