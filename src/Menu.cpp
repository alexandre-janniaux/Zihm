
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
#include <Zihm/Menu.hpp>

namespace zin
{

////////////////////////////////////////////////////////////
Menu::Menu()
{
    setLocking(true);

    m_drawing.declare("Body", m_body);
    m_body.setFillColor(sf::Color(100, 100, 100));

    addTrigger(ClickTrigger(std::bind(&Menu::setLocking, this, false), sf::Mouse::Button::Left, Hovering::None));
}

////////////////////////////////////////////////////////////
Menu::Menu(std::initializer_list<sf::String> slotLabels)
{
    for( auto& label : slotLabels )
        addSlot(label);
}

////////////////////////////////////////////////////////////
void Menu::attachWidget(Slot& slot)
{
    Widget::attachWidget(slot);

    slot.setPosition(sf::Vector2f(m_body.getSize().x, 0));
    m_body.setSize(sf::Vector2f(m_body.getSize().x + slot.getSize().x, 36));
    setSize(m_body.getSize());
}

////////////////////////////////////////////////////////////
void Menu::addSlot(const sf::String& label)
{
    Slot* slot = new Slot(label);
    m_slots.push_back(slot);
    attachWidget(*slot);
}

////////////////////////////////////////////////////////////  
void Menu::onLocking()
{
    for( auto& child : m_children )
        child->setLocking(true);
}

////////////////////////////////////////////////////////////  
void Menu::onUnlocking()
{
    for( auto& child : m_children )
        child->setLocking(false);
}

////////////////////////////////////////////////////////////
void Menu::attachSublist(List& list, size_t range)
{
    if( range < getChildrenCount() )
    {
        Slot* slot = static_cast<Slot*>(m_children[range]);

        slot->attachWidget(list);

        list.move(-2, 33);
        list.setVisibility(false);

        slot->addTrigger(MouseOverTrigger(std::bind(&List::setVisibility, &list, true)));
        slot->addTrigger(MouseOutTrigger(std::bind(&List::setVisibility, &list, false)));
        list.addTrigger(MouseOverTrigger(std::bind(&List::setLocking, this, true)));
        list.addTrigger(MouseOutTrigger(std::bind(&List::setLocking, this, false)));
        slot->addTrigger(MouseOverTrigger(std::bind(&List::setTopChild, this, slot)));
    }
}

}