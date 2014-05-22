#ifndef ACTIONNODE_H
#define ACTIONNODE_H

#include "EventNode.h"

template <typename Event_type>
class ActionNode
{
    public:
        ActionNode(Event_type action, EventNode* event);
        EventNode* getNextNode();
        Event_type getEvent();
    protected:
    private:
        Event_type m_action;
        std::shared_ptr<EventNode> m_nextNode;

};

template <typename Event_type>
ActionNode<Event_type>::ActionNode(Event_type action, EventNode* event) : m_action(action), m_nextNode(event)
{

}

template <typename Event_type>
EventNode* ActionNode<Event_type>::getNextNode(){
    if(m_nextNode){
        return m_nextNode.get();
    }else{
    return NULL;
    }
}

template <typename Event_type>
Event_type ActionNode<Event_type>::getEvent(){
    return m_action;
}

#endif // ACTIONNODE_H