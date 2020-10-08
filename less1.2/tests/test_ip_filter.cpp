#define BOOST_TEST_MODULE test_ip_filter

// own
#include <ip_filter.h>
// boost
#include <boost/test/unit_test.hpp>
#include <boost/tokenizer.hpp>
// std
#include <vector>
#include <string>


BOOST_AUTO_TEST_SUITE(test_ip_filter)


BOOST_AUTO_TEST_CASE(check_stream_splitter)
{
	ip_tools::string_vector raw_data
	{
		"113.162.145.156	111	0",
		"157.39.22.224	5	6",
		"79.180.73.190	2	1",
		"179.210.145.4	22	0",
		"219.102.120.135	486	0",
		"67.232.81.208	1	0",
		"85.254.10.197	0	7",
		"23.240.215.189	6	0",
		"1.29.168.152	17	0",
		"185.69.186.168	1	3",
		"110.152.103.161	0	1",
		"185.182.81.131	1	1",
		"68.45.152.8	2	0",
		"114.221.179.117	0	1",
		"185.89.100.249	752	0",
		"46.70.113.73	1	0",
		"188.68.0.38	1	0",
	};

	BOOST_REQUIRE_EQUAL(raw_data.size(), 17);
	
	ip_tools::string_vector res1;
	for (auto&& str : raw_data)
	{
		auto tmp = ip_tools::split(str, '\t');
		if (tmp.size())
			res1.push_back(tmp[0]);
	}

	ip_tools::string_vector res2;
	for (auto&& str : raw_data)
	{
		auto tmp = ip_tools::fast_split(str, "\t");
		if (tmp.size())
			res2.push_back(tmp[0]);
	}

	//BOOST_REQUIRE_EQUAL(res1.size(), res2.size());
}



BOOST_AUTO_TEST_CASE(check_ip_sort)
{
	ip_tools::IpFilter ipFilter;
	
	ip_tools::string_vector data
	{
		"10.29.168.152",
		"192.168.1.237",
		"46.182.19.219",
		"255.1.12.16",
		"1.1.46.1",
		"1.231.69.33",
		"46.223.254.56",
		"192.168.1.235",
		"1.70.46.170",
		"1.87.203.225",		
		"1.1.234.46",
		"46.223.254.56", 
		"46.161.60.92"
	};

	ipFilter.setIpPool(data);
	ipFilter.sort(ip_tools::IpFilter::Order::Acsending);

	BOOST_CHECK(std::is_sorted(ipFilter.getIpPool().cbegin(), ipFilter.getIpPool().cend(), std::greater<boost::asio::ip::address_v4>()) == true);
}



BOOST_AUTO_TEST_CASE(check_octet_filter)
{
	BOOST_REQUIRE_EQUAL(17, 17);
	
	ip_tools::IpFilter ipFilter;

	ip_tools::string_vector data
	{
		"10.29.168.152",
		"192.168.1.237",
		"46.182.19.219",
		"255.1.12.16",
		"1.1.46.1",
		"1.231.69.33",
		"46.223.254.56",
		"192.168.1.235",
		"1.70.46.170",
		"1.87.203.225",
		"1.1.234.46",
		"46.223.254.56",
		"46.161.60.92"
	};

	ipFilter.setIpPool(data);
	ipFilter.sort(ip_tools::IpFilter::Order::Acsending);
	auto res = ipFilter.applyFilter({ 0, 231 }); 
	BOOST_CHECK(res.size() == 0);

	res = ipFilter.applyFilter({ 0, -1, 231 });
	BOOST_CHECK(res.size() == 1);

	res = ipFilter.applyFilter({ 46 });
	BOOST_CHECK(res.size() == 7);

	res = ipFilter.applyFilter({ 0, 192, 168 });
	BOOST_CHECK(res.size() == 2);
}


BOOST_AUTO_TEST_SUITE_END()
