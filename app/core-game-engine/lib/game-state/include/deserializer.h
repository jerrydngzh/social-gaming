// Purpose of the deserilizer is to read the game data from mikes data structure and initialize GameState with it
// Will basically have factory methods that return a ready GameState object

#include "gameState.h"
#include "staticGameData.h"
#include <variant>
#include <cassert>


class GameStateFactory {
    // THIS CURRENTLY STUBS ROCK PAPER SCISSORS!
    private:
        struct ParseData {
            std::string type;
            Value* value_v;
            std::pair<std::string, Value*> pair_v;
        };

        template<typename T>
        static ParseData
        visit(std::unique_ptr<T>& library, int index) {
            // get the type
            std::string type = library->getMapping(index).type;
            int numChildren = library->getMapping(index).children.size();
            library->getMapping(index).print();

            if(type == "root") {
                ParseData parse = visit(library, library->getMapping(index).children.at(0));
                std::cout << std::endl << "[DEBUG] Value* (root) = " << parse.value_v << std::endl;

                return parse;
            } else if(type == "number") {
                IntegerValue* value_p = new IntegerValue(library->getMapping(index).key, stoi(library->getMapping(index).value));

                std::cout << std::endl << "[DEBUG] IntegerValue* = " << value_p << std::endl;

                return {"number", value_p, {}};
            } else if (type == "expression") {
                if(numChildren == 1) {
                    ParseData parse = visit(library, library->getMapping(index).children.at(0));
                    std::cout << std::endl << "[DEBUG] Value* (expression) = " << parse.value_v << std::endl;

                    return parse;
                } else {
                    std::pair<std::string, Value*> key = visit(library, library->getMapping(index).children.at(0)).pair_v;
                    std::pair<std::string, Value*> value = visit(library, library->getMapping(index).children.at(1)).pair_v;

                    std::cout << std::endl << "[DEBUG] key = {" << key.first << ", " << key.second << "}" << std::endl;
                    std::cout << "[DEBUG] value = {" << value.first << ", " << value.second << "}" << std::endl;

                    MapValue* value_p = new MapValue({key, value});
                    std::cout << "[DEBUG] MapValue* = " << value_p << std::endl;

                    return {"map", value_p, {}};
                }
            } else if (type == "list_literal") {
                std::vector<Value*> values;
                for (const int& child : library->getMapping(index).children) {
                    ParseData parse = visit(library, child);
                    std::cout << std::endl << "[DEBUG] Value* (List) = " << parse.value_v << std::endl;
                    values.emplace_back(parse.value_v);
                }
                
                ListValue* value_p = new ListValue(values);
                std::cout << "[DEBUG] ListValue* = " << value_p << std::endl;
                return {"list", value_p, {}};
            } 
            else if (type == "quoted_string") {
                StringValue* string_p = new StringValue(library->getMapping(index).value);
                std::cout << std::endl << "[DEBUG] StringValue* = " << string_p << std::endl;
                std::pair pair_v = std::make_pair<std::string, Value*>(library->getMapping(index).key, string_p);

                return {"pair", nullptr, pair_v};           
            }
        }

    public:
        static GameState createInitialGameState(std::unique_ptr<StaticGameData>& gameData) {
            GameState gameState;

            // Constants
            // StringValue* rockName = new StringValue("Rock");
            // StringValue* paperName = new StringValue("Paper");
            // StringValue* scissorsName = new StringValue("Scissors");

            // MapValue* rock = new MapValue({{"name", rockName}, {"beats", scissorsName}});
            // MapValue* paper = new MapValue({{"name", paperName}, {"beats", rockName}});
            // MapValue* scissors = new MapValue({{"name", scissorsName}, {"beats", paperName}});

            // ListValue* weapons = new ListValue("weapons", {rock, paper, scissors});

            // gameState.addConstant(weapons);
            gameState.addConstant(visit(gameData->constants, 0).value_v);

            // Variables
            gameState.addVariable(visit(gameData->variables, 0).value_v);

            // Per Player
            gameState.addPerPlayer(visit(gameData->perPlayer, 0).value_v);

            return gameState;
        }
};