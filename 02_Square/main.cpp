
#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
GLFWwindow* window;
#include <glm/glm.hpp>
using namespace glm;

#include "include/shader.hpp"

int main( void )
{
	glfwInit();	
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE); 

	window = glfwCreateWindow( 300, 300, "02 Draw Triangle", NULL, NULL);
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	glewInit();

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);



	// Create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders( "SimpleVertexShader.vert", "SimpleFragmentShader.frag" );

	//首先先叫出這些獨一無二的點 （只定義四個）
	GLfloat vertices[] = {
		0.8f, 0.8f, 0.0f,   // 右上角
		0.8f, -0.8f, 0.0f,  // 右下角
		-0.8f, -0.8f, 0.0f, // 左下角
		-0.8f, 0.8f, 0.0f   // 左上角
	};

	//Index 從零開始
	GLuint indices[] = { 
		0, 1, 3, // 第一個三角形
		1, 2, 3  // 第二個三角形
	};

	// 建立 VAO 
	GLuint VAO;
	glGenVertexArrays(1, &VAO);	// 註冊

    // 把 VBO 送到緩衝器，給 OpenGL 用
	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
	// 把 EBO 送到緩衝器，給 OpenGL 看
	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); 
		

	// 製作 VAO
	glBindVertexArray(VAO);		// 綁定 VAO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);	// 塞 VBO 
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); // 塞 EBO
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0 ); // 設定好指標
	glBindVertexArray(0);	// 做好這個 VAO 之後解綁



	// Change to Wireframe Mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	do{
		glClear( GL_COLOR_BUFFER_BIT );

		// Use Shader
		glUseProgram(programID);




		glBindVertexArray(VAO);		// 要用的時候，綁定 VAO
		glEnableVertexAttribArray(0); // 啟用 Vertex Attribute
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // Draw the triangle !
		glDisableVertexAttribArray(0); // 關閉 Vertex Attribute
		glBindVertexArray(0);	// 解綁 VAO




		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );

	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
	glDeleteProgram(programID);

	glfwTerminate();

	return 0;
}

