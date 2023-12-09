#include "interpreter.h"

#include <cassert>

extern "C" {
TSLanguage* tree_sitter_socialgaming();
}

DtoFromGame requestInputChoice(int clientID, std::string prompt, std::vector<std::string> choices, int timeout);
DtoFromGame requestInputText(int clientID, std::string prompt, int timeout);
DtoFromGame requestInputRange(int clientID, std::string prompt, int min, int max, int timeout);
DtoFromGame requestInputVote(int clientID, std::string prompt, std::vector<std::string> choices, int timeout);
DtoFromGame outputMessage(int clientID, std::string message, int timeout);
DtoFromGame outputScores(std::map<int, int> scores);
DtoFromGame nullDto();
DtoFromGame endGameDto();

std::string getValue(ts::Node node);

Value* parseExpression(ts::Node node);
Value* parseQualifiedIdentifier(ts::Node node);

void printNode(std::string message, ts::Node node);

const ts::Language Interpreter::language = tree_sitter_socialgaming();

// Game state is manipulated throught the interpreter proccess
GameState* gs;
// The request variable is set once the interpreter needs to request user input
DtoFromGame request = nullDto();

DtoFromGame Interpreter::run(GameState* gameStatePointer) {
    gs = gameStatePointer;
    request = nullDto();

    // Loop through rules until we have a request for user input
    while (request.command == "null") {
        // First update the current rule we are at
        if (gs->rulesState.currentNode.getID() == gs->rulesState.nextNode.getID()) {
            // Default recursion
            ts::Node n = gs->rulesState.currentNode;
            // std::cout << "#1#" << gs->rulesState.currentNode.getID() << std::endl;
            if (n.getNumNamedChildren() > 0) {
                // std::cout << "#2#" << gs->rulesState.currentNode.getID() << std::endl;
                gs->rulesState.currentNode = n.getChild(0);
                // std::cout << "#2.5#" << gs->rulesState.currentNode.getID() << std::endl;
            } else if (!n.getNextSibling().isNull()) {
                // std::cout << "#3#" << gs->rulesState.currentNode.getID() << std::endl;
                gs->rulesState.currentNode = n.getNextSibling();
            } else {
                // std::cout << "#4#" << std::endl;
                n = n.getParent();
                while (n.getNextSibling().isNull()) {
                    // If we reach the root while looking for next rule, no more rules left to interpret, end game
                    if (n.getID() == gs->rulesState.tree->getRootNode().getID()) {
                        return endGameDto();
                    }
                    n = n.getParent();
                }
                gs->rulesState.currentNode = n.getNextSibling();
            }
            gs->rulesState.nextNode = gs->rulesState.currentNode;
        } else {
            gs->rulesState.currentNode = gs->rulesState.nextNode;
        }

        // Execute the next rule
        ts::Node n = gs->rulesState.currentNode;
        // std::cout << "#6#" << gs->rulesState.currentNode.getID() << std::endl;

        // Find and execute assoiciated action with the symbol of this node.
        const ts::Symbol type = n.getSymbol();
        auto actionIt = Interpreter::actions.find(type);

        if (actionIt != Interpreter::actions.end()) {
            Action* action = actionIt->second;
            action->execute(n);
        } else {
            // Handle other symbols as needed
            std::cout << "Unimplemented node type: " << n.getType() << " (" << n.getSymbol() << ")" << std::endl;
        }
    }
    return request;
}

ts::Symbol Interpreter::toSymbol(const std::string_view& symbolName) {
    // std::cout << "symbolName: " << symbolName << " symbolEnum: " << language.getSymbolForName(symbolName, false) << std::endl;
    return language.getSymbolForName(symbolName, true);
}

class RecurseAction : public Interpreter::Action {
   public:
    void execute(const ts::Node& node) override {
        for (int i = 0; i < node.getNumChildren(); i++) {
            ts::Node child = node.getChild(i);

            const ts::Symbol type = child.getSymbol();

            auto actionIt = Interpreter::actions.find(type);

            if (actionIt != Interpreter::actions.end()) {
                Action* action = actionIt->second;
                action->execute(child);
            } else {
                // Handle other symbols as needed
                std::cout << "Unimplemented node type: " << child.getType() << " (" << child.getSymbol() << ")" << std::endl;
            }
        }
    }
};

class RuleAction : public Interpreter::Action {
   public:
    void execute(const ts::Node& node) override {
        std::cout << "rule...\n";  // node.getSExpr().get();
    }
};

class NoAction : public Interpreter::Action {
   public:
    void execute(const ts::Node& node) override {
        // std::cout << node.getSExpr().get();
        return;
    }
};

class ForAction : public Interpreter::Action {
   public:
    void execute(const ts::Node& node) override {
        // std::cout << node.getSExpr().get();
        //  First initialize identifier
        printNode("FOR", node.getChild(0));
        printNode("IDENTIFIER", node.getChild(1));
        printNode("IN", node.getChild(2));
        printNode("LIST", node.getChild(3));
        printNode("BODY", node.getChild(4));
        return;
    }
};

