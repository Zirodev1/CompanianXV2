// src/ai/chat.cpp
#include <string>
#include <iostream>
#include "Z:/dev/ai/CompanionX/include/ai/chat.h"
std::string processInput(const std::string& input) {
    if (input == "hello") return "Hi there!";
    if (input == "move") return "Moving now!";
    return "I don’t get it yet.";
}