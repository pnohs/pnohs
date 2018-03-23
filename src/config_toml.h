//
// Created by genshen on 3/23/18.
//

#ifndef PNOHS_CONFIG_TOML_H
#define PNOHS_CONFIG_TOML_H

#include "config/config.h"

class configToml : public kiwi::config {

public:
    // config property here
    std::string Filename;

    configToml();

    // a simple single mode example.
    // make a instance without resolving config file.
    static configToml *newInstance();

    // make instance and resolve config file.
    static configToml *newInstance(const std::string &configureFilePath);

private:
    static configToml *pConfigInstance;

    void resolveConfig(std::shared_ptr<cpptoml::table> table) override;

    void putConfigData(kiwi::Bundle &bundle) override;

    void getConfigData(kiwi::Bundle &bundle) override;
};

#endif //PNOHS_CONFIG_TOML_H
