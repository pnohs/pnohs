//
// Created by genshen on 2018-03-31.
//

#include <iostream>
#include <args.hpp>
#include "convert.h"

void binaryToJson(args::Subparser &parser);

void jsonToBinary(args::Subparser &parser);


//args::Group arguments("arguments");
//args::ValueFlag<std::string> input(arguments, "input", "input file path", {'i', "input"});
//args::ValueFlag<std::string> output(arguments, "output", "output file path", {'o', "output"});

int main(int argc, char *argv[]) {
    // parse arguments using lib args: https://github.com/Taywee/args#refactoring-commands.
    args::ArgumentParser parser("dispatch file conversion tool");
    args::HelpFlag help(parser, "help", "Display this help menu", {'h', "help"});

    args::Group commands(parser, "commands");
    args::Command b2j(commands, "b2j", "Convert binary dispatch file to json dispatch file.", &binaryToJson);
    args::Command j2b(commands, "j2b", "Convert json dispatch file to binary dispatch file.", &jsonToBinary);

//    args::GlobalOptions globals(parser, arguments);

    try {
        parser.ParseCLI(argc, argv);
    } catch (args::Help) {
        std::cout << parser;
        std::cout << "  use \"" << parser.helpParams.programName
                  << " COMMAND --help\" for more information about a command." << std::endl;
    } catch (args::Error &e) {
        std::cerr << e.what() << std::endl << parser;
        return 1;
    }
    return 0;
}

// todo refactor: most code of binaryToJson and jsonToBinary are the same.
void binaryToJson(args::Subparser &parser) {
    args::ValueFlag<std::string> bin(parser, "bin", "path of binary file.", {'b', "bin"});
    args::ValueFlag<std::string> output(parser, "output", "path of output json file.", {'o', "output"});
    args::HelpFlag help(parser, "help", "Display this help message of this command.", {'h', "help"});
    parser.Parse();

    if (bin) {
        std::string bin_file = args::get(bin);
        std::string output_file = "dispatch.json"; // default value for output.
        if (output) {
            output_file = args::get(output);
        }
        convert::convertToJson(bin_file, output_file); // do conversion.
    } else {
        std::cerr << "error: no input file." << std::endl;
    }
}

void jsonToBinary(args::Subparser &parser) {
    args::ValueFlag<std::string> json(parser, "json", "path of json file.", {'j', "json"});
    args::ValueFlag<std::string> output(parser, "output", "path of output json file.", {'o', "output"});
    args::HelpFlag help(parser, "help", "Display this help message of this command.", {'h', "help"});
    parser.Parse();

    if (json) {
        if (json) {
            std::string json_file = args::get(json);
            std::string output_file = "dispatch.bin"; // default value for output.
            if (output) {
                output_file = args::get(output);
            }
            convert::convertToBinary(json_file, output_file); // do conversion.
        } else {
            std::cerr << "error: no json input file." << std::endl;
        }
    }
}
