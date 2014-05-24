#ifndef OREVENTNODE_H
#define OREVENTNODE_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <memory>
#include "EventNode.h"
#include "ActionNode.h"

class OrEventNode: public EventNode
{
    public:
        OrEventNode(sf::Keyboard::Key event, std::unique_ptr<EventNode> nextNode);
        virtual ~OrEventNode();
        EventNode* getNode();
        void setNextNode(std::unique_ptr<EventNode> nextNode);
        sf::Keyboard::Key getEvent();
        bool isEventTriggered(std::vector<sf::Event>& keyboardEvents);

    protected:
    private:
        ActionNode<sf::Keyboard::Key> m_actionNode;
        std::unique_ptr<EventNode> m_nextNode;
};

#endif // OREVENTNODE_H
