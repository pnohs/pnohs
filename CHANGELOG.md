
<a name="v0.3.1"></a>
## [v0.3.1](https://github.com/genshen/pnohs/compare/v0.3.0...v0.3.1)

> 2019-11-23

### Build

* **pkg:** update googletest to version 1.10.0

### Ci

* **gitlab-ci:** update gitlab-ci dokcer images version to hpcer/hpcdev:pkg-0.3.0.

### Docs

* **changelog:** update changelog for version 0.3.1

### Improvement

* **routing:** set the routing data type as vector<double>(not just double)

### Merge

* Merge branch 'dev' into 'master'
* Merge branch 'feature-routing-vector' into 'dev'

### Refactor

* **params:** make vector params in function NodesPool::setNodesParams as const and ref
* **routing:** refactor reouting deliver code of getting routing data from model context

### Style

* update files mode to 644: .chglog and src/pnohs-config.cmake.in

### BREAKING CHANGE


now the routing data type is vector<double>, not double.


<a name="v0.3.0"></a>
## [v0.3.0](https://github.com/genshen/pnohs/compare/v0.3.0-alpha-3...v0.3.0)

> 2019-09-24

### Chore

* replace dead domain to git.hpcer.dev and update kiwi version.


<a name="v0.3.0-alpha-3"></a>
## [v0.3.0-alpha-3](https://github.com/genshen/pnohs/compare/v0.3.0-alpha-2...v0.3.0-alpha-3)

> 2019-07-26

### Docs

* **changelog:** update changelog for version 0.3.0-alpha-3.

### Feat

* **params:** add parameters metadata to class ParamsList.
* **params:** change type of params(e.g type param_const) from double to union to support different param types.
* **scheduler:** add blocking time counting for simulation nodes selecting.

### Merge

* Merge branch 'dev' into 'master' for v0.3.0-alpha-3.

### Refactor

* **params:** rename func parameter type(params key) in ParamsList from std::string to params_ke

### Revert

* **params:** change type of initial variable, temporary variable and status variable to double, not param_union.

### BREAKING CHANGE


member keys in class ParamsList is moved to member metadata_list.

type of param_const have been changed from double to union type.


<a name="v0.3.0-alpha-2"></a>
## [v0.3.0-alpha-2](https://github.com/genshen/pnohs/compare/v0.3.0-alpha...v0.3.0-alpha-2)

> 2019-06-07

### Docs

* **changelog:** update changelog for version 0.3.0-alpha-2.

### Fix

* **params:** rename ParamsList::setValues to ParamsList::setValuesMap to fix compiling issue.

### Merger

* Merge branch 'dev' into 'master' for version v0.3.0-alpha-2

### BREAKING CHANGE


ParamsList::setValues was renamed to ParamsList::setValuesMap.


<a name="v0.3.0-alpha"></a>
## [v0.3.0-alpha](https://github.com/genshen/pnohs/compare/v0.2.0...v0.3.0-alpha)

> 2019-06-07

### Docs

* **changelog:** update changelog for version 0.3.0-alpha.

### Feat

* **model-register:** return model id when registering runoff and routing model.
* **modelcontext:** add onBind interface for model context.
* **params:** add member keys(model params keys/names) for class ParamsList, as well as its tests.

### Merge

* Merge branch 'dev' into 'master' for version 0.3.0-alpha.

### Test

* **params:** add more tests for params binding in params list data structure.

### BREAKING CHANGE


add another template param(ID) for template class ParamsList<N, ID>.


<a name="v0.2.0"></a>
## [v0.2.0](https://github.com/genshen/pnohs/compare/v0.2.0-beta...v0.2.0)

> 2019-05-22

### Build

* **cmake:** add cmake EXPORT installation for lib pnohs.
* **cmake:** update cmake files to link exported target.
* **dependency:** update dependency kiwi and gtest.
* **dependency:** update to pkg tool version v0.2.0-beta.

### Ci

* **gitlab-ci:** update .gitlab-ci.yml config file to build project using image hpcer/hpcdev:pkg-0.2.0

### Docs

* **changelog:** update changelog to show what's new in version v0.2.0.

### Feat

* **model-adapter:** add model id for register map.

### Merge

