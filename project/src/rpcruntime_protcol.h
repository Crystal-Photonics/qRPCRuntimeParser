#ifndef RPCRUNTIMEPROTCOL_H
#define RPCRUNTIMEPROTCOL_H

#include "channel_codec_wrapper.h"
#include "rpcruntime_decoded_function_call.h"
#include "rpcruntime_decoder.h"
#include "rpcruntime_encoder.h"
#include "rpcruntime_protocol_description.h"
#include <QByteArray>
#include <QObject>
#include <chrono>
#include <memory>

enum class RPCConsoleLevel { note, debug, warning, error };

class RPCIODevice : public QObject {
    Q_OBJECT
    public:
    RPCIODevice();
    virtual void send(std::vector<unsigned char> data, std::vector<unsigned char> pre_encodec_data);

    virtual bool waitReceived(std::chrono::steady_clock::duration timeout = std::chrono::seconds(1), int bytes = 1, bool isPolling = false);

    signals:
    void decoded_received(const QByteArray &);
    void message(const QByteArray &);

    void received(const QByteArray &);

    void sent(const QByteArray &);
    void decoded_sent(const QByteArray &);
};

enum class RPCError { success, timeout_happened };

struct RPCFunctionCallResult {
    std::unique_ptr<RPCRuntimeDecodedFunctionCall> decoded_function_call_reply = nullptr;
    uint trials_needed = 0;
    std::chrono::steady_clock::duration duration_needed;
    RPCError error = RPCError::success;
};

class RPCRuntimeProtocol : public QObject {
    Q_OBJECT
    public:
    RPCRuntimeProtocol(RPCIODevice &device, std::chrono::steady_clock::duration timeout);
    ~RPCRuntimeProtocol();

    RPCFunctionCallResult call_and_wait(const RPCRuntimeEncodedFunctionCall &call);
    RPCFunctionCallResult call_and_wait(const RPCRuntimeEncodedFunctionCall &call, std::chrono::steady_clock::duration timeout);
    void clear();
    RPCRuntimeEncodedFunctionCall encode_function(const std::string &name) const;
    RPCRuntimeEncodedFunctionCall encode_function(const int request_id) const;
    bool function_exists_for_encoding(const std::string &name) const;
    const channel_codec_instance_t *debug_get_channel_codec_instance() const;
    RPCFunctionCallResult call_get_hash_function(std::chrono::steady_clock::duration timeout);
    RPCFunctionCallResult call_get_hash_function(int retries);
    RPCFunctionCallResult call_get_hash_function();
    bool load_xml_file(QString search_dir);
    unsigned int retries_per_transmission{2};
    const std::string &get_xml_file_path() const;

    RPCRunTimeProtocolDescription description;
    signals:
    void console_message(RPCConsoleLevel level, QString message);

    private:
    RPCRuntimeDecoder decoder;
    RPCRuntimeEncoder encoder;
    Channel_codec_wrapper channel_codec;
    QMetaObject::Connection connection;
    std::unique_ptr<RPCRuntimeDecodedFunctionCall> descriptor_answer;
    RPCIODevice *device = nullptr;

    std::chrono::steady_clock::duration device_timeout;
    std::string xml_file_path;
};

#endif // RPCRUNTIMEPROTCOL_H
