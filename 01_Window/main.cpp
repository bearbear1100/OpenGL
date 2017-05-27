// Include standard headers
#include <stdio.h>
#include <stdlib.h>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
using namespace glm;

int main( void )
{
	// 初始化 GLFW
	glfwInit();
	
	
	// 設定參數
	glfwWindowHint(GLFW_SAMPLES, 4);	// 抗鋸齒： 4x MSAA, means that each pixel of the window's buffer consists of 4 subsamples
	// OpenGL3.3 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);	// 主版本
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);	// 次版本
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // MacOs需要加上這句，配置才會啟用;
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 告訴 OpenGL 使用 Core-profile 模式
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE); // 不能調視窗大小



	// Open a window and create its OpenGL context
	window = glfwCreateWindow( 1024, 768, "01 Just Open Window", NULL, NULL);
	glfwMakeContextCurrent(window);
	glewInit();


	// 讓你可以透過 ESC 關閉
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// 背景深藍色
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);



	do{
		// Clear the screen. It can cause flickering, so it's there nonetheless.
		glClear( GL_COLOR_BUFFER_BIT );


		// Do nothing !!

		
		// Swap buffers （交換前後Buffer)
		glfwSwapBuffers(window);
		// Check whether any Event be triggered （滑鼠、鍵盤...）
		glfwPollEvents();

	} // ESC key was pressed or the window was closed.
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );

	// Close OpenGL window and terminate GLFW.
	glfwTerminate();

	return 0;
}

