#include "rpcruntime_paramter_description.h"

RPCRuntimeParameterDescription::RPCRuntimeParameterDescription(RPCRuntimeParameterDescription::Type type, int bit_size, std::string parameter_name)
	: type(type)
	, bit_size(bit_size)
	, parameter_name(std::move(parameter_name)) {}

RPCRuntimeParameterDescription::Type RPCRuntimeParameterDescription::get_type() const {
	return type;
}

int RPCRuntimeParameterDescription::get_bit_size() const {
	return bit_size;
}

const std::string &RPCRuntimeParameterDescription::get_parameter_name() const {
	return parameter_name;
}

int RPCRuntimeParameterDescription::get_parameter_position() const
{
	return parameter_position;
}
