#ifndef RevertCarang_h
#define RevertCarang_h

#include <stdio.h>
#include "inclusao.h"
#include "Event.h"
#include "Component.h"
#include "Action.h"
#include <iostream>
#include <string>

class Event;
class RevertCarang : public Action{
    
public:
    RevertCarang(Event&);
    ~RevertCarang();
    void Execute();
    bool Is(std::string);
private:
    std::string name;
    int frameCount;
};


#endif /* RevertCarang_hpp */
