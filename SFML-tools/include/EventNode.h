#ifndef LOGICALNODE_H
#define LOGICALNODE_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <memory>

class EventNode
{
public:
    virtual bool isEventTriggered(std::vector<sf::Event>& keyboardEvents) = 0;
    virtual EventNode* getNode() = 0;
    virtual void setNextNode(std::unique_ptr<EventNode> nextNode) = 0;
    virtual sf::Keyboard::Key getEvent() = 0;
protected:
private:
};


#endif // LOGICALNODE_H
