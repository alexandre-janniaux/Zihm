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
#include <Zihm/Window.hpp>

namespace zin
{

////////////////////////////////////////////////////////////
Window::Window()
{
    m_drawing.declare("Body", m_body);

    m_body.setFillColor(sf::Color(100, 100, 100));
    m_body.setOutlineColor(sf::Color::White);
    m_body.setOutlineThickness(2);
    m_body.setPosition(sf::Vector2f(2, 2));

    addTrigger(DragAndDropTrigger(std::bind(&Window::move, this, std::placeholders::_1, std::placeholders::_2)));

    setSize(sf::Vector2f(300, 200));
}

////////////////////////////////////////////////////////////  
void Window::onResizing()
{
    m_body.setSize(getSize());
}

}