#pragma once

namespace prompts {

    class Message {
    public:
        Message(int number);
        int getNumber();
    
    private:
        int number;
    };
}

