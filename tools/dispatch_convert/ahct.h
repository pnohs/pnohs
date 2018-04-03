//
// Created by wujiahao on 2018/4/2.
//

#ifndef PNOHS_AHCT_H
#define PNOHS_AHCT_H

#include <string>
#include <ios>

namespace ahct {
    static const std::string DEFAULT_DIS_JSON_FILE_PATH = "dispatch.json";
    static const std::string DEFAULT_DIS_BIN_FILE_PATH = "dispatch.bin";
    static const std::ios::openmode MODE_OPEN_DIS_BIN_FILE4WRITING = std::ios::binary | std::ios::trunc | std::ios::out;
    static const std::ios::openmode MODE_OPEN_DIS_BIN_FILE4READING = std::ios::binary | std::ios::in;
    static const std::ios::openmode MODE_OPEN_DIS_TEXT_FILE4WRITING = std::ios::trunc | std::ios::out;
    static const std::ios::openmode MODE_OPEN_DIS_TEXT_FILE4READING = std::ios::in;

    static const std::string ARGS_BIN2JSON_OPTION_NAME = "bin2json";

    static const std::string ARGS_JSON2BIN_OPTION_NAME = "json2bin";

    static const std::string ARGS_HINT_MSEEAGE = " [--j2b|--b2j] <inputfile outputfile>|<inputfile>|<> ";
    static const std::string ARGS_VERSION_MSEEAGE = "version 0.1.0 \n"
                                                    "Copyright (C) 2017 USTB";
}

#endif //PNOHS_AHCT_H
