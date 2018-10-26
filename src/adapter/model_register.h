//
// Created by genshen $EMAIL on 10/16/18.
//

#ifndef PNOHS_MODEL_REGISTER_H
#define PNOHS_MODEL_REGISTER_H

#include <map>
#include "runoff_adapter.h"
#include "routing_adapter.h"

/**
 * You can register user developed models by a key.
 * Later, you can create a model instance by function @fn makeModeInstance.
 * // todo add tests.
 *
 * Usage (RunoffInterface as example):
 *  1. Create a class (named as A ) inheriting from both RunoffInterface and RunoffAdapter.
 *  2. Add implementation for some abstract interface and RunoffInterface::newInstance interface.
 *  3. register class: ModelRegister::registerRunoffModel("example_key", A::newInstance);
 *  4. create model instance: auto pModel = ModelRegister::newInstanceRunoff("example_key");
 *
 */
namespace ModelRegister {

    typedef std::string _type_model_key;

    class RunoffInterface {
    public:
        /**
         * create a new runoff model instance by model key.
         * @param key model key.
         * @return pointer to new runoff model instance.
         */
        static RunoffAdapter *newInstance(const _type_model_key key);
    };

    class RoutingInterface {
    public:
        /**
         * create a new routing model instance by model key.
         * @param key model key.
         * @return pointer to new routing model instance.
         */
        static RoutingAdapter *newInstance(const _type_model_key key);
    };

    typedef RunoffAdapter *(*RunoffInstanceInterface)(const _type_model_key key);

    typedef RoutingAdapter *(*RoutingInstanceInterface)(const _type_model_key key);

    /**
     * If you register a runoff model, then the runoff model instantiation interface will be saved in this map.
     */
    std::map<_type_model_key, RunoffInstanceInterface> runoffNest;

    /**
     * The same as above, but for routing models.
     */
    std::map<_type_model_key, RoutingInstanceInterface> routingNest;

    /**
     * register one or multiple runoff model.
     * Just adding model instantiation interface/callback to @var runoffNest.
     * @param key unique model key for this model.
     * @param model the model instantiation callback function.
     */
    static void registerRunoffModel(const _type_model_key key, RunoffInstanceInterface model);

    /**
     * un register a runoff model by the model key.
     * Then, the model instantiation callback function will be remove for map @var runoffNest.
     * @param key unique model key to tag the model to be unregistered.
     */
    static void unRegisterRunoffModel(const _type_model_key key);

    /**
     * remove all routing models, clean map @var routingNest.
     */
    static void unRegisterAllRunoffModels();

    /**
     * create a runoff model instance using registered @typedef RunoffInstanceInterface.
     * If the model specified by @param key is not registered, nullptr will be returned.
     * @param key unique model key.
     * @return pointer to runoff model instance or nullptr.
     */
    static RunoffAdapter *newInstanceRunoff(const _type_model_key key);

    /**
     * register one or multiple routing model.
     * Just adding model instantiation interface/callback to @var routingNest.
     * @param key unique model key to tag the model.
     * @param model the model instantiation callback function.
     */
    static void registerRoutingModel(const _type_model_key key, RoutingInstanceInterface model);

    /**
     * unregister a runoff model by the model key.
     * Then, the model instantiation callback function will be remove for map @var routingNest.
     * @param key unique model key to tag the model to be unregistered.
     */
    static void unRegisterRoutingModel(const _type_model_key key);

    /**
     * remove all routing models, clean map @var routingNest.
     */
    static void unRegisterAllRoutingModels();

    /**
     * create a runoff model instance using registered @typedef RunoffInstanceInterface.
     * If the model specified by @param key is not registered, nullptr will be returned.
     * @param key unique model key.
     * @return pointer to runoff model instance or nullptr.
     */
    static RoutingAdapter *newInstanceRouting(const _type_model_key key);

    /**
     * unregister all models, including routing and runoff models.
     */
    static void unRegisterAll();
}


#endif //PNOHS_MODEL_REGISTER_H
