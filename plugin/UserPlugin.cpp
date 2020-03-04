#include "UserPlugin.h"

using namespace yazi::engine;
using namespace yazi::plugin;

UserPlugin::UserPlugin() : Plugin()
{

}

UserPlugin::~UserPlugin()
{

}

bool UserPlugin::run(Holder & holder)
{
    holder.ref<string>("output") += "user plugin run!";
    return true;
}

