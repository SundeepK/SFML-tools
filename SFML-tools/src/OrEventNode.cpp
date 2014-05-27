#include "OrEventNode.h"

OrEventNode::OrEventNode(sf::Keyboard::Key event, std::unique_ptr<EventNode> nextNode) : InputEventNode(event, std::move(nextNode))
{
}

OrEventNode::~OrEventNode()
{
}

bool OrEventNode::isEventTriggered(std::vector<sf::Event>& keyboardEvents){

    bool found = std::find_if(keyboardEvents.begin(), keyboardEvents.end(), [this](const sf::Event& event) -> bool { return event.key.code == getEvent();} ) != keyboardEvents.end();
    if(getNode()){
       return found || getNode()->isEventTriggered(keyboardEvents);
    }else{
        return found;
    }
}
