/*
 * Copyright © 2018 Evgeny Shulgin <izaronplatz@gmail.com>
 * This code is released under the license described in the LICENSE file
 */
#include <iostream>

#include <arguments.h>
#include <benchmark.h>
#include <logger.h>
#include <paint.h>
#include <puzzle.h>
#include <timespan.h>
#pragma warning(push, 0)
#include <Magick++.h>
#pragma warning(pop)

#include "model/Grid.h"

int InitArguments(int argc, char** argv) {
    try {
        cli_args::parser.ParseCLI(argc, argv);
    }
    catch(const args::Help&) {
        std::cout << cli_args::parser;
        return 0;
    }
    catch(const args::ParseError& e) {
        Logger::get()->error(e.what());
        std::cerr << cli_args::parser;
        return 1;
    }
    catch(const args::ValidationError& e) {
        Logger::get()->error(e.what());
        std::cerr << cli_args::parser;
        return 1;
    }

    return -1;  // Success, run further
}

int Init(int argc, char** argv) {
    Logger::Init();
    Magick::InitializeMagick(*argv);
    return InitArguments(argc, argv);
}

int Run() {
    // Either do nothing, or convert an image to a puzzle,
    // or launch benchmark on a folder, or solve a puzzle
    if (!cli_args::inputPuzzle && !cli_args::benchmark &&
            !cli_args::inputImage) {
        Logger::get()->info("There is nothing to solve");
    } else if (cli_args::inputImage) {
        std::string image_path = args::get(cli_args::inputImage);
        const bool convertToMono = args::get(cli_args::black);
        std::string result_path = image_path.substr(0,
                image_path.find_last_of('.')) +
                (convertToMono ? "_mono" : "") + ".pzl";
        Logger::get()->info("Trying to encode {}", image_path);
        Logger::get()->info("Save the puzzle to {}", result_path);
        Paint::EncodeImage(image_path, result_path, convertToMono);
    } else if (cli_args::benchmark) {
        Benchmark benchmark;
        if (!benchmark.Run(args::get(cli_args::benchmark))) {
            return 1;
        }
    } else {
        Timespan ts;
        Puzzle puzzle;
        const bool showGui = args::get(cli_args::gui);
        if (!puzzle.Solve(args::get(cli_args::inputPuzzle), !showGui)) {
            return 1;
        }
        if (showGui) {
            Grid grid;
            grid.init(puzzle.config());
        }
        ts.Peek(true);
    }

    return 0;
}

int main(int argc, char** argv) {
    int init = Init(argc, argv);
    if (init >= 0) {
        return init;
    }

    return Run();
}
