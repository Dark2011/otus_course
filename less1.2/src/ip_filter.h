#pragma once

#include "tools.h"


namespace ip_tools
{
	class IpFilter
	{
	public:
		enum class Order { Acsending, Descending };

		void setIpPool(const string_vector&);
		const ipv4_vector& getIpPool() const;
		//
		void sort(Order);
		//

		/*!
		*	The first byte (zero position in vector) is used 
		*	as a flag that set search mode in "search this value in any octet",
		*	if this byte has not zero value.
		*	In other cases - this byte has to be zero, and all other bytes represent
		*	searched values in appropriate octet;
		*
		*	{ 46 }  - search ip with value 46 in any octet
		*	{ 0 , 1, 52 } - search ip with 1 in the first octet and 52 in the second octet
		*	{ 0, -1, -1, 240 } - search ip with 240 in the third octet 
		*
		*
		*/
		string_vector applyFilter(const std::vector<int>& filter);

		template <typename T>
		void print(const T& ipData) const
		{
			auto iter = ipData.cbegin();
			for (; iter != ipData.cend() - 1; ++iter)
				std::cout << *iter << std::endl;
			std::cout << *iter;
		}

	private:
		ipv4_vector _ipPool;
	};
}
