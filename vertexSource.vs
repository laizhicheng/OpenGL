#version 330 core                                                    
layout (location = 0) in vec3 aPos;   // λ�ñ���������λ��ֵΪ 0          
layout (location = 1) in vec3 color;  // ��ɫ����������λ��ֵΪ 1          
out vec4 ourColor;                                                   
void main()
{                                                         
	gl_Position = vec4(aPos, 1.0);                                   
	ourColor = vec4(color,1.0f);   // ��ourColor����Ϊ���ǴӶ�����������õ���������ɫ
}                                                                    