#include <iostream>
#include <string>
#include <stdexcept>
#include <stdio.h>
#include <sys/resource.h>
#include <time.h>
#include <errno.h>
using namespace std;

#include "Logger.h"
#include "IniFile.h"
#include "Singleton.h"
using namespace yazi::utility;

#include "Workflow.h"
using namespace yazi::engine;

string get_root_path()
{
    char path[1024];
    memset(path, 0, 1024);
    int cnt = readlink("/proc/self/exe", path, 1024);
    if (cnt < 0 || cnt >= 1024)
    {
        return "";
    }
    for (int i = cnt; i >= 0; --i)
    {
        if (path[i] == '/')
        {
            path[i] = '\0';
            break;
        }
    }
    return string(path);
}

int main()
{
    // get the program's root path
    string root_path = get_root_path();

    // initialize the global logger
    Logger::instance()->open(root_path + "/main.log");

    // initialize the ini file
    IniFile * conf = Singleton<IniFile>::instance();
    conf->load(root_path + "/main.ini");
    conf->set("root", "path", root_path);

    // initialize the work flow
    Workflow * workflow = Singleton<Workflow>::instance();
    workflow->load(root_path + "/workflow.xml");

    const string & input = "this is input";

    string output1;
    workflow->run("1", input, output1); // run the work 1
    printf("work1 output1: %s\n", output1.c_str());

    string output2;
    workflow->run("2", input, output2); // run the work 2
    printf("work2 output2: %s\n", output2.c_str());

    return 0;
}
