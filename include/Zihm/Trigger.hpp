////////////////////////////////////////////////////////////
//
// Zihm C++ library
// Copyright (C) 2011-2012 Pierre-E. Brian (zinlibs@gmail.com)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

#ifndef TRIGGER_HPP
#define TRIGGER_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include <functional>
#include <Zihm/Config.hpp>


namespace zin
{

class Widget;

enum class Hovering
{
    None,
    Over,
    Out
};

////////////////////////////////////////////////////////////
/// Trigger
////////////////////////////////////////////////////////////
class ZIHM_API Trigger
{
public :

    ////////////////////////////////////////////////////////////
    /// Default constructor
    ////////////////////////////////////////////////////////////
    Trigger() : m_owner(nullptr) {}

    ////////////////////////////////////////////////////////////
    /// Listen the specified event
    ////////////////////////////////////////////////////////////
    virtual void listen(const sf::Event& event) = 0;

    ////////////////////////////////////////////////////////////
    /// Declare a widget as owner
    ////////////////////////////////////////////////////////////
    void declareOwner(Widget& owner) { m_owner = &owner; }

protected :

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    std::function<void()> m_callback;
    Widget*               m_owner;
};

class ZIHM_API MouseOverTrigger : public Trigger
{
public :

    ////////////////////////////////////////////////////////////
    /// Default constructor
    ////////////////////////////////////////////////////////////
    MouseOverTrigger(std::function<void()> callback);

    ////////////////////////////////////////////////////////////
    /// Listen the specified event
    ////////////////////////////////////////////////////////////
    void listen(const sf::Event& event);

protected :

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    bool m_isOver;
};

class ZIHM_API MouseOutTrigger : public Trigger
{
public :

    ////////////////////////////////////////////////////////////
    /// Default constructor
    ////////////////////////////////////////////////////////////
    MouseOutTrigger(std::function<void()> callback);
    
    ////////////////////////////////////////////////////////////
    /// Listen the specified event
    ////////////////////////////////////////////////////////////
    void listen(const sf::Event& event);

protected :

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    bool m_isOut;
};

class ZIHM_API MouseButtonPressedTrigger : public Trigger
{
public :

    ////////////////////////////////////////////////////////////
    /// Default constructor
    ////////////////////////////////////////////////////////////
    MouseButtonPressedTrigger(std::function<void()> callback, sf::Mouse::Button button = sf::Mouse::Button::Left, Hovering hovering = Hovering::None);
    
    ////////////////////////////////////////////////////////////
    /// Listen the specified event
    ////////////////////////////////////////////////////////////
    void listen(const sf::Event& event);

protected :

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    Hovering          m_hovering;
    sf::Mouse::Button m_button;
};

class ZIHM_API MouseButtonReleasedTrigger : public Trigger
{
public :

    ////////////////////////////////////////////////////////////
    /// Default constructor
    ////////////////////////////////////////////////////////////
    MouseButtonReleasedTrigger(std::function<void()> callback, sf::Mouse::Button button = sf::Mouse::Button::Left, Hovering hovering = Hovering::None);
    
    ////////////////////////////////////////////////////////////
    /// Listen the specified event
    ////////////////////////////////////////////////////////////
    void listen(const sf::Event& event);

protected :

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    Hovering          m_hovering;
    sf::Mouse::Button m_button;
};

class ZIHM_API ClickTrigger : public Trigger
{
public :

    ////////////////////////////////////////////////////////////
    /// Default constructor
    ////////////////////////////////////////////////////////////
    ClickTrigger(std::function<void()> callback, sf::Mouse::Button button = sf::Mouse::Button::Left, Hovering hovering = Hovering::None);
    
    ////////////////////////////////////////////////////////////
    /// Listen the specified event
    ////////////////////////////////////////////////////////////
    void listen(const sf::Event& event);

protected :

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    Hovering           m_hovering;
    bool               m_isPressed;
    sf::Mouse::Button  m_button;
};

class ZIHM_API DoubleClickTrigger : public Trigger
{
public :

    ////////////////////////////////////////////////////////////
    /// Default constructor
    ////////////////////////////////////////////////////////////
    DoubleClickTrigger(std::function<void()> callback, Hovering hovering = Hovering::None);
    
    ////////////////////////////////////////////////////////////
    /// Listen the specified event
    ////////////////////////////////////////////////////////////
    void listen(const sf::Event& event);

protected :

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    Hovering           m_hovering;
    bool               m_isPressed;
    unsigned int       m_step;
};

class ZIHM_API TripleClickTrigger : public Trigger
{
public :

    ////////////////////////////////////////////////////////////
    /// Default constructor
    ////////////////////////////////////////////////////////////
    TripleClickTrigger(std::function<void()> callback, Hovering hovering = Hovering::None);
    
    ////////////////////////////////////////////////////////////
    /// Listen the specified event
    ////////////////////////////////////////////////////////////
    void listen(const sf::Event& event);

protected :

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    Hovering           m_hovering;
    bool               m_isPressed;
    unsigned int       m_step;
};

class ZIHM_API DragAndDropTrigger : public Trigger
{
public :

    ////////////////////////////////////////////////////////////
    /// Default constructor
    ////////////////////////////////////////////////////////////
    DragAndDropTrigger(std::function<void(float, float)> callback);
    
    ////////////////////////////////////////////////////////////
    /// Listen the specified event
    ////////////////////////////////////////////////////////////
    void listen(const sf::Event& event);

protected :

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    bool                              m_isPressed;
    bool                              m_isFirstMove;
    float                             m_x;
    float                             m_y;
    std::function<void(float, float)> m_callback2;
};

class ZIHM_API KeyPressedTrigger : public Trigger
{
public :

    ////////////////////////////////////////////////////////////
    /// Default constructor
    ////////////////////////////////////////////////////////////
    KeyPressedTrigger(std::function<void()> callback);
    
    ////////////////////////////////////////////////////////////
    /// Listen the specified event
    ////////////////////////////////////////////////////////////
    void listen(const sf::Event& event);
};

class ZIHM_API TextEnteredTrigger : public Trigger
{
public :

    ////////////////////////////////////////////////////////////
    /// Default constructor
    ////////////////////////////////////////////////////////////
    TextEnteredTrigger(std::function<void(char)> callback);
    
    ////////////////////////////////////////////////////////////
    /// Listen the specified event
    ////////////////////////////////////////////////////////////
    void listen(const sf::Event& event);

protected :

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    std::function<void(char)> m_callback2;
};

}

#endif // TRIGGER_HPP