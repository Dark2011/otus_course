#include <version.h>

#include <vector>


int main(int argc, char* argv[])
{
	std::cout << "BUILD " << version() << std::endl;;
	std::cout << "Hello, world!" << std::endl;	
	//
	return 0;
}
