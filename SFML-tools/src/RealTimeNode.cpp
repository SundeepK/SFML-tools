#include "RealTimeNode.h"

RealTimeNode::RealTimeNode(sf::Keyboard::Key event, std::unique_ptr<EventNode> nextNode) : InputEventNode(event, std::move(nextNode))
{
}

RealTimeNode::~RealTimeNode()
{
}


bool RealTimeNode::isEventTriggered(std::vector<sf::Event>& keyboardEvents){
    return sf::Keyboard::isKeyPressed(getEvent());
}
