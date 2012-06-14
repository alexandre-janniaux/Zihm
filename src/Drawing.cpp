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
#include <Zihm/Drawing.hpp>


namespace zin
{

////////////////////////////////////////////////////////////
void Drawing::declare(const sf::String& name, sf::Drawable& drawable, bool isVisible)
{
    size_t k = getRange(name);

    if( k != m_items.size() )
        m_items.push_back({name, &drawable, isVisible});
}

////////////////////////////////////////////////////////////
void Drawing::show(const sf::String& name)
{
    size_t k = getRange(name);

    if( k != m_items.size() )
        m_items[k].isVisible = true;
}

////////////////////////////////////////////////////////////
void Drawing::hide(const sf::String& name)
{
    size_t k = getRange(name);

    if( k != m_items.size() )
        m_items[k].isVisible = false;
}

////////////////////////////////////////////////////////////
void Drawing::switchVisibility(const sf::String& name)
{
    size_t k = getRange(name);

    if( k != m_items.size() )
        m_items[k].isVisible = !m_items[k].isVisible;
}

////////////////////////////////////////////////////////////
void Drawing::setVisibility(const sf::String& name, bool isVisible)
{
    size_t k = getRange(name);

    if( k != m_items.size() )
        m_items[k].isVisible = isVisible;
}

////////////////////////////////////////////////////////////
void Drawing::sort(const sf::String& name, size_t range)
{
    size_t k = getRange(name);

    if( k != m_items.size() )
    {
        Item item = m_items[k];

        m_items.erase(m_items.begin() + k);
        m_items.insert(m_items.begin() + range, item);
    }
}

////////////////////////////////////////////////////////////
size_t Drawing::getRange(const sf::String& name)
{
    size_t k = 0;

    for( ; k <= m_items.size(); k++ )
        if( k < m_items.size() )
            if( m_items[k].name == name )
                return k;

    return k;
}

////////////////////////////////////////////////////////////
void Drawing::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for( auto& item : m_items )
        if( item.isVisible )
            target.draw(*item.drawable, states);
}

}