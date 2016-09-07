#ifndef RPCRUNTIMETRANSFER_H
#define RPCRUNTIMETRANSFER_H

#include <vector>

class RPCRuntimeFunction;

/*
 * A RPCRuntimeTransfer represents the Data in RPC-Generator encoding received or to be sent
 */

class RPCRuntimeTransfer {
	public:
	//Note: The passed in RPCRuntimeFunction must stay valid during the life-time of a RPCRuntimeTransfer
	RPCRuntimeTransfer(const RPCRuntimeFunction &function);

	//number of bytes that need to be added before the message is complete
	int get_min_number_of_missing_bytes() const;

	template <class Iterator>
	void add_data(Iterator &begin_it, Iterator &end_it) {
		data.insert(data.end(), begin_it, end_it);
	}

	const std::vector<unsigned char> encode() const;

	private:
	std::vector<unsigned char> data;
	const RPCRuntimeFunction *function;
};

#endif //RPCRUNTIMETRANSFER_H
