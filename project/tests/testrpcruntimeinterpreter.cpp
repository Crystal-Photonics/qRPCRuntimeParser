#include "testrpcruntimeinterpreter.h"
#include "rpcruntime_decoder.h"
#include "rpcruntime_protocol_description.h"

#include <QByteArray>
#include <QPair>
#include <QString>
#include <QStringList>
#include <QTreeWidgetItem>
#include <fstream>
#include <functional>

using namespace std::string_literals;

#define RUNTEST 1

void TestRPCRuntimeInterpreter::initTestCase() {
    callBack_FieldID = "";
    callBack_humanReadableName = "";
	callBack_plotIndex = QPair<int, int>(0, 0);
    callBack_timestamp = QDateTime();
    callBack_value = 0;
}

void TestRPCRuntimeInterpreter::loadXMLFile_rpcInt16EnumTest() {
#if RUNTEST
    RPCRunTimeProtocolDescription rpcinterpreter;

	{
		std::ifstream xmlfile{"scripts/rpcInt16EnumTest.xml"};
		Q_ASSERT(xmlfile);
		bool result = rpcinterpreter.openProtocolDescription(xmlfile);
		QCOMPARE(result, true);
	}

	auto &funList = rpcinterpreter.get_functions();

	QCOMPARE(funList.size(), 1u);
	QCOMPARE(funList[0].get_function_name(), "rpcFunc_sendUint16AndEnumAndEnum"s);
	QCOMPARE(funList[0].get_request_id(), 2);
	QCOMPARE(funList[0].get_request_parameters().empty(), false);

	QCOMPARE(funList[0].get_request_parameters().size(), 3u);
	QCOMPARE(funList[0].get_request_parameters()[0].get_parameter_name(), "param1"s);
	QCOMPARE(funList[0].get_request_parameters()[1].get_parameter_name(), "param2"s);
	QCOMPARE(funList[0].get_request_parameters()[2].get_parameter_name(), "param3"s);

	QCOMPARE(funList[0].get_request_parameters()[0].get_parameter_type(), "uint16_t"s);
	QCOMPARE(funList[0].get_request_parameters()[1].get_parameter_type(), "enum1_t"s);
	QCOMPARE(funList[0].get_request_parameters()[2].get_parameter_type(), "enum2_t"s);

	QCOMPARE(funList[0].get_request_parameters()[0].get_type(), RPCRuntimeParameterDescription::Type::integer);
	QCOMPARE(funList[0].get_request_parameters()[1].get_type(), RPCRuntimeParameterDescription::Type::enumeration);
	QCOMPARE(funList[0].get_request_parameters()[2].get_type(), RPCRuntimeParameterDescription::Type::enumeration);

	QCOMPARE(funList[0].get_request_parameters()[0].get_bit_size(), 16);
	QCOMPARE(funList[0].get_request_parameters()[0].as_integer().is_signed, false);
	QCOMPARE(funList[0].get_request_parameters()[1].get_bit_size(), 8);
	QCOMPARE(funList[0].get_request_parameters()[2].get_bit_size(), 8);

	QCOMPARE(funList[0].get_request_parameters()[0].get_parameter_position(), 1);
	QCOMPARE(funList[0].get_request_parameters()[1].get_parameter_position(), 2);
	QCOMPARE(funList[0].get_request_parameters()[2].get_parameter_position(), 3);

	QCOMPARE(funList[0].get_request_parameters()[1].as_enumeration().values.size(), 4u);

	QCOMPARE(funList[0].get_request_parameters()[1].as_enumeration().values[0].first, 0);
	QCOMPARE(funList[0].get_request_parameters()[1].as_enumeration().values[0].second, "enum1_None"s);

	QCOMPARE(funList[0].get_request_parameters()[1].as_enumeration().values[1].first, 1);
	QCOMPARE(funList[0].get_request_parameters()[1].as_enumeration().values[1].second, "enum1_A"s);

	QCOMPARE(funList[0].get_request_parameters()[1].as_enumeration().values[2].first, 2);
	QCOMPARE(funList[0].get_request_parameters()[1].as_enumeration().values[2].second, "enum1_B"s);

	QCOMPARE(funList[0].get_request_parameters()[1].as_enumeration().values[3].first, 3);
	QCOMPARE(funList[0].get_request_parameters()[1].as_enumeration().values[3].second, "enum1_C"s);

	QCOMPARE(funList[0].get_request_parameters()[2].as_enumeration().values.size(), 2u);

	QCOMPARE(funList[0].get_request_parameters()[2].as_enumeration().values[0].first, 0);
	QCOMPARE(funList[0].get_request_parameters()[2].as_enumeration().values[0].second, "enum2_A"s);

	QCOMPARE(funList[0].get_request_parameters()[2].as_enumeration().values[1].first, 1);
	QCOMPARE(funList[0].get_request_parameters()[2].as_enumeration().values[1].second, "enum2_B"s);

	QCOMPARE(funList[0].get_reply_parameters().empty(), true);
#endif
}

void TestRPCRuntimeInterpreter::loadXMLFile_rpcSignedUnsignedTest() {
#if RUNTEST
    RPCRunTimeProtocolDescription rpcinterpreter;

	{
		std::ifstream xmlfile{"scripts/rpcSignedUnsignedTest.xml"};
		Q_ASSERT(xmlfile);
		bool result = rpcinterpreter.openProtocolDescription(xmlfile);
		QCOMPARE(result, true);
	}

	auto &funList = rpcinterpreter.get_functions();
	QCOMPARE(funList.size(), 1u);
	QCOMPARE(funList[0].get_request_parameters().size(), 4u);
	QCOMPARE(funList[0].get_request_parameters()[0].as_integer().is_signed, true);
	QCOMPARE(funList[0].get_request_parameters()[1].as_integer().is_signed, true);
	QCOMPARE(funList[0].get_request_parameters()[2].as_integer().is_signed, false);
	QCOMPARE(funList[0].get_request_parameters()[3].as_integer().is_signed, false);

	QCOMPARE(funList[0].get_reply_parameters().empty(), true);
#endif
}

void TestRPCRuntimeInterpreter::loadXMLFile_rpcInt32ReplyTest() {
#if RUNTEST
    RPCRunTimeProtocolDescription rpcinterpreter;

	{
		std::ifstream xmlfile{"scripts/rpcInt32ReplyTest.xml"};
		Q_ASSERT(xmlfile);
		bool result = rpcinterpreter.openProtocolDescription(xmlfile);
		QCOMPARE(result, true);
	}

	auto &funList = rpcinterpreter.get_functions();
	QCOMPARE(funList.size(), 1u);
	QCOMPARE(funList[0].get_function_name(), "simpleTest"s);
	QCOMPARE(funList[0].get_request_id(), 4);
	QCOMPARE(funList[0].get_request_parameters().size(), 1u);
	QCOMPARE(funList[0].get_request_parameters()[0].get_parameter_name(), "i"s);
	QCOMPARE(funList[0].get_request_parameters()[0].get_bit_size(), 32);
	QCOMPARE(funList[0].get_request_parameters()[0].as_integer().is_signed, true);
	QCOMPARE(funList[0].get_request_parameters()[0].get_parameter_type(), "int32_t"s);
	QCOMPARE(funList[0].get_request_parameters()[0].get_type(), RPCRuntimeParameterDescription::Type::integer);
	QCOMPARE(funList[0].get_request_parameters()[0].get_parameter_position(), 1);

	QCOMPARE(funList[0].get_reply_parameters().empty(), false);
	QCOMPARE(funList[0].get_reply_id(), 5);
	QCOMPARE(funList[0].get_reply_parameters().size(), 1u);
	QCOMPARE(funList[0].get_reply_parameters()[0].get_parameter_name(), "return_value_out"s);
	QCOMPARE(funList[0].get_reply_parameters()[0].get_bit_size(), 32);
	QCOMPARE(funList[0].get_reply_parameters()[0].get_type(), RPCRuntimeParameterDescription::Type::array);
	QCOMPARE(funList[0].get_reply_parameters()[0].get_parameter_position(), 1);
	QCOMPARE(funList[0].get_reply_parameters()[0].as_array().number_of_elements, 1);
	QCOMPARE(funList[0].get_reply_parameters()[0].as_array().type->get_type(), RPCRuntimeParameterDescription::Type::integer);
	QCOMPARE(funList[0].get_reply_parameters()[0].as_array().type->get_bit_size(), 32);
	QCOMPARE(funList[0].get_reply_parameters()[0].as_array().type->as_integer().is_signed, true);
#endif
}

