#include "game.h"
#include "include/interpreter.h"

Game::Game(const ts::Tree& tree, std::string_view fileContents, //to remove
        std::vector<Mapping> &configurationData,
        std::vector<Mapping> &constantsData,
        std::vector<Mapping> &variablesData,
        std::vector<Mapping> &perPlayerData,
        std::vector<Mapping> &perAudienceData):
    configurationLibrary(Configuration(configurationData)),
    constantsLibrary(Constants(constantsData)),
    variablesLibrary(Variables(variablesData)),
    perPlayerLibrary(PerPlayer(perPlayerData)),
    perAudienceLibrary(PerAudience(perAudienceData)),
    rulesLibrary(Rules(tree.getRootNode().getChildByFieldName("rules"), 10)),
    tree(tree),
    runner(this, tree)
    {}

Game::Game(std::string_view filename) : 
    configurationLibrary(Configuration({})),
    constantsLibrary(Constants({})),
    variablesLibrary(Variables({})),
    perPlayerLibrary(PerPlayer({})),
    perAudienceLibrary(PerAudience({})),
    rulesLibrary(Rules(tree.getRootNode().getChildByFieldName("rules"), 10)),
    tree(parseTree(parseGAMEFromFile(std::string(filename)))), 
    runner(this, tree)
    {
    ts::Node root = tree.getRootNode();

    // initialize the extractor object
    // is there a way to not repeat the initial parsing?
    Extractor extractor(parseGAMEFromFile(std::string(filename)));

    // extract header nodes from the tree
    ts::Node configurationNode = root.getChildByFieldName("configuration");
    ts::Node constantsNode = root.getChildByFieldName("constants");
    ts::Node variablesNode = root.getChildByFieldName("variables");
    ts::Node perPlayerNode = root.getChildByFieldName("per_player");
    ts::Node perAudienceNode = root.getChildByFieldName("per_audience");

    // Use Extractor object to get a data structure for the contents of the node
    std::vector<Mapping> configurationData = extractor.format(configurationNode);
    std::vector<Mapping> constantsData = extractor.format(constantsNode);
    std::vector<Mapping> variablesData = extractor.format(variablesNode);
    std::vector<Mapping> perPlayerData = extractor.format(perPlayerNode);
    std::vector<Mapping> perAudienceData = extractor.format(perAudienceNode);

    // Create and Initialize Objects for each of the game sections
    configurationLibrary = Configuration(configurationData);
    constantsLibrary = Constants(constantsData);
    variablesLibrary = Variables(variablesData);
    perPlayerLibrary = PerPlayer(perPlayerData);
    perAudienceLibrary = PerAudience(perAudienceData);
}

Game::~Game() {}

void Game::startGame() {//to remove
    Interpreter gameRunner(this, this->tree);
    gameRunner.run(rulesLibrary.getNode());
}

Configuration* Game::getConfiguration(){
    return &this->configurationLibrary;
}
// IO::requestInputChoice(String prompt, vector<String> choices, int timeout);
// IO::requestInputText(String prompt, int timeout);
// IO::requestInputRange(String prompt, pair<int> range, int timeout);
// IO::requestInputVote(String prompt, vector<String> choices, int timeout);
// IO::outputMessage(vector<Player> players, String message, int timeout);
// IO::outputScores(vector<Scores> scores);

// Should take in an input DTO Object which has been passed down from container manager to container
DtoFromGame Game::run(DTOtoGame dto){
    // processing here currently stubbed
    DtoFromGame dtoToContainer = {true, 42, "example", 123, {1, 10}, {}};
    return dtoToContainer;
}


//getConfiguration, run
// Configuration* initialize();
// outMessage run()