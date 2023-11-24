#include "include/configurationState.h"

ConfigurationState::ConfigurationState() {
    settings = std::vector<Setting*>();
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
