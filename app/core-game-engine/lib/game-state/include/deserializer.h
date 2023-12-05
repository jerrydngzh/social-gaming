// Purpose of the deserilizer is to read the game data from mikes data structure and initialize GameState with it
// Will basically have factory methods that return a ready GameState object

#include "gameState.h"
#include "staticGameData.h"


class GameStateFactory {
    // THIS CURRENTLY STUBS ROCK PAPER SCISSORS!
    private:
        // TODO: extract quoted_string, list literals for now
        template<typename T>
        static Value* visit(std::unique_ptr<T>& library, int index) {
            // get the type
            std::string type = library->getMapping(index).type;
            int numChildren = library->getMapping(index).children.size();
            library->getMapping(index).print();

            if(type == "number") {
                IntegerValue* integer_p = new IntegerValue(library->getMapping(index).key, stoi(library->getMapping(index).value));
                return integer_p;
            } else if (type == "expression" || type == "root") {
                if(numChildren == 1) {
                    return visit(library, library->getMapping(index).children.at(0));
                } else {
                    Value* key = visit(library, library->getMapping(index).children.at(0));
                    Value* value = visit(library, library->getMapping(index).children.at(1));

                    MapValue* map_p = new MapValue({key, value});
                    return map_p;
                }
            } else if (type == "list_literal") {
                std::vector<Value*> values;
                for (const int& child : library->getMapping(index).children) {
                    values.push_back(visit(library, child));
                }
                
                ListValue* list_p = new ListValue(values);
                return list_p;
            } else if (type == "quoted_string") {
                StringValue* string_p = new StringValue(library->getMapping(index).value);
                MapValue* map_p = new MapValue(library->getMapping(index).key, string_p);
                return map_p;           
            }
        }

    public:
        static GameState createInitialGameState(std::unique_ptr<StaticGameData>& gameData) {
            GameState gameState;

            gameData->constants->print();
            std::cout << "*********************" << std::endl;
            visit(gameData->constants, 0);
            // visit(gameData->variables, 0);
            // visit(gameData->perPlayer, 0);

            // Constants
            StringValue* rockName = new StringValue("Rock");
            StringValue* paperName = new StringValue("Paper");
            StringValue* scissorsName = new StringValue("Scissors");

            MapValue* rock = new MapValue({{"name", rockName}, {"beats", scissorsName}});
            MapValue* paper = new MapValue({{"name", paperName}, {"beats", rockName}});
            MapValue* scissors = new MapValue({{"name", scissorsName}, {"beats", paperName}});

            ListValue* weapons = new ListValue("weapons", {rock, paper, scissors});

            gameState.addConstant(weapons);

            // Variables
            gameState.addVariable(visit(gameData->variables, 0));

            // Per Player
            gameState.addPerPlayer(visit(gameData->perPlayer, 0));

            return gameState;
        }
};