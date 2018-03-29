//
// Created by genshen on 2017/12/24.
//

#include <vector>
#include <iostream>
#include "pnohs.h"

int main(int argc, char *argv[]) {
    //(new pnohs())->run(argc, argv);
// or:
//    pnohs *app = new pnohs();
//    app->run(argc, argv);
    std::vector<long> test;
    long tmp[10] = {1,2,3,4,5,6,7,8,9,0};
    test.insert(test.begin(),tmp, tmp+10);

    for(std::vector<long>::iterator index=test.begin();index != test.end(); index++)
    {
        std::cout << *index << "\t";
    }
}