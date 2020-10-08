#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

#include "ip_filter.h"
#include <boost/asio/ip/address_v4.hpp>

#define BOOST_ENDIAN_DEPRECATED_NAMES // I should use it for compatibility with new boost versions
#include <boost/endian/endian.hpp>


namespace ip_tools
{

    void IpFilter::setIpPool(const string_vector& pool) 
    {
        _ipPool.reserve(pool.size());
        for (auto&& strAdr : pool)
        {
            try
            {
                _ipPool.push_back(boost::asio::ip::address_v4::from_string(strAdr));
            }
            catch(...)
            {
                // here we got wrong ip address string;
                continue;
            }
        }
    }

    const ipv4_vector& IpFilter::getIpPool() const { return _ipPool; }

    void IpFilter::sort(Order order)
    {
        if (order == Order::Acsending)
             std::sort(_ipPool.begin(), _ipPool.end(), std::greater<boost::asio::ip::address_v4>());
        else std::sort(_ipPool.begin(), _ipPool.end(), std::less<boost::asio::ip::address_v4>());  
    }


    string_vector IpFilter::applyFilter(std::vector<int> filter)
    {
        string_vector result;

        auto ip_comparator = [filter](boost::asio::ip::address_v4& addr) 
        {
            const size_t OctetesCnt = 4;
            bool res = false;

            auto internal_comparator = [OctetesCnt, addr](int oct_iter, unsigned char byteValue)
            {
                size_t offset = OctetesCnt - oct_iter;
                uint32_t address = 0;
                memcpy(&address, addr.to_bytes().data(), 4);
                boost::endian::endian_reverse_inplace(address);

                int applyOffset = (address >> (offset * 8)) & 255;
                
                //int applyOffset = (addr.to_uint() >> (offset * 8)) & 255; // it doesn't work with boost less the 1.68.0 
                //  (in version 1.58.0 that is default version of libboost_all_dev we should use addr.to_ulong()
                return !(applyOffset ^ byteValue);
            };

            if (!filter.size() || filter.size() > OctetesCnt + 1)
            {
                res = false;
            }                
            else if (filter[0] != 0)
            {
                int searchedVal = filter[0];
                for (int i = 1; i <= OctetesCnt && !res; ++i)
                    res = internal_comparator(i, searchedVal);
            }
            else
            {
                res = true;
                for (int i = 1; i < filter.size() && res; ++i)
                {
                    if(filter[i] >= 0)
                        res &= internal_comparator(i, (unsigned char)filter[i]);
                }
            }
            //
            return res;
        };

        auto iter_begin = std::find_if(_ipPool.begin(),  _ipPool.end(),  ip_comparator);
        auto iter_end   = std::find_if(_ipPool.rbegin(), _ipPool.rend(), ip_comparator);

        if (iter_begin != _ipPool.end() &&  iter_end != _ipPool.rend())
        {
            ptrdiff_t gap = iter_end - _ipPool.rbegin();

            auto iter = iter_begin;
            for (; iter != _ipPool.end() - gap; ++iter)
            {
                if (ip_comparator(*iter))
                    result.push_back((*iter).to_string());
            }
        }
        
        return result;
    }
}
