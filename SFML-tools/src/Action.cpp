#include "Action.h"

Action::Action()
{
}


Action::Action(sf::Keyboard::Key key, ActionType actionType)
{
    switch(actionType){
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


 Action& Action::operator=(  Action& rhs){
    m_linkedNode = std::move(rhs.m_linkedNode);
    return *this;
}

Action::Action (const Action& rhs) : m_linkedNode((rhs.m_linkedNode.get())){

}

 Action::Action(EventNode* nextEvent): m_linkedNode(nextEvent){
 }


Action Action::operator&& ( Action& lhs)
{
    EventNode* node = m_linkedNode.get();
    while(node){
        EventNode* n = node->getNode();
        if(n){
           node = n;
        }else{
            break;
        }
    }
    node->setNextNode(new RealtimeAndNode(lhs.m_linkedNode->getEvent(), NULL));
    Action m((std::move(m_linkedNode)));
	return m;
}

//Action Action::operator|| (const Action& lhs)
//{
//    EventNode* node = m_linkedNode.get();
//    while(node){
//        EventNode* n = node->getNode();
//        if(n){
//           node = n;
//        }else{
//            break;
//        }
//    }
//    EventNode* n1 = lhs.m_linkedNode.get();
//    node->setNextNode(new RealtimeOrNode(n1->getEvent(), lhs.m_linkedNode.get()) );
//	return Action(m_linkedNode.get());
//}


bool Action::isActionTriggered(std::vector<sf::Event>& events ){
    return  m_linkedNode->isEventTriggered(events);
}
