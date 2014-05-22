#include "RealtimeAndNode.h"

RealtimeAndNode::RealtimeAndNode(sf::Keyboard::Key event, EventNode* nextNode) : m_actionNode(event, nextNode)
{
}

RealtimeAndNode::~RealtimeAndNode()
{
}

EventNode* RealtimeAndNode::getNode(){
    m_actionNode.getNextNode();
}

void RealtimeAndNode::setNextNode(EventNode* nextNode){
    m_nextNode.reset(nextNode);
}

bool RealtimeAndNode::isEventTriggered(std::vector<sf::Event>& keyboardEvents){
    bool eventTriggered =  sf::Keyboard::isKeyPressed(m_actionNode.getEvent());
    if(m_nextNode){
       return eventTriggered && m_nextNode->isEventTriggered(keyboardEvents);
    }else{
        return eventTriggered;
    }
}
