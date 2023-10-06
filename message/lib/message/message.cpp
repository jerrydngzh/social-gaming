#include "message.h"

using prompts::Message;


Message::Message(int number)
    : number{number}
    {}


int Message::getNumber() {
    return number;
}
