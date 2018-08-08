//
// Created by genshen on 6/30/18.
//

#ifndef PNOHS_STRATEGY_CONTAINER_H
#define PNOHS_STRATEGY_CONTAINER_H

#include <string>
#include <map>
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
      * Note: make sure the pointer variable strategy is create by "new" keyword,
      *       or "signal 11: SIGSEGV" error will be thrown when deleting this strategy(deleting an object not create by 'new').
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
     * returns the count of strategy.
     * @return the strategy count.
     */
    static unsigned long strategies();

    /**
     * delete one strategy by key.
     * @param key strategy key
     */
    static void destroyStrategy(const std::string &key);

    /**
     * delete all strategy entity.
     */
    static void destroyAllStrategies();

private:
    // declare a map for storage all pickup strategy.
    static std::map<std::string, StrategyAdapter *> container;

};


#endif //PNOHS_STRATEGY_CONTAINER_H
