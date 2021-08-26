#pragma once
#include <string>
#include <iostream>
//ÉùÃ÷µµ(Ðû¸æ£©


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

