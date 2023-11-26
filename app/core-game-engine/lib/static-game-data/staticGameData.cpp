#include "staticGameData.h"

StaticGameData::StaticGameData(const std::string &fileContents) {
    // initialize an extractor object
    Extractor extractor(fileContents);
    
    // get a tree object from tree parser
    ts::Tree tree = parseTree(fileContents);

    // get the nodes for parsing
    ts::Node configurationNode = tree.getRootNode().getChildByFieldName("configuration");
    ts::Node constantsNode = tree.getRootNode().getChildByFieldName("constants");
    ts::Node perAudienceNode = tree.getRootNode().getChildByFieldName("per_audience");
    ts::Node perPlayerNode = tree.getRootNode().getChildByFieldName("per_player");
    ts::Node variablesNode = tree.getRootNode().getChildByFieldName("variables");

    // extract the data into custom data structure
    std::vector<Mapping> configurationData = extractor.format(configurationNode);
    std::vector<Mapping> constantsData = extractor.format(constantsNode);
    std::vector<Mapping> perAudienceData = extractor.format(perAudienceNode);
    std::vector<Mapping> perPlayerData = extractor.format(perPlayerNode);
    std::vector<Mapping> variablesData = extractor.format(variablesNode);

    // initialize libraries
    this->configuration = std::make_unique<Configuration>(configurationData);
    this->constants = std::make_unique<Constants>(constantsData);
    this->perAudience = std::make_unique<PerAudience>(perAudienceData);
    this->perPlayer = std::make_unique<PerPlayer>(perPlayerData);
    this->variables = std::make_unique<Variables>(variablesData);
}// StaticGameData()


StaticGameData::~StaticGameData() {}


std::string StaticGameData::getGameName() const {
    return configuration->getGameName();
}// getGameName()