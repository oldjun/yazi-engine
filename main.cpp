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