void TestRPCRuntimeInterpreter::loadXMLFile_rpcArrayInputTest() {
#if RUNTEST
    RPCRunTimeProtocolDescription rpcinterpreter;

	{
		std::ifstream xmlfile{"scripts/arrayInputTest.xml"};
		Q_ASSERT(xmlfile);
		bool result = rpcinterpreter.openProtocolDescription(xmlfile);
		QCOMPARE(result, true);
	}

	auto &funList = rpcinterpreter.get_functions();
	QCOMPARE(funList.size(), 1u);
	QCOMPARE(funList[0].get_function_name(), "arrayInputTest"s);
	QCOMPARE(funList[0].get_request_id(), 10);
	QCOMPARE(funList[0].get_request_parameters().size(), 1u);
	QCOMPARE(funList[0].get_request_parameters()[0].get_parameter_name(), "text_in"s);
	QCOMPARE(funList[0].get_request_parameters()[0].get_bit_size(), 336);
	QCOMPARE(funList[0].get_request_parameters()[0].get_type(), RPCRuntimeParameterDescription::Type::array);
	QCOMPARE(funList[0].get_request_parameters()[0].as_array().number_of_elements, 42);
	QCOMPARE(funList[0].get_request_parameters()[0].get_parameter_position(), 1);

	QCOMPARE(funList[0].get_request_parameters()[0].as_array().number_of_elements, 1);
	QCOMPARE(funList[0].get_request_parameters()[0].as_array().type->get_type(), RPCRuntimeParameterDescription::Type::character);
	QCOMPARE(funList[0].get_request_parameters()[0].as_array().type->get_bit_size(), 8);
	QCOMPARE(funList[0].get_request_parameters()[0].as_array().type->get_parameter_type(), "char"s);

	QCOMPARE(funList[0].get_reply_parameters().empty(), false);
	QCOMPARE(funList[0].get_reply_id(), 11);
	QCOMPARE(funList[0].get_reply_parameters().size(), 0u);
#endif
}

void TestRPCRuntimeInterpreter::loadXMLFile_rpcMultiArrayInputTest() {
#if RUNTEST
    RPCRunTimeProtocolDescription rpcinterpreter;

	{
		std::ifstream xmlfile{"scripts/multiArrayInputTest.xml"};
		Q_ASSERT(xmlfile);
		bool result = rpcinterpreter.openProtocolDescription(xmlfile);
		QCOMPARE(result, true);
	}

	auto &funList = rpcinterpreter.get_functions();
	auto &pl = funList[0].get_request_parameters();

	QCOMPARE(funList.size(), 1u);

	QCOMPARE(funList[0].get_function_name(), "multiArrayTest"s);
	QCOMPARE(funList[0].get_request_id(), 8);
	QCOMPARE(pl.size(), 1u);
	QCOMPARE(pl[0].get_parameter_name(), "text_in"s);
	QCOMPARE(pl[0].get_bit_size(), 192);
	QCOMPARE(pl[0].get_type(), RPCRuntimeParameterDescription::Type::array);
	QCOMPARE(pl[0].as_array().number_of_elements, 2);
	QCOMPARE(pl[0].get_parameter_position(), 1);
	QCOMPARE(pl[0].get_parameter_type(), "char [2][3][4]"s);

	QCOMPARE(pl[0].as_array().number_of_elements, 1);

	QCOMPARE(pl[0].as_array().type->get_type(), RPCRuntimeParameterDescription::Type::array);
	QCOMPARE(pl[0].as_array().type->get_bit_size(), 96);
	QCOMPARE(pl[0].as_array().type->get_parameter_type(), "char [3][4]"s);
	QCOMPARE(pl[0].as_array().type->as_array().number_of_elements, 3);

	QCOMPARE(pl[0].as_array().type->as_array().number_of_elements, 1);
	QCOMPARE(pl[0].as_array().type->as_array().type->get_type(), RPCRuntimeParameterDescription::Type::array);
	QCOMPARE(pl[0].as_array().type->as_array().type->get_bit_size(), 32);
	QCOMPARE(pl[0].as_array().type->as_array().type->get_parameter_type(), "char [4]"s);
	QCOMPARE(pl[0].as_array().type->as_array().type->as_array().number_of_elements, 4);

	QCOMPARE(pl[0].as_array().type->as_array().type->as_array().number_of_elements, 1);
	QCOMPARE(pl[0].as_array().type->as_array().type->as_array().type->get_type(), RPCRuntimeParameterDescription::Type::character);
	QCOMPARE(pl[0].as_array().type->as_array().type->as_array().type->get_bit_size(), 8);
	QCOMPARE(pl[0].as_array().type->as_array().type->as_array().type->get_parameter_type(), "char"s);
	QCOMPARE(pl[0].as_array().type->as_array().type->as_array().type->as_array().number_of_elements, 1);

	QCOMPARE(funList[0].get_reply_parameters().empty(), false);
	QCOMPARE(funList[0].get_reply_id(), 9);
	QCOMPARE(funList[0].get_reply_parameters().size(), 0u);
#endif
}

void TestRPCRuntimeInterpreter::loadXMLFile_rpcStructInputTest() {
#if RUNTEST
    RPCRunTimeProtocolDescription rpcinterpreter;

	{
		std::ifstream xmlfile{"scripts/structInputTest.xml"};
		Q_ASSERT(xmlfile);
		bool result = rpcinterpreter.openProtocolDescription(xmlfile);
		QCOMPARE(result, true);
	}

	auto &funList = rpcinterpreter.get_functions();

	QCOMPARE(funList.size(), 1u);

	QCOMPARE(funList[0].get_function_name(), "structInputTest"s);
	QCOMPARE(funList[0].get_request_id(), 22);
	QCOMPARE(funList[0].get_request_parameters().size(), 0u);

	QCOMPARE(funList[0].get_reply_id(), 23);
	QCOMPARE(funList[0].get_reply_parameters().size(), 1u);
	QCOMPARE(funList[0].get_reply_parameters()[0].get_parameter_name(), "s_out"s);
	QCOMPARE(funList[0].get_reply_parameters()[0].get_bit_size(), 64);
	QCOMPARE(funList[0].get_reply_parameters()[0].get_type(), RPCRuntimeParameterDescription::Type::array);
	QCOMPARE(funList[0].get_reply_parameters()[0].as_array().number_of_elements, 1);
	QCOMPARE(funList[0].get_reply_parameters()[0].get_parameter_position(), 1);

	QCOMPARE(funList[0].get_reply_parameters()[0].as_array().number_of_elements, 1);
	QCOMPARE(funList[0].get_reply_parameters()[0].as_array().type->get_type(), RPCRuntimeParameterDescription::Type::structure);
	QCOMPARE(funList[0].get_reply_parameters()[0].as_array().type->get_bit_size(), 64);
	QCOMPARE(funList[0].get_reply_parameters()[0].as_array().type->get_parameter_type(), "struct TestStruct"s);

	QCOMPARE(funList[0].get_reply_parameters()[0].as_array().type->as_structure().members.size(), 4u);
	QCOMPARE(funList[0].get_reply_parameters()[0].as_array().type->as_structure().members[0].get_type(), RPCRuntimeParameterDescription::Type::integer);
	QCOMPARE(funList[0].get_reply_parameters()[0].as_array().type->as_structure().members[0].get_bit_size(), 32);
	QCOMPARE(funList[0].get_reply_parameters()[0].as_array().type->as_structure().members[0].get_parameter_name(), "n1"s);
	QCOMPARE(funList[0].get_reply_parameters()[0].as_array().type->as_structure().members[0].as_integer().is_signed, false);
	QCOMPARE(funList[0].get_reply_parameters()[0].as_array().type->as_structure().members[0].get_parameter_type(), "uint32_t"s);
	QCOMPARE(funList[0].get_reply_parameters()[0].as_array().type->as_structure().members[0].get_parameter_position(), 1);

	QCOMPARE(funList[0].get_reply_parameters()[0].as_array().type->as_structure().members[1].get_type(), RPCRuntimeParameterDescription::Type::integer);
	QCOMPARE(funList[0].get_reply_parameters()[0].as_array().type->as_structure().members[1].get_bit_size(), 16);
	QCOMPARE(funList[0].get_reply_parameters()[0].as_array().type->as_structure().members[1].get_parameter_name(), "n2"s);
	QCOMPARE(funList[0].get_reply_parameters()[0].as_array().type->as_structure().members[1].get_parameter_type(), "int16_t"s);
	QCOMPARE(funList[0].get_reply_parameters()[0].as_array().type->as_structure().members[1].as_integer().is_signed, true);
	QCOMPARE(funList[0].get_reply_parameters()[0].as_array().type->as_structure().members[1].get_parameter_position(), 2);

	QCOMPARE(funList[0].get_reply_parameters()[0].as_array().type->as_structure().members[2].get_type(), RPCRuntimeParameterDescription::Type::character);
	QCOMPARE(funList[0].get_reply_parameters()[0].as_array().type->as_structure().members[2].get_bit_size(), 8);
	QCOMPARE(funList[0].get_reply_parameters()[0].as_array().type->as_structure().members[2].get_parameter_name(), "n3"s);
	QCOMPARE(funList[0].get_reply_parameters()[0].as_array().type->as_structure().members[2].get_parameter_type(), "char"s);
	QCOMPARE(funList[0].get_reply_parameters()[0].as_array().type->as_structure().members[2].get_parameter_position(), 3);

	QCOMPARE(funList[0].get_reply_parameters()[0].as_array().type->as_structure().members[3].get_type(), RPCRuntimeParameterDescription::Type::integer);
	QCOMPARE(funList[0].get_reply_parameters()[0].as_array().type->as_structure().members[3].get_bit_size(), 8);
	QCOMPARE(funList[0].get_reply_parameters()[0].as_array().type->as_structure().members[3].get_parameter_name(), "n4"s);
	QCOMPARE(funList[0].get_reply_parameters()[0].as_array().type->as_structure().members[3].get_parameter_type(), "uint8_t"s);
	QCOMPARE(funList[0].get_reply_parameters()[0].as_array().type->as_structure().members[3].as_integer().is_signed, false);
	QCOMPARE(funList[0].get_reply_parameters()[0].as_array().type->as_structure().members[3].get_parameter_position(), 4);

#endif
}

