#include "RealTimeNode.h"

RealtimeAndNode::RealtimeAndNode(sf::Keyboard::Key event, std::unique_ptr<EventNode> nextNode) : InputEventNode(event, std::move(nextNode))
{
}

RealtimeAndNode::~RealtimeAndNode()
{
}

bool RealtimeAndNode::isEventTriggered(std::vector<sf::Event>& keyboardEvents){
    bool eventTriggered =  sf::Keyboard::isKeyPressed(getEvent());
    if(getNode()){
       return eventTriggered && getNode()->isEventTriggered(keyboardEvents);
    }else{
        return eventTriggered;
    }
}
