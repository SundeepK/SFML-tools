#ifndef OREVENTNODE_H
#define OREVENTNODE_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <memory>
#include "InputEventNode.h"
#include "ActionNode.h"

class OrEventNode: public InputEventNode
{
    public:
        OrEventNode(sf::Keyboard::Key event, std::unique_ptr<EventNode> nextNode);
        virtual ~OrEventNode();
        bool isEventTriggered(std::vector<sf::Event>& keyboardEvents);

};

#endif // OREVENTNODE_H
