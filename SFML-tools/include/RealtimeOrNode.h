#ifndef REALTIMEORNODE_H
#define REALTIMEORNODE_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <memory>
#include "RealTimeNode.h"
#include "ActionNode.h"

class RealtimeOrNode : public RealTimeNode
{
    public:
        RealtimeOrNode(sf::Keyboard::Key event, std::unique_ptr<EventNode> nextNode);
        virtual ~RealtimeOrNode();
        bool isEventTriggered(std::vector<sf::Event>& keyboardEvents);

    protected:
    private:

};

#endif // REALTIMEORNODE_H
