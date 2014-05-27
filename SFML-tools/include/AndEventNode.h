#ifndef ANDEVENTNODE_H
#define ANDEVENTNODE_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <memory>
#include "InputEventNode.h"
#include "ActionNode.h"

class AndEventNode : public InputEventNode
{
    public:
        AndEventNode(sf::Keyboard::Key event, std::unique_ptr<EventNode> nextNode);
        virtual ~AndEventNode();
        bool isEventTriggered(std::vector<sf::Event>& keyboardEvents);
};

#endif // ANDEVENTNODE_H
