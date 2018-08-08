//
// Created by genshen on 6/30/18.
//

#include "strategy_container.h"

std::map<std::string, StrategyAdapter *> StrategyContainer::container; // define here.

void StrategyContainer::registerStrategy(const std::string &key, StrategyAdapter *strategy) {
    // type auto is: std::map<std::string, StrategyAdapter *>::iterator
    auto it = container.find(key);
    if (it == container.end()) {
        container.insert(std::pair<std::string, StrategyAdapter *>(key, strategy));
    } else {
        // todo handle the error: already exist.
        // just overwrite it.
        container[key] = strategy;
    }
}

StrategyAdapter *StrategyContainer::findStrategyByKey(const std::string &key) {
    auto it = container.find(key);
    if (it == container.end()) {
        return nullptr;
    } else {
        return (*it).second;
    }
}

unsigned long StrategyContainer::strategies() {
    return container.size();
}

void StrategyContainer::destroyStrategy(const std::string &key) {
    auto itr = container.find(key);
    if (itr != container.end()) {
        delete (*itr).second;
        container.erase(itr);
    }
}

void StrategyContainer::destroyAllStrategies() {
    std::map<std::string, StrategyAdapter *>::iterator itr;
    for (itr = container.begin(); itr != container.end();) {
        delete itr->second;
        itr->second = nullptr;
        container.erase(itr++);
    }
}
