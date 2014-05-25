#include "Action.h"

Action::Action()
{
}


Action::Action(sf::Keyboard::Key key, ActionType actionType)
{

//    m_linkedNode.reset(new RealTimeNode(key, NULL));


    switch(actionType)
    {
    case RealTime:
        m_linkedNode.reset(new RealtimeAndNode(key, NULL));
        break;
    case Event:
        m_linkedNode.reset(new AndEventNode(key, NULL));
        break;
    }

}

Action::~Action()
{
    m_linkedNode.reset();
}

Action::Action(std::unique_ptr<EventNode> nextEvent): m_linkedNode(std::move(nextEvent))
{

}

Action& Action::operator=(  Action rhs)
{
    m_linkedNode = std::move(rhs.m_linkedNode);
    return *this;
}

Action::Action (const Action& rhs) : m_linkedNode((rhs.m_linkedNode.get()))
{

}

Action::Action(EventNode* nextEvent)
{
    m_linkedNode.reset(nextEvent);
}

Action Action::operator&& ( Action lhs)
{
    if( m_linkedNode->getNode())
    {
        EventNode* node = m_linkedNode.get();

        while(node)
        {
            EventNode* n = node->getNode();
            if(n)
            {
                node = n;
            }
            else
            {
                break;
            }
        }
        node->setNextNode(new RealtimeAndNode(lhs.m_linkedNode->getEvent(), NULL));
        return Action ((std::move(m_linkedNode)));
    }
    else
    {
        std::unique_ptr<EventNode> event(new RealtimeAndNode(m_linkedNode->getEvent(), NULL));
        event->setNextNode(new RealtimeAndNode(lhs.m_linkedNode->getEvent(), NULL));
        return Action ((std::move(event)));
    }
}

Action Action::operator|| (const Action& lhs)
{
    if( m_linkedNode->getNode())
    {
        EventNode* node = m_linkedNode.get();

        while(node)
        {
            EventNode* n = node->getNode();
            if(n)
            {
                node = n;
            }
            else
            {
                break;
            }
        }
        node->setNextNode(new RealtimeOrNode(lhs.m_linkedNode->getEvent(), NULL));
        return Action ((std::move(m_linkedNode)));
    }
    else
    {
        std::unique_ptr<EventNode> event(new RealtimeOrNode(m_linkedNode->getEvent(), NULL));
        event->setNextNode(new RealtimeOrNode(lhs.m_linkedNode->getEvent(), NULL));
        return Action ((std::move(event)));
    }
}


bool Action::isActionTriggered(std::vector<sf::Event>& events )
{
    return  m_linkedNode->isEventTriggered(events);
}
