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
                   std::unique_ptr<EventNode> node(new RealtimeAndNode (lhs.m_linkedNode->getEvent(), NULL));

        setNextNode(m_linkedNode.get(), std::move(node));
        andedAction = Action ((std::move(m_linkedNode)));
    }else{
        std::unique_ptr<EventNode> event = getNewAndNode(m_linkedNode->getEvent(), m_actionType);
           std::unique_ptr<EventNode> node(new RealtimeAndNode (lhs.m_linkedNode->getEvent(), NULL));

        event->setNextNode(std::move(node));
        andedAction = Action ((std::move(event)));
    }
    return andedAction;
}

void Action::setNextNode(EventNode* node, std::unique_ptr<EventNode> nodeToSet){
    while(node){
        EventNode* n = node->getNode();
        if(n){
            node = n;
        }else{
            break;
        }
    }
    node->setNextNode(std::move(nodeToSet));
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
   std::unique_ptr<EventNode> node(new RealtimeAndNode (lhs.m_linkedNode->getEvent(), NULL));
    return applyOperator(std::move(node));
}

Action Action::applyOperator(std::unique_ptr<EventNode> nextNode){
    Action andedAction;
    if( m_linkedNode->getNode()){
        andedAction = newActionWithNextNode(std::move(nextNode));
    }else{
        std::unique_ptr<EventNode> event = getNewOrNode(m_linkedNode->getEvent(), m_actionType);
        event->setNextNode(std::move(nextNode));
        andedAction = Action ((std::move(event)));
    }
    return andedAction;
}

Action Action::newActionWithNextNode(std::unique_ptr<EventNode>  node){
      setNextNode(m_linkedNode.get(), std::move(node));
      return Action ((std::move(m_linkedNode)));
}

bool Action::isActionTriggered(std::vector<sf::Event>& events )
{
    return  m_linkedNode->isEventTriggered(events);
}
