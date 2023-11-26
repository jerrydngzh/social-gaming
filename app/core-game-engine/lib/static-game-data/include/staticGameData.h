#include "configuration.h"
#include "constants.h"
#include "perAudience.h"
#include "perPlayer.h"
#include "variables.h"
#include "treeParser.h"
#include "mapping.h"


// A container initializing all the static game libraries
// (Configuration, Constants, PerAudience, PerPlayer, Variables)
class StaticGameData {
    public:
        StaticGameData(const std::string &fileContents);
        ~StaticGameData();

        std::unique_ptr<Configuration> configuration;
        std::unique_ptr<Constants> constants;
        std::unique_ptr<PerAudience> perAudience;
        std::unique_ptr<PerPlayer> perPlayer;
        std::unique_ptr<Variables> variables;

        std::string getGameName() const;
}; // StaticGameData