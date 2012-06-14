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
#include <Zihm/List.hpp>

namespace zin
{

////////////////////////////////////////////////////////////
List::List()
{
    m_drawing.declare("Body", m_body);

    m_body.setFillColor(sf::Color(100, 100, 100));
    m_body.setOutlineColor(sf::Color::White);
    m_body.setOutlineThickness(2);
    m_body.setPosition(sf::Vector2f(2, 2));
}

////////////////////////////////////////////////////////////
List::List(std::initializer_list<sf::String> slotLabels)
{
    for( auto& label : slotLabels )
        addSlot(label);
}

////////////////////////////////////////////////////////////
List::~List()
{
   for( auto& slot : m_slots )
        delete slot;

    m_slots.clear(); 
}

////////////////////////////////////////////////////////////
void List::addSlot(const sf::String& label)
{
    Slot* slot = new Slot(label);
    m_slots.push_back(slot);
    attachWidget(*slot);
}

////////////////////////////////////////////////////////////  
void List::onResizing()
{
    for( size_t k(0); k < m_children.size(); k++ )
    {
        Slot* slot = static_cast<Slot*>(m_children[k]);
        
        slot->setWidth(getSize().x);
        slot->setPosition(sf::Vector2f(2, 2 + k * 36));
    }

    m_body.setSize(getSize());
}

////////////////////////////////////////////////////////////  
void List::onLocking()
{
    for( auto& child : m_children )
        child->setLocking(true);
}

////////////////////////////////////////////////////////////  
void List::onUnlocking()
{
    for( auto& child : m_children )
        child->setLocking(false);
}

////////////////////////////////////////////////////////////
void List::attachWidget(Slot& slot)
{
    Widget::attachWidget(slot);
    setSize(sf::Vector2f(slot.getSize().x > getSize().x ? slot.getSize().x : m_body.getSize().x, m_body.getSize().y + 36.2));
}

////////////////////////////////////////////////////////////
void List::attachSublist(List& list, size_t range)
{
    if( range < getChildrenCount() )
    {
        Slot* slot = static_cast<Slot*>(m_children[range]);

        slot->attachWidget(list);

        list.move(getSize().x - 10, -2);
        list.setVisibility(false);

        slot->addTrigger(MouseOverTrigger(std::bind(&List::setVisibility, &list, true)));
        slot->addTrigger(MouseOutTrigger(std::bind(&List::setVisibility, &list, false)));
        list.addTrigger(MouseOverTrigger(std::bind(&List::setLocking, this, true)));
        list.addTrigger(MouseOutTrigger(std::bind(&List::setLocking, this, false)));
        list.addTrigger(ClickTrigger(std::bind(&List::setVisibility, this, false)));
        slot->addTrigger(MouseOverTrigger(std::bind(&List::setTopChild, this, slot)));
    }
}

}