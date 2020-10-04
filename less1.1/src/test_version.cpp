#define BOOST_TEST_MODULE test_version

// own
#include <version.h>
// boost
#include <boost/test/unit_test.hpp>
#include <boost/tokenizer.hpp>
// std
#include <vector>


BOOST_AUTO_TEST_SUITE(test_version)

BOOST_AUTO_TEST_CASE(validate_version_call)
{
	std::string current_version = version();
	BOOST_CHECK(current_version.length() > 0);	
}


BOOST_AUTO_TEST_CASE(parsing_validate)
{
	std::string current_version = version();
		
	using separator = boost::char_separator<char>;
	using tokenizer = boost::tokenizer<separator> ;
	tokenizer tok{current_version, separator{"."}};
	//
	std::vector<std::string> res;	
	for(auto&& token : tok)
		res.push_back(token);
	
	const int VERSION_DIGIT_COUNT = 3;	
	BOOST_CHECK_EQUAL(res.size(), VERSION_DIGIT_COUNT);
	
	//
	const int VERSION_PATCH_POS = 2;
	//BOOST_TEST_MESSAGE("PATCH " << std::stoi(res[VERSION_PATCH_POS]) << std::endl); 
	BOOST_CHECK(std::stoi(res[VERSION_PATCH_POS]) > 0);
}


BOOST_AUTO_TEST_CASE(validate_patch_version)
{
	std::string current_version = version();
		
	using separator = boost::char_separator<char>;
	using tokenizer = boost::tokenizer<separator> ;
	tokenizer tok{current_version, separator{"."}};
	//
	std::vector<std::string> res;	
	for(auto&& token : tok)
		res.push_back(token);	

	const int VERSION_PATCH_POS = 2;
	BOOST_CHECK(std::stoi(res[VERSION_PATCH_POS]) > 0);
}

BOOST_AUTO_TEST_SUITE_END()
