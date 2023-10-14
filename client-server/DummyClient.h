#pragma once

#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>


class DummyClient {
public:
    DummyClient();
    bool create_or_join_game();
    void process();
    void read_message(std::string message);
    std::string write_message();
    std::string get_string_prefix(const std::string& message);
    void run_game_code();
    void run_game_instruction();

private:
    std::string message_for_server;
    std::string message_from_server;
};