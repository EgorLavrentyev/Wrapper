#include <iostream>
#include "engine.h"
#include "wrapper.h"

class Subject
{
public:
	int Multiply(int a, int b)
	{
		return a * b;
	}
};

int main(int argc, char** argv)
{
	try
	{
		Subject subj;
		Wrapper wrapper(&subj, &Subject::Multiply, { {"arg1", 0}, {"arg2", 0} });
		Engine engine;
		engine.register_command(&wrapper, "command1");
		std::cout << engine.execute("command1", { {"arg2", 4}, {"arg1", 5} }) << std::endl;
	}
	catch (std::exception& error)
	{
		std::cout << error.what() << std::endl;
	}

	return 0;
}