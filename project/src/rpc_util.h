#ifndef RPC_UTIL_H
#define RPC_UTIL_H

#include <sstream>

struct Byte_stream : std::stringstream{
	template <class...T>
	Byte_stream(T && ...t) : std::stringstream(std::forward<T>(t)...){
		unsetf(std::ios_base::skipws);
	}
};

#endif // RPC_UTIL_H
