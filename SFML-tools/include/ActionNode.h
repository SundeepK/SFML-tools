#ifndef ACTIONNODE_H
#define ACTIONNODE_H

#include "EventNode.h"

template <typename Event_type>
class ActionNode
{
    public:
        ActionNode();

        ActionNode(Event_type action, std::unique_ptr<EventNode> event);
        EventNode* getNextNode();
        Event_type getEvent();
        ActionNode ( ActionNode& rhs);

        ActionNode& operator= ( ActionNode rhs);

    protected:
    private:
        Event_type m_action;
        std::unique_ptr<EventNode> m_nextNode;

};

template <typename Event_type>
ActionNode<Event_type>::ActionNode()
{
}


template <typename Event_type>
ActionNode<Event_type>::ActionNode ( ActionNode<Event_type>& rhs) : m_action(rhs.m_action),  m_nextNode(std::move(rhs.m_nextNode))
{

}

template <typename Event_type>
ActionNode<Event_type>& ActionNode<Event_type>::operator=(  ActionNode<Event_type> rhs)
{
    m_nextNode = std::move(rhs.m_nextNode);
    m_action = rhs.m_action;
    return *this;
}

template <typename Event_type>
ActionNode<Event_type>::ActionNode(Event_type action, std::unique_ptr<EventNode> event) : m_action(action), m_nextNode(std::move(event))
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