void TestRPCRuntimeInterpreter::loadXMLFile_rpcArrayInStructTest() {
#if RUNTEST
    RPCRunTimeProtocolDescription rpcinterpreter;

	{
		std::ifstream xmlfile{"scripts/arrayInStructTest.xml"};
		Q_ASSERT(xmlfile);
		bool result = rpcinterpreter.openProtocolDescription(xmlfile);
		QCOMPARE(result, true);
	}

	auto &funList = rpcinterpreter.get_functions();

	QCOMPARE(funList.size(), 1u);

	QCOMPARE(funList[0].get_function_name(), "arrayInStructTest"s);
	QCOMPARE(funList[0].get_request_id(), 24);
	QCOMPARE(funList[0].get_request_parameters().size(), 0u);

	QCOMPARE(funList[0].get_reply_id(), 23);
	QCOMPARE(funList[0].get_reply_parameters().size(), 1u);
	QCOMPARE(funList[0].get_reply_parameters()[0].get_parameter_name(), "s_inout"s);
	QCOMPARE(funList[0].get_reply_parameters()[0].get_bit_size(), 400);
	QCOMPARE(funList[0].get_reply_parameters()[0].get_type(), RPCRuntimeParameterDescription::Type::array);
	QCOMPARE(funList[0].get_reply_parameters()[0].as_array().number_of_elements, 1);
	QCOMPARE(funList[0].get_reply_parameters()[0].get_parameter_position(), 1);

	QCOMPARE(funList[0].get_reply_parameters()[0].as_array().number_of_elements, 1);
	QCOMPARE(funList[0].get_reply_parameters()[0].as_array().type->get_type(), RPCRuntimeParameterDescription::Type::structure);
	QCOMPARE(funList[0].get_reply_parameters()[0].as_array().type->get_bit_size(), 400);
	QCOMPARE(funList[0].get_reply_parameters()[0].as_array().type->get_parameter_type(), "TypedefTestStruct"s);

	QCOMPARE(funList[0].get_reply_parameters()[0].as_array().type->as_structure().members.size(), 3u);
	QCOMPARE(funList[0].get_reply_parameters()[0].as_array().type->as_structure().members[0].get_type(), RPCRuntimeParameterDescription::Type::integer);
	QCOMPARE(funList[0].get_reply_parameters()[0].as_array().type->as_structure().members[0].get_bit_size(), 16);
	QCOMPARE(funList[0].get_reply_parameters()[0].as_array().type->as_structure().members[0].get_parameter_name(), "n"s);
	QCOMPARE(funList[0].get_reply_parameters()[0].as_array().type->as_structure().members[0].as_integer().is_signed, false);
	QCOMPARE(funList[0].get_reply_parameters()[0].as_array().type->as_structure().members[0].get_parameter_type(), "uint16_t"s);
	QCOMPARE(funList[0].get_reply_parameters()[0].as_array().type->as_structure().members[0].get_parameter_position(), 1);

	QCOMPARE(funList[0].get_reply_parameters()[0].as_array().type->as_structure().members[1].get_type(), RPCRuntimeParameterDescription::Type::array);
	QCOMPARE(funList[0].get_reply_parameters()[0].as_array().type->as_structure().members[1].get_bit_size(), 336);
	QCOMPARE(funList[0].get_reply_parameters()[0].as_array().type->as_structure().members[1].as_array().number_of_elements, 42);
	QCOMPARE(funList[0].get_reply_parameters()[0].as_array().type->as_structure().members[1].get_parameter_name(), "ia"s);
	QCOMPARE(funList[0].get_reply_parameters()[0].as_array().type->as_structure().members[1].get_parameter_type(), "uint8_t [42]"s);
	QCOMPARE(funList[0].get_reply_parameters()[0].as_array().type->as_structure().members[1].get_parameter_position(), 2);

	QCOMPARE(funList[0].get_reply_parameters()[0].as_array().type->as_structure().members[1].as_array().number_of_elements, 1);
	QCOMPARE(funList[0].get_reply_parameters()[0].as_array().type->as_structure().members[1].as_array().type->get_type(),
			 RPCRuntimeParameterDescription::Type::integer);
	QCOMPARE(funList[0].get_reply_parameters()[0].as_array().type->as_structure().members[1].as_array().type->get_parameter_type(), "uint8_t"s);
	QCOMPARE(funList[0].get_reply_parameters()[0].as_array().type->as_structure().members[1].as_array().type->get_bit_size(), 8);
	QCOMPARE(funList[0].get_reply_parameters()[0].as_array().type->as_structure().members[1].as_array().type->as_integer().is_signed, false);
	QCOMPARE(funList[0].get_reply_parameters()[0].as_array().type->as_structure().members[1].as_array().type->as_array().number_of_elements, 1);

	QCOMPARE(funList[0].get_reply_parameters()[0].as_array().type->as_structure().members[2].get_type(), RPCRuntimeParameterDescription::Type::array);
	QCOMPARE(funList[0].get_reply_parameters()[0].as_array().type->as_structure().members[2].get_bit_size(), 48);
	QCOMPARE(funList[0].get_reply_parameters()[0].as_array().type->as_structure().members[2].as_array().number_of_elements, 1);
	QCOMPARE(funList[0].get_reply_parameters()[0].as_array().type->as_structure().members[2].get_parameter_name(), "iaa"s);
	QCOMPARE(funList[0].get_reply_parameters()[0].as_array().type->as_structure().members[2].get_parameter_type(), "uint8_t [1][2][3]"s);
	QCOMPARE(funList[0].get_reply_parameters()[0].as_array().type->as_structure().members[2].get_parameter_position(), 3);

	QCOMPARE(funList[0].get_reply_parameters()[0].as_array().type->as_structure().members[2].as_array().number_of_elements, 1);
	QCOMPARE(funList[0].get_reply_parameters()[0].as_array().type->as_structure().members[2].as_array().type->get_type(),
			 RPCRuntimeParameterDescription::Type::array);
	QCOMPARE(funList[0].get_reply_parameters()[0].as_array().type->as_structure().members[2].as_array().type->get_parameter_type(), "uint8_t [2][3]"s);
	QCOMPARE(funList[0].get_reply_parameters()[0].as_array().type->as_structure().members[2].as_array().type->get_bit_size(), 48);
	QCOMPARE(funList[0].get_reply_parameters()[0].as_array().type->as_structure().members[2].as_array().type->as_array().number_of_elements, 2);

	QCOMPARE(funList[0].get_reply_parameters()[0].as_array().type->as_structure().members[2].as_array().type->as_array().number_of_elements, 1);
	QCOMPARE(funList[0].get_reply_parameters()[0].as_array().type->as_structure().members[2].as_array().type->as_array().type->get_type(),
			 RPCRuntimeParameterDescription::Type::array);
	QCOMPARE(funList[0].get_reply_parameters()[0].as_array().type->as_structure().members[2].as_array().type->as_array().type->get_parameter_type(),
			 "uint8_t [3]"s);
	QCOMPARE(funList[0].get_reply_parameters()[0].as_array().type->as_structure().members[2].as_array().type->as_array().type->get_bit_size(), 24);
	QCOMPARE(funList[0].get_reply_parameters()[0].as_array().type->as_structure().members[2].as_array().type->as_array().type->as_array().number_of_elements,
			 3);

	QCOMPARE(funList[0].get_reply_parameters()[0].as_array().type->as_structure().members[2].as_array().type->as_array().type->as_array().type->get_type(),
			 RPCRuntimeParameterDescription::Type::integer);
	QCOMPARE(funList[0].get_reply_parameters()[0].as_array().type->as_structure().members[2].as_array().type->as_array().type->as_array().type->get_bit_size(),
			 8);
	QCOMPARE(
		funList[0].get_reply_parameters()[0].as_array().type->as_structure().members[2].as_array().type->as_array().type->as_array().type->get_parameter_type(),
		"uint8_t"s);
	QCOMPARE(funList[0]
				 .get_reply_parameters()[0]
				 .as_array()
				 .type->as_structure()
				 .members[2]
				 .as_array()
				 .type->as_array()
				 .type->as_array()
				 .type->as_integer()
				 .is_signed,
			 false);

#endif
}

