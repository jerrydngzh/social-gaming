#include "include/configurationState.h"

ConfigurationState::ConfigurationState() {
    settings = std::vector<Setting*>();
}

ConfigurationState::~ConfigurationState() {
    for (auto setting : settings) {
        delete setting;//Todo: make unique so this is not needed
    }
}

Setting* ConfigurationState::getSetting(std::string name) const  {
    auto it = std::find_if(settings.begin(), settings.end(), [name](Setting* setting) {return setting->getName() == name;});
    if (it != settings.end()) {
        return *it;
    }
    return nullptr;
}

std::vector<Setting*> ConfigurationState::getSettings() const {
    return settings;
}

void ConfigurationState::addSetting(Setting* setting) {
    settings.push_back(setting);
}
