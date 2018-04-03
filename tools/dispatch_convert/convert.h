//
// Created by genshen on 3/31/18.
//

#ifndef PNOHS_CONVERT_H
#define PNOHS_CONVERT_H


#include <iostream>
#include <json.hpp>
#include <dispatch/dispatch_parse.h>
#include <dispatch/dispatch_writer.h>

namespace convert {
    void convertToJson(std::string disBinPath, std::string disTextPath);

    void convertToBinary(std::string disTextPath, std::string disBinPath);
};

#endif //PNOHS_CONVERT_H