void TestRPCRuntimeInterpreter::loadXMLFile_rpcEnumInArrayTest() {
#if RUNTEST
    RPCRunTimeProtocolDescription rpcinterpreter;

	{
		std::ifstream xmlfile{"scripts/enumInArray.xml"};
		Q_ASSERT(xmlfile);
		bool result = rpcinterpreter.openProtocolDescription(xmlfile);
		QCOMPARE(result, true);
	}

	auto &funList = rpcinterpreter.get_functions();
	auto &pl = funList[0].get_reply_parameters();

	QCOMPARE(funList.size(), 1u);

	QCOMPARE(funList[0].get_function_name(), "enumInArray"s);
	QCOMPARE(funList[0].get_request_id(), 24);

	QCOMPARE(pl.size(), 1u);
	QCOMPARE(pl[0].get_parameter_name(), "return_value_out"s);
	QCOMPARE(pl[0].get_bit_size(), 32);
	QCOMPARE(pl[0].get_type(), RPCRuntimeParameterDescription::Type::array);
	QCOMPARE(pl[0].as_array().number_of_elements, 1);
	QCOMPARE(pl[0].get_parameter_position(), 1);
	QCOMPARE(pl[0].get_parameter_type(), "TypedefTestEnum [1]"s);

	QCOMPARE(pl[0].as_array().number_of_elements, 1);
	QCOMPARE(pl[0].as_array().type->get_type(), RPCRuntimeParameterDescription::Type::enumeration);
	QCOMPARE(pl[0].as_array().type->get_bit_size(), 32);
	QCOMPARE(pl[0].as_array().type->get_parameter_type(), "TypedefTestEnum"s);
	QCOMPARE(pl[0].as_array().type->as_array().number_of_elements, 1);

	QCOMPARE(pl[0].as_array().type->as_enumeration().values.size(), 3u);

	QCOMPARE(pl[0].as_array().type->as_enumeration().values[0].first, 0);
	QCOMPARE(pl[0].as_array().type->as_enumeration().values[0].second, "TTEa"s);

	QCOMPARE(pl[0].as_array().type->as_enumeration().values[1].first, 1);
	QCOMPARE(pl[0].as_array().type->as_enumeration().values[1].second, "TTEb"s);

	QCOMPARE(pl[0].as_array().type->as_enumeration().values[2].first, 5);
	QCOMPARE(pl[0].as_array().type->as_enumeration().values[2].second, "TTEc"s);

#endif
}

void TestRPCRuntimeInterpreter::loadXMLFile_rpcNegValueInEnumTest() {
#if RUNTEST
    RPCRunTimeProtocolDescription rpcinterpreter;

	{
		std::ifstream xmlfile{"scripts/negValueInEnum.xml"};
		Q_ASSERT(xmlfile);
		bool result = rpcinterpreter.openProtocolDescription(xmlfile);
		QCOMPARE(result, true);
	}

	auto &funList = rpcinterpreter.get_functions();
	auto &pl = funList[0].get_reply_parameters();

	QCOMPARE(funList.size(), 1u);

	QCOMPARE(funList[0].get_function_name(), "negValueInEnum"s);
	QCOMPARE(funList[0].get_request_id(), 24);
	QCOMPARE(funList[0].get_reply_id(), 23);

	QCOMPARE(pl.size(), 1u);
	QCOMPARE(pl[0].get_parameter_name(), "testEnum"s);

	QCOMPARE(pl[0].get_type(), RPCRuntimeParameterDescription::Type::enumeration);
	QCOMPARE(pl[0].get_bit_size(), 8);
	QCOMPARE(pl[0].get_parameter_type(), "enum TestEnum"s);
	QCOMPARE(pl[0].as_array().number_of_elements, 1);

	QCOMPARE(pl[0].as_enumeration().values.size(), 2u);

	QCOMPARE(pl[0].as_enumeration().values[0].first, 0);
	QCOMPARE(pl[0].as_enumeration().values[0].second, "TEa"s);

	QCOMPARE(pl[0].as_enumeration().values[1].first, 1);
	QCOMPARE(pl[0].as_enumeration().values[1].second, "TEb"s);

#endif
}

#if 0
void TestRPCRuntimeInterpreter::loadXMLFile_rpcDecodeTest_uint32_t() {
#if RUNTEST
	const uint8_t inBinData_array[] = {0x04, 0x05, 0x10, 0x20, 0x30};
    RPCRunTimeProtocolDescription rpcinterpreter;

	QByteArray inBinData = QByteArray((char *)inBinData_array, sizeof(inBinData_array));

	{
		std::ifstream xmlfile{"scripts/decodeTest_uint32_t.xml"};
		Q_ASSERT(xmlfile);
		bool result = rpcinterpreter.openProtocolDescription(xmlfile);
		QCOMPARE(result, true);
	}

    RPCRuntimeDecoder decoder(rpcinterpreter);
    decoder.RPCDecodeRPCData(inBinData);
	QCOMPARE(decoder.transfer.getTotalLength(), 5);

	QCOMPARE(decoder.decodedParams.count(), (int)1);
	QCOMPARE(decoder.decodedParams[0].value, (int64_t)0x30201005);

#endif
}

void TestRPCRuntimeInterpreter::loadXMLFile_rpcDecodeTest_int8_t() {
#if RUNTEST
    const uint8_t inBinData_array[2] = {0x04, 0xF0};
    RPCRunTimeProtocolDescription rpcinterpreter;

	QByteArray inBinData = QByteArray((char *)inBinData_array, sizeof(inBinData_array));

	{
		std::ifstream xmlfile{"scripts/decodeTest_int8_t.xml"};
		Q_ASSERT(xmlfile);
		bool result = rpcinterpreter.openProtocolDescription(xmlfile);
		QCOMPARE(result, true);
	}

    RPCRuntimeDecoder decoder(rpcinterpreter);
    decoder.RPCDecodeRPCData(inBinData);

	QCOMPARE(decoder.decodedParams.count(), 1);
	QCOMPARE(decoder.decodedParams[0].value, (int64_t)-16);

#endif
}

void TestRPCRuntimeInterpreter::loadXMLFile_rpcDecodeTest_int16_t() {
#if RUNTEST
    const uint8_t inBinData_array[3] = {0x04, 0xF0, 0xFF};
    RPCRunTimeProtocolDescription rpcinterpreter;

	QByteArray inBinData = QByteArray((char *)inBinData_array, sizeof(inBinData_array));

	{
		std::ifstream xmlfile{"scripts/decodeTest_int16_t.xml"};
		Q_ASSERT(xmlfile);
		bool result = rpcinterpreter.openProtocolDescription(xmlfile);
		QCOMPARE(result, true);
	}

    RPCRuntimeDecoder decoder(rpcinterpreter);
    decoder.RPCDecodeRPCData(inBinData);

	QCOMPARE(decoder.decodedParams.count(), 1);
	QCOMPARE(decoder.decodedParams[0].value, (int64_t)-16);

#endif
}

