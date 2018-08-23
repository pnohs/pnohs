<a name=""></a>
# [](https://git.gensh.me/HPCer/hydrology/pnohs/compare/v0.1.1...v) (2018-08-23)



<a name="0.1.1"></a>
## [0.1.1](https://git.gensh.me/HPCer/hydrology/pnohs/compare/v0.1.0...v0.1.1) (2018-08-23)


### Bug Fixes

* **$compile:** fixed all compiling warnings ([8accf7f](https://git.gensh.me/HPCer/hydrology/pnohs/commits/8accf7f))
* **$compile:** fixed compiling error of "call to implicitly-deleted copy constructor of 'std::fstream'. ([03c8416](https://git.gensh.me/HPCer/hydrology/pnohs/commits/03c8416))
* **build:** KIWI_EXPORT_INCLUDE_PATH ([86469f6](https://git.gensh.me/HPCer/hydrology/pnohs/commits/86469f6))
* **cmake:** fix cmake problem in building unit test. ([c99bd82](https://git.gensh.me/HPCer/hydrology/pnohs/commits/c99bd82))
* **dependency:** fixed compiling error caused by nlohmann/json and args dependency ([9ef8875](https://git.gensh.me/HPCer/hydrology/pnohs/commits/9ef8875))
* **dependency:** update to newest kiwi framework to fix null-terminated string bug in kiwi bundle. ([e34f2d4](https://git.gensh.me/HPCer/hydrology/pnohs/commits/e34f2d4))
* **dispatch-convert-tool:** fixed code in tools to adapt new file stream dispatch parsing api. ([1a27e72](https://git.gensh.me/HPCer/hydrology/pnohs/commits/1a27e72))
* **message-looper:** pass simulation communication domain to message looper(pre one is MPI_COMM_WORL ([a971e1e](https://git.gensh.me/HPCer/hydrology/pnohs/commits/a971e1e))
* **models:** fixed compile error [#1](https://git.gensh.me/HPCer/hydrology/pnohs/issues/1) in model by add #include <typeinfo> ([7656ea1](https://git.gensh.me/HPCer/hydrology/pnohs/commits/7656ea1))
* **routing:** pass an empty TypeRouting list to stashUpstreamRouting method if it is river orgin. ([85132fa](https://git.gensh.me/HPCer/hydrology/pnohs/commits/85132fa))
* **scheduler:** fixed problem: given a total-steps T, but the simulation will run T+1 steps. ([73ac503](https://git.gensh.me/HPCer/hydrology/pnohs/commits/73ac503))
* **simulation:** change vector of SimulationNode in nodes_pool to pointer. ([afe7c25](https://git.gensh.me/HPCer/hydrology/pnohs/commits/afe7c25))
* **tools, simulation:** fixed memory leak problem in tools and simulation code. ([c4bfe91](https://git.gensh.me/HPCer/hydrology/pnohs/commits/c4bfe91))


### Features

* **cli:** use new lib Taywee/args for command line parsing. ([9b14721](https://git.gensh.me/HPCer/hydrology/pnohs/commits/9b14721))
* **config:** add configure parse ([b619d5d](https://git.gensh.me/HPCer/hydrology/pnohs/commits/b619d5d))
* **config:** add configure sync ([a9eb0e0](https://git.gensh.me/HPCer/hydrology/pnohs/commits/a9eb0e0))
* **config:** move config data to class ConfigValues, and add 'pickup_strategy' config. ([0b4f00e](https://git.gensh.me/HPCer/hydrology/pnohs/commits/0b4f00e))
* **debug:** add MPI_Wtime for stopwatch to count time. ([78c9770](https://git.gensh.me/HPCer/hydrology/pnohs/commits/78c9770))
* **debug:** add river routing time line graph for debugging. ([7b2b250](https://git.gensh.me/HPCer/hydrology/pnohs/commits/7b2b250))
* **dependency:** add package.json for changelog ([eea21eb](https://git.gensh.me/HPCer/hydrology/pnohs/commits/eea21eb))
* **dependency:** update to newest kiwi framework. ([67db257](https://git.gensh.me/HPCer/hydrology/pnohs/commits/67db257))
* **dispatch:** new file stream api for dispatch parsing ([b58ae89](https://git.gensh.me/HPCer/hydrology/pnohs/commits/b58ae89))
* **dispatch-convert-tool:** add command line parse for dispatch-convert-tool. ([fdb24ac](https://git.gensh.me/HPCer/hydrology/pnohs/commits/fdb24ac))
* **dispatch-convert-tool:** finish the function of dispatch convertion between binary file and json file. ([177f84f](https://git.gensh.me/HPCer/hydrology/pnohs/commits/177f84f))
* **graph:** add api for checking river outlet and river origin. ([e1cb1cf](https://git.gensh.me/HPCer/hydrology/pnohs/commits/e1cb1cf))
* **graph:** add class Graph(in src/graph.h) for getting sub-graph information. ([0e911ef](https://git.gensh.me/HPCer/hydrology/pnohs/commits/0e911ef))
* **graph:** add feature of gathering graph global nodes ids. ([cb4704d](https://git.gensh.me/HPCer/hydrology/pnohs/commits/cb4704d))
* **graph:** add global graph traversing. ([d372ef2](https://git.gensh.me/HPCer/hydrology/pnohs/commits/d372ef2))
* **graph:** bind dispatch parse results to river-routing graph. ([e98fd7f](https://git.gensh.me/HPCer/hydrology/pnohs/commits/e98fd7f))
* **init:** initial commit ([9a66a79](https://git.gensh.me/HPCer/hydrology/pnohs/commits/9a66a79))
* **logs:** add colorful and multi-levels logs. ([06ce5a4](https://git.gensh.me/HPCer/hydrology/pnohs/commits/06ce5a4))
* **message-loop:** add mpi thread and message-loop MPI_Mprobe support. ([9adbbe6](https://git.gensh.me/HPCer/hydrology/pnohs/commits/9adbbe6))
* **model-adapter:** add interface for reseting models/model-context for next simulation. ([deca6ad](https://git.gensh.me/HPCer/hydrology/pnohs/commits/deca6ad))
* **model-adapter:** add model adapter(routing adapter + runoff adapter + model_context) and an flow ([e240452](https://git.gensh.me/HPCer/hydrology/pnohs/commits/e240452))
* **model-adapter:** add model interface of onBind() and onParamsPassed(). ([5193042](https://git.gensh.me/HPCer/hydrology/pnohs/commits/5193042))
* **models:** add a simple HBV model with tests. ([c0ffc57](https://git.gensh.me/HPCer/hydrology/pnohs/commits/c0ffc57))
* **models:** add model interface of params count. ([d1865bf](https://git.gensh.me/HPCer/hydrology/pnohs/commits/d1865bf))
* **nodespool:** add eachNode function for nodespool to iterate each simulation node. ([f1bcc23](https://git.gensh.me/HPCer/hydrology/pnohs/commits/f1bcc23))
* **params:** add a basic parameter interface in src/ds directory. ([8e9f63c](https://git.gensh.me/HPCer/hydrology/pnohs/commits/8e9f63c))
* **partition:** add a new dispatch parse and generator with tested, and add a tool based on this di ([630e523](https://git.gensh.me/HPCer/hydrology/pnohs/commits/630e523))
* **partition:** add partition interface ([d201fa7](https://git.gensh.me/HPCer/hydrology/pnohs/commits/d201fa7))
* **partition:** read simulation dispatch results from partition file ([c1ccee9](https://git.gensh.me/HPCer/hydrology/pnohs/commits/c1ccee9))
* **river-graph:** add river network graph ([2d56401](https://git.gensh.me/HPCer/hydrology/pnohs/commits/2d56401))
* **routing:** add enqueue and enqueue interface for upstream taskqueue. ([fda53a2](https://git.gensh.me/HPCer/hydrology/pnohs/commits/fda53a2))
* **routing:** add streamflow routing deliver api. ([0872d49](https://git.gensh.me/HPCer/hydrology/pnohs/commits/0872d49))
* **routing:** finish straightforward deliver(memory copy deliver mode for downstream at current processor) ([7f2ffc6](https://git.gensh.me/HPCer/hydrology/pnohs/commits/7f2ffc6))
* **routing-message:** add basic message listening code template for stream routing message. ([236d2d1](https://git.gensh.me/HPCer/hydrology/pnohs/commits/236d2d1))
* **routing-message:** add implementation of the interface of StreamRoutingMessageRunner ([3bdb63f](https://git.gensh.me/HPCer/hydrology/pnohs/commits/3bdb63f))
* **routing-message:** use a new implementation of exit condition for routing message runner. ([e809db3](https://git.gensh.me/HPCer/hydrology/pnohs/commits/e809db3))
* **scheduler:** add 'longest' pickup strategy for scheduler. ([010df51](https://git.gensh.me/HPCer/hydrology/pnohs/commits/010df51))
* **scheduler:** add a new simulation pichup strategy: circle-pickup. ([a953595](https://git.gensh.me/HPCer/hydrology/pnohs/commits/a953595))
* **scheduler:** add constructor for using existing NodesPool in scheduler/s_context:SContext. ([5f3b6f4](https://git.gensh.me/HPCer/hydrology/pnohs/commits/5f3b6f4))
* **scheduler:** add interface of reseting scheduler context and nodes pool completion status. ([bce06d6](https://git.gensh.me/HPCer/hydrology/pnohs/commits/bce06d6))
* **scheduler:** add schedule adapter, and add ring pichup strategy. ([7aa7ccd](https://git.gensh.me/HPCer/hydrology/pnohs/commits/7aa7ccd))
* **scheduler:** finish the todo of dequeue upstream in scheduler ([c7ea4c7](https://git.gensh.me/HPCer/hydrology/pnohs/commits/c7ea4c7))
* **scheduler:** move original pichup strategy (named simple pickup strategy) to simple_pickup.cpp. ([abd3630](https://git.gensh.me/HPCer/hydrology/pnohs/commits/abd3630))
* **scheduler:** move original pichup strategy (named simple pickup strategy) to simple_pickup.cpp. ([d0a5d68](https://git.gensh.me/HPCer/hydrology/pnohs/commits/d0a5d68))
* **simulation:** add all-completed and potentially_completed status update for nodespool. ([568568d](https://git.gensh.me/HPCer/hydrology/pnohs/commits/568568d))
* **simulation:** add simulation context ([342dace](https://git.gensh.me/HPCer/hydrology/pnohs/commits/342dace))
* **simulation:** add simulation time counter. ([77b03f9](https://git.gensh.me/HPCer/hydrology/pnohs/commits/77b03f9))
* **task-dispatch:** remove "pre_handle" partition code ([3bb4fba](https://git.gensh.me/HPCer/hydrology/pnohs/commits/3bb4fba))


### Reverts

* **license:** change license GPL to MPL(Mozilla Public License). ([810c743](https://git.gensh.me/HPCer/hydrology/pnohs/commits/810c743))
* **log:** add pickup strategy log in simulation.cpp, and removed poststep log in scheduler.cpp. ([87f3f70](https://git.gensh.me/HPCer/hydrology/pnohs/commits/87f3f70))
* **models:** make ModelContext and ModelAdapter in SimulationNode public. ([f658563](https://git.gensh.me/HPCer/hydrology/pnohs/commits/f658563))
* **nodespool:** move implementation of forEachNode to nodespool.h file to escape compiling error. ([de4ccbb](https://git.gensh.me/HPCer/hydrology/pnohs/commits/de4ccbb))



