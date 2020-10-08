#include "ip_filter.h"


#define READ_FROM_FILE



int main(int argc, char* argv[])
{
    //ip_tools::IpFilter ipFilter;

    //ip_tools::string_vector data
    //{
    //    "231.233.69.33",
    //    "10.29.168.152",
    //    "192.168.1.237",
    //    "46.182.19.219",
    //    "255.1.12.16",
    //    "1.1.46.1",
    //    "1.231.69.33",
    //    "46.223.254.56",
    //    "192.168.1.235",
    //    "1.70.46.170",
    //    "1.87.203.225",
    //    "1.1.234.46",
    //    "46.223.254.56",
    //    "46.161.60.92"
    //};

    //ipFilter.setIpPool(data);
    //ipFilter.sort(ip_tools::IpFilter::Order::Acsending);
    //auto res = ipFilter.applyFilter({ 0, 231 });


    try
    {
        ip_tools::string_vector data;
       
#ifndef READ_FROM_FILE        
        for (std::string line; std::getline(std::cin, line);)
        {
            std::vector<std::string> v = ip_tools::fast_split(line, "\t");
            if(v.size())
                data.push_back(v.at(0));
        }
#else
        ip_tools::read_ip_from_file("C:\\Projects\\tests\\otus\\otus_course\\less1.2\\etc\\ip_filter.tsv", data);
#endif
        ip_tools::IpFilter ipfilter;
        ipfilter.setIpPool(data);
        ipfilter.sort(ip_tools::IpFilter::Order::Acsending);
        ipfilter.print(ipfilter.getIpPool());

        std::vector<std::vector<int>> filters = {
                                                    { 0, 1 },
                                                    { 0, 46, 70 },
                                                    { 46 }
                                                };

        for (auto&& fitler_iter : filters)
        {
            std::cout << std::endl;
            auto filteredIp = ipfilter.applyFilter(fitler_iter);
            ipfilter.print(filteredIp);
        }



        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first byte and output
        // ip = filter(1)

        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first and second bytes and output
        // ip = filter(46, 70)

        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        // TODO filter by any byte and output
        // ip = filter_any(46)

        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;



}