void TestRPCRuntimeInterpreter::loadXMLFile_rpcDecodeTest_array_char() {
#if RUNTEST
	const uint8_t inBinData_array[42] = {0x06, 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64, 0x21, 0x00, 0x00, 0x00,
										 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

    RPCRunTimeProtocolDescription rpcinterpreter;

	QByteArray inBinData = QByteArray((char *)inBinData_array, sizeof(inBinData_array));

	{
		std::ifstream xmlfile{"scripts/decodeTest_array_char.xml"};
		Q_ASSERT(xmlfile);
		bool result = rpcinterpreter.openProtocolDescription(xmlfile);
		QCOMPARE(result, true);
	}

    RPCRuntimeDecoder decoder(rpcinterpreter);
    decoder.RPCDecodeRPCData(inBinData);

	QCOMPARE(decoder.decodedParams.count(), 1);
	QCOMPARE(decoder.decodedParams[0].string, "Hello World!"s);

#endif
}

void TestRPCRuntimeInterpreter::loadXMLFile_rpcDecodeTest_struct_int() {
#if RUNTEST
	const uint8_t inBinData_array[] = {0x18, 0x2b, 0x00, 0x48, 0x61, 0x6c, 0x6c, 0x6f, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x30, 0x31,
									   0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x34, 0x38, 0x39, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
									   0x38, 0x39, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x00, 0x10, 0x20, 0x01, 0x11, 0x21};

    RPCRunTimeProtocolDescription rpcinterpreter;

	QByteArray inBinData = QByteArray((char *)inBinData_array, sizeof(inBinData_array));

	{
		std::ifstream xmlfile{"scripts/decodeTest_struct_int.xml"};
		Q_ASSERT(xmlfile);
		bool result = rpcinterpreter.openProtocolDescription(xmlfile);
		QCOMPARE(result, true);
	}

    RPCRuntimeDecoder decoder(rpcinterpreter);
    decoder.RPCDecodeRPCData(inBinData);

	auto &funList = rpcinterpreter.get_functions();
	QCOMPARE(funList[0].get_reply_parameters().size(), 1u);
	QCOMPARE(funList[0].get_reply_parameters()[0].get_parameter_name(), "s_inout"s);
	QCOMPARE(funList[0].get_reply_parameters()[0].get_type(), RPCRuntimeParameterDescription::Type::array);
	QCOMPARE(funList[0].get_reply_parameters()[0].as_array().number_of_elements, 1);

	QCOMPARE(funList[0].get_reply_parameters()[0].as_array().number_of_elements, 1);
	QCOMPARE(funList[0].get_reply_parameters()[0].as_array().members[0].get_type(), RPCRuntimeParameterDescription::Type::structure);

	QCOMPARE(funList[0].get_reply_parameters()[0].as_array().members[0].as_array().number_of_elements, 3);
	QCOMPARE(funList[0].get_reply_parameters()[0].as_array().members[0].as_array().members[0].get_type(), RPCRuntimeParameterDescription::Type::integer);
	QCOMPARE(funList[0].get_reply_parameters()[0].as_array().members[0].as_array().members[1].get_type(), RPCRuntimeParameterDescription::Type::array);
	QCOMPARE(funList[0].get_reply_parameters()[0].as_array().members[0].as_array().members[1].as_array().number_of_elements, 42);
	QCOMPARE(funList[0].get_reply_parameters()[0].as_array().members[0].as_array().members[2].get_type(), RPCRuntimeParameterDescription::Type::array);
	QCOMPARE(funList[0].get_reply_parameters()[0].as_array().members[0].as_array().members[2].as_array().number_of_elements, 1);

	QCOMPARE(decoder.decodedParams.count(), 1);
	QCOMPARE(decoder.decodedParams[0].subParams.count(), 1);
	QCOMPARE(decoder.decodedParams[0].subParams[0].subParams.count(), 3);
	QCOMPARE(decoder.decodedParams[0].subParams[0].subParams[0].value, (int64_t)43);

	QCOMPARE(decoder.decodedParams[0].subParams[0].subParams[1].subParams.count(), 42);
	QCOMPARE(decoder.decodedParams[0].subParams[0].subParams[1].subParams[0].value, (int64_t)0x48);
	QCOMPARE(decoder.decodedParams[0].subParams[0].subParams[1].getParamDescription().get_parameter_type(), RPCRuntimeParameterDescription::Type::array);
	QCOMPARE(decoder.decodedParams[0].subParams[0].subParams[1].string,
			 "0x48 0x61 0x6c 0x6c 0x6f 0x33 0x34 0x35 0x36 0x37 0x38 0x39 0x30 0x31 0x32 0x33 0x34 0x35 0x36 0x37 0x34 0x38 0x39 0x30 0x31 0x32 0x33 "
			 "0x34 0x35 0x36 0x37 0x38 0x39 0x30 0x31 0x32 0x33 0x34 0x35 0x36 0x37 0x38"s);
	QCOMPARE(decoder.decodedParams[0].subParams[0].subParams[1].subParams[0].getParamDescription().get_parameter_type(),
			 RPCRuntimeParameterDescription::Type::integer);

	QCOMPARE(decoder.decodedParams[0].subParams[0].subParams[2].subParams.count(), 1);
	QCOMPARE(decoder.decodedParams[0].subParams[0].subParams[2].subParams[0].subParams.count(), 2);
	QCOMPARE(decoder.decodedParams[0].subParams[0].subParams[2].subParams[0].subParams[0].subParams.count(), 3);
	QCOMPARE(decoder.decodedParams[0].subParams[0].subParams[2].subParams[0].subParams[0].subParams[0].value, (int64_t)0x00);
	QCOMPARE(decoder.decodedParams[0].subParams[0].subParams[2].subParams[0].subParams[0].subParams[1].value, (int64_t)0x10);
	QCOMPARE(decoder.decodedParams[0].subParams[0].subParams[2].subParams[0].subParams[0].subParams[2].value, (int64_t)0x20);

	QCOMPARE(decoder.decodedParams[0].subParams[0].subParams[2].subParams[0].subParams[1].subParams[0].value, (int64_t)0x01);
	QCOMPARE(decoder.decodedParams[0].subParams[0].subParams[2].subParams[0].subParams[1].subParams[1].value, (int64_t)0x11);
	QCOMPARE(decoder.decodedParams[0].subParams[0].subParams[2].subParams[0].subParams[1].subParams[2].value, (int64_t)0x21);

#endif
}

void TestRPCRuntimeInterpreter::loadXMLFile_rpcDecodeTest_struct_int_testID() {
#if RUNTEST
	const uint8_t inBinData_array[] = {0x18, 0x2b, 0x00, 0x48, 0x61, 0x6c, 0x6c, 0x6f, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x30, 0x31,
									   0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x34, 0x38, 0x39, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
									   0x38, 0x39, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x00, 0x10, 0x20, 0x01, 0x11, 0x21};

    RPCRunTimeProtocolDescription rpcinterpreter;

	QByteArray inBinData = QByteArray((char *)inBinData_array, sizeof(inBinData_array));

	{
		std::ifstream xmlfile{"scripts/decodeTest_struct_int.xml"};
		Q_ASSERT(xmlfile);
		bool result = rpcinterpreter.openProtocolDescription(xmlfile);
		QCOMPARE(result, true);
	}

    RPCRuntimeDecoder decoder(rpcinterpreter);
    decoder.RPCDecodeRPCData(inBinData);
	QCOMPARE(decoder.decodedParams.count(), 1);
	QCOMPARE(decoder.decodedParams[0].subParams.count(), 1);
	QCOMPARE(decoder.decodedParams[0].subParams[0].subParams.count(), 3);
	QCOMPARE(decoder.decodedParams[0].subParams[0].subParams[0].FieldID, "scripts/decodeTest_struct_int.xml?24?0?0?0"s);
	QCOMPARE(decoder.decodedParams[0].subParams[0].subParams[1].FieldID, "scripts/decodeTest_struct_int.xml?24?0?0?1"s);
	QCOMPARE(decoder.decodedParams[0].subParams[0].subParams[2].FieldID, "scripts/decodeTest_struct_int.xml?24?0?0?2"s);
    //qDebug() << decoder.decodedParams[0].subParams[0].subParams[2].getParamDescription().typeName;
    //qDebug() << decoder.decodedParams[0].subParams[0].subParams[2].getParamDescription().name;

	QCOMPARE(decoder.decodedParams[0].subParams[0].subParams[2].subParams.count(), 1);
	QCOMPARE(decoder.decodedParams[0].subParams[0].subParams[2].subParams[0].FieldID, "scripts/decodeTest_struct_int.xml?24?0?0?2?0"s);

	QCOMPARE(decoder.decodedParams[0].subParams[0].subParams[2].subParams[0].subParams[0].FieldID, "scripts/decodeTest_struct_int.xml?24?0?0?2?0?0"s);
	QCOMPARE(decoder.decodedParams[0].subParams[0].subParams[2].subParams[0].subParams[1].FieldID, "scripts/decodeTest_struct_int.xml?24?0?0?2?0?1"s);
    qDebug() << decoder.decodedParams[0].subParams[0].subParams[2].subParams[0].subParams[1].getParamDescription().typeName;
    qDebug() << decoder.decodedParams[0].subParams[0].subParams[2].subParams[0].subParams[1].getParamDescription().name;

#endif
}

void TestRPCRuntimeInterpreter::loadXMLFile_rpcDecodeTest_struct_int_TestByID() {
#if RUNTEST
	const uint8_t inBinData_array[] = {0x18, 0x2b, 0x00, 0x48, 0x61, 0x6c, 0x6c, 0x6f, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x30, 0x31,
									   0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x34, 0x38, 0x39, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
									   0x38, 0x39, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x00, 0x10, 0x20, 0x01, 0x11, 0x21};

    RPCRunTimeProtocolDescription rpcinterpreter;

	QByteArray inBinData = QByteArray((char *)inBinData_array, sizeof(inBinData_array));

	{
		std::ifstream xmlfile{"scripts/decodeTest_struct_int.xml"};
		Q_ASSERT(xmlfile);
		bool result = rpcinterpreter.openProtocolDescription(xmlfile);
		QCOMPARE(result, true);
	}

    RPCRuntimeDecoder decoder(rpcinterpreter);
    decoder.RPCDecodeRPCData(inBinData);
	QCOMPARE(decoder.fieldExists("scripts/fail.xml?25?0?0?2?0?1"), false);
	QCOMPARE(decoder.fieldExists("scripts/decodeTest_struct_int.xml?25?0?0?2?0?1"), false);
	QCOMPARE(decoder.fieldExists("scripts/decodeTest_struct_int.xml?24?0?0?2?0?1"), true);
	QCOMPARE(decoder.fieldExists("scripts/decodeTest_struct_int.xml?24?0?0?2?0?2"), false);
	QCOMPARE(decoder.fieldExists("scripts/decodeTest_struct_int.xml?24?0?0?2?0?1?0"), true);
	QCOMPARE(decoder.fieldExists("scripts/decodeTest_struct_int.xml?24?0?0?2?0?1?0?0"), false);
	QCOMPARE(decoder.fieldExists("scripts/decodeTest_struct_int.xml?24?0?0?0"), true);
	QCOMPARE(decoder.fieldExists("scripts/decodeTest_struct_int.xml?24?0?0?1"), true);
	QCOMPARE(decoder.fieldExists("scripts/decodeTest_struct_int.xml?24?0?0?2"), true);
	QCOMPARE(decoder.fieldExists("scripts/decodeTest_struct_int.xml?24?0?0?3"), false);

#endif
}

void TestRPCRuntimeInterpreter::loadXMLFile_rpcDecodeTest_struct_int_AccessByID() {
#if RUNTEST || 0
	const uint8_t inBinData_array[] = {0x18, 0x2b, 0x00, 0x48, 0x61, 0x6c, 0x6c, 0x6f, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x30, 0x31,
									   0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x34, 0x38, 0x39, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
									   0x38, 0x39, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x00, 0x10, 0x20, 0x01, 0x11, 0x21};

    RPCRunTimeProtocolDescription rpcinterpreter;

	QByteArray inBinData = QByteArray((char *)inBinData_array, sizeof(inBinData_array));

	{
		std::ifstream xmlfile{"scripts/decodeTest_struct_int.xml"};
		Q_ASSERT(xmlfile);
		bool result = rpcinterpreter.openProtocolDescription(xmlfile);
		QCOMPARE(result, true);
	}

    RPCRuntimeDecoder decoder(rpcinterpreter);
    decoder.RPCDecodeRPCData(inBinData);
    RPCRuntimeDecodedParam decParam = decoder.getDecodedParamByFieldID("scripts/decodeTest_struct_int.xml?24?0?0?2?0?1");
	QCOMPARE(decParam.isNull(), false);
	QCOMPARE(decParam.getParamDescription().name, ""s);
	QCOMPARE(decParam.getParamDescription().typeName, "uint8_t [3]"s);
	QCOMPARE(decParam.string, "0x01 0x11 0x21"s);

    decParam = decoder.getDecodedParamByFieldID("scripts/decodeTest_struct_int.xml?24?0?0?2?0?0");
	QCOMPARE(decParam.isNull(), false);
	QCOMPARE(decParam.getParamDescription().name, ""s);
	QCOMPARE(decParam.getParamDescription().typeName, "uint8_t [3]"s);
	QCOMPARE(decParam.string, "0x00 0x10 0x20"s);

    decParam = decoder.getDecodedParamByFieldID("scripts/decodeTest_struct_int.xml?24?0?0?2?0?2");
	QCOMPARE(decParam.isNull(), true);

    decParam = decoder.getDecodedParamByFieldID("scripts/decodeTest_struct_int.xml?24?0");
	QCOMPARE(decParam.isNull(), false);
	QCOMPARE(decParam.getParamDescription().name, "s_inout"s);
	QCOMPARE(decParam.getParamDescription().typeName, "TypedefTestStruct [1]"s);
	QCOMPARE(decParam.string, ""s);
	QCOMPARE(decParam.subParams.count(), 1);
	QCOMPARE(decParam.subParams[0].subParams.count(), 3);

    RPCRuntimeTransfer decTransfer = decoder.getDecodedTransferByFieldID("scripts/decodeTest_struct_int.xml?24");
	QCOMPARE(decTransfer.isNull(), false);
	QCOMPARE(decTransfer.isReply(), false);
	QCOMPARE(decTransfer.getName(), "typedefStructTest"s);

#endif
}

void TestRPCRuntimeInterpreter::loadXMLFile_rpcDecodeTest_struct_int_watchpoint_callback(QString FieldID, QString humanReadableName, QPair<int, int> plotIndex,
																						 QDateTime timestamp, int64_t value) {
    callBack_FieldID = FieldID;
    callBack_humanReadableName = humanReadableName;
    callBack_plotIndex = plotIndex;
    callBack_timestamp = timestamp;
    callBack_value = value;
}

void TestRPCRuntimeInterpreter::loadXMLFile_rpcDecodeTest_struct_int_watchpoint()

{
#if RUNTEST || 0
	const uint8_t inBinData_array[] = {0x18, 0x2b, 0x00, 0x48, 0x61, 0x6c, 0x6c, 0x6f, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x30, 0x31,
									   0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x34, 0x38, 0x39, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
									   0x38, 0x39, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x00, 0x10, 0x20, 0x01, 0x11, 0x21};

    RPCRunTimeProtocolDescription rpcinterpreter;

	QByteArray inBinData = QByteArray((char *)inBinData_array, sizeof(inBinData_array));

	{
		std::ifstream xmlfile{"scripts/decodeTest_struct_int.xml"};
		Q_ASSERT(xmlfile);
		bool result = rpcinterpreter.openProtocolDescription(xmlfile);
		QCOMPARE(result, true);
	}

	QPair<int, int> testPlotIndex(0, 1);
    QDateTime timeStamp = QDateTime(QDateTime::currentDateTime());

    RPCRuntimeDecoder decoder(rpcinterpreter);
    decoder.addWatchPoint("scripts/decodeTest_struct_int.xml?24?0?0?0", "humanReadableName", testPlotIndex,
						  std::bind(&TestRPCRuntimeInterpreter::loadXMLFile_rpcDecodeTest_struct_int_watchpoint_callback, this, std::placeholders::_1,
									std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5));
    decoder.setTimeStamp(timeStamp);
    initTestCase();
    decoder.RPCDecodeRPCData(inBinData);

	QCOMPARE(callBack_FieldID, "scripts/decodeTest_struct_int.xml?24?0?0?0"s);
	QCOMPARE(callBack_humanReadableName, "humanReadableName"s);
	QCOMPARE(callBack_plotIndex, testPlotIndex);
	QCOMPARE(callBack_timestamp, timeStamp);
	QCOMPARE(callBack_value, (int64_t)43);

    decoder.removeWatchPoint("scripts/decodeTest_struct_int.xml?24?0?0?0");
    initTestCase();
    decoder.RPCDecodeRPCData(inBinData);
	QCOMPARE(callBack_value, (int64_t)0);

    decoder.addWatchPoint("scripts/decodeTest_struct_int.xml?24?30?0?0", "humanReadableName", testPlotIndex,
						  std::bind(&TestRPCRuntimeInterpreter::loadXMLFile_rpcDecodeTest_struct_int_watchpoint_callback, this, std::placeholders::_1,
									std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5));

    initTestCase();
    decoder.RPCDecodeRPCData(inBinData);
	QCOMPARE(callBack_value, (int64_t)0);

#endif
}

void TestRPCRuntimeInterpreter::loadXMLFile_rpcDecodeTest_struct_int_treewidgetreport() {
#if RUNTEST
	const uint8_t inBinData_array[] = {0x18, 0x2b, 0x00, 0x48, 0x61, 0x6c, 0x6c, 0x6f, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x30, 0x31,
									   0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x34, 0x38, 0x39, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
									   0x38, 0x39, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x00, 0x10, 0x20, 0x01, 0x11, 0x21};

    RPCRunTimeProtocolDescription rpcinterpreter;

	QByteArray inBinData = QByteArray((char *)inBinData_array, sizeof(inBinData_array));

	{
		std::ifstream xmlfile{"scripts/decodeTest_struct_int.xml"};
		Q_ASSERT(xmlfile);
		bool result = rpcinterpreter.openProtocolDescription(xmlfile);
		QCOMPARE(result, true);
	}

    RPCRuntimeDecoder decoder(rpcinterpreter);
    decoder.RPCDecodeRPCData(inBinData);

    QList<QTreeWidgetItem *> items = decoder.getTreeWidgetReport(NULL);

	QCOMPARE(items.count(), 1);
	QCOMPARE(items[0]->text(0), "typedefStructTest"s);
	QCOMPARE(items[0]->text(1), "RPC_UART_RESULT typedefStructTest(TypedefTestStruct s_inout[1]);"s);

	QCOMPARE(items[0]->child(0)->childCount(), 1);
	QCOMPARE(items[0]->child(0)->text(0), "Request"s);
	QCOMPARE(items[0]->child(0)->text(1), ""s);

	QCOMPARE(items[0]->child(0)->child(0)->data(0, Qt::UserRole).toString(), "scripts/decodeTest_struct_int.xml?24?0"s);
	QCOMPARE(items[0]->child(0)->child(0)->childCount(), 1);
	QCOMPARE(items[0]->child(0)->child(0)->child(0)->childCount(), 3);
	QCOMPARE(items[0]->child(0)->child(0)->child(0)->child(0)->childCount(), 0);
	QCOMPARE(items[0]->child(0)->child(0)->child(0)->child(0)->text(0), "n(uint16_t)"s);
	QCOMPARE(items[0]->child(0)->child(0)->child(0)->child(0)->text(1), "43"s);
	qDebug() << items[0]->child(0)->child(0)->child(0)->child(0)->data(0, Qt::UserRole).toString();

	QCOMPARE(items[0]->child(0)->child(0)->child(0)->child(0)->childCount(), 0);
	QCOMPARE(items[0]->child(0)->child(0)->child(0)->child(1)->text(0), "ia(uint8_t [42])"s);
	QCOMPARE(items[0]->child(0)->child(0)->child(0)->child(1)->text(1).trimmed(),
			 "0x48 0x61 0x6C 0x6C 0x6F 0x33 0x34 0x35 0x36 0x37 0x38 0x39 0x30 0x31 0x32 0x33 0x34 0x35 0x36 0x37 0x34 0x38 0x39 0x30 0x31 0x32 0x33 "
					 "0x34 0x35 0x36 0x37 0x38 0x39 0x30 0x31 0x32 0x33 0x34 0x35 0x36 0x37 0x38")
				 .trimmed());

	QCOMPARE(items[0]->child(0)->child(0)->child(0)->child(2)->childCount(), 1);
	QCOMPARE(items[0]->child(0)->child(0)->child(0)->child(2)->text(0), "iaa(uint8_t [1][2][3])"s);
	QCOMPARE(items[0]->child(0)->child(0)->child(0)->child(2)->text(1).trimmed(), "").trimmed());

	QCOMPARE(items[0]->child(0)->child(0)->child(0)->child(2)->child(0)->childCount(), 2);
	QCOMPARE(items[0]->child(0)->child(0)->child(0)->child(2)->child(0)->data(0, Qt::UserRole).toString(), "scripts/decodeTest_struct_int.xml?24?0?0?2?0"s);
	QCOMPARE(items[0]->child(0)->child(0)->child(0)->child(2)->child(0)->text(0), "[0]"s);
	QCOMPARE(items[0]->child(0)->child(0)->child(0)->child(2)->child(0)->text(1).trimmed(), "").trimmed());

	QCOMPARE(items[0]->child(0)->child(0)->child(0)->child(2)->child(0)->child(0)->childCount(), 0);
	QCOMPARE(items[0]->child(0)->child(0)->child(0)->child(2)->child(0)->child(0)->data(0, Qt::UserRole).toString(),
			 "scripts/decodeTest_struct_int.xml?24?0?0?2?0?0"s);
	QCOMPARE(items[0]->child(0)->child(0)->child(0)->child(2)->child(0)->child(0)->text(0), "[0]"s);
	QCOMPARE(items[0]->child(0)->child(0)->child(0)->child(2)->child(0)->child(0)->text(1).trimmed(), "0x00 0x10 0x20").trimmed());

	QCOMPARE(items[0]->child(0)->child(0)->child(0)->child(2)->child(0)->child(1)->childCount(), 0);
	QCOMPARE(items[0]->child(0)->child(0)->child(0)->child(2)->child(0)->child(1)->data(0, Qt::UserRole).toString(),
			 "scripts/decodeTest_struct_int.xml?24?0?0?2?0?1"s);
	QCOMPARE(items[0]->child(0)->child(0)->child(0)->child(2)->child(0)->child(1)->text(0), "[1]"s);
	QCOMPARE(items[0]->child(0)->child(0)->child(0)->child(2)->child(0)->child(1)->text(1).trimmed(), "0x01 0x11 0x21").trimmed());

