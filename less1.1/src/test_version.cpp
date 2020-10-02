#define BOOST_TEST_MODULE test_version

#include <version.h>
#include <boost/test/unit_test.hpp>
#include <boost/tokenizer.hpp>
#include <vector>


BOOST_AUTO_TEST_SUITE(test_version)

BOOST_AUTO_TEST_CASE(validate_test_version)
{
	std::string current_version = version();
	BOOST_CHECK_EQUAL(1, 1);	
	
	std::cout << "BUILD " << current_version << std::endl;

	using tokenizer = boost::tokenizer<boost::char_separator<char>> ;
	tokenizer tok{current_version};
	std::vector<std::string> res;
	
	for(auto&& token : tok)
		res.push_back(token);
	
	const int VERSION_DIGIT_COUNT = 3;
	BOOST_CHECK_EQUAL(res.size(), VERSION_DIGIT_COUNT);
	/*
	//
	const int VERSION_PATCH_POS = 2;	
	
	std::cout << "PATCH " << std::stoi(res[VERSION_PATCH_POS]) << std::endl;
	BOOST_CHECK(std::stoi(res[VERSION_PATCH_POS]) > 0);*/
}

BOOST_AUTO_TEST_SUITE_END()
