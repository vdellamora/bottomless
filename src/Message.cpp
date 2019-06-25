#include "../include/Message.h"

Message::Message(Event& associated, std::string text) : Action(associated){
	this->text = text;
	this->done = false;
}
Message::~Message(){}
void Message::Execute(){
	//Criar texto
	//Exibir texto
	//Esperar botão pra encerrar texto
	done = true;
}
bool Message::GetDone(){return done;}
bool Message::Is(std::string type){return type == "Message";}