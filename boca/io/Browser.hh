/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "TApplication.h"
#include "TBrowser.h"

namespace boca {

class Browser : public TBrowser
{
public:
    Browser() : TBrowser() {}
    ~Browser() {
        gApplication->Terminate();
    }
};

}
