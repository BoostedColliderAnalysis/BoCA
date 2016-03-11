/**
 * Copyright (C) 2015 Jan Hajer
 */
#include <vector>

#include "TApplication.h"
#include "TFile.h"
#include "TBrowser.h"

class Browser : public TBrowser
{
public:
    Browser() : TBrowser() {}
    virtual ~Browser() {
        gApplication->Terminate();
    }
};

int main(int argc, char** argv)
{
    std::vector<std::string> arguments(argv + 1, argv + argc);
    std::vector<TFile*> files;
    for (auto const & argument : arguments) files.emplace_back(TFile::Open(argument.c_str(), "read"));
    TApplication application("Browser", &argc, argv);
    Browser browser;
    application.Run();
}
