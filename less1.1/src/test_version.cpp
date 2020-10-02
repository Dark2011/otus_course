#define BOOST_TEST_MODULE test_version

#include <version.h>
#include <boost/test/unit_test.hpp>
#include <boost/tokenizer.hpp>
#include <vector>


BOOST_AUTO_TEST_SUITE(test_version)

BOOST_AUTO_TEST_CASE(validate_test_version)
{
	std::string current_version = version();
	BOOST_CHECK(current_version.length() > 0);
	
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
	BOOST_CHECK(std::stoi(res[VERSION_PATCH_POS]) > 0);
}

BOOST_AUTO_TEST_SUITE_END()
