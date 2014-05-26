#include "RealTimeNode.h"

RealTimeNode::RealTimeNode(sf::Keyboard::Key event, std::unique_ptr<EventNode> nextNode) : m_actionNode(event, std::move(nextNode))
{
}

RealTimeNode::~RealTimeNode()
{
}

EventNode* RealTimeNode::getNode(){
    m_actionNode.getNextNode();
}

void RealTimeNode::setNextNode(std::unique_ptr<EventNode> nextNode){
    m_nextNode = std::move(nextNode);
}
sf::Keyboard::Key RealTimeNode::getEvent(){
    return m_actionNode.getEvent();
}


bool RealTimeNode::isEventTriggered(std::vector<sf::Event>& keyboardEvents){
    return sf::Keyboard::isKeyPressed(m_actionNode.getEvent());
}
