#include "RealtimeOrNode.h"

RealtimeOrNode::RealtimeOrNode(sf::Keyboard::Key event, std::unique_ptr<EventNode> nextNode) : m_actionNode(event, std::move(nextNode))
{
}

RealtimeOrNode::~RealtimeOrNode()
{
}

EventNode* RealtimeOrNode::getNode(){
    m_actionNode.getNextNode();
}

void RealtimeOrNode::setNextNode(std::unique_ptr<EventNode> nextNode){
    m_nextNode = std::move(nextNode);
}

sf::Keyboard::Key RealtimeOrNode::getEvent(){
    return m_actionNode.getEvent();
}


bool RealtimeOrNode::isEventTriggered(std::vector<sf::Event>& keyboardEvents){
    bool eventTriggered =  sf::Keyboard::isKeyPressed(m_actionNode.getEvent());
    if(m_nextNode){
       return eventTriggered || m_nextNode->isEventTriggered(keyboardEvents);
    }else{
        return eventTriggered;
    }
}
