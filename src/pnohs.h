//
//  Created by genshen on 2017/12/24.
//

#ifndef PNOHS_APP_H
#define PNOHS_APP_H

#include <kiwi_app.h>
#include "simulation.h"

class pnohs : public kiwi::kiwiApp {

private:
    std::string configFilePath = "config.toml"; // configure file path default value.

    Simulation *mSimulation = nullptr;

    bool beforeCreate(int argc, char *argv[]) override;

    /**
     * parse command line argv, and print necessary help information (e.g. run: app --help).
     * @param argc argc from function main().
     * @param argv argv from function main().
     * @return false for interrupting the running of the program after parsing argv.
     */
    bool parseCommands(int argc, char *argv[]);

    void onCreate() override;

    bool prepare() override;

    void onStart() override;

    void onFinish() override;

    void beforeDestroy() override;

    void onDestroy() override;

};


#endif // PNOHS_APP_H
