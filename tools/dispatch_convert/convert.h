//
// Created by genshen on 3/31/18.
//

#ifndef PNOHS_CONVERT_H
#define PNOHS_CONVERT_H


#include <iostream>
#include <dispatch/dispatch_parse.h>
#include <json.hpp>
#include <dispatch/dispatch_writer.h>

class convert {

public:
    static void convertToText(std::string disBinPath, std::string disTextPath);
    static void convertToBinary(std::string disTextPath, std::string disBinPath);
};


#endif //PNOHS_CONVERT_H