#endif
}

//

void TestRPCRuntimeInterpreter::loadXMLFile_rpcSignedUnsingedBug() {
#if 0
#if RUNTEST || 1
	const uint8_t inBinData_array[] = {0xFF, 0xFF, 0xFF, 0x04, 0x02, 0x52, 0x00, 0x9A, 0x00, 0x50, 0x00, 0x3C, 0x00, 0xE3, 0x4D};

    RPCRunTimeProtocolDescription rpcinterpreter;

	QByteArray inBinData = QByteArray((char *)inBinData_array, sizeof(inBinData_array));

	{
		std::ifstream xmlfile{"scripts/rpcSignedUnsingedBug.xml"};
		Q_ASSERT(xmlfile);
		bool result = rpcinterpreter.openProtocolDescription(xmlfile);
		QCOMPARE(result, true);
	}

    RPCRuntimeDecoder decoder(rpcinterpreter);
    decoder.RPCDecodeChannelCodedData(inBinData);

	QCOMPARE(decoder.decodedParams.count(), 4);
	QCOMPARE(decoder.decodedParams[0].value, (int64_t)82);
	QCOMPARE(decoder.decodedParams[1].value, (int64_t)410);
	QCOMPARE(decoder.decodedParams[2].value, (int64_t)80);
	QCOMPARE(decoder.decodedParams[3].value, (int64_t)60);

#endif
#endif
}

