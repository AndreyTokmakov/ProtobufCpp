/**============================================================================
Name        : Common.cpp
Created on  : 08.07.2025
Author      : Andrei Tokmakov
Version     : 1.0
Copyright   : Your copyright notice
Description : Common.cpp
============================================================================**/

#include <iostream>

#include "Common.h"

#include "common.pb.h"

#include <google/protobuf/util/json_util.h>

namespace Common
{
    template<typename Ty>
    concept ProtobufType = requires(Ty proto, std::string& str) {
        { google::protobuf::util::MessageToJsonString(proto, &str) } ->
            std::same_as< google::protobuf::util::Status>;
    };


    std::ostream& operator<<(std::ostream& stream, ProtobufType auto& proto)
    {
        std::string str;
        google::protobuf::util::MessageToJsonString(proto, &str);
        return stream << str;
    }

    enum class Type {
        One,
        Two
    };

    common::Request buildRequest(Type type)
    {
        common::Request request;

        if (Type::One == type)
            request.mutable_typeone();
        else
            request.mutable_typetwo();

        return request;
    }

    common::Response handleRequest(const common::Request& request)
    {
        common::Response response;

        if (request.has_typeone()) {
            response.mutable_result()->mutable_success();
        } else {
            response.mutable_result()->mutable_error()->set_message("Error!!!");
        }

        return response;
    }

    void test()
    {
        const common::Request request = buildRequest(Type::Two);
        std::cout << request << std::endl;

        const common::Response response = handleRequest(request);
        std::cout << response << std::endl;
    }
}


void Common::TestAll()
{
    test();
}