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
#include <Zihm/Slot.hpp>


namespace zin
{
////////////////////////////////////////////////////////////
Slot::Slot()
{
    m_drawing.declare("Body", m_body);
    m_drawing.declare("Text", m_text);

    m_body.setFillColor(sf::Color(100, 100, 100));
    m_text.setPosition(sf::Vector2f(7, 0));

    setSize(m_body.getSize());
}

////////////////////////////////////////////////////////////
Slot::Slot(const sf::String& string)
{
    m_drawing.declare("Body", m_body);
    m_drawing.declare("Text", m_text);

    m_body.setFillColor(sf::Color(100, 100, 100));
    m_text.setPosition(sf::Vector2f(7, 0));

    setString(string);

    setSize(m_body.getSize());
}

////////////////////////////////////////////////////////////
void Slot::setString(const sf::String& string)
{
    m_text.setString(string);
    m_body.setSize(sf::Vector2f(m_text.getLocalBounds().width + 12, m_text.getCharacterSize() + 7));

    setSize(m_body.getSize());
}

////////////////////////////////////////////////////////////
void Slot::setWidth(float width)
{
    m_body.setSize(sf::Vector2f(width, m_body.getSize().y));
    setSize(m_body.getSize());
}

////////////////////////////////////////////////////////////
void Slot::onFocusGained()
{
    m_body.setFillColor(sf::Color(150, 150, 150));
    m_body.setOutlineColor(sf::Color::White);
}

////////////////////////////////////////////////////////////
void Slot::onFocusLost()
{
    m_body.setFillColor(sf::Color(100, 100, 100));
    m_body.setOutlineColor(sf::Color::White);
}

}