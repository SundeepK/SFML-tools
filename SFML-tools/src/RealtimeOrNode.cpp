#include "RealTimeNode.h"

RealtimeOrNode::RealtimeOrNode(sf::Keyboard::Key event, std::unique_ptr<EventNode> nextNode) : InputEventNode(event, std::move(nextNode))
{
}

RealtimeOrNode::~RealtimeOrNode()
{
}

bool RealtimeOrNode::isEventTriggered(std::vector<sf::Event>& keyboardEvents){
    bool eventTriggered =  sf::Keyboard::isKeyPressed(getEvent());
    if(getNode()){
       return eventTriggered ||  getNode()->isEventTriggered(keyboardEvents);
    }else{
        return eventTriggered;
    }
}
