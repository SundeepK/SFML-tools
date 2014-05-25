#ifndef REALTIMEANDNODE_H
#define REALTIMEANDNODE_H

#include "EventNode.h"
#include "ActionNode.h"
#include <memory>

class RealtimeAndNode : public EventNode
{
    public:
        RealtimeAndNode(sf::Keyboard::Key event, std::unique_ptr<EventNode> nextNode);
        virtual ~RealtimeAndNode();
        EventNode* getNode();
        void setNextNode(EventNode* nextNode);
        sf::Keyboard::Key getEvent();
        bool isEventTriggered(std::vector<sf::Event>& keyboardEvents);

    protected:
    private:
        ActionNode<sf::Keyboard::Key> m_actionNode;
        std::unique_ptr<EventNode> m_nextNode;

};

#endif // REALTIMEANDNODE_H
