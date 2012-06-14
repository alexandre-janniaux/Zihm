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

#ifndef DRAWING_HPP
#define DRAWING_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include <vector>
#include <Zihm/Config.hpp>


namespace zin
{
////////////////////////////////////////////////////////////
/// Drawing
////////////////////////////////////////////////////////////
class ZIHM_API Drawing : public sf::Drawable
{
public :

    ////////////////////////////////////////////////////////////
    /// declare a new item to the drawing
    ////////////////////////////////////////////////////////////
    void declare(const sf::String& name, sf::Drawable& drawable, bool isVisible = true);

    ////////////////////////////////////////////////////////////
    /// show the item specified by name
    ////////////////////////////////////////////////////////////
    void show(const sf::String& name);

    ////////////////////////////////////////////////////////////
    /// hide the item specified by name
    ////////////////////////////////////////////////////////////
    void hide(const sf::String& name);

    ////////////////////////////////////////////////////////////
    /// switch the visibility of the item specified by name
    ////////////////////////////////////////////////////////////
    void switchVisibility(const sf::String& name);

    ////////////////////////////////////////////////////////////
    /// set the visibility of the item specified by name
    ////////////////////////////////////////////////////////////
    void setVisibility(const sf::String& name, bool isVisible);

    ////////////////////////////////////////////////////////////
    /// sort the item specified by name to the given range
    ////////////////////////////////////////////////////////////
    void sort(const sf::String& name, size_t range);

protected :

    ////////////////////////////////////////////////////////////
    /// get the range of the item specified by name
    ////////////////////////////////////////////////////////////
    size_t getRange(const sf::String& name);
    
    ////////////////////////////////////////////////////////////
    /// Draw the drawing in the rendering target
    ////////////////////////////////////////////////////////////
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    
    ////////////////////////////////////////////////////////////
    /// Item
    ////////////////////////////////////////////////////////////
    struct Item {sf::String name; sf::Drawable* drawable; bool isVisible; };

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    std::vector<Item> m_items;
};

}

#endif // DRAWING_HPP