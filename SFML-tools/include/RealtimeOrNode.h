#ifndef REALTIMEORNODE_H
#define REALTIMEORNODE_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <memory>
#include "EventNode.h"
#include "ActionNode.h"

class RealtimeOrNode : public EventNode
{
    public:
        RealtimeOrNode(sf::Keyboard::Key event, std::unique_ptr<EventNode> nextNode);
        virtual ~RealtimeOrNode();
        EventNode* getNode();
        void setNextNode(std::unique_ptr<EventNode> nextNode);
        sf::Keyboard::Key getEvent();
        bool isEventTriggered(std::vector<sf::Event>& keyboardEvents);

    protected:
    private:
        ActionNode<sf::Keyboard::Key> m_actionNode;
        std::unique_ptr<EventNode> m_nextNode;
};

#endif // REALTIMEORNODE_H
