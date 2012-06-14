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
#include <Zihm/LineEdit.hpp>

namespace zin
{

////////////////////////////////////////////////////////////
LineEdit::LineEdit() :
m_isActivated(false)
{
    m_drawing.declare("Body",   m_body);
    m_drawing.declare("Carret", m_carret, false);
    m_drawing.declare("Text",   m_text);

    m_body.setSize(sf::Vector2f(50, m_text.getCharacterSize() + 6));
    m_body.setFillColor(sf::Color(0, 0, 0, 0));
    m_body.setOutlineColor(sf::Color::White);
    m_body.setOutlineThickness(2);
    m_body.setPosition(sf::Vector2f(2, 2));
    m_carret.setPosition(sf::Vector2f(10, -2));
    m_carret.setString('|');
    m_text.setPosition(sf::Vector2f(7, 0));

    setSize(m_body.getSize());
    
    addTrigger(ClickTrigger(std::bind(&LineEdit::setActivation, this, true), sf::Mouse::Button::Left, Hovering::Over));
    addTrigger(ClickTrigger(std::bind(&LineEdit::setActivation, this, false), sf::Mouse::Button::Left, Hovering::Out));
    addTrigger(TextEnteredTrigger(std::bind(&LineEdit::addCharacter, this, std::placeholders::_1)));
}

////////////////////////////////////////////////////////////
void LineEdit::setString(const sf::String& string)
{
    m_text.setString(string);
    float width = m_text.getLocalBounds().width;
    m_carret.setPosition(!m_text.getString().isEmpty() ? width + 4 : 4, -2);

    if( width + m_carret.getLocalBounds().width + 7 > m_body.getLocalBounds().width )
    {
        m_body.setSize(sf::Vector2f(width + m_carret.getLocalBounds().width + 7, m_text.getCharacterSize() + 6));
        setSize(m_body.getSize());
    }
}

////////////////////////////////////////////////////////////
void LineEdit::setWidth(float width)
{
    m_body.setSize(sf::Vector2f(width, m_text.getCharacterSize() + 6));
    setSize(m_body.getSize());
}

////////////////////////////////////////////////////////////
void LineEdit::update(sf::Time time)
{
    if( m_isActivated )
    {
        m_carretTimer+=time;

        if( m_carretTimer >= sf::seconds(.5f) )
        {
            m_carretTimer = sf::Time::Zero;
            m_drawing.switchVisibility("Carret");
        }
    }
}

////////////////////////////////////////////////////////////
void LineEdit::setActivation(bool isActivated)
{
    if( m_isActivated != isActivated )
    {
        m_carretTimer = sf::Time::Zero;
        m_drawing.setVisibility("Carret", isActivated);
        m_isActivated = isActivated;
    }
}

////////////////////////////////////////////////////////////
void LineEdit::addCharacter(char character)
{
    if( m_isActivated )
    {       
        if( character != 13 && character != 32 )
        {
            std::string string = m_text.getString().toAnsiString();

            if( character == 8 )
            {
                if( !string.empty() )
                    string.erase(string.end() - 1);
            }

            else
            {
                sf::Text text(character);

                if( m_text.getLocalBounds().width + text.getLocalBounds().width + m_carret.getLocalBounds().width + 7 < m_body.getLocalBounds().width )
                    string+=character;
            }

             setString(string);
         }
    }
}

}