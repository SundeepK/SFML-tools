#ifndef EVENCONTROLLER_H
#define EVENCONTROLLER_H

#include <unordered_map>
#include "Action.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "TemplateHasher.h"



template <typename Key_type, typename Hasher_type = TemplateHasher<Key_type>, typename... Arguments>
class ActionController
{

	struct ActionToCallbacks
	{
	    Action m_action;
	    std::vector<std::function<void(float dt, Arguments...)>> m_callbacks;
	};

public:
    ActionController();
    ActionController(ActionController&& source);
    Action& operator[] (const Key_type& actionKey);
    void addCallback(const Key_type& actionKey, std::function<void(float dt, Arguments...)> callback);
    ActionController& operator= (ActionController&& controller);

    void update(sf::RenderWindow& window);
    void update(std::vector<sf::Event> events);
    void triggerCallbacks(float dt, Arguments...);
    void triggerCallbacks(sf::RenderWindow& window, float dt, Arguments...);

protected:
private:
    std::unordered_map<const Key_type,  ActionToCallbacks, Hasher_type> m_keyToActions;
    std::unordered_map<const Key_type,  ActionToCallbacks, Hasher_type> m_keyToReleasedActions;

    std::vector<sf::Event> m_events;
    std::vector<sf::Event> m_releasedEvents;

};


template <typename Key_type, typename Hasher_type, typename... Arguments>
ActionController<Key_type, Hasher_type, Arguments...>::ActionController()
{
}

template <typename Key_type, typename Hasher_type, typename... Arguments>
ActionController<Key_type, Hasher_type, Arguments...>::ActionController(ActionController&& source)
    : m_events(std::move(source.m_events))
    , m_keyToActions(std::move(source.m_keyToActions))
{
}



template <typename Key_type, typename Hasher_type, typename... Arguments>
ActionController<Key_type, Hasher_type, Arguments...>& ActionController<Key_type, Hasher_type, Arguments...>::operator= (ActionController&& source)
{
    m_events = std::move(source.m_events);
    m_keyToActions = std::move(source.m_keyToActions);

    return *this;
}

template <typename Key_type, typename Hasher_type, typename... Arguments>
Action& ActionController<Key_type, Hasher_type, Arguments...>::operator[] (const Key_type& actionKey)
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

template <typename Key_type, typename Hasher_type, typename... Arguments>
void ActionController<Key_type, Hasher_type, Arguments... >::addCallback(const Key_type& actionKey, std::function<void(float dt, Arguments... args)> callback)
{
    if(m_keyToActions.find(actionKey) != m_keyToActions.end())
    {
        m_keyToActions[actionKey].m_callbacks.push_back(callback);
    }
}

template <typename Key_type, typename Hasher_type, typename... Arguments>
void ActionController<Key_type, Hasher_type,  Arguments... >::update(sf::RenderWindow& window)
{
    m_events.clear();
    m_releasedEvents.clear();
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

        if (event.type == sf::Event::KeyPressed)
            m_events.push_back(event);

        if (event.type == sf::Event::KeyReleased)
            m_releasedEvents.push_back(event);

    }

}


template <typename Key_type, typename Hasher_type, typename... Arguments>
void ActionController<Key_type, Hasher_type,  Arguments... >::update(std::vector<sf::Event> events)
{
    m_events.clear();
    m_releasedEvents.clear();
    for(sf::Event event: events)
    {
        switch (event.type)
        {
        case sf::Event::GainedFocus:
            break;

        case sf::Event::LostFocus:
            break;
        }

        if (event.type == sf::Event::KeyPressed)
            m_events.push_back(event);

        if (event.type == sf::Event::KeyReleased)
            m_releasedEvents.push_back(event);

    }
}

template <typename Key_type, typename Hasher_type, typename... Arguments>
void ActionController<Key_type, Hasher_type, Arguments... >::triggerCallbacks(float dt, Arguments... args)
{
    for ( auto actionItr = m_keyToActions.begin(); actionItr!= m_keyToActions.end(); ++actionItr )
    {
        if(actionItr->second.m_action.isActionTriggered(m_events))
        {
            auto callbacks = actionItr->second.m_callbacks;
            for(auto && fn : callbacks)
                fn(dt, args...);
        }
    }

}

template <typename Key_type, typename Hasher_type, typename... Arguments>
void ActionController<Key_type, Hasher_type, Arguments... >::triggerCallbacks(sf::RenderWindow& window, float dt, Arguments... args)
{
		for (auto actionItr = m_keyToActions.begin(); actionItr != m_keyToActions.end(); ++actionItr) {
			if (actionItr->second.m_action.getActionType() == ActionType::Released) {
				if (actionItr->second.m_action.isActionTriggered(m_releasedEvents)) {
					auto callbacks = actionItr->second.m_callbacks;
					for (auto && fn : callbacks)
						fn(dt, args...);
					break;
				}
			}
	}

}
#endif // EVENCONTROLLER_H
