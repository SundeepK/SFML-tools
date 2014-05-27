#ifndef INPUTEVENTNODE_H
#define INPUTEVENTNODE_H

#include "EventNode.h"
#include "ActionNode.h"

class InputEventNode : public EventNode
{
public:
    InputEventNode(sf::Keyboard::Key event, std::unique_ptr<EventNode> nextNode);
    virtual ~InputEventNode();
    EventNode* getNode();
    void setNextNode(std::unique_ptr<EventNode> nextNode);
    sf::Keyboard::Key getEvent();

protected:
private:
    ActionNode<sf::Keyboard::Key> m_actionNode;
    std::unique_ptr<EventNode> m_nextNode;
};



#endif // INPUTEVENTNODE_H
