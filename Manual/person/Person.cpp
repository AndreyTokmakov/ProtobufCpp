/**============================================================================
Name        : Person.cpp
Created on  : 07.07.2025
Author      : Andrei Tokmakov
Version     : 1.0
Copyright   : Your copyright notice
Description : Person.cpp
============================================================================**/

#include "Person.h"
#include <expected>

#include "person.pb.h"
#include "date.pb.h"

namespace PersonTests
{
    using demo::Person;

    Person makePerson(const std::string& name,
                      int32_t id,
                      const std::string& email,
                      const std::vector<std::string>& phones = {})
    {
        Person person;
        person.set_name(name);
        person.set_id(id);
        person.set_email(email);

        date_time::Date* birthday = person.mutable_birthday();
        birthday->set_day(21);
        birthday->set_month(9);
        birthday->set_year(1990);

        addr::Address* address = person.mutable_address();
        address->set_city("Abu Dhabi");
        address->set_street("Al Rahah");

        for (const std::string& phone: phones) {
            person.add_phones(phone);
        }

        return person;
    }

    std::expected<std::string, std::string> Serialize(const Person& person)
    {
        std::string data;
        if (!person.SerializeToString(&data)) {
            return std::unexpected("Failed to serialize.");
        }

        return data;
    }

    std::expected<Person, std::string> DeSerialize(const std::string& data)
    {
        Person person;
        if (!person.ParseFromString(data)) {
            return std::unexpected("Failed to parse");
        }

        return person;
    }

    void print(const Person& person)
    {
        std::cout << "Person: \n{\n"
                  << "\t name: '"  << person.name() << "'\n"
                  << "\t id: "    << person.id() << "\n"
                  << "\t email: '" << person.email() << "'\n";

        std::cout << "\t birthday: " << person.birthday().day() << "/" << person.birthday().month()
                  << "/" << person.birthday().year() << "\n";
        std::cout << "\t address: " << person.address().city() << ", " << person.address().street() << "\n";

        std::cout <<  "\t phones: [ ";
        for (const std::string_view phone: person.phones()) {
            std::cout << "'" << phone << "' ";
        }

        std::cout << "]\n}\n";
    }

    void test()
    {
        const Person person { makePerson(
                "Alice", 123, "alice@example.com", {"+123456789", "+987654321"}
        )};

        const std::expected<std::string, std::string> data = Serialize(person);
        if (!data) {
            std::cerr << data.error() << std::endl;
        }

        const std::string& buff = data.value();
        std::cout << "Serialized data size = " << buff.size() << std::endl;

        const std::expected<Person, std::string> outPerson = DeSerialize(buff);
        if (!outPerson) {
            std::cerr << data.error() << std::endl;
        }

        print(outPerson.value());

        google::protobuf::ShutdownProtobufLibrary();
    }
}


void Person::TestAll()
{
    PersonTests::test();

}