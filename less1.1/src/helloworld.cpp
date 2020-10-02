#include <version.h>

#include <vector>

int main(int argc, char* argv[])
{
	std::cout << "BUILD " << version() << std::endl;;
	std::cout << "Hello, world!";	

	std::vector<std::string> test;
	test.push_back("123");

	std::stoi(test[0]);
	return 0;
}