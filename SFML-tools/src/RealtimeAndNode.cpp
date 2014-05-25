#include "RealtimeAndNode.h"

RealtimeAndNode::RealtimeAndNode(sf::Keyboard::Key event, std::unique_ptr<EventNode> nextNode) : m_actionNode(event, std::move(nextNode))
{
}

RealtimeAndNode::~RealtimeAndNode()
{
}

EventNode* RealtimeAndNode::getNode(){
  return   m_nextNode.get();
}

void RealtimeAndNode::setNextNode(EventNode* nextNode){
    m_nextNode.reset(nextNode);
}

sf::Keyboard::Key RealtimeAndNode::getEvent(){
    return m_actionNode.getEvent();
}

bool RealtimeAndNode::isEventTriggered(std::vector<sf::Event>& keyboardEvents){
    bool eventTriggered =  sf::Keyboard::isKeyPressed(m_actionNode.getEvent());
    if(m_nextNode){
       return eventTriggered && m_nextNode->isEventTriggered(keyboardEvents);
    }else{
        return eventTriggered;
    }
}
