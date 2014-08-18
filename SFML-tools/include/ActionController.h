#ifndef EVENCONTROLLER_H
#define EVENCONTROLLER_H

#include <unordered_map>
#include "Action.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "TemplateHasher.h"


struct ActionToCallbacks
{
    Action m_action;
    std::vector<std::function<void(float dt)>> m_callbacks;
};

template <typename Key_type, typename Hasher_type = TemplateHasher<Key_type>>
class ActionController
{
public:
    ActionController();
    ActionController(ActionController&& source);
    Action& operator[] (const Key_type& actionKey);
    void addCallback(const Key_type& actionKey, std::function<void(float dt)> callback);
    ActionController& operator= (ActionController&& controller);

    void update(sf::RenderWindow& window);
    void triggerCallbacks(float dt);
protected:
private:
    std::unordered_map<const Key_type,  ActionToCallbacks, Hasher_type> m_keyToActions;
    std::vector<sf::Event> m_events;

};


template <typename Key_type, typename Hasher_type>
ActionController<Key_type, Hasher_type>::ActionController()
{
}

template <typename Key_type, typename Hasher_type>
ActionController<Key_type, Hasher_type>::ActionController(ActionController&& source)
    : m_events(std::move(source.m_events))
    , m_keyToActions(std::move(source.m_keyToActions))
{
}



template <typename Key_type, typename Hasher_type>
ActionController<Key_type, Hasher_type>& ActionController<Key_type, Hasher_type>::operator= (ActionController&& source)
{
    m_events = std::move(source.m_events);
    m_keyToActions = std::move(source.m_keyToActions);

    return *this;
}

template <typename Key_type, typename Hasher_type>
Action& ActionController<Key_type, Hasher_type>::operator[] (const Key_type& actionKey)
{
    ActionToCallbacks actionsToCallbacks = m_keyToActions[actionKey];
    if(m_keyToActions.find(actionKey) != m_keyToActions.end())
    {
        return m_keyToActions[actionKey].m_action;
    }
    else
    {
        ActionToCallbacks actCallbacks = {};
        m_keyToActions[actionKey] =  actCallbacks;
        return m_keyToActions[actionKey].m_action;
    }
}

template <typename Key_type, typename Hasher_type>
void ActionController<Key_type, Hasher_type>::addCallback(const Key_type& actionKey, std::function<void(float dt)> callback)
{
    if(m_keyToActions.find(actionKey) != m_keyToActions.end())
    {
        m_keyToActions[actionKey].m_callbacks.push_back(callback);
    }
}

template <typename Key_type, typename Hasher_type>
void ActionController<Key_type, Hasher_type>::update(sf::RenderWindow& window)
{
    m_events.clear();
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }

        switch (event.type)
        {
        case sf::Event::GainedFocus:
            break;

        case sf::Event::LostFocus:
            break;
        }

        m_events.push_back(event);
    }

}

template <typename Key_type, typename Hasher_type>
void ActionController<Key_type, Hasher_type>::triggerCallbacks(float dt)
{
    for ( auto actionItr = m_keyToActions.begin(); actionItr!= m_keyToActions.end(); ++actionItr )
    {
        if(actionItr->second.m_action.isActionTriggered(m_events))
        {
            auto callbacks = actionItr->second.m_callbacks;
            for(auto && fn : callbacks)
                fn(dt);
        }

    }
}
#endif // EVENCONTROLLER_H
