#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include "hello window[1].h"

// 入门----你好，三角形


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

//创建main函数，在这个函数中我们将会实例化GLFW窗口
int main()
{


	//glfwInit函数来初始化GLFW， GLFW 是辅助开发的工具库
	glfwInit();
	//使用glfwWindowHint函数来配置GLFW 主版本Major、次版本Minor、核心模式
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // mac OS X系统需要再加这一配置

	//创建一个窗口对象，这个窗口对象存放了所有和窗口相关的数据，而且会被GLFW的其他函数频繁地用到。
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	//创建完窗口我们就可以通知GLFW将我们窗口的上下文设置为当前线程的主上下文了。
	//GLAD是用来管理OpenGL的函数指针的，所以在调用任何OpenGL的函数之前我们需要初始化GLAD。
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//必须告诉OpenGL渲染窗口的尺寸大小，即视口(Viewport)
	glViewport(0, 0, 800, 600);

	//当用户改变窗口的大小的时候，视口也应该被调整.
	//对窗口注册一个回调函数(Callback Function)，
	//它会在每次窗口大小被调整的时候被调用。
	// 这个帧缓冲大小函数需要一个GLFWwindow作为它的第一个参数，以及两个整数表示窗口的新维度。
	// 每当窗口改变大小，GLFW会调用这个函数并填充相应的参数供你处理。
	// 下面这个函数写在这里总是提示 缺少 “ ; ”分号，所以把这个函数放到别的文件中了
	//void framebuffer_size_callback(GLFWwindow * window, int width, int height)
	//{
	//	glViewport(0, 0, width, height);
	//}
	//我们还需要注册这个函数，告诉GLFW我们希望每当窗口调整大小的时候调用这个函数：
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	//当窗口被第一次显示的时候framebuffer_size_callback也会被调用。
	//对于视网膜(Retina)显示屏，width和height都会明显比原输入值更高一点。


	// 顶点数据
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};
	// 创建一个 VBO 顶点缓存对象
	unsigned int VBO;
	glGenBuffers(1, &VBO);

	// OpenGL有很多缓冲对象类型，顶点缓冲对象的缓冲类型是GL_ARRAY_BUFFER。
	// OpenGL允许我们同时绑定多个缓冲，只要它们是不同的缓冲类型
	// 使用glBindBuffer函数把新创建的缓冲绑定到GL_ARRAY_BUFFER目标上
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	/***
	从这一刻起，我们使用的任何（在GL_ARRAY_BUFFER目标上的）
	缓冲调用都会用来配置当前绑定的缓冲(VBO)。
	然后我们可以调用glBufferData函数，它会把之前定义的顶点数据复制到缓冲的内存中：
	*/
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	/**
	glBufferData是一个专门用来把用户定义的数据复制到当前绑定缓冲的函数。它的第一个参数是目标缓冲的类型：顶点缓冲对象当前绑定到GL_ARRAY_BUFFER目标上。第二个参数指定传输数据的大小(以字节为单位)；用一个简单的sizeof计算出顶点数据大小就行。第三个参数是我们希望发送的实际数据。

	第四个参数指定了我们希望显卡如何管理给定的数据。它有三种形式：
	GL_STATIC_DRAW ：数据不会或几乎不会改变。
	GL_DYNAMIC_DRAW：数据会被改变很多。
	GL_STREAM_DRAW ：数据每次绘制时都会改变。
	*/

	// 处理shader
	// 顶点着色器的引用
	unsigned int vertexShader;
	//创建一个顶点着色器
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	// 把着色器源码添加到着色器里
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	/*glShaderSource函数把要编译的着色器对象作为第一个参数。第二参数指定了传递的源码字符串数量，这里只有一个。
		第三个参数是顶点着色器真正的源码，第四个参数我们先设置为NULL。*/

		//检测在调用glCompileShader后编译是否成功
	int  success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	// 编译失败：
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// 处理片段着色器
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// 着色器程序， 组合顶点、片段着色器
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// 处理链接失败
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::GL_LINK FAILED\n" << infoLog << std::endl;
	}

	//// 激活 shaderProgram对象
	//glUseProgram(shaderProgram);
	////在glUseProgram函数调用之后，
	////	每个着色器调用和渲染调用都会使用这个程序对象（也就是之前写的着色器)了。

	// 删除着色器对象
	//对了，在把着色器对象链接到程序对象以后，记得删除着色器对象，我们不再需要它们了：
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	/*顶点着色器允许我们指定任何以顶点属性为形式的输入。这使其具有很强的灵活性的同时，它还的确意味着我们必须手动指定输入数据的哪一个部分对应顶点着色器的哪一个顶点属性。所以，我们必须在渲染前指定OpenGL该如何解释顶点数据。

		我们的顶点缓冲数据会被解析为下面这样子：*/

		/*位置数据被储存为32位（4字节）浮点值。
		每个位置包含3个这样的值。
		在这3个值之间没有空隙（或其他值）。这几个值在数组中紧密排列(Tightly Packed)。
		数据中第一个值在缓冲开始的位置。*/

		//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		//glEnableVertexAttribArray(0); // 对应 顶点着色器的 layout(location = 0)

		// 顶点数组对象 跳到这一步 VBO到VAO这一步 不理解 
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
	// 2. 把顶点数组复制到缓冲中供OpenGL使用
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3. 设置顶点属性指针
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	//我们可不希望只绘制一个图像之后我们的应用程序就立即退出并关闭窗口。
	while (!glfwWindowShouldClose(window))
	{
		// 监听输入
		processInput(window);

		// 渲染指令
		//为了测试一切都正常工作，我们使用一个自定义的颜色清空屏幕。在每个新的渲染迭代开始的时候我们总是希望清屏，否则我们仍能看见上一次迭代的渲染结果（这可能是你想要的效果，但通常这不是）
		//由于现在我们只关心颜色值，所以我们只清空颜色缓冲。

		// 调用了glClearColor来 设置清空屏幕所用的颜色
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		//当调用glClear函数，清除颜色缓冲之后，整个颜色缓冲都会被填充为glClearColor里所设置的颜色。
		glClear(GL_COLOR_BUFFER_BIT);
		// 疑问为啥要 用两步来实现这个功能，因为是状态机！？
		//glClearColor函数是一个状态设置函数，
		//	而glClear函数则是一个状态使用的函数，
		//	它使用了当前的状态来获取应该清除为的颜色。

		



		// 激活 shaderProgram对象
		glUseProgram(shaderProgram);
		//在glUseProgram函数调用之后，
		//	每个着色器调用和渲染调用都会使用这个程序对象（也就是之前写的着色器)了。

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);


		// 检查并调用事件，交换缓冲
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	//glfwWindowShouldClose函数在我们每次循环的开始前检查一次GLFW是否被要求退出，如果是的话该函数返回true然后渲染循环便结束了，之后为我们就可以关闭应用程序了。
	//glfwPollEvents函数检查有没有触发什么事件（比如键盘输入、鼠标移动等）、更新窗口状态，并调用对应的回调函数（可以通过回调方法手动设置）。
	//glfwSwapBuffers函数会交换颜色缓冲（它是一个储存着GLFW窗口每一个像素颜色值的大缓冲），它在这一迭代中被用来绘制，并且将会作为输出显示在屏幕上。
	// 双缓冲(Double Buffer) 简单理解为离屏canvas? 
	//应用程序使用单缓冲绘图时可能会存在图像闪烁的问题。 这是因为生成的图像不是一下子被绘制出来的，而是按照从左到右，由上而下逐像素地绘制而成的。
	//。前缓冲保存着最终输出的图像，它会在屏幕上显示；而所有的的渲染指令都会在后缓冲上绘制。当所有的渲染指令执行完毕后，我们交换(Swap)前缓冲和后缓冲，这样图像就立即呈显出来

	// 最后一步 正确释放/删除之前的分配的所有资源
	glfwTerminate();
	return 0;
}