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

#ifndef LIST_HPP
#define LIST_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include <Zihm/Widget.hpp>
#include <Zihm/Slot.hpp>
#include <Zihm/Config.hpp>
#include <initializer_list>


namespace zin
{
////////////////////////////////////////////////////////////
/// List is a widget derived from the Widget class
////////////////////////////////////////////////////////////
class ZIHM_API List : public Widget
{
public :

    ////////////////////////////////////////////////////////////
    /// Default constructor
    ////////////////////////////////////////////////////////////
    List();

    ////////////////////////////////////////////////////////////
    /// Constructor
    ////////////////////////////////////////////////////////////
    List(std::initializer_list<sf::String> slotLabels);

    ////////////////////////////////////////////////////////////
    /// Destructor
    ////////////////////////////////////////////////////////////
    ~List();
    
    ////////////////////////////////////////////////////////////
    /// Attach a slot to the list
    ////////////////////////////////////////////////////////////
    void attachWidget(Slot& slot);

    ////////////////////////////////////////////////////////////
    /// Add a slot to the list
    ////////////////////////////////////////////////////////////
    void addSlot(const sf::String& label);

    ////////////////////////////////////////////////////////////
    /// Attach a slot and a sublist to the list
    ////////////////////////////////////////////////////////////
    void attachSublist(List& list, size_t range);

protected :

    ////////////////////////////////////////////////////////////
    /// Method called when the list is resized
    ////////////////////////////////////////////////////////////  
    void onResizing();

    ////////////////////////////////////////////////////////////
    /// Method called when the widget is locked
    ////////////////////////////////////////////////////////////  
    void onLocking();

    ////////////////////////////////////////////////////////////
    /// Method called when the widget is unlocked
    ////////////////////////////////////////////////////////////  
    void onUnlocking();

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    sf::RectangleShape m_body;
    std::vector<Slot*> m_slots;
};

}

#endif // LIST_HPP