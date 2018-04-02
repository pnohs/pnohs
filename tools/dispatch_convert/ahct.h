//
// Created by wujiahao on 2018/4/2.
//

#ifndef PNOHS_AHCT_H
#define PNOHS_AHCT_H

#include <string>
#include <ios>

namespace ahct{
    static const std::string DEFAULT_DIS_JSON_FILE_PATH = "dispatch.json";
    static const std::string DEFAULT_DIS_BIN_FILE_PATH = "dispatch.bin";
    static const std::ios::openmode MODE_OPEN_DIS_BIN_FILE4WRITING = std::ios::binary | std::ios::trunc | std::ios::out;
    static const std::ios::openmode MODE_OPEN_DIS_TEXT_FILE4WRITING = std::ios::trunc | std::ios::out;
    static const std::ios::openmode MODE_OPEN_DIS_TEXT_FILE4READING = std::ios::in;


    static const std::string ARGS_HELP_OPTION_NAME = "help";
    static const std::string ARGS_HELP_OPTION1 = "-h";
    static const std::string ARGS_HELP_OPTION2 = "--help";
    static const std::string ARGS_HELP_OPTION_DESCRIPTE = "shows this help messag";
    static const unsigned short ARGS_HELP_ARGC = 0;

    static const std::string ARGS_VERSION_OPTION_NAME = "version";
    static const std::string ARGS_VERSION_OPTION1 = "-v";
    static const std::string ARGS_VERSION_OPTION2 = "--version";
    static const std::string ARGS_VERSION_OPTION_DESCRIPTE = "show package versio";
    static const unsigned short ARGS_VERSION_ARGC = 0;

    static const std::string ARGS_BIN2JSON_OPTION_NAME = "bin2json";
    static const std::string ARGS_BIN2JSON_OPTION1 = "-b";
    static const std::string ARGS_BIN2JSON_OPTION2 = "--bin2json";
    static const std::string ARGS_BIN2JSON_OPTION_DESCRIPTE = "convert binary dispatch file to json dispatch file"
                                                               " (arguments: binaryFilePath jsonFilePath)"
                                                               " (default: dispatch.dis  dispatch.json)";
    static const unsigned short ARGS_BIN2JSON_ARGC = 0;

    static const std::string ARGS_JSON2BIN_OPTION_NAME = "json2bin";
    static const std::string ARGS_JSON2BIN_OPTION1 = "-j";
    static const std::string ARGS_JSON2BIN_OPTION2 = "--json2bin";
    static const std::string ARGS_JSON2BIN_OPTION_DESCRIPTE = "convert binary json file to binary dispatch file"
                                                              " (arguments: jsonFilePath binaryFilePath)"
                                                              " (default: dispatch.json dispatch.dis)";
    static const unsigned short ARGS_JSON2BIN_ARGC = 0;

    static const std::string ARGS_HINT_MSEEAGE = " [-j|b] <inputfile outputfile>|<inputfile>|<> ";
    static const std::string ARGS_VERSION_MSEEAGE ="version 0.1.0 \n"
                                                   "Copyright (C) 2017 USTB";
}

#endif //PNOHS_AHCT_H
