#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include "hello window[1].h"

// ����----��ã�������


const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";

//����main��������������������ǽ���ʵ����GLFW����
int main()
{


	//glfwInit��������ʼ��GLFW�� GLFW �Ǹ��������Ĺ��߿�
	glfwInit();
	//ʹ��glfwWindowHint����������GLFW ���汾Major���ΰ汾Minor������ģʽ
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // mac OS Xϵͳ��Ҫ�ټ���һ����

	//����һ�����ڶ���������ڶ����������кʹ�����ص����ݣ����һᱻGLFW����������Ƶ�����õ���
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	//�����괰�����ǾͿ���֪ͨGLFW�����Ǵ��ڵ�����������Ϊ��ǰ�̵߳����������ˡ�
	//GLAD����������OpenGL�ĺ���ָ��ģ������ڵ����κ�OpenGL�ĺ���֮ǰ������Ҫ��ʼ��GLAD��
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//�������OpenGL��Ⱦ���ڵĳߴ��С�����ӿ�(Viewport)
	glViewport(0, 0, 800, 600);

	//���û��ı䴰�ڵĴ�С��ʱ���ӿ�ҲӦ�ñ�����.
	//�Դ���ע��һ���ص�����(Callback Function)��
	//������ÿ�δ��ڴ�С��������ʱ�򱻵��á�
	// ���֡�����С������Ҫһ��GLFWwindow��Ϊ���ĵ�һ���������Լ�����������ʾ���ڵ���ά�ȡ�
	// ÿ�����ڸı��С��GLFW�������������������Ӧ�Ĳ������㴦��
	// �����������д������������ʾ ȱ�� �� ; ���ֺţ����԰���������ŵ�����ļ�����
	//void framebuffer_size_callback(GLFWwindow * window, int width, int height)
	//{
	//	glViewport(0, 0, width, height);
	//}
	//���ǻ���Ҫע���������������GLFW����ϣ��ÿ�����ڵ�����С��ʱ��������������
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	//�����ڱ���һ����ʾ��ʱ��framebuffer_size_callbackҲ�ᱻ���á�
	//��������Ĥ(Retina)��ʾ����width��height�������Ա�ԭ����ֵ����һ�㡣


	// ��������
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};
	// ����һ�� VBO ���㻺�����
	unsigned int VBO;
	glGenBuffers(1, &VBO);

	// OpenGL�кܶ໺��������ͣ����㻺�����Ļ���������GL_ARRAY_BUFFER��
	// OpenGL��������ͬʱ�󶨶�����壬ֻҪ�����ǲ�ͬ�Ļ�������
	// ʹ��glBindBuffer�������´����Ļ���󶨵�GL_ARRAY_BUFFERĿ����
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	/***
	����һ��������ʹ�õ��κΣ���GL_ARRAY_BUFFERĿ���ϵģ�
	������ö����������õ�ǰ�󶨵Ļ���(VBO)��
	Ȼ�����ǿ��Ե���glBufferData�����������֮ǰ����Ķ������ݸ��Ƶ�������ڴ��У�
	*/
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	/**
	glBufferData��һ��ר���������û���������ݸ��Ƶ���ǰ�󶨻���ĺ��������ĵ�һ��������Ŀ�껺������ͣ����㻺�����ǰ�󶨵�GL_ARRAY_BUFFERĿ���ϡ��ڶ�������ָ���������ݵĴ�С(���ֽ�Ϊ��λ)����һ���򵥵�sizeof������������ݴ�С���С�����������������ϣ�����͵�ʵ�����ݡ�

	���ĸ�����ָ��������ϣ���Կ���ι�����������ݡ�����������ʽ��
	GL_STATIC_DRAW �����ݲ���򼸺�����ı䡣
	GL_DYNAMIC_DRAW�����ݻᱻ�ı�ܶࡣ
	GL_STREAM_DRAW ������ÿ�λ���ʱ����ı䡣
	*/

	// ����shader
	// ������ɫ��������
	unsigned int vertexShader;
	//����һ��������ɫ��
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	// ����ɫ��Դ����ӵ���ɫ����
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	/*glShaderSource������Ҫ�������ɫ��������Ϊ��һ���������ڶ�����ָ���˴��ݵ�Դ���ַ�������������ֻ��һ����
		�����������Ƕ�����ɫ��������Դ�룬���ĸ���������������ΪNULL��*/

		//����ڵ���glCompileShader������Ƿ�ɹ�
	int  success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	// ����ʧ�ܣ�
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// ����Ƭ����ɫ��
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// ��ɫ������ ��϶��㡢Ƭ����ɫ��
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// ��������ʧ��
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::GL_LINK FAILED\n" << infoLog << std::endl;
	}

	//// ���� shaderProgram����
	//glUseProgram(shaderProgram);
	////��glUseProgram��������֮��
	////	ÿ����ɫ�����ú���Ⱦ���ö���ʹ������������Ҳ����֮ǰд����ɫ��)�ˡ�

	// ɾ����ɫ������
	//���ˣ��ڰ���ɫ���������ӵ���������Ժ󣬼ǵ�ɾ����ɫ���������ǲ�����Ҫ�����ˣ�
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	/*������ɫ����������ָ���κ��Զ�������Ϊ��ʽ�����롣��ʹ����к�ǿ������Ե�ͬʱ��������ȷ��ζ�����Ǳ����ֶ�ָ���������ݵ���һ�����ֶ�Ӧ������ɫ������һ���������ԡ����ԣ����Ǳ�������Ⱦǰָ��OpenGL����ν��Ͷ������ݡ�

		���ǵĶ��㻺�����ݻᱻ����Ϊ���������ӣ�*/

		/*λ�����ݱ�����Ϊ32λ��4�ֽڣ�����ֵ��
		ÿ��λ�ð���3��������ֵ��
		����3��ֵ֮��û�п�϶��������ֵ�����⼸��ֵ�������н�������(Tightly Packed)��
		�����е�һ��ֵ�ڻ��忪ʼ��λ�á�*/

		//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		//glEnableVertexAttribArray(0); // ��Ӧ ������ɫ���� layout(location = 0)

		// ����������� ������һ�� VBO��VAO��һ�� ����� 
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
	// 2. �Ѷ������鸴�Ƶ������й�OpenGLʹ��
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3. ���ö�������ָ��
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	//���ǿɲ�ϣ��ֻ����һ��ͼ��֮�����ǵ�Ӧ�ó���������˳����رմ��ڡ�
	while (!glfwWindowShouldClose(window))
	{
		// ��������
		processInput(window);

		// ��Ⱦָ��
		//Ϊ�˲���һ�ж���������������ʹ��һ���Զ������ɫ�����Ļ����ÿ���µ���Ⱦ������ʼ��ʱ����������ϣ�������������������ܿ�����һ�ε�������Ⱦ����������������Ҫ��Ч������ͨ���ⲻ�ǣ�
		//������������ֻ������ɫֵ����������ֻ�����ɫ���塣

		// ������glClearColor�� ���������Ļ���õ���ɫ
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		//������glClear�����������ɫ����֮��������ɫ���嶼�ᱻ���ΪglClearColor�������õ���ɫ��
		glClear(GL_COLOR_BUFFER_BIT);
		// ����ΪɶҪ ��������ʵ��������ܣ���Ϊ��״̬������
		//glClearColor������һ��״̬���ú�����
		//	��glClear��������һ��״̬ʹ�õĺ�����
		//	��ʹ���˵�ǰ��״̬����ȡӦ�����Ϊ����ɫ��

		



		// ���� shaderProgram����
		glUseProgram(shaderProgram);
		//��glUseProgram��������֮��
		//	ÿ����ɫ�����ú���Ⱦ���ö���ʹ������������Ҳ����֮ǰд����ɫ��)�ˡ�

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);


		// ��鲢�����¼�����������
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	//glfwWindowShouldClose����������ÿ��ѭ���Ŀ�ʼǰ���һ��GLFW�Ƿ�Ҫ���˳�������ǵĻ��ú�������trueȻ����Ⱦѭ��������ˣ�֮��Ϊ���ǾͿ��Թر�Ӧ�ó����ˡ�
	//glfwPollEvents���������û�д���ʲô�¼�������������롢����ƶ��ȣ������´���״̬�������ö�Ӧ�Ļص�����������ͨ���ص������ֶ����ã���
	//glfwSwapBuffers�����ύ����ɫ���壨����һ��������GLFW����ÿһ��������ɫֵ�Ĵ󻺳壩��������һ�����б��������ƣ����ҽ�����Ϊ�����ʾ����Ļ�ϡ�
	// ˫����(Double Buffer) �����Ϊ����canvas? 
	//Ӧ�ó���ʹ�õ������ͼʱ���ܻ����ͼ����˸�����⡣ ������Ϊ���ɵ�ͼ����һ���ӱ����Ƴ����ģ����ǰ��մ����ң����϶��������صػ��ƶ��ɵġ�
	//��ǰ���屣�������������ͼ����������Ļ����ʾ�������еĵ���Ⱦָ����ں󻺳��ϻ��ơ������е���Ⱦָ��ִ����Ϻ����ǽ���(Swap)ǰ����ͺ󻺳壬����ͼ����������Գ���

	// ���һ�� ��ȷ�ͷ�/ɾ��֮ǰ�ķ����������Դ
	glfwTerminate();
	return 0;
}