class DiscardAction : public Interpreter::Action {
   public:
    void execute(const ts::Node& node) override {
        printNode("DISCARD", node.getChild(0));
        printNode("EXPRESSION", node.getChild(1));
        printNode("LIST", node.getChild(3));
        printNode("TERMINATOR", node.getChild(4));

        std::string targetListName = getValue(node.getChild(3));

        assert(gs->values.at(targetListName)->kind == Value::Kind::LIST);

        MapValue* targetList = (MapValue*)(gs->values.at(targetListName));

        Value* expression = parseExpression(node.getChild(1));
        assert(expression->kind == Value::Kind::INTEGER);

        int numToDiscard = ((IntegerValue*)expression)->value;
        delete expression;  // TODO: Smart Pointers

        // erase first numToDiscard elements of targetList (discard n elements)
        auto it = targetList->value.begin();
        while (numToDiscard-- > 0 && it != targetList->value.end()) {
            it = targetList->value.erase(it);
        }

        return;
    }
};

class AssignmentAction : public Interpreter::Action {
   public:
    void execute(const ts::Node& node) override {
        printNode("ASSIGNMENT", node);
        printNode("TARGET", node.getChild(0));
        printNode("ASSIGNMENT OPERATOR", node.getChild(1));
        printNode("EXPRESSION", node.getChild(2));
        printNode("TERMINATOR", node.getChild(3));

        Value* target = parseQualifiedIdentifier(node.getChild(0));

        Value* newValue = parseExpression(node.getChild(2));
        delete newValue;  // TODO: smart pointers

        // target = newValue; TODO: need to implement =operator to assign new value

        return;
    }
};

class MessageAction : public Interpreter::Action {
   public:
    void execute(const ts::Node& node) override {
        printNode("MESSAGE", node);
        printNode("MESSAGE", node.getChild(0));
        printNode("TARGET", node.getChild(1));
        printNode("STRING", node.getChild(2));
        printNode("TERMINATOR", node.getChild(3));

        Value* message = parseExpression(node.getChild(0));
        assert(message->kind == Value::Kind::STRING || true);  // TODO parseExpression string
        std::string outMessage = "";

        for (auto p : gs->players) {
            gs->rulesState.isParallel = true;
            request = outputMessage(p.second->id, outMessage, 0);
        }
        return;
    }
};

class InputChoiceAction : public Interpreter::Action {
   public:
    void execute(const ts::Node& node) override {
        printNode("INPUT CHOICE", node);
        printNode("INPUT CHOICE", node.getChild(0));
        printNode("TO", node.getChild(1));
        printNode("TARGET", node.getChild(2));
        printNode("PROMPT", node.getChild(3));
        printNode("STRING", node.getChild(4));
        printNode("CHOICES", node.getChild(5));
        printNode("OPTION LIST", node.getChild(6));
        printNode("TARGET", node.getChild(7));
        printNode("IDENTIFIER", node.getChild(8));
        printNode("TIMEOUT", node.getChild(9));
        printNode("EXPRESSION", node.getChild(10));
        return;
    }
};

// TODO
class ExtendAction : public Interpreter::Action {
   public:
    void execute(const ts::Node& node) override {
        return;
    }
};

// TODO
class MatchAction : public Interpreter::Action {
   public:
    void execute(const ts::Node& node) override {
        return;
    }
};

// TODO
class ScoresAction : public Interpreter::Action {
   public:
    void execute(const ts::Node& node) override {
        return;
    }
};

// Create a mapping of symbols to actions objects
const std::map<ts::Symbol, Interpreter::Action*> Interpreter::actions = {
    {ts::Symbol(0), new NoAction()},  // No action by default
    {toSymbol("body"), new RecurseAction()},
    //{ts::Symbol(26), new NoAction()}, //Inner rules node (26)
    {ts::Symbol(98), new RecurseAction()},  // Outermost rules node (98)
    {toSymbol("rule"), new RecurseAction()},
    {toSymbol("for"), new ForAction()},
    {toSymbol("discard"), new DiscardAction()},
    {toSymbol("assignment"), new AssignmentAction()},
    {toSymbol("message"), new MessageAction()},
    {toSymbol("input_choice"), new InputChoiceAction()},
    // Add more symbols and corresponding action objects
};
DtoFromGame requestInputChoice(Value* target, int clientID, std::string prompt, std::vector<std::string> choices, int timeout) {
    gs->rulesState.requests.insert(std::make_pair(clientID, target));
    return DtoFromGame{gs->rulesState.isParallel, clientID, "INPUT", false, {0, 0}, Setting("null", Setting::Kind::INTEGER), choices};
}
DtoFromGame outputMessage(int clientID, std::string message, int timeout) {
    return DtoFromGame{gs->rulesState.isParallel, clientID, "INPUT", false, {0, 0}, Setting("null", Setting::Kind::INTEGER), {}};
}
DtoFromGame nullDto() {
    return DtoFromGame{false, 0, "null", false, {0, 0}, Setting("null", Setting::Kind::INTEGER), {}};
}
DtoFromGame endGameDto() {
    return DtoFromGame{false, 0, "GAMEEND", false, {0, 0}, Setting("null", Setting::Kind::INTEGER), {}};
}

std::string getValue(ts::Node node) {
    return std::string(node.getSourceRange(gs->rulesState.rawGameFile));
}

Value* parseExpression(ts::Node node) {
    // TODO: evaluate expressions
    // TODO: change to smart pointer
    return new IntegerValue(0);
}

Value* parseQualifiedIdentifier(ts::Node node) {
    // TODO: find the value* that this qualified identfier is refering to
    return nullptr;
}

void printNode(std::string message, ts::Node node) {
    std::cout << message << ": " << node.getType() << " Value: " << getValue(node) << std::endl;
}