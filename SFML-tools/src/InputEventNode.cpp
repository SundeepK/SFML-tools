#include "InputEventNode.h"

InputEventNode::InputEventNode(sf::Keyboard::Key event, std::unique_ptr<EventNode> nextNode) : m_actionNode(event, std::move(nextNode))
{
}

InputEventNode::~InputEventNode()
{
}

EventNode* InputEventNode::getNode(){
  return   m_actionNode.getNextNode();
}

void InputEventNode::setNextNode(std::unique_ptr<EventNode> nextNode){
     ActionNode<sf::Keyboard::Key> a (m_actionNode.getEvent(),std::move(nextNode));
    m_actionNode = a;
}

sf::Keyboard::Key InputEventNode::getEvent(){
    return m_actionNode.getEvent();
}

