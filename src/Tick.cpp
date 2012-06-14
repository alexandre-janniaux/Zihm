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
#include <Zihm/Tick.hpp>

namespace zin
{

////////////////////////////////////////////////////////////
Tick::Tick() :
m_isActivated(false)
{
    m_drawing.declare("Body", m_body);
    m_drawing.declare("Tick", m_tick, false);

    m_body.setFillColor(sf::Color(0, 0, 0, 0));
    m_body.setOutlineColor(sf::Color::White);
    m_body.setOutlineThickness(2);
    m_body.setSize(sf::Vector2f(20, 20));
    m_body.setPosition(sf::Vector2f(2, 2));
    m_tick.setFillColor(sf::Color::White);
    m_tick.setSize(sf::Vector2f(12, 12));
    m_tick.setPosition(sf::Vector2f(6, 6));

    setSize(m_body.getSize());

    addTrigger(MouseButtonPressedTrigger(std::bind(&Tick::switchActivation, this), sf::Mouse::Button::Left, Hovering::Over));
}

////////////////////////////////////////////////////////////
void Tick::onFocusGained()
{
    m_body.setFillColor(sf::Color(50, 50, 50));
}

////////////////////////////////////////////////////////////
void Tick::onFocusLost()
{
    if( !m_isActivated )
        m_body.setFillColor(sf::Color(0, 0, 0, 0));
}

////////////////////////////////////////////////////////////
void Tick::switchActivation()
{
    m_isActivated = !m_isActivated;
    m_drawing.switchVisibility("Tick");
}

}