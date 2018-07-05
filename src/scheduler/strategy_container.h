//
// Created by genshen on 6/30/18.
//

#ifndef PNOHS_STRATEGY_CONTAINER_H
#define PNOHS_STRATEGY_CONTAINER_H

#include <string>
#include "strategy_adapter.h"

/**
 * In this class, all strategies is in here.
 * by calling registerPickupStrategy.
 * // todo add test.
 */
class StrategyContainer {
public:
    /**
      * add an pickup strategy and initialize this strategy.
      * @param key the key to uniquely identifies the pickup strategy.
      * @param strategy the pointer to the strategy entity identified by strategyKey.
      */
    static void registerStrategy(const std::string &key, StrategyAdapter *strategy);

    /**
     * find a strategy specified by the {@param key}, if the strategy does not exists, null pointer will be returned.
     * @param key the key to uniquely identifies the pickup strategy.
     * @return the pointer to strategy specified by {@param key}.
     */
    static StrategyAdapter *findStrategyByKey(const std::string &key);

    /**
     * delete one strategy by key.
     * @param key strategy key
     */
    static void DestroyStrategy(const std::string &key);

    /**
     * delete all strategy entity.
     */
    static void DestroyAllStrategies();

private:
    // declare a map for storage all pickup strategy.
    static std::map<std::string, StrategyAdapter *> container;

};


#endif //PNOHS_STRATEGY_CONTAINER_H