void TestRPCRuntimeInterpreter::loadXMLFile_rpcDecodeTest_enum() {
#if RUNTEST
    const uint8_t inBinData_array[] = {0x1a, 0x01};

    RPCRunTimeProtocolDescription rpcinterpreter;

	QByteArray inBinData = QByteArray((char *)inBinData_array, sizeof(inBinData_array));

	{
		std::ifstream xmlfile{"scripts/decodeTest_enum.xml"};
		Q_ASSERT(xmlfile);
		bool result = rpcinterpreter.openProtocolDescription(xmlfile);
		QCOMPARE(result, true);
	}

    RPCRuntimeDecoder decoder(rpcinterpreter);
    decoder.RPCDecodeRPCData(inBinData);

	QCOMPARE(decoder.decodedParams.count(), 1);
	QCOMPARE(decoder.decodedParams[0].string, "TEb"s);
	QCOMPARE(decoder.decodedParams[0].value, (int64_t)1);

#endif
}

void TestRPCRuntimeInterpreter::loadXMLFile_rpcDecodeTest_struct_int_report() {
#if RUNTEST
	const uint8_t inBinData_array[] = {0x18, 0x2b, 0x00, 0x48, 0x61, 0x6c, 0x6c, 0x6f, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x30, 0x31,
									   0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x34, 0x38, 0x39, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
									   0x38, 0x39, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x00, 0x10, 0x20, 0x01, 0x11, 0x21};

    RPCRunTimeProtocolDescription rpcinterpreter;

	QByteArray inBinData = QByteArray((char *)inBinData_array, sizeof(inBinData_array));

	{
		std::ifstream xmlfile{"scripts/decodeTest_struct_int.xml"};
		Q_ASSERT(xmlfile);
		bool result = rpcinterpreter.openProtocolDescription(xmlfile);
		QCOMPARE(result, true);
	}

    RPCRuntimeDecoder decoder(rpcinterpreter);
    decoder.RPCDecodeRPCData(inBinData);

	QCOMPARE(decoder.decodedParams.count(), 1);

	QStringList report = decoder.getPrintableReport();

    QFile inFile("scripts/decodeTest_struct_int_report_mask.txt");

    QFile outfile("scripts/decodeTest_struct_int_report_output.txt");
    outfile.open(QIODevice::WriteOnly);
    inFile.open(QIODevice::ReadOnly);
	QTextStream out(&outfile);    // we will serialize the data into the file
	QTextStream in_mask(&inFile); // we will serialize the data into the file

    QString line_mask;
    QStringList in;
    do {
        line_mask = in_mask.readLine();
        in.append(line_mask);

    } while (!line_mask.isNull());

	for (int i = 0; i < report.count(); i++) {
		out << report[i] + '\n';
    }
	QCOMPARE(in.count() - 1, report.count());
	for (int i = 0; i < report.count(); i++) {
		QCOMPARE(in[i], report[i]);
    }
#endif
}

void TestRPCRuntimeInterpreter::loadXMLFile_rpcDecodeTest_enum_report() {
#if RUNTEST
    const uint8_t inBinData_array[] = {0x1a, 0x01};

    RPCRunTimeProtocolDescription rpcinterpreter;

	QByteArray inBinData = QByteArray((char *)inBinData_array, sizeof(inBinData_array));

	{
		std::ifstream xmlfile{"scripts/decodeTest_enum.xml"};
		Q_ASSERT(xmlfile);
		bool result = rpcinterpreter.openProtocolDescription(xmlfile);
		QCOMPARE(result, true);
	}

    RPCRuntimeDecoder decoder(rpcinterpreter);
    decoder.RPCDecodeRPCData(inBinData);

	QStringList report = decoder.getPrintableReport();
    QFile inFile("scripts/decodeTest_enum_report_mask.txt");

    QFile outfile("scripts/decodeTest_enum_report_output.txt");
    outfile.open(QIODevice::WriteOnly);
    inFile.open(QIODevice::ReadOnly);
	QTextStream out(&outfile);    // we will serialize the data into the file
	QTextStream in_mask(&inFile); // we will serialize the data into the file

    QString line_mask;
    QStringList in;
    do {
        line_mask = in_mask.readLine();
        in.append(line_mask);

    } while (!line_mask.isNull());

	for (int i = 0; i < report.count(); i++) {
		out << report[i] + '\n';
    }
	QCOMPARE(in.count() - 1, report.count());
	for (int i = 0; i < report.count(); i++) {
		QCOMPARE(in[i], report[i]);
    }
#endif
}

