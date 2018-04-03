//
// Created by genshen on 2018-03-31.
//

#include <iostream>
#include <argagg.hpp>
#include "convert.h"
#include "ahct.h"

bool doConversion(int argc, char **argv);

int main(int argc, char *argv[]) {
    if (doConversion(argc, argv)) {
        return 0;
    } else {
        return -1;
    }
}

bool doConversion(int argc, char **argv) {
    // parse arguments using lib args: https://github.com/vietjtnguyen/argagg.
    argagg::parser argparser{{
                                     {"help", {"-h", "--help"}, "shows this help message.", 0},
                                     {"version", {"-v", "--version"}, "show this dispatch convert tool version", 0},
                                     {"bin2json", {"--b2j"},
                                             "convert binary dispatch file to json dispatch file"
                                                     " (arguments: binaryFilePath jsonFilePath)"
                                                     " (default: dispatch.dis  dispatch.json)",
                                             0},
                                     {"json2bin", {"--j2b"},
                                             "convert binary json file to binary dispatch file"
                                                     " (arguments: jsonFilePath binaryFilePath)"
                                                     " (default: dispatch.json dispatch.dis)",
                                             0},
//                                     {"json", {"-j", "--json",}, "path of input json file (default:dispatch.json)", 1},
//                                     {"bin", {"-b", "--bin"}, "path of input bin file (default:dispatch.dis)", 1},
//                                     {"output", {"-o", "--output"}, "path of output file (-j'default:dispatch.dis -b'default:dispatch.json)", 1},
                             }};

    argagg::parser_results args;
    argagg::fmt_ostream fmt_err_stream(std::cerr);
    argagg::fmt_ostream fmt_out_stream(std::cerr);

    try {
        args = argparser.parse(argc, argv);
    } catch (const std::exception &e) {
        fmt_err_stream << e.what() << std::endl;
        return false;
    }

    if (args["help"]) {
        fmt_out_stream << "Usage: " << argv[0] << ahct::ARGS_HINT_MSEEAGE << std::endl
                       << argparser;
        return true;
    }
    if (args["version"]) {
        fmt_out_stream << ahct::ARGS_VERSION_MSEEAGE << std::endl;
        return true;
    }

    //-j2b 和 -b2j 选项有且只能有一个
    if (!args[ahct::ARGS_JSON2BIN_OPTION_NAME] == !args[ahct::ARGS_BIN2JSON_OPTION_NAME]) {
        fmt_out_stream << "Usage: " << argv[0] << ahct::ARGS_HINT_MSEEAGE << std::endl
                       << argparser;
        return false;
    }

    // 要么有两个参数<inputfile outputfile>，要么有一个参数<inputfile>，要么没有参数<>，才会往后执行
    std::string inputFilePath, outputFilePath;
    if (args.pos.size() == 2) {
        inputFilePath = args.as<std::string>(0);
        outputFilePath = args.as<std::string>(1);
    } else if (args.pos.size() == 1) { // 只指定了输入文件路径，则输出文件路径使用默认路径
        inputFilePath = args.as<std::string>(0);
        if (args[ahct::ARGS_JSON2BIN_OPTION_NAME]) { // todo ?
            outputFilePath = ahct::DEFAULT_DIS_BIN_FILE_PATH;
        } else {
            outputFilePath = ahct::DEFAULT_DIS_JSON_FILE_PATH;
        }
    } else if (args.pos.size() == 0) {  // 未指定输入输出文件路径，则输入输出文件路径为默认
        if (args[ahct::ARGS_JSON2BIN_OPTION_NAME]) { // todo ?
            inputFilePath = ahct::DEFAULT_DIS_JSON_FILE_PATH;
            outputFilePath = ahct::DEFAULT_DIS_BIN_FILE_PATH;
        } else {
            inputFilePath = ahct::DEFAULT_DIS_BIN_FILE_PATH;
            outputFilePath = ahct::DEFAULT_DIS_JSON_FILE_PATH;
        }
    } else {
        fmt_err_stream << "Usage: " << argv[0] << ahct::ARGS_HINT_MSEEAGE << std::endl << argparser;
        return false;
    }

    if (args[ahct::ARGS_JSON2BIN_OPTION_NAME]) { // todo ?
        convert::convertToBinary(inputFilePath, outputFilePath);
        return true;
    }
    if (args[ahct::ARGS_BIN2JSON_OPTION_NAME]) { // todo ?
        convert::convertToText(inputFilePath, outputFilePath);
        return true;
    }

    // 无option时，提示
    fmt_err_stream << "Usage: " << argv[0] << ahct::ARGS_HINT_MSEEAGE << std::endl << argparser;
    return false;

}
