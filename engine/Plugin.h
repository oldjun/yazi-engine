#pragma once
#include <string>
using namespace std;

#include "Holder.h"

namespace yazi {
namespace engine {

class Plugin
{
public:
    Plugin() : m_name(""), m_switch(false) {}
    Plugin(const string & name, bool flag) : m_name(name), m_switch(flag) {}
    virtual ~Plugin() {}

    void set_name(const string & name) { m_name = name; }
    const string & get_name() const { return m_name; }

    void set_switch(bool flag) { m_switch = flag; }
    bool get_switch() const { return m_switch; }

    virtual bool run(Holder & holder) = 0;

protected:
    string m_name;
    bool m_switch;
};

}}
