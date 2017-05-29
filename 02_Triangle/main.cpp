
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

	window = glfwCreateWindow( 400, 300, "02 Draw Triangle", NULL, NULL);
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	glewInit();

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);




	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);	// 註冊
	glBindVertexArray(VertexArrayID);	// 綁定

	// Create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders( "SimpleVertexShader.vert", "SimpleFragmentShader.frag" );


	static const GLfloat g_vertex_buffer_data[] = { 
		-1.0f, -1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		 0.0f,  1.0f, 0.0f,
	};

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(
		GL_ARRAY_BUFFER,	// 使用的型態
		sizeof(g_vertex_buffer_data),	// Data 的長度
		g_vertex_buffer_data,	// Data 的位置
		GL_STATIC_DRAW	// Data 該怎麼用
	);



	do{
		glClear( GL_COLOR_BUFFER_BIT );



		// Use our shader
		glUseProgram(programID);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0); //Specifies the index of the generic vertex attribute to be enabled or disabled.
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);	
		// 因為這個範例只有一個屬性（位置）而且上面 Bind 過，這裡其實不用再Bind一次。
		// 但是以後如果有多張圖片或多個屬性的時候就需要，所以通常會在 Pointer 之前會根據不同的屬性再 bind 一次
		glVertexAttribPointer(
			0,                  // 要對應 Shader 
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // no extra data between each position
			(void*)0            // array buffer offset
		);

		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, 3); // 3 indices starting at 0 -> 1 triangle
		glDisableVertexAttribArray(0);




		glfwSwapBuffers(window);
		glfwPollEvents();

	}
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );


	glDeleteBuffers(1, &vertexbuffer);
	glDeleteVertexArrays(1, &VertexArrayID);
	glDeleteProgram(programID);

	glfwTerminate();

	return 0;
}

