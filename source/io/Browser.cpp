/**
 * Copyright (C) 2015 Jan Hajer
 */
#include <deque>

#include "TFile.h"

#include "boca/io/Browser.hh"

int main(int argc, char** argv)
{
    auto files = std::deque<TFile>{};
    for (auto const & argument : std::vector<std::string>(argv + 1, argv + argc)) files.emplace_back(argument.c_str(), "read");
    TApplication application("Browser", &argc, argv);
    boca::Browser browser;
    application.Run();
}
