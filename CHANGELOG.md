<a name=""></a>
#  (2018-04-10)


### Bug Fixes

* **build:** KIWI_EXPORT_INCLUDE_PATH ([86469f6](https://git.gensh.me/HPCer/hydrology/pnohs/commits/86469f6))
* **dispatch-convert-tool:** fixed code in tools to adapt new file stream dispatch parsing api. ([1a27e72](https://git.gensh.me/HPCer/hydrology/pnohs/commits/1a27e72))
* **tools, simulation:** fixed memory leak problem in tools and simulation code. ([c4bfe91](https://git.gensh.me/HPCer/hydrology/pnohs/commits/c4bfe91))


### Features

* **cli:** use new lib Taywee/args for command line parsing. ([9b14721](https://git.gensh.me/HPCer/hydrology/pnohs/commits/9b14721))
* **config:** add configure parse ([b619d5d](https://git.gensh.me/HPCer/hydrology/pnohs/commits/b619d5d))
* **config:** add configure sync ([a9eb0e0](https://git.gensh.me/HPCer/hydrology/pnohs/commits/a9eb0e0))
* **dependency:** add package.json for changelog ([eea21eb](https://git.gensh.me/HPCer/hydrology/pnohs/commits/eea21eb))
* **dispatch:** new file stream api for dispatch parsing ([b58ae89](https://git.gensh.me/HPCer/hydrology/pnohs/commits/b58ae89))
* **dispatch-convert-tool:** add command line parse for dispatch-convert-tool. ([fdb24ac](https://git.gensh.me/HPCer/hydrology/pnohs/commits/fdb24ac))
* **dispatch-convert-tool:** finish the function of dispatch convertion between binary file and json file. ([177f84f](https://git.gensh.me/HPCer/hydrology/pnohs/commits/177f84f))
* **graph:** add api for checking river outlet and river origin. ([e1cb1cf](https://git.gensh.me/HPCer/hydrology/pnohs/commits/e1cb1cf))
* **graph:** bind dispatch parse results to river-routing graph. ([e98fd7f](https://git.gensh.me/HPCer/hydrology/pnohs/commits/e98fd7f))
* **init:** initial commit ([9a66a79](https://git.gensh.me/HPCer/hydrology/pnohs/commits/9a66a79))
* **models:** add a simple HBV model with tests. ([c0ffc57](https://git.gensh.me/HPCer/hydrology/pnohs/commits/c0ffc57))
* **partition:** add a new dispatch parse and generator with tested, and add a tool based on this di ([630e523](https://git.gensh.me/HPCer/hydrology/pnohs/commits/630e523))
* **partition:** add partition interface ([d201fa7](https://git.gensh.me/HPCer/hydrology/pnohs/commits/d201fa7))
* **partition:** read simulation dispatch results from partition file ([c1ccee9](https://git.gensh.me/HPCer/hydrology/pnohs/commits/c1ccee9))
* **river-graph:** add river network graph ([2d56401](https://git.gensh.me/HPCer/hydrology/pnohs/commits/2d56401))
* **routing:** add enqueue and enqueue interface for upstream taskqueue. ([fda53a2](https://git.gensh.me/HPCer/hydrology/pnohs/commits/fda53a2))
* **routing:** add streamflow routing deliver api. ([0872d49](https://git.gensh.me/HPCer/hydrology/pnohs/commits/0872d49))
* **routing:** finish straightforward deliver(memory copy deliver mode for downstream at current processor) ([7f2ffc6](https://git.gensh.me/HPCer/hydrology/pnohs/commits/7f2ffc6))
* **routing-message:** add basic message listening code template for stream routing message. ([236d2d1](https://git.gensh.me/HPCer/hydrology/pnohs/commits/236d2d1))
* **simulation:** add all-completed and potentially_completed status update for nodespool. ([568568d](https://git.gensh.me/HPCer/hydrology/pnohs/commits/568568d))
* **simulation:** add simulation context ([342dace](https://git.gensh.me/HPCer/hydrology/pnohs/commits/342dace))
* **task-dispatch:** remove "pre_handle" partition code ([3bb4fba](https://git.gensh.me/HPCer/hydrology/pnohs/commits/3bb4fba))



