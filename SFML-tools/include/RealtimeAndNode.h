#ifndef REALTIMEANDNODE_H
#define REALTIMEANDNODE_H

#include "EventNode.h"
#include "ActionNode.h"

class RealtimeAndNode : public EventNode
{
    public:
        RealtimeAndNode(sf::Keyboard::Key event, EventNode* nextNode);
        virtual ~RealtimeAndNode();
        EventNode* getNode();
        void setNextNode(EventNode* nextNode);
        bool isEventTriggered(std::vector<sf::Event>& keyboardEvents);

    protected:
    private:
        ActionNode<sf::Keyboard::Key> m_actionNode;
        std::shared_ptr<EventNode> m_nextNode;

};

#endif // REALTIMEANDNODE_H
