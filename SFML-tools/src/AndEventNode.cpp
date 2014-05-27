#include "AndEventNode.h"
#include <functional>

AndEventNode::AndEventNode(sf::Keyboard::Key event, std::unique_ptr<EventNode> nextNode) : InputEventNode(event, std::move(nextNode))
{
}

AndEventNode::~AndEventNode()
{
}

bool AndEventNode::isEventTriggered(std::vector<sf::Event>& keyboardEvents){

    bool found = std::find_if(keyboardEvents.begin(), keyboardEvents.end(), [this](const sf::Event& event) -> bool { return event.key.code == getEvent();} ) != keyboardEvents.end();
    if(getNode()){
       return found && getNode()->isEventTriggered(keyboardEvents);
    }else{
        return found;
    }
}



