
#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
GLFWwindow* window;
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
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

	window = glfwCreateWindow( 400, 300, "02 Draw Triangle", NULL, NULL);
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	glewInit();

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);




	// Create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders( "SimpleVertexShader.vert", "SimpleFragmentShader.frag" );

	// 拿到 "MVP" uniform 的 ID，代表他在著色器的位置，存起來方便之後可以控制
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");

	// 告訴著色器，物體該怎麼投影，畫面以外的物件會被捨棄。
	glm::mat4 Projection = glm::perspective(
		glm::radians(45.0f), // 視野夾角 45 度
		4.0f / 3.0f, // 畫面比例 4:3
		0.1f, 		// 最近可視距離
		100.0f		// 最遠可視距離
	);

	// Camera matrix
	glm::mat4 View = glm::lookAt(
		glm::vec3(3,3,3), // Camera 座標
		glm::vec3(0,0,0), // Center 畫面的中心（看向哪裡）
		glm::vec3(0,1,0)  // Head 可以當作軸的方向 (0,-1,0)會上下顛倒
	);

	// Model matrix : 先在原點不動。
	glm::mat4 Model      = glm::mat4(1.0f);

	// MVP 將 Model,View,Projection 相乘 （註：矩陣乘法，會反過來）
	glm::mat4 MVP        = Projection * View * Model; 




	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);	// 註冊
	glBindVertexArray(VertexArrayID);		// 綁定

	static const GLfloat g_vertex_buffer_data[] = { 
		-1.0f, -1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		 0.0f,  1.0f, 0.0f,
	};

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	do{
		glClear( GL_COLOR_BUFFER_BIT );
		glUseProgram(programID);


		
		// 將剛剛設定完的 MVP 交給著色器，當作傳入的參數 uniform MVP 。
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);



		// Position
		glEnableVertexAttribArray(0); 
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		
		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDisableVertexAttribArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();

	}
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );
	// close
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteVertexArrays(1, &VertexArrayID);
	glDeleteProgram(programID);

	glfwTerminate();

	return 0;
}

