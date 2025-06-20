// Exceptions.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdexcept>
#include <exception>
#include <string>

// Custom exception class derived from std::exception
class CustomException : public std::exception {
public:
    CustomException(const std::string& message) : msg(message) {}
    const char* what() const noexcept override {
        return msg.c_str();
    }
private:
    std::string msg;
};

bool do_even_more_custom_application_logic()
{
    // Throwing a standard exception (logic_error)
    throw std::logic_error("A standard exception was thrown in do_even_more_custom_application_logic");

    std::cout << "Running Even More Custom Application Logic." << std::endl;

    return true;
}

void do_custom_application_logic()
{
    std::cout << "Running Custom Application Logic." << std::endl;

    try {
        // Wrapping the call with an exception handler that catches std::exception
        if(do_even_more_custom_application_logic())
        {
            std::cout << "Even More Custom Application Logic Succeeded." << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Caught standard exception in do_custom_application_logic: " << e.what() << std::endl;
    }

    // Throw a custom exception derived from std::exception
    throw CustomException("Custom exception thrown in do_custom_application_logic");

    std::cout << "Leaving Custom Application Logic." << std::endl;
}

float divide(float num, float den)
{
    // Throwing exception if dividing by zero
    if (den == 0.0f) {
        throw std::runtime_error("Attempted division by zero");
    }
    return (num / den);
}

void do_division() noexcept
{
    float numerator = 10.0f;
    float denominator = 0.0f;

    try {
        auto result = divide(numerator, denominator);
        std::cout << "divide(" << numerator << ", " << denominator << ") = " << result << std::endl;
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Caught runtime error in do_division: " << e.what() << std::endl;
    }
}

int main()
{
    std::cout << "Exceptions Tests!" << std::endl;

    try {
        do_division();
        do_custom_application_logic();
    }
    catch (const CustomException& e) {
        std::cerr << "Caught custom exception in main: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Caught standard exception in main: " << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << "Caught unknown exception in main." << std::endl;
    }
}
