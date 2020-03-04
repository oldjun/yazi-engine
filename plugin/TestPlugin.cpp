#include "TestPlugin.h"

using namespace yazi::engine;
using namespace yazi::plugin;

TestPlugin::TestPlugin() : Plugin()
{

}

TestPlugin::~TestPlugin()
{

}

bool TestPlugin::run(Holder & holder)
{
    holder.ref<string>("output") += "test plugin run!";
    return true;
}

