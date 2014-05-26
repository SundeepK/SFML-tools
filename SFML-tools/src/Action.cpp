#include "Action.h"

Action::Action()
{
}


Action::Action(sf::Keyboard::Key key, ActionType actionType) : m_actionType(actionType)
{
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

Action Action::operator&& ( Action lhs){
    Action andedAction;
    if( m_linkedNode->getNode()){
        setNextNode(m_linkedNode.get(), new RealtimeAndNode(lhs.m_linkedNode->getEvent(), NULL));
        andedAction = Action ((std::move(m_linkedNode)));
    }else{
        std::unique_ptr<EventNode> event = getNewAndNode(m_linkedNode->getEvent(), m_actionType);
        event->setNextNode(new RealtimeAndNode(lhs.m_linkedNode->getEvent(), NULL));
        andedAction = Action ((std::move(event)));
    }
    return andedAction;
}

void Action::setNextNode(EventNode* node, EventNode* nodeToSet){
    while(node){
        EventNode* n = node->getNode();
        if(n){
            node = n;
        }else{
            break;
        }
    }
    node->setNextNode(nodeToSet);
}

std::unique_ptr<EventNode> Action::getNewAndNode(sf::Keyboard::Key key, ActionType actionType){
    std::unique_ptr<EventNode> event;
    switch(actionType)
    {
    case RealTime:
        event.reset(new RealtimeAndNode(key, NULL));
        break;
    case Event:
        event.reset(new AndEventNode(key, NULL));
        break;
    }
    return event;
}


std::unique_ptr<EventNode> Action::getNewOrNode(sf::Keyboard::Key key, ActionType actionType)
{
    std::unique_ptr<EventNode> event;
    switch(actionType)
    {
    case RealTime:
        event.reset(new RealtimeOrNode(key, NULL));
        break;
    case Event:
        event.reset(new OrEventNode(key, NULL));
        break;
    }
    return event;
}

Action Action::operator|| (const Action& lhs)
{
    Action andedAction;
    RealtimeOrNode node(lhs.m_linkedNode->getEvent(), NULL);
    if( m_linkedNode->getNode()){
        andedAction = newActionWithNextNode(&node);
    }else{
        std::unique_ptr<EventNode> event = getNewOrNode(m_linkedNode->getEvent(), m_actionType);
        event->setNextNode(new RealtimeOrNode(lhs.m_linkedNode->getEvent(), NULL));
        andedAction = Action ((std::move(event)));
    }
    return andedAction;
}

Action Action::newActionWithNextNode(EventNode* node){
      setNextNode(m_linkedNode.get(), node);
      return Action ((std::move(m_linkedNode)));
}

bool Action::isActionTriggered(std::vector<sf::Event>& events )
{
    return  m_linkedNode->isEventTriggered(events);
}
