//
//  Created by genshen on 2017/12/24.
//

#ifndef PNOHS_APP_H
#define PNOHS_APP_H

#include <kiwi_app.h>
#include "simulation.h"

class pnohs : public kiwi::kiwiApp {

private:
    std::string configFilePath; // configure file path.

    Simulation *simulation = nullptr;

    bool beforeCreate(int argc, char *argv[]) override;

    void onCreate() override;

    bool prepare() override;

    void onStart() override;

    void beforeDestroy() override;

    void onFinish() override;

    void onDestroy() override;

};


#endif // PNOHS_APP_H