void TestRPCRuntimeInterpreter::loadXMLFile_rpcDecodeTestFromChannelEncodedData_enum_report() {
#if RUNTEST
    const uint8_t inBinData_array[] = {'J', 'U', 'N', 'K', 0xff, 0xff, 0xff, 0x00, 0x1a, 0x01, 0x96, 0xe1, 'J', 'U', 'N', 'K'};

    RPCRunTimeProtocolDescription rpcinterpreter;

	QByteArray inBinData = QByteArray((char *)inBinData_array, sizeof(inBinData_array));

	{
		std::ifstream xmlfile{"scripts/decodeTest_enum.xml"};
		Q_ASSERT(xmlfile);
		bool result = rpcinterpreter.openProtocolDescription(xmlfile);
		QCOMPARE(result, true);
	}

    RPCRuntimeDecoder decoder(rpcinterpreter);
    decoder.RPCDecodeChannelCodedData(inBinData);
	QCOMPARE(decoder.getErrorCRCHappened(), false);
	QStringList report = decoder.getPrintableReport();
    QFile inFile("scripts/decodeTest_enum_report_mask.txt");
    inFile.open(QIODevice::ReadOnly);
	QTextStream in_mask(&inFile); // we will serialize the data into the file

    QString line_mask;
    QStringList in;
    do {
        line_mask = in_mask.readLine();
        in.append(line_mask);

    } while (!line_mask.isNull());

	QCOMPARE(in.count() - 1, report.count());
	for (int i = 0; i < report.count(); i++) {
		QCOMPARE(in[i], report[i]);
    }
#endif
}

void TestRPCRuntimeInterpreter::loadXMLFile_rpcDecodeTestFromChannelEncodedData_struct_int_report() {
#if RUNTEST
	const uint8_t inBinData_array[] = {'J',  'U',  'N',  'K',  0xff, 0xff, 0xff, 0x74, 0x18, 0x2b, 0x00, 0x48, 0x60, 0x6c, 0x6c, 0x6f, 0x32,
									   0x34, 0x34, 0x36, 0x36, 0x38, 0x1f, 0x38, 0x30, 0x30, 0x32, 0x32, 0x34, 0x34, 0x36, 0x36, 0x34, 0x38,
									   0x39, 0x30, 0x31, 0x00, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x30, 0x31, 0x32, 0x33, 0x34,
									   0x35, 0x18, 0x36, 0x37, 0x38, 0x00, 0x10, 0x20, 0x00, 0x11, 0x20, 0x93, 0x31, 'J',  'U',  'N',  'K'};

    RPCRunTimeProtocolDescription rpcinterpreter;

	QByteArray inBinData = QByteArray((char *)inBinData_array, sizeof(inBinData_array));

	{
		std::ifstream xmlfile{"scripts/decodeTest_struct_int.xml"};
		Q_ASSERT(xmlfile);
		bool result = rpcinterpreter.openProtocolDescription(xmlfile);
		QCOMPARE(result, true);
	}

    RPCRuntimeDecoder decoder(rpcinterpreter);
    decoder.RPCDecodeChannelCodedData(inBinData);

	QCOMPARE(decoder.decodedParams.count(), 1);
	QCOMPARE(decoder.getErrorCRCHappened(), false);
	QStringList report = decoder.getPrintableReport();

    QFile inFile("scripts/decodeTest_struct_int_report_mask.txt");

    inFile.open(QIODevice::ReadOnly);
	QTextStream in_mask(&inFile); // we will serialize the data into the file

    QString line_mask;
    QStringList in;
    do {
        line_mask = in_mask.readLine();
        in.append(line_mask);

    } while (!line_mask.isNull());

	QCOMPARE(in.count() - 1, report.count());
	for (int i = 0; i < report.count(); i++) {
		QCOMPARE(in[i], report[i]);
    }
#endif
}

void TestRPCRuntimeInterpreter::loadXMLFile_rpcAccessParamDescriptionByFieldID_struct_int_report() {
#if RUNTEST
    RPCRunTimeProtocolDescription rpcinterpreter;

	{
		std::ifstream xmlfile{"scripts/decodeTest_struct_int.xml"};
		Q_ASSERT(xmlfile);
		bool result = rpcinterpreter.openProtocolDescription(xmlfile);
		QCOMPARE(result, true);
	}

	RPCRuntimeParameterDescription paramDesc = rpcinterpreter.getParamDescriptionByFieldID("scripts/decodeTest_struct_int.xml?24?0?0?0");

	QCOMPARE(paramDesc.get_parameter_type(), RPCRuntimeParameterDescription::Type::integer);

    paramDesc = rpcinterpreter.getParamDescriptionByFieldID("scripts/decodeTest_struct_int.xml?25");

	QCOMPARE(paramDesc.rpcParamType, RPCParamType_t::param_none);

    paramDesc = rpcinterpreter.getParamDescriptionByFieldID("scripts/decodeTest_struct_int.xml?24?1?0?0");

	QCOMPARE(paramDesc.rpcParamType, RPCParamType_t::param_none);

    paramDesc = rpcinterpreter.getParamDescriptionByFieldID("scripts/decodeTest_struct_int.xml?24?0?1?0");

	QCOMPARE(paramDesc.rpcParamType, RPCParamType_t::param_none);

    paramDesc = rpcinterpreter.getParamDescriptionByFieldID("scripts/decodeTest_struct_int.xml?24?0?0?1");

	QCOMPARE(paramDesc.get_parameter_type(), RPCRuntimeParameterDescription::Type::array);
#endif
}

void TestRPCRuntimeInterpreter::loadXMLFile_rpcDecodeTestFromChannelEncodedData_WrongCRC() {
#if RUNTEST
	const uint8_t inBinData_array[] = {'J',  'U',  'N',  'K',  0xff, 0xff, 0xff, 0x74, 0x18, 0x2b, 0x00, 0x48, 0x60, 0x6c, 0x6c, 0x6f, 0x32,
									   0x34, 0x34, 0x36, 0x36, 0x38, 0x1f, 0x38, 0x30, 0x30, 0x32, 0x32, 0x34, 0x34, 0x36, 0x36, 0x34, 0x38,
									   0x39, 0x30, 0x31, 0x00, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x30, 0x31, 0x32, 0x33, 0x34,
									   0x35, 0x18, 0x36, 0x37, 0x38, 0x00, 0x10, 0x20, 0x00, 0x11, 0x20, 0x93, 0x30, 'J',  'U',  'N',  'K'};

    RPCRunTimeProtocolDescription rpcinterpreter;

	QByteArray inBinData = QByteArray((char *)inBinData_array, sizeof(inBinData_array));

	{
		std::ifstream xmlfile{"scripts/decodeTest_struct_int.xml"};
		Q_ASSERT(xmlfile);
		bool result = rpcinterpreter.openProtocolDescription(xmlfile);
		QCOMPARE(result, true);
	}

    RPCRuntimeDecoder decoder(rpcinterpreter);
    decoder.RPCDecodeChannelCodedData(inBinData);

	QCOMPARE(decoder.getErrorCRCHappened(), true);
#endif
}

void TestRPCRuntimeInterpreter::playWithChannelEncoding() {
#if RUNTEST
    const uint8_t inBinData_array[] = {0x1a, 0x01};
	QByteArray inBinData = QByteArray((char *)inBinData_array, sizeof(inBinData_array));

    RPCRunTimeProtocolDescription rpcinterpreter;
    rpcinterpreter.openProtocolDescription("scripts/decodeTest_enum.xml");

    RPCRuntimeDecoder decoder(rpcinterpreter);

    QByteArray outBinData = decoder.encodeToChannelCodedData(inBinData);

    QFile outfile("scripts/channelEncodedData.txt");
    outfile.open(QIODevice::WriteOnly);
	QTextStream out(&outfile); // we will serialize the data into the file
    QString line("{");
	for (int i = 0; i < outBinData.count() - 1; i++) {
		line += "0x%1, ").arg((uint8_t)outBinData[i], 2, 16, QChar('0'));
		if (line.length() > 100) {
			out << line + "\n";
            line = "";
        }
    }
	line += "0x%1}").arg((uint8_t)outBinData[outBinData.count() - 1], 2, 16, QChar('0'));
    out << line;
#endif
}
#endif
