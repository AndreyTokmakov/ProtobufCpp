/**============================================================================
Name        : Request.cpp
Created on  : 07.07.2025
Author      : Andrei Tokmakov
Version     : 1.0
Copyright   : Your copyright notice
Description : Request.cpp
============================================================================**/

#include "Request.h"

#include <expected>

#include "request.pb.h"
#include "status.pb.h"
#include "type.pb.h"

namespace Request
{
    using demo::Request;


    template<typename ProtoType>
    concept HasErrWithStringSetter = requires(ProtoType& protoObj, const std::string& str) {
        { protoObj.mutable_error()->set_message(str) } -> std::same_as<void>;
    };

    void setErrorMessage(HasErrWithStringSetter auto & request, const std::string& message)
    {
        request.mutable_error()->set_message(message);
    }

    Request makeRequest()
    {
        Request request;

        setErrorMessage(request, "Oppss");
        // request.mutable_error()->set_code(123);

        return request;
    }


    void print(const Request& request)
    {
        std::cout << "Request: \n{\n"
                  << "\t id: "    << request.id() << "\n"
                  << "\t data: '" << request.data() << "'\n";

        const enums::Type type = request.type();
        const enums::Status status = request.status();

        std::cout << "\t type: ";
        if (type == enums::Ping) {std::cout << "Ping" << "\n";}
        else if (type == enums::Notification) { std::cout << "Notification" << "\n"; }
        else if (type == enums::Event) { std::cout << "Event" << "\n"; }

        std::cout << "\t status: ";
        if (status == enums::Success) {std::cout << "Success" << "\n";}
        else if (status == enums::Failure) { std::cout << "Failure" << "\n"; }

        std::cout << "\t error: { code : " << request.error().code() << ", message : "
            << request.error().message() << "}\n";

        std::cout << "}\n";
    }

    void test()
    {
        const Request request { makeRequest() };

        print(request);

    }
}


void Request::TestAll()
{
    test();
}