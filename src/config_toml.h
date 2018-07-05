//
// Created by genshen on 3/23/18.
//

#ifndef PNOHS_CONFIG_TOML_H
#define PNOHS_CONFIG_TOML_H

#include "config/config.h"
#include "config_values.h"

class ConfigToml : public kiwi::config {

public:

    ConfigToml();

    // A simple single mode.
    // Make a instance without resolving config file.
    // If the config instance exists, just return the pointer of the instance.
    static ConfigToml *getInstance();

    // Make instance and resolve config file.
    // If instance exists, return the pointer of the instance.
    static ConfigToml *newInstance(const std::string &configureFilePath);

    inline ConfigValues *getConfigValue() {
        return &confV;
    }

private:
    static ConfigToml *pConfigInstance; // pointer of instance of this class.

    // all data in toml configure file is parsed to here.
    ConfigValues confV;

    // override this function to resolve parsed config file.
    void resolveConfig(std::shared_ptr<cpptoml::table> table) override;

    // [master processor] pack config data for syncing to other processors.
    void putConfigData(kiwi::Bundle &bundle) override;

    // [other processors] unpack config data
    void getConfigData(kiwi::Bundle &bundle) override;
};

#endif //PNOHS_CONFIG_TOML_H
