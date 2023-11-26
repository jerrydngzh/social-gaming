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
    this->configurationLibrary = std::make_unique<Configuration>(configurationData);
    this->constantsLibrary = std::make_unique<Constants>(constantsData);
    this->perAudienceLibrary = std::make_unique<PerAudience>(perAudienceData);
    this->perPlayerLibrary = std::make_unique<PerPlayer>(perPlayerData);
    this->variablesLibrary = std::make_unique<Variables>(variablesData);
}// StaticGameData()


StaticGameData::~StaticGameData() {}


std::string StaticGameData::getGameName() const {
    return configurationLibrary->getGameName();
}// getName()


void StaticGameData::printStaticData(std::string libraryType) const {
    if(libraryType == "configuration") {
        configurationLibrary->print();
    } else if (libraryType == "constants") {
        constantsLibrary->print();
    } else if (libraryType == "perAudience") {
        perAudienceLibrary->print();
    } else if (libraryType == "perPlayer") {
        perPlayerLibrary->print();
    } else if (libraryType == "variables") {
        variablesLibrary->print();
    } else {
        std::cout << "[ERROR] '" << libraryType << "' not found" << std::endl;
    }
}// printStaticData()
