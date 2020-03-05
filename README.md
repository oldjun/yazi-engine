# yazi-engine
a c++ work flow based on plugin

|Author|junping|
|---|---|
|E-mail|oldjun@sina.com|
|Wechat|chenjunping1024|

## Definition of work flow
a real project is complex, how to divide the complex modules into some pieces simple modules is a big challenge. Here we provide the work flow to accomplish the job. The work flow is a configuration written with XML document, as follows:
```xml
<?xml version="1.0"?>
<workflow>
    <work name="1" switch="on">
        <plugin name="testplugin.so" switch="on" />
        <plugin name="userplugin.so" switch="on" />
    </work>
    <work name="2" switch="on">
        <plugin name="userplugin.so" switch="on" />
    </work>
</workflow>
```
as you see, in the work flow we define two works(work1 & work2), each work is an independent procedure, they have no relation to each other.
in each work we define some plugins which are dynamic library(in the linux platform we call them so file). when the work1 run, it means the test and user plugin will run. when the work2 run, it means only the user plugin will run. in a work, the plugins will run sequentially to accomplish the work's job.

## How to write your plugin
plugin/UserPlugin.h
```c++
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
```
plugin/UserPlugin.cpp
```c++
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
```
## Holder: the flyweight design pattern
if you look into the details of the user plugin's `run` function, you may notice that the `run` function has a holder parameter. a holder is shared by all the plugins whthin the same work.one plugin can fetch the midway data which comes from the other plugin executed before.
in one plugin we can set the midway data like this:
```c++
holder.ref<string>("name") = "junping";
holder.set<int>("age", 30);
```
in another plugin we can get the midway data like this:
```c++
string & name = holder.ref<string>("name");
int age = holder.get<int>("age");
```
## How to run the work
```c++
#include <iostream>
#include <string>
#include <stdio.h>
using namespace std;

#include "System.h"
#include "Singleton.h"
using namespace yazi::utility;

#include "Workflow.h"
using namespace yazi::engine;

int main()
{
    System * sys = Singleton<System>::instance();
    sys->init();

    // initialize the work flow
    Workflow * workflow = Singleton<Workflow>::instance();
    workflow->load(sys->get_root_path() + "/workflow.xml");

    const string & input = "this is input";

    string output1;
    workflow->run("1", input, output1); // run the work 1
    printf("work1 output1: %s\n", output1.c_str());

    string output2;
    workflow->run("2", input, output2); // run the work 2
    printf("work2 output2: %s\n", output2.c_str());

    return 0;
}
```
you need to declare input & output before runing a work. the input & output will hold by the `holder`.in a plugin, you can acquire the input or output by the string reference:
```c++
string & input = holder.ref<string>("input");
string & output = holder.ref<string>("output");
```

## Compile & Run the project
download the source code, cd into the yazi-engine project working directory
### compile the plugin
```bash
cd ./yazi-engine
make plugin
```
### compile the main
```bash
cd ./yazi-engine
make
./main
```
