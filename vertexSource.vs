#version 330 core                                                    
layout (location = 0) in vec3 aPos;   // 位置变量的属性位置值为 0          
layout (location = 1) in vec3 color;  // 颜色变量的属性位置值为 1          
out vec4 ourColor;                                                   
void main()
{                                                         
	gl_Position = vec4(aPos, 1.0);                                   
	ourColor = vec4(color,1.0f);   // 将ourColor设置为我们从顶点数据那里得到的输入颜色
}                                                                    