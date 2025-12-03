/**============================================================================
Name        : main.cpp
Created on  : 03.11.2025
Author      : Andrei Tokmakov
Version     : 1.0
Copyright   : Your copyright notice
Description : C++ UtiliProtoBuffties
============================================================================**/

#include <iostream>
#include <string_view>
#include <vector>
#include <filesystem>
#include <print>

#include "message.pb.h"
#include "FileUtilities.h"


namespace
{
    constexpr std::filesystem::path getTestDataDir() noexcept
    {
        return std::filesystem::current_path() / "../../resources/";
    }
}



namespace server
{
    using namespace demo_service;

    Message makeMessage(const std::string& text,
                        [[maybe_unused]] int32_t error = 0)
    {
        Message message;
        message.set_payload(text);
        // message.set_errorcode(error);
        return message;
    }

    std::string makeMessageAsStr(const std::string& text,
                                 const int32_t error = 0)
    {
        const Message msg = makeMessage(text, error);
        std::string data;
        msg.SerializeToString(&data);

        return data;
    }

    void storeMessageToFile(const std::string& text,
                            const int32_t error = 0)
    {
        const Message msg = makeMessage(text, error);
        std::string data;
        msg.SerializeToString(&data);

        const std::filesystem::path dataFile = getTestDataDir() / "data.bin";
        const int32_t bytes = FileUtilities::WriteToFile(dataFile, data);

        std::println("{} bytes written to file {}", bytes, dataFile.string());
    }
}

namespace client
{
    using namespace demo_service;

    void processMessage(const server::Message& message)
    {
        std::cout << message.payload() << std::endl;
        // std::cout << message.errorcode() << std::endl;
    }

    void processMessageAsStr(const std::string& messageData)
    {
        Message msg;
        msg.ParseFromString(messageData);
        std::cout << msg.payload() << std::endl;
        // std::cout << msg.errorcode() << std::endl;
    }

    void processMessageFromFile()
    {
        const std::filesystem::path dataFile = getTestDataDir() / "data.bin";
        const std::string messageData = FileUtilities::ReadFile(dataFile);

        Message msg;
        msg.ParseFromString(messageData);
        std::cout << msg.payload() << std::endl;
        // std::cout << msg.errorcode() << std::endl;
    }
}

int main([[maybe_unused]] int argc,
         [[maybe_unused]] char** argv)
{
    const std::vector<std::string_view> args(argv + 1, argv + argc);


    /*
    {
        const auto message = server::makeMessage("Hello World!", 11);
        client::processMessage(message);
    }
    {
        const std::string message = server::makeMessageAsStr("Hello World!", 22);
        client::processMessageAsStr(message);
    }*/

    // server::storeMessageToFile("Hello World -3", 333);
    client::processMessageFromFile();


    return EXIT_SUCCESS;
}

// sudo apt install protobuf-compiler libprotobuf-dev
// /home/andtokm/DiskS/ProjectsUbuntu/third_party/protobuf/build/protoc --cpp_out=. addressbook.proto