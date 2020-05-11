#include<GL/glew.h>
#include<GLFW/glfw3.h>

#include<iostream>

static unsigned int CompileShader(unsigned int type, const std::string &source) {
	
	unsigned int id = glCreateShader(GL_VERTEX_SHADER);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, NULL);
	glCompileShader(id);

	int result;
	glGetShader(id, GL_COMPULE_STATUS, &result);

	if(!result) { // GL_FALSE is just a zero actually 
		std::cout << "ERROR COMPILING SHADER\n";
	}

	return id;
}

static uint glCreateShader(const std::string &vertextShader, const std::string &fragmentShader) {
	uint program = glCreateProgram();
	uint vs = CompileShader(GL_VERTEX_SHADER, vertextShader);
	uint fs = Compil eShader(GL_FRAGMENT_SHADER, vertextShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLingProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return 0;
}

int main(void)
{
	GLFWwindow* window;

	if(!glfwInit()) {
		return -1;
	}

	window = glfwCreateWindow(640, 480, "Hello OpenGL", NULL, NULL);

	if(!window) {
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if(glewInit() != GLEW_OK) {
		std::out << "Error!\n";
	}

	std::out << glGetString(GL_VERSION) << std::endl;

	float positions[6] = {
		-0.5f, -0.5f,
		 0.5f,  0.5f,
		 0.5f, -0.5f 
  	};

	uint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

	 while(!glfwWindowShouldClose(window)) {
	 	glClear(GL_COLOR_BUFFER_BIT);

	 	glDrawArrays(GL_TRIANGLES, 0, 3);

	 	glfwSwapBuffers(window);

	 	glfwPollEvents();
	 }

	 glfwTerminate();
	 return 0;   
}