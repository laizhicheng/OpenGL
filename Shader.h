#pragma once
#include <string>
#include <iostream>
//������(���棩


class Shader
{

public:
	Shader(const char* vertexPath, const char* fragmentPath);
	std::string vertexString;
	std::string fragmentString;
	const char* vertexSource;
	const char* fragmentSource;




	void test();


private:


};

