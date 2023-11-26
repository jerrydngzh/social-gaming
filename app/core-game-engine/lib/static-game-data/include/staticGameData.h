#include "configuration.h"
#include "constants.h"
#include "perAudience.h"
#include "perPlayer.h"
#include "variables.h"
#include "treeParser.h"
#include "mapping.h"

class StaticGameData {
    private:
        std::unique_ptr<Configuration> configurationLibrary;
        std::unique_ptr<Constants> constantsLibrary;
        std::unique_ptr<PerAudience> perAudienceLibrary;
        std::unique_ptr<PerPlayer> perPlayerLibrary;
        std::unique_ptr<Variables> variablesLibrary;

    public:
        StaticGameData(const std::string &fileContents);
        ~StaticGameData();

        std::string getGameName() const; 
        void printStaticData(std::string libraryType) const;
}; // StaticGameData