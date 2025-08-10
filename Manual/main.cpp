/**============================================================================
Name        : main.cpp
Created on  : 29.02.2025
Author      : Andrei Tokmakov
Version     : 1.0
Copyright   : Your copyright notice
Description : C++ UtiliProtoBuffties
============================================================================**/

#include <iostream>
#include <string_view>
#include <vector>

#include "person/Person.h"
#include "request/Request.h"
#include "common/Common.h"



int main([[maybe_unused]] int argc,
         [[maybe_unused]] char** argv)
{
    const std::vector<std::string_view> args(argv + 1, argv + argc);

    //Person::TestAll();
    //Request::TestAll();
    Common::TestAll();

    return EXIT_SUCCESS;
}