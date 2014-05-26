#ifndef REALTIMENODE_H
#define REALTIMENODE_H

#include "EventNode.h"
#include "ActionNode.h"
#include <memory>

class RealTimeNode : public EventNode
{
    public:
        RealTimeNode(sf::Keyboard::Key event, std::unique_ptr<EventNode> nextNode);
        virtual ~RealTimeNode();
        EventNode* getNode();
        void setNextNode(std::unique_ptr<EventNode> nextNode);
        sf::Keyboard::Key getEvent();
        bool isEventTriggered(std::vector<sf::Event>& keyboardEvents);

    protected:
    private:
        ActionNode<sf::Keyboard::Key> m_actionNode;
        std::unique_ptr<EventNode> m_nextNode;
};

#endif // REALTIMENODE_H
