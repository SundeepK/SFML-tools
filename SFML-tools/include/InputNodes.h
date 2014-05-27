#ifndef REALTIMENODE_H
#define REALTIMENODE_H

#include "EventNode.h"
#include <memory>
#include "InputEventNode.h"
#include "EventNode.h"


class RealTimeNode : public InputEventNode
{
    public:
        RealTimeNode(sf::Keyboard::Key event, std::unique_ptr<EventNode> nextNode);
        virtual ~RealTimeNode();
        bool isEventTriggered(std::vector<sf::Event>& keyboardEvents);
};

class RealtimeOrNode : public InputEventNode
{
    public:
        RealtimeOrNode(sf::Keyboard::Key event, std::unique_ptr<EventNode> nextNode);
        virtual ~RealtimeOrNode();
        bool isEventTriggered(std::vector<sf::Event>& keyboardEvents);

};

class RealtimeAndNode : public InputEventNode
{
    public:
        RealtimeAndNode(sf::Keyboard::Key event, std::unique_ptr<EventNode> nextNode);
        virtual ~RealtimeAndNode();
        bool isEventTriggered(std::vector<sf::Event>& keyboardEvents);

};

class AndEventNode : public InputEventNode
{
    public:
        AndEventNode(sf::Keyboard::Key event, std::unique_ptr<EventNode> nextNode);
        virtual ~AndEventNode();
        bool isEventTriggered(std::vector<sf::Event>& keyboardEvents);
};

class OrEventNode: public InputEventNode
{
    public:
        OrEventNode(sf::Keyboard::Key event, std::unique_ptr<EventNode> nextNode);
        virtual ~OrEventNode();
        bool isEventTriggered(std::vector<sf::Event>& keyboardEvents);

};

#endif // REALTIMENODE_H
