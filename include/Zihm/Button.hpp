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

#ifndef BUTTON_HPP
#define BUTTON_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include <Zihm/Widget.hpp>
#include <Zihm/Config.hpp>


namespace zin
{
////////////////////////////////////////////////////////////
/// Button is a widget derived from the Widget class
////////////////////////////////////////////////////////////
class ZIHM_API Button : public Widget
{
public :

    ////////////////////////////////////////////////////////////
    /// Default constructor
    ////////////////////////////////////////////////////////////
    Button();

    ////////////////////////////////////////////////////////////
    /// Set the string of the button text
    ////////////////////////////////////////////////////////////
    void setString(const sf::String& string);

protected :

    ////////////////////////////////////////////////////////////
    /// Method called when the button is focused
    ////////////////////////////////////////////////////////////
    void onFocusGained();

    ////////////////////////////////////////////////////////////
    /// Method called when the button is unfocused
    ////////////////////////////////////////////////////////////
    void onFocusLost();

    ////////////////////////////////////////////////////////////
    /// Method called when the button is pressed
    ////////////////////////////////////////////////////////////
    void onPress();

    ////////////////////////////////////////////////////////////
    /// Method called when the button is released
    ////////////////////////////////////////////////////////////
    void onRelease();

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    bool                               m_isPressed;
    sf::Text                           m_text;
    sf::RectangleShape                 m_body;
};

}

#endif // BUTTON_HPP