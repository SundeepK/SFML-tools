#ifndef ACTION_H
#define ACTION_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "EventNode.h"
#include "InputNodes.h"
#include <memory>

enum ActionType
{
    RealTime,
    Event
};


class Action
{
public:
    Action();
    Action(sf::Keyboard::Key key, ActionType actionType = RealTime );
    virtual ~Action();
    Action operator&& ( Action lhs);
    Action& operator= ( Action rhs);
    Action (const Action& rhs);
    Action operator|| (const Action& lhs);
    bool isActionTriggered(std::vector<sf::Event>& events);
    Action(std::unique_ptr<EventNode> nextEvent);
    Action(EventNode* nextEvent);

protected:
private:
    std::unique_ptr<EventNode> getNewAndNode(sf::Keyboard::Key key, ActionType actionType);
    std::unique_ptr<EventNode> getNewOrNode(sf::Keyboard::Key key, ActionType actionType);
    void setNextNode(EventNode* node, std::unique_ptr<EventNode> eventToSet);
    Action newActionWithNextNode(std::unique_ptr<EventNode>  node);
    Action applyOperator(std::unique_ptr<EventNode> event,std::unique_ptr<EventNode> nextNode);


    ActionType m_actionType;
    std::unique_ptr<EventNode> m_linkedNode;
};

#endif // ACTION_H
