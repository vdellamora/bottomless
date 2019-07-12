#include "../include/RevertCarang.h"

RevertCarang::RevertCarang(Event& associated): Action(associated){
    started = false;
    done = false;
}

RevertCarang::~RevertCarang(){
    
}

void RevertCarang::Execute(){
    Sprite* s = (Sprite*) associated.GetAssociated().GetComponent("Sprite");
    if (s){
        if (s->Finished()){
            started = true;
            s->NewSprite("assets/img/caranguejao.png",20, 0.2f);
            s->SetLoops(true);
            done = true;
        } else {
            TRACE("porra");
        }
    } else {
        
        started = true;
        done = true;
    }
}
bool RevertCarang::Is(std::string name){
    return name == "RevertCarang";
}
