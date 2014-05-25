#include "AndEventNode.h"
#include <functional>

AndEventNode::AndEventNode(sf::Keyboard::Key event, std::unique_ptr<EventNode> nextNode) : m_actionNode(event, std::move(nextNode))
{
}

AndEventNode::~AndEventNode()
{
}


EventNode* AndEventNode::getNode(){
    m_actionNode.getNextNode();
}

void AndEventNode::setNextNode(EventNode* nextNode){
    m_nextNode.reset(nextNode);
}

sf::Keyboard::Key AndEventNode::getEvent(){
    return m_actionNode.getEvent();
}


bool AndEventNode::isEventTriggered(std::vector<sf::Event>& keyboardEvents){

    bool found = std::find_if(keyboardEvents.begin(), keyboardEvents.end(), [this](const sf::Event& event) -> bool { return event.key.code == m_actionNode.getEvent();} ) != keyboardEvents.end();
    if(m_nextNode){
       return found && m_nextNode->isEventTriggered(keyboardEvents);
    }else{
        return found;
    }
}



