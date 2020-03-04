#pragma once

#include "Plugin.h"
using namespace yazi::engine;

namespace yazi {
namespace plugin {

class UserPlugin : public Plugin
{
public:
    UserPlugin();
    virtual ~UserPlugin();

    virtual bool run(Holder & holder);

};

// create plugin
extern "C" Plugin* create()
{
    return new (std::nothrow) UserPlugin();
}

// destroy plugin
extern "C" void destroy(Plugin *p)
{
    delete p;
    p = NULL;
}

}}
