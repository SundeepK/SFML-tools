#include "OrEventNode.h"

OrEventNode::OrEventNode(sf::Keyboard::Key event, std::unique_ptr<EventNode> nextNode) : m_actionNode(event, std::move(nextNode))
{
}

OrEventNode::~OrEventNode()
{
}


EventNode* OrEventNode::getNode(){
    m_actionNode.getNextNode();
}

void OrEventNode::setNextNode(std::unique_ptr<EventNode> nextNode){
    m_nextNode = std::move(nextNode);
}

sf::Keyboard::Key OrEventNode::getEvent(){
    return m_actionNode.getEvent();
}

bool OrEventNode::isEventTriggered(std::vector<sf::Event>& keyboardEvents){

    bool found = std::find_if(keyboardEvents.begin(), keyboardEvents.end(), [this](const sf::Event& event) -> bool { return event.key.code == m_actionNode.getEvent();} ) != keyboardEvents.end();
    if(m_nextNode){
       return found || m_nextNode->isEventTriggered(keyboardEvents);
    }else{
        return found;
    }
}
