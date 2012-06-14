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

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <Zihm/Trigger.hpp>
#include <Zihm/Widget.hpp>
#include <iostream>


namespace zin
{

////////////////////////////////////////////////////////////
MouseOverTrigger::MouseOverTrigger(std::function<void()> callback) :
m_isOver(false)
{
    m_callback = callback;
}

////////////////////////////////////////////////////////////
void MouseOverTrigger::listen(const sf::Event& event)
{
    if( m_owner )
    {
        if( event.type == sf::Event::MouseMoved )
        {
            if( !m_isOver )
            {
                if( m_owner->contains(event.mouseMove.x, event.mouseMove.y) )
                {
                    m_isOver = true;
                    m_callback();
                }
            }

            else
            {
                if( !m_owner->contains(event.mouseMove.x, event.mouseMove.y) )
                    m_isOver = false;
            }
        }
    }
}

////////////////////////////////////////////////////////////
MouseOutTrigger::MouseOutTrigger(std::function<void()> callback) :
m_isOut(false)
{
    m_callback = callback;
}

////////////////////////////////////////////////////////////
void MouseOutTrigger::listen(const sf::Event& event)
{
    if( m_owner )
    {
        if( event.type == sf::Event::MouseMoved )
        {
            if( !m_isOut )
            {
                if( !m_owner->contains(event.mouseMove.x, event.mouseMove.y) )
                {
                    m_isOut = true;
                    m_callback();
                }
            }

            else
            {
                if( m_owner->contains(event.mouseMove.x, event.mouseMove.y) )
                    m_isOut = false;
            }
        }
    }
}

////////////////////////////////////////////////////////////
MouseButtonPressedTrigger::MouseButtonPressedTrigger(std::function<void()> callback, sf::Mouse::Button button, Hovering hovering) :
m_hovering(hovering),
m_button(button)
{
    m_callback = callback;
}

////////////////////////////////////////////////////////////
void MouseButtonPressedTrigger::listen(const sf::Event& event)
{
    if( event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == m_button )
    {
        if( m_hovering == Hovering::Over )
        {
            if( m_owner )
                if( m_owner->contains(event.mouseButton.x, event.mouseButton.y) )
                    m_callback();
        }

        else if( m_hovering == Hovering::Out )
        {
            if( m_owner )
                if( !m_owner->contains(event.mouseButton.x, event.mouseButton.y) )
                    m_callback();
        }

        else m_callback();
    }
}

////////////////////////////////////////////////////////////
MouseButtonReleasedTrigger::MouseButtonReleasedTrigger(std::function<void()> callback, sf::Mouse::Button button, Hovering hovering) :
m_hovering(hovering),
m_button(button)
{
    m_callback = callback;
}

////////////////////////////////////////////////////////////
void MouseButtonReleasedTrigger::listen(const sf::Event& event)
{
    if( event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == m_button )
    {
        if( m_hovering == Hovering::Over )
        {
            if( m_owner )
                if( m_owner->contains(event.mouseButton.x, event.mouseButton.y) )
                    m_callback();
        }

        else if( m_hovering == Hovering::Out )
        {
            if( m_owner )
                if( !m_owner->contains(event.mouseButton.x, event.mouseButton.y) )
                    m_callback();
        }

        else m_callback();
    }
}

////////////////////////////////////////////////////////////
ClickTrigger::ClickTrigger(std::function<void()> callback, sf::Mouse::Button button, Hovering hovering) :
m_hovering(hovering),
m_isPressed(false),
m_button(button)
{
    m_callback = callback;
}

////////////////////////////////////////////////////////////
void ClickTrigger::listen(const sf::Event& event)
{
    if( event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == m_button )
    {
        if( !m_isPressed )
        {
            if( m_hovering == Hovering::Over )
            {
                if( m_owner )
                    if( m_owner->contains(event.mouseButton.x, event.mouseButton.y) )
                        m_isPressed = true;
            }

            else if( m_hovering == Hovering::Out )
            {
                if( m_owner )
                    if( !m_owner->contains(event.mouseButton.x, event.mouseButton.y) )
                        m_isPressed = true;
            }

            else m_isPressed = true;
        }
    }

    else if( event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == m_button )
        if( m_isPressed )
        {
            m_isPressed = false;
            m_callback();
        }
}

////////////////////////////////////////////////////////////
DoubleClickTrigger::DoubleClickTrigger(std::function<void()> callback, Hovering hovering) :
m_hovering(hovering),
m_isPressed(false),
m_step(0)
{
    m_callback = callback;
}

////////////////////////////////////////////////////////////
void DoubleClickTrigger::listen(const sf::Event& event)
{
    if( event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Button::Left )
    {
        if( m_hovering == Hovering::Over )
        {
            if( m_owner )
                if( m_owner->contains(event.mouseButton.x, event.mouseButton.y) )
                    m_isPressed = true;
        }

        else if( m_hovering == Hovering::Out )
        {
            if( m_owner )
                if( !m_owner->contains(event.mouseButton.x, event.mouseButton.y) )
                    m_isPressed = true;
        }

        else m_isPressed = true;
    }

    else if( event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Button::Left )
        if( m_isPressed )
        {
            m_isPressed = false;

            m_step++;
                
            if( m_step == 2 )
            {
                m_step = 0;
                m_callback();
            }
        }
}

////////////////////////////////////////////////////////////
TripleClickTrigger::TripleClickTrigger(std::function<void()> callback, Hovering hovering) :
m_hovering(hovering),
m_isPressed(false),
m_step(0)
{
    m_callback = callback;
}

////////////////////////////////////////////////////////////
void TripleClickTrigger::listen(const sf::Event& event)
{
    if( event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Button::Left )
    {
        if( m_hovering == Hovering::Over )
        {
            if( m_owner )
                if( m_owner->contains(event.mouseButton.x, event.mouseButton.y) )
                    m_isPressed = true;
        }

        else if( m_hovering == Hovering::Out )
        {
            if( m_owner )
                if( !m_owner->contains(event.mouseButton.x, event.mouseButton.y) )
                    m_isPressed = true;
        }

        else m_isPressed = true;
    }

    else if( event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Button::Left )
        if( m_isPressed )
        {
            m_isPressed = false;

            m_step++;
                
            if( m_step == 3 )
            {
                m_step = 0;
                m_callback();
            }
        }
}

////////////////////////////////////////////////////////////
DragAndDropTrigger::DragAndDropTrigger(std::function<void(float, float)> callback) :
m_isPressed(false),
m_x(0),
m_y(0),
m_isFirstMove(false)
{
    m_callback2 = callback;
}

////////////////////////////////////////////////////////////
void DragAndDropTrigger::listen(const sf::Event& event)
{
    if( event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Button::Left )
    {
        if( m_owner )
        {
            if( m_owner->contains(event.mouseButton.x, event.mouseButton.y) )
            {
                if( !m_isPressed )
                {
                    m_isPressed = true;
                    m_isFirstMove = true;
                }
            }
        }
    }

    else if( event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Button::Left )
    {
        if( m_isPressed )
        {
            m_isPressed = false;
            m_isFirstMove = false;
        }
    }

    else if( event.type == sf::Event::MouseMoved )
    {
        if( m_isPressed )
        {
            if( !m_isFirstMove )
                m_callback2(event.mouseMove.x - m_x, event.mouseMove.y - m_y);

            m_x = event.mouseMove.x;
            m_y = event.mouseMove.y;

            m_isFirstMove = false;
        }
    }
}

////////////////////////////////////////////////////////////
KeyPressedTrigger::KeyPressedTrigger(std::function<void()> callback)
{
    m_callback = callback;
}

////////////////////////////////////////////////////////////
void KeyPressedTrigger::listen(const sf::Event& event) {}

////////////////////////////////////////////////////////////
TextEnteredTrigger::TextEnteredTrigger(std::function<void(char)> callback) :
m_callback2(callback)
{}

////////////////////////////////////////////////////////////
void TextEnteredTrigger::listen(const sf::Event& event)
{
    if( event.type == sf::Event::TextEntered )
        if( event.text.unicode < 128 )
            m_callback2(static_cast<char>(event.text.unicode));
}

}