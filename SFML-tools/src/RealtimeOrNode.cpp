#include "RealtimeOrNode.h"

RealtimeOrNode::RealtimeOrNode(sf::Keyboard::Key event, std::unique_ptr<EventNode> nextNode) : m_actionNode(event, std::move(nextNode))
{
}

RealtimeOrNode::~RealtimeOrNode()
{
}

EventNode* RealtimeOrNode::getNode(){
  return   m_actionNode.getNextNode();
}

void RealtimeOrNode::setNextNode(std::unique_ptr<EventNode> nextNode){
     ActionNode<sf::Keyboard::Key> a (m_actionNode.getEvent(),std::move(nextNode));
    m_actionNode = a;
}

sf::Keyboard::Key RealtimeOrNode::getEvent(){
    return m_actionNode.getEvent();
}


bool RealtimeOrNode::isEventTriggered(std::vector<sf::Event>& keyboardEvents){
    bool eventTriggered =  sf::Keyboard::isKeyPressed(m_actionNode.getEvent());
    if(m_actionNode.getNextNode()){
       return eventTriggered ||  m_actionNode.getNextNode()->isEventTriggered(keyboardEvents);
    }else{
        return eventTriggered;
    }
}
