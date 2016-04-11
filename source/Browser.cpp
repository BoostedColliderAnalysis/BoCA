/**
 * Copyright (C) 2015 Jan Hajer
 */
#include <deque>

#include "TApplication.h"
#include "TFile.h"
#include "TBrowser.h"

class Browser : public TBrowser
{
public:
    Browser() : TBrowser() {}
    ~Browser() {
        gApplication->Terminate();
    }
};

int main(int argc, char** argv)
{
    std::deque<TFile> files;
    for (auto const & argument : std::vector<std::string>(argv + 1, argv + argc)) files.emplace_back(argument.c_str(), "read");
    TApplication application("Browser", &argc, argv);
    Browser browser;
    application.Run();
}
