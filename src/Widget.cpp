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

#include <Zihm/Widget.hpp>
#include <iostream>

namespace zin
{
////////////////////////////////////////////////////////////
Widget::Widget() :
m_parent(nullptr),
m_isVisible(true),
m_isLocked(false),
m_isFocused(false)
{
    static int count;
    m_id = count++;

    addTrigger(MouseOverTrigger(std::bind(&Widget::onFocusGained, this)));
    addTrigger(MouseOutTrigger(std::bind(&Widget::onFocusLost, this)));
}

////////////////////////////////////////////////////////////
Widget::~Widget()
{
    for( auto& trigger : m_triggers )
        delete trigger;

    m_triggers.clear();
    m_children.clear();
}

////////////////////////////////////////////////////////////
void Widget::attachWidget(Widget& widget)
{
    if( &widget != this )
    {
        widget.m_parent = this;
        m_children.push_back(&widget);
    }
}

////////////////////////////////////////////////////////////
Widget& Widget::getWidget(size_t indice)
{
    return *m_children[indice];
}

////////////////////////////////////////////////////////////
void Widget::detachWidget(size_t widgetId)
{
    for( size_t k(0); k < m_children.size(); k++ )
    {
        if( m_children[k]->getId() == widgetId )
        {
            m_children.erase(m_children.begin() + k);
            return;
        }
    }
}

////////////////////////////////////////////////////////////
void Widget::detachWidget(Widget& widget)
{
    for( int k(0); k < m_children.size(); k++ )
    {
        if( m_children[k] == &widget )
        {
            m_children.erase(m_children.begin() + k);
            return;
        }
    }
}

////////////////////////////////////////////////////////////
void Widget::addTrigger(MouseOverTrigger trigger)
{
    Trigger* ptr = new MouseOverTrigger(trigger);
    m_triggers.push_back(ptr);
    ptr->declareOwner(*this);
}

////////////////////////////////////////////////////////////
void Widget::addTrigger(MouseOutTrigger trigger)
{
    Trigger* ptr = new MouseOutTrigger(trigger);
    m_triggers.push_back(ptr);
    ptr->declareOwner(*this);
}

////////////////////////////////////////////////////////////
void Widget::addTrigger(MouseButtonPressedTrigger trigger)
{
    Trigger* ptr = new MouseButtonPressedTrigger(trigger);
    m_triggers.push_back(ptr);
    ptr->declareOwner(*this);
}

////////////////////////////////////////////////////////////
void Widget::addTrigger(MouseButtonReleasedTrigger trigger)
{
    Trigger* ptr = new MouseButtonReleasedTrigger(trigger);
    m_triggers.push_back(ptr);
    ptr->declareOwner(*this);
}

////////////////////////////////////////////////////////////
void Widget::addTrigger(ClickTrigger trigger)
{
    Trigger* ptr = new ClickTrigger(trigger);
    m_triggers.push_back(ptr);
    ptr->declareOwner(*this);
}

////////////////////////////////////////////////////////////
void Widget::addTrigger(DoubleClickTrigger trigger)
{
    Trigger* ptr = new DoubleClickTrigger(trigger);
    m_triggers.push_back(ptr);
    ptr->declareOwner(*this);
}

////////////////////////////////////////////////////////////
void Widget::addTrigger(TripleClickTrigger trigger)
{
    Trigger* ptr = new TripleClickTrigger(trigger);
    m_triggers.push_back(ptr);
    ptr->declareOwner(*this);
}

////////////////////////////////////////////////////////////
void Widget::addTrigger(DragAndDropTrigger trigger)
{
    Trigger* ptr = new DragAndDropTrigger(trigger);
    m_triggers.push_back(ptr);
    ptr->declareOwner(*this);
}

////////////////////////////////////////////////////////////
void Widget::addTrigger(KeyPressedTrigger trigger)
{
    Trigger* ptr = new KeyPressedTrigger(trigger);
    m_triggers.push_back(ptr);
    ptr->declareOwner(*this);
}

////////////////////////////////////////////////////////////
void Widget::addTrigger(TextEnteredTrigger trigger)
{
    Trigger* ptr = new TextEnteredTrigger(trigger);
    m_triggers.push_back(ptr);
    ptr->declareOwner(*this);
}

////////////////////////////////////////////////////////////
size_t Widget::getId()
{
    return m_id;
}

////////////////////////////////////////////////////////////
size_t Widget::getChildrenCount()
{
    return m_children.size();
}

////////////////////////////////////////////////////////////
sf::Vector2f Widget::transform(sf::Vector2f point)
{
    point = getTransform().getInverse().transformPoint(point);

    if( m_parent != nullptr )
        point = m_parent->transform(point);

    return point;
}

////////////////////////////////////////////////////////////
bool Widget::contains(int x, int y)
{
    sf::Vector2f mouseCoords = transform(sf::Vector2f(x, y));
    return mouseCoords.x > 0 && mouseCoords.x < getSize().x && mouseCoords.y > 0 && mouseCoords.y < getSize().y;
}

////////////////////////////////////////////////////////////
bool Widget::isLocked()
{
    return m_isLocked;
}

////////////////////////////////////////////////////////////
void Widget::update(sf::Time time)
{
    for( auto& child : m_children )
        child->update(time);
}

////////////////////////////////////////////////////////////
void Widget::setVisibility(bool isVisible)
{
    m_isVisible = isVisible;
}

////////////////////////////////////////////////////////////
void Widget::setLocking(bool isLocked)
{
    if( m_isLocked != isLocked )
    {
        m_isLocked = isLocked;
        isLocked ? onLocking() : onUnlocking();
    }
}

////////////////////////////////////////////////////////////
void Widget::setTopChild(Widget* widget)
{
    for( size_t k(0); k < m_children.size(); k++ )
        if( m_children[k] == widget )
        {
            m_children.push_back(m_children[k]);
            m_children.erase(m_children.begin() + k);
            break;
        }
}

////////////////////////////////////////////////////////////
void Widget::setSize(const sf::Vector2f& size)
{
    if( size.x != m_size.x || size.y != m_size.y )
    {
        m_size = size;
        onResizing();
    }
}

////////////////////////////////////////////////////////////
const sf::Vector2f& Widget::getSize() const
{
    return m_size;
}

////////////////////////////////////////////////////////////
void Widget::onEvent(const sf::Event& event)
{
    if( m_isVisible )
        for( auto& child : m_children )
            child->onEvent(event);

    if( !m_isLocked )
        for( auto& trigger : m_triggers )
            trigger->listen(event);
}

////////////////////////////////////////////////////////////
void Widget::draw(
    sf::RenderTarget& target,
    sf::RenderStates  states
) const {

    if( m_isVisible )
    {
        states.transform*=getTransform();

        target.draw(m_drawing, states);

        for( auto& child : m_children )
            target.draw(*child, states);
    }
}

}