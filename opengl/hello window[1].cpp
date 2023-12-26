#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include "hello window[1].h"

// ����----��ã�����

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