#pragma once

// boost
#include <boost/tokenizer.hpp>
#include <boost/asio/ip/address_v4.hpp>
// std
#include <vector>
#include <string>
#include <iostream>
#include <fstream>



namespace ip_tools
{

    using string_vector = std::vector<std::string>;
    using ipv4_vector = std::vector<boost::asio::ip::address_v4>;

    // ("",  '.') -> [""]
    // ("11", '.') -> ["11"]
    // ("..", '.') -> ["", "", ""]
    // ("11.", '.') -> ["11", ""]
    // (".11", '.') -> ["", "11"]
    // ("11.22", '.') -> ["11", "22"]
    inline std::vector<std::string> split(const std::string& str, char d)
    {
        std::vector<std::string> r;

        std::string::size_type start = 0;
        std::string::size_type stop = str.find_first_of(d);
        while (stop != std::string::npos)
        {
            r.push_back(str.substr(start, stop - start));

            start = stop + 1;
            stop = str.find_first_of(d, start);
        }

        r.push_back(str.substr(start));

        return r;
    }


    inline auto fast_split(const std::string& str, const char* d)
    {
        ip_tools::string_vector res;
        using separator = boost::char_separator<char>;
        using tokenizer = boost::tokenizer<separator>;
        tokenizer tok{ str, separator{d} };

        for (auto&& token : tok)
            res.push_back(token);

        return res;
    }


    inline void read_ip_from_file(const char* filename, ip_tools::string_vector& ip_pool)
    {
        std::streambuf* backup = std::cin.rdbuf();
        std::ifstream file(filename, std::ifstream::in);
        std::cin.rdbuf(file.rdbuf());

        for (std::string line; std::getline(std::cin, line);)
        {
            std::vector<std::string> v = fast_split(line, "\t");
            if (v.size())
                ip_pool.push_back(v[0]);
        }
        std::cin.rdbuf(backup);
    }
}
