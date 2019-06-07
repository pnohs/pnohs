//
// Created by genshen $EMAIL on 10/16/18.
//

#ifndef PNOHS_MODEL_REGISTER_H
#define PNOHS_MODEL_REGISTER_H

#include <map>
#include "../utils/predefine.h"
#include "runoff_adapter.h"
#include "routing_adapter.h"

/**
 * You can register user developed models by a model instance interface and a model key.
 * Note that the model key (string type) must be unique globally.
 * Later, you can create a model instance by function @fn makeModeInstance.
 * // todo add tests.
 *
 * Usage (RunoffInterface as example):
 *  1. Create a class (named as A ) inheriting from both RunoffInterface and RunoffAdapter.
 *  2. Add implementation for some abstract interface and RunoffInterface::newInstance interface.
 *  3. register class: ModelRegister::registerRunoffModel("example_key", A::newInstance);
 *  3.1 you can optionally get the model id by calling @fn getModelIdByKey(${model_key});
 *  4. create model instance: auto pModel = ModelRegister::newInstanceRunoff(${model_id});
 *
 */
class ModelRegister {
public:
    static const _type_model_id MODEL_ID_NULL;

    class RunoffInterface {
    public:
        /**
         * create a new runoff model instance.
         * @return pointer to new runoff model instance.
         */
        static RunoffAdapter *newInstance();
    };

    class RoutingInterface {
    public:
        /**
         * create a new routing model instance.
         * @return pointer to new routing model instance.
         */
        static RoutingAdapter *newInstance();
    };

    typedef RunoffAdapter *(*RunoffInstanceInterface)();

    typedef RoutingAdapter *(*RoutingInstanceInterface)();

    /**
     * register one or multiple runoff model.
     * Just adding model instantiation interface/callback to @var runoffNest.
     * After registering, a unique model id will be generated for this model and bound to this model,
     * you can get the model id by calling @fn getModelKeyByName(${model_key}).
     * @param key unique model name for this model.
     * @param model the model instantiation callback function.
     * @return the id of registered run off model.
     */
    static _type_model_id registerRunoffModel(const _type_model_key key, RunoffInstanceInterface model);

    /**
     * un-register a runoff model by the model id.
     * Then, the model instantiation callback function will be remove for map @var runoffNest.
     * @param id unique model id to tag the model to be unregistered.
     */
    static void unRegisterRunoffModel(const _type_model_id id);

    /**
     * remove all routing models, clean map @var routingNest.
     */
    static void unRegisterAllRunoffModels();

    /**
     * create a runoff model instance using registered @typedef RunoffInstanceInterface.
     * If the model specified by @param id is not registered, nullptr will be returned.
     * @param id unique model id.
     * @return pointer to runoff model instance or nullptr.
     */
    static RunoffAdapter *newInstanceRunoff(const _type_model_id id);

    /**
     * register one or multiple routing model.
     * Just adding model instantiation interface/callback to @var routingNest.
     * After registering, a unique model key will be generated for this model and bound to this model,
     * you can get the model key by calling @fn getModelKeyByName(${model_name}).
     * @param name unique model name to tag the model.
     * @param model the model instantiation callback function.
     * @return the id of registered run off model.
     */
    static _type_model_id registerRoutingModel(const _type_model_key name, RoutingInstanceInterface model);

    /**
     * unregister a runoff model by the model id.
     * Then, the model instantiation callback function will be remove for map @var routingNest.
     * @param id unique model id to tag the model to be unregistered.
     */
    static void unRegisterRoutingModel(const _type_model_id id);

    /**
     * remove all routing models, clean map @var routingNest.
     */
    static void unRegisterAllRoutingModels();

    /**
     * create a runoff model instance using registered @typedef RunoffInstanceInterface.
     * If the model specified by @param id is not registered, nullptr will be returned.
     * @param id unique model id.
     * @return pointer to runoff model instance or nullptr.
     */
    static RoutingAdapter *newInstanceRouting(const _type_model_id id);


    /**
     * unregister all models, including routing and runoff models.
     */
    static void unRegisterAll();

    /**
     * Find a generated model id by unique model key.
     * If it is not found, 0 will be returned.
     * @param key the model key.
     * @return the generated model id.
     */
    static _type_model_id getModelIdByKey(const _type_model_key key);

private:

    /**
     * If you register a runoff model, then the runoff model instantiation interface will be saved in this map.
     */
    static std::map<_type_model_id, RunoffInstanceInterface> runoffNest;

    /**
     * The same as above, but for routing models.
     */
    static std::map<_type_model_id, RoutingInstanceInterface> routingNest;

    /**
     * key-id map of models.
     */
    static std::map<_type_model_key, _type_model_id> id_key_map;

    /**
     * delete item in map @var id_key_map by the value model id.
     * @param id model id.
     */
    static void eraseIdKeyMapById(const _type_model_id id);

    /**
     * generate a new unique model id.
     * @return unique model id.
     */
    static _type_model_id generateModelId();

};


#endif //PNOHS_MODEL_REGISTER_H
