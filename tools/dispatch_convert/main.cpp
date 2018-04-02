//
// Created by genshen on 2018-03-31.
//

#include <fstream>
#include <iostream>
#include <json.hpp>
#include <argagg.hpp>

#include "convert.h"
#include "ahct.h"

bool doConvertion(int argc, char *argv[]);

int main(int argc, char *argv[]) {
    if (doConvertion(argc, argv)) {
        return 0;
    } else {
        return -1;
    }
}

bool doConvertion(int argc, char *argv[]) {
    // parse arguments using lib args: https://github.com/vietjtnguyen/argagg.
    argagg::parser argparser{{
                                     {ahct::ARGS_HELP_OPTION_NAME, {ahct::ARGS_HELP_OPTION1, ahct::ARGS_HELP_OPTION2},
                                             ahct::ARGS_HELP_OPTION_DESCRIPTE, ahct::ARGS_HELP_ARGC},
                                     {ahct::ARGS_VERSION_OPTION_NAME, {ahct::ARGS_VERSION_OPTION1, ahct::ARGS_VERSION_OPTION2},
                                             ahct::ARGS_VERSION_OPTION_DESCRIPTE, ahct::ARGS_VERSION_ARGC},
                                     {ahct::ARGS_BIN2JSON_OPTION_NAME, {ahct::ARGS_BIN2JSON_OPTION1, ahct::ARGS_BIN2JSON_OPTION2},
                                             ahct::ARGS_BIN2JSON_OPTION_DESCRIPTE, ahct::ARGS_BIN2JSON_ARGC},
                                     {ahct::ARGS_JSON2BIN_OPTION_NAME, {ahct::ARGS_JSON2BIN_OPTION1, ahct::ARGS_JSON2BIN_OPTION2},
                                             ahct::ARGS_JSON2BIN_OPTION_DESCRIPTE, ahct::ARGS_JSON2BIN_ARGC},
//                                     {"json", {"-j", "--json",}, "path of input json file (default:dispatch.json)", 1},
//                                     {"bin", {"-b", "--bin"}, "path of input bin file (default:dispatch.dis)", 1},
//                                     {"output", {"-o", "--output"}, "path of output file (-j'default:dispatch.dis -b'default:dispatch.json)", 1},
                             }};

    argagg::parser_results args;
    argagg::fmt_ostream fmtErr(std::cerr);
    argagg::fmt_ostream fmtOut(std::cerr);

    std::string inputFilePath, outputFilePath;

    try {
        args = argparser.parse(argc, argv);
    } catch (const std::exception &e) {
        fmtErr << e.what() << std::endl;
        return false;
    }

    if (args[ahct::ARGS_HELP_OPTION_NAME]) {
        fmtOut << "Usage: " << argv[0] << ahct::ARGS_HINT_MSEEAGE << std::endl << argparser;
        return true;
    }
    if (args[ahct::ARGS_VERSION_OPTION_NAME]) {
        fmtOut << ahct::ARGS_VERSION_MSEEAGE << std::endl;
        return true;
    }

    //-j 和 -b 选项有且只能有一个
    if ((!args[ahct::ARGS_JSON2BIN_OPTION_NAME] && !args[ahct::ARGS_BIN2JSON_OPTION_NAME])
        || (args[ahct::ARGS_JSON2BIN_OPTION_NAME] && args[ahct::ARGS_BIN2JSON_OPTION_NAME])) {

        fmtOut << "Usage: " << argv[0] << ahct::ARGS_HINT_MSEEAGE << std::endl << argparser;

        return false;
    }

    // 要么有两个参数<inputfile outputfile>，要么有一个参数<inputfile>，要么没有参数<>，才会往后执行
    if (args.pos.size() == 2) {
        inputFilePath = args.as<std::string>(0);
        outputFilePath = args.as<std::string>(1);
    } else if (args.pos.size() == 1) { // 只指定了输入文件路径，则输出文件路径使用默认路径
        inputFilePath = args.as<std::string>(0);
        if (args["ARGS_JSON2BIN_OPTION_NAME"]) {
            outputFilePath = ahct::DEFAULT_DIS_BIN_FILE_PATH;
        } else {
            outputFilePath = ahct::DEFAULT_DIS_JSON_FILE_PATH;
        }
    } else if (args.pos.size() == 0) {  // 未指定输入输出文件路径，则输入输出文件路径为默认
        if (args["ARGS_JSON2BIN_OPTION_NAME"]) {
            inputFilePath = ahct::DEFAULT_DIS_JSON_FILE_PATH;
            outputFilePath = ahct::DEFAULT_DIS_BIN_FILE_PATH;
        } else {
            inputFilePath = ahct::DEFAULT_DIS_BIN_FILE_PATH;
            outputFilePath = ahct::DEFAULT_DIS_JSON_FILE_PATH;
        }
    } else {
        fmtErr << "Usage: " << argv[0] << ahct::ARGS_HINT_MSEEAGE << std::endl << argparser;
        return false;
    }

    if (args["ARGS_JSON2BIN_OPTION_NAME"]) {
        convert::convertToBinary(inputFilePath, outputFilePath);
        return true;
    }
    if (args["ARGS_BIN2JSON_OPTION_NAME"]) {
        convert::convertToText(inputFilePath, outputFilePath);
        return true;
    }

    // 无option时，提示
    fmtErr << "Usage: " << argv[0] << ahct::ARGS_HINT_MSEEAGE << std::endl << argparser;
    return false;

}