* Merge branch 'dev' into 'master'
* **model-register:** Merge pull request [#4](https://github.com/genshen/pnohs/issues/4) from genshen/feature-register-model-id


<a name="v0.2.0-beta"></a>
## [v0.2.0-beta](https://github.com/genshen/pnohs/compare/v0.2.0-alpha...v0.2.0-beta)

> 2018-10-26

### Docs

* **changelog:** update changelogs.

### Feat

* **dispatch-convert-tool:** add dispatch convert tool back.
* **model-adapter:** add model register feature.
* **output:** add result conversion from map-vector to 1-d array.
* **output:** add utils class SimReduction for saving simulaiton results.
* **stopwatch:** add stopwatch enable option.

### Fix

* **message-loop:** fixed bug of "pthread_create error with code 11".

### Merge

* Merge branch 'dev' into branch 'master' for release v0.2.0-beta.
* Merge pull request [#2](https://github.com/genshen/pnohs/issues/2) from genshen/fix-pthread-creation-error
* **output:** Merge branch 'feature-sim-reduction' into dev.
* **stopwatch:** Merge branch 'fix-stopwatch-enable-switch' into 'dev'

### Revert

* **stopwatch:** fixed compile error: undefined reference to 'stopwatch::enabled'.


<a name="v0.2.0-alpha"></a>
## [v0.2.0-alpha](https://github.com/genshen/pnohs/compare/v0.1.0...v0.2.0-alpha)

> 2018-08-25

### Build

* **cmake:** make pnohs as an lib (except tests).
* **dependency:** use mpi test env from kiwi framework and linked googletest lib(not src include).

### Chore

* **gitignore:** remove vendor directory.
* **gitignore:** add vendor and pkg.dep.cmake as ignore file.

### Docs

* **changelog:** update changelogs.
* **readme:** modified readme for building pnohs library.

### Feat

* **graph:** add global graph traversing.
* **graph:** add feature of gathering graph global nodes ids.
* **graph:** add class Graph(in src/graph.h) for getting sub-graph information.
* **model-adapter:** add interface for reseting models/model-context for next simulation.
* **model-adapter:** add model interface of onBind() and onParamsPassed().
* **models:** add model interface of params count.
* **nodespool:** add eachNode function for nodespool to iterate each simulation node.
* **params:** add typedef for params values type(e.g. _type_param, _type_param_mpi).
* **params:** add parameters passing for all nodes in NodesPool, and removed "static" of paramCount()
* **params:** add a basic parameter interface in src/ds directory.
* **scheduler:** add interface of reseting scheduler context and nodes pool completion status.
* **scheduler:** add constructor for using existing NodesPool in scheduler/s_context:SContext.

### Fix

* **cmake:** fix cmake problem in building unit test.
* **message-looper:** pass simulation communication domain to message looper(pre one is MPI_COMM_WORL
* **routing:** pass an empty TypeRouting list to stashUpstreamRouting method if it is river orgin.

### Merge

* **dependency:** update to newest kiwi framework to use global/local mpi_process.
* **graph:** Merge branch 'feature-graph-traversing' into 'dev'
* **model-adapter:** merge branch 'feature-model-interface' into dev

### Refactor

* removed application code (e.g. config, models)
* **dependency:** update to newest kiwi framework to use global/local mpi_process.
* **graph:** combine two different gather method in gatherAllNodesIds: gather to root or gather to all processors.
* **graph:** make node id in graph const value, and restrict node id in SimulationNode non-null
* **model-adapter:** add parameters size to model-adapter interface onParamsPassed().
* **model-adapter:** add virtual destructors for model adapter.
* **simulation:** rename _time_steps in class SimulationNode to _time_step.

### Revert

* **license:** change license GPL to MPL(Mozilla Public License).
* **model-adapter:** make function paramCount a member function in ModelAdapter.
* **models:** make ModelContext and ModelAdapter in SimulationNode public.
* **nodespool:** move implementation of forEachNode to nodespool.h file to escape compiling error.

### Test

* **scheduler:** add test for strategy adapter.


<a name="v0.1.0"></a>
## v0.1.0

> 2018-07-05

### Build

* **cmake:** add static binary build document and remove deprecated FindMPI features.
* **dependency:** add file dependency.cmake and move dependencies (mpi,pthread) to this file.
* **dependency:** add pthread dependency.
* **dependency:** add concurrentqueue pacakge
* **pkg:** add build (post install) section

### Docs

* **README:** update dependency and build section in README.md
* **build:** update build document in README.md
* **changelog:** update changelog

### Feat

* **cli:** use new lib Taywee/args for command line parsing.
* **config:** move config data to class ConfigValues, and add 'pickup_strategy' config.
* **config:** add configure parse
* **config:** add configure sync
* **debug:** add river routing time line graph for debugging.
* **debug:** add MPI_Wtime for stopwatch to count time.
* **dependency:** update to newest kiwi framework.
* **dependency:** add package.json for changelog
* **dispatch:** new file stream api for dispatch parsing
* **dispatch-convert-tool:** finish the function of dispatch convertion between binary file and json file.
* **dispatch-convert-tool:** add command line parse for dispatch-convert-tool.
* **graph:** bind dispatch parse results to river-routing graph.
* **graph:** add api for checking river outlet and river origin.
* **init:** initial commit
* **logs:** add colorful and multi-levels logs.
* **message-loop:** add mpi thread and message-loop MPI_Mprobe support.
* **model-adapter:** add model adapter(routing adapter + runoff adapter + model_context) and an flow
* **models:** add a simple HBV model with tests.
* **partition:** add partition interface
* **partition:** read simulation dispatch results from partition file
* **partition:** add a new dispatch parse and generator with tested, and add a tool based on this di
* **river-graph:** add river network graph
* **routing:** finish straightforward deliver(memory copy deliver mode for downstream at current processor)
* **routing:** add streamflow routing deliver api.
* **routing:** add enqueue and enqueue interface for upstream taskqueue.
* **routing-message:** use a new implementation of exit condition for routing message runner.
* **routing-message:** add basic message listening code template for stream routing message.
* **routing-message:** add implementation of the interface of StreamRoutingMessageRunner
* **routing-message:** Merge branch 'feature-routing-deliver' into 'develop'
* **scheduler:** add 'longest' pickup strategy for scheduler.
* **scheduler:** finish the todo of dequeue upstream in scheduler
* **scheduler:** move original pichup strategy (named simple pickup strategy) to simple_pickup.cpp.
* **scheduler:** move original pichup strategy (named simple pickup strategy) to simple_pickup.cpp.
* **scheduler:** add schedule adapter, and add ring pichup strategy.
* **scheduler:** add a new simulation pichup strategy: circle-pickup.
* **simulation:** add simulation context
* **simulation:** add all-completed and potentially_completed status update for nodespool.
* **simulation:** add simulation time counter.
* **task-dispatch:** remove "pre_handle" partition code

### Fix

* **$compile:** fixed compiling error of "call to implicitly-deleted copy constructor of 'std::fstream'.
* **$compile:** Merge branch 'feature-routing-deliver' into 'develop'
* **$compile:** fixed all compiling warnings
* **build:** KIWI_EXPORT_INCLUDE_PATH
* **dependency:** update to newest kiwi framework to fix null-terminated string bug in kiwi bundle.
* **dependency:** fixed compiling error caused by nlohmann/json and args dependency
* **dispatch-convert-tool:** fixed code in tools to adapt new file stream dispatch parsing api.
* **models:** fixed compile error [#1](https://github.com/genshen/pnohs/issues/1) in model by add #include <typeinfo>
* **scheduler:** fixed problem: given a total-steps T, but the simulation will run T+1 steps.
* **simulation:** change vector of SimulationNode in nodes_pool to pointer.

### Merge

* **debug:** Merge branch 'feature_routing_graph_debug' into 'dev'
* **scheduler:** Merge branch 'feature-pickup-strategy' into 'dev'

### Refactor

* **data-struct:** add typedef for [node id], [node_index], [mpirank id], [file offset] .
* **dependency:** new version pencil-cli
* **partition:** rewrite partition module
* **partition:** refactor code for reading dispatch results
* **routing-deliver:** update deliver api.

### Revert

* Merge branch 'dev' into 'master'
* **all:** Merge branch 'feature-stream-dispatch-parse' into develop
* **log:** add pickup strategy log in simulation.cpp, and removed poststep log in scheduler.cpp.
* **partition:** merge branch feature-wr-partition-file to branch develop
* **scheduler:** Merge branch 'dequeue_of_scheduler' into 'feature-routing-deliver'
* **simulation:** Merge branch 'fix-[#3](https://github.com/genshen/pnohs/issues/3)-nodes-vector' into 'dev',no need fixing, which is dispatch file problem.

### Style

* removed unnecessary comments.
* **all:** fixed spell mistake of word 'initial'.
* **dispatch:** rename dispatch/node.hpp to dispatch/dnode.hpp and add inline to its member function
* **dispatch-convert-tool:** change code of command line parsing to a more clear style.
* **dispatch-convert-tool:** removed some unnecessary comment.
* **model:** removed some unused code.
* **partition:** format code style

### Test

* **graph:** add test for upstream nodes task queue.
* **graph:** add test for graph node api of checking river outlet and river origin.

