#pragma once

#include "Plugin.h"
using namespace yazi::engine;

namespace yazi {
namespace plugin {

class TestPlugin : public Plugin
{
public:
    TestPlugin();
    virtual ~TestPlugin();

    virtual bool run(Holder & holder);

};

// create plugin
extern "C" Plugin* create()
{
    return new (std::nothrow) TestPlugin();
}

// destroy plugin
extern "C" void destroy(Plugin *p)
{
    delete p;
    p = NULL;
}

}}
