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

#ifndef WIDGET_HPP
#define WIDGET_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include <list>
#include <Zihm/Trigger.hpp>
#include <Zihm/Drawing.hpp>
#include <Zihm/Config.hpp>


namespace zin
{
////////////////////////////////////////////////////////////
/// Widget is the base class for all the GUI items
////////////////////////////////////////////////////////////
class ZIHM_API Widget : public sf::Drawable, public sf::Transformable, public sf::NonCopyable
{
public:

    ////////////////////////////////////////////////////////////
    /// destructor
    ////////////////////////////////////////////////////////////
    virtual ~Widget();

    ////////////////////////////////////////////////////////////
    /// Update the widget using the time spent since last call
    ////////////////////////////////////////////////////////////
    virtual void update(sf::Time time);

    ////////////////////////////////////////////////////////////
    /// Attach a child widget to the current one
    ////////////////////////////////////////////////////////////
    virtual void attachWidget(Widget& widget);

    ////////////////////////////////////////////////////////////
    /// Get a child widget according to its indice
    ////////////////////////////////////////////////////////////
    Widget& getWidget(size_t indice);

    ////////////////////////////////////////////////////////////
    /// Set the size of the widget
    ////////////////////////////////////////////////////////////
    virtual void setSize(const sf::Vector2f& size);

    ////////////////////////////////////////////////////////////
    /// Move the widget
    ////////////////////////////////////////////////////////////
    void move(float x, float y) { sf::Transformable::move(x, y); }

    ////////////////////////////////////////////////////////////
    /// Get the size of the widget
    ////////////////////////////////////////////////////////////
    const sf::Vector2f& getSize() const;

    ////////////////////////////////////////////////////////////
    /// Get the unique identifier of the widget
    ////////////////////////////////////////////////////////////
    size_t getId();

    ////////////////////////////////////////////////////////////
    /// Get the children's count
    ////////////////////////////////////////////////////////////
    size_t getChildrenCount();

    ////////////////////////////////////////////////////////////
    /// Return true if the widget contains the coords
    ////////////////////////////////////////////////////////////
    bool contains(int x, int y);

    ////////////////////////////////////////////////////////////
    /// Return true if the widget is locked
    ////////////////////////////////////////////////////////////
    bool isLocked();

    ////////////////////////////////////////////////////////////
    /// Detach a child widget
    ////////////////////////////////////////////////////////////
    void detachWidget(size_t childId);

    ////////////////////////////////////////////////////////////
    /// Detach a child widget
    ////////////////////////////////////////////////////////////
    void detachWidget(Widget& child);

    ////////////////////////////////////////////////////////////
    /// Add a trigger to the widget
    ////////////////////////////////////////////////////////////
    void addTrigger(MouseOverTrigger trigger);

    ////////////////////////////////////////////////////////////
    /// Add a trigger to the widget
    ////////////////////////////////////////////////////////////
    void addTrigger(MouseOutTrigger trigger);

    ////////////////////////////////////////////////////////////
    /// Add a trigger to the widget
    ////////////////////////////////////////////////////////////
    void addTrigger(MouseButtonPressedTrigger trigger);

    ////////////////////////////////////////////////////////////
    /// Add a trigger to the widget
    ////////////////////////////////////////////////////////////
    void addTrigger(MouseButtonReleasedTrigger trigger);

    ////////////////////////////////////////////////////////////
    /// Add a trigger to the widget
    ////////////////////////////////////////////////////////////
    void addTrigger(ClickTrigger trigger);

    ////////////////////////////////////////////////////////////
    /// Add a trigger to the widget
    ////////////////////////////////////////////////////////////
    void addTrigger(DoubleClickTrigger trigger);

    ////////////////////////////////////////////////////////////
    /// Add a trigger to the widget
    ////////////////////////////////////////////////////////////
    void addTrigger(TripleClickTrigger trigger);

    ////////////////////////////////////////////////////////////
    /// Add a trigger to the widget
    ////////////////////////////////////////////////////////////
    void addTrigger(DragAndDropTrigger trigger);

    ////////////////////////////////////////////////////////////
    /// Add a trigger to the widget
    ////////////////////////////////////////////////////////////
    void addTrigger(KeyPressedTrigger trigger);

    ////////////////////////////////////////////////////////////
    /// Add a trigger to the widget
    ////////////////////////////////////////////////////////////
    void addTrigger(TextEnteredTrigger trigger);

    ////////////////////////////////////////////////////////////
    /// Send an event to the widget
    ////////////////////////////////////////////////////////////
    void onEvent(const sf::Event& event);

    ////////////////////////////////////////////////////////////
    /// Set the visibility of the widget
    ////////////////////////////////////////////////////////////
    void setVisibility(bool isVisible);

    ////////////////////////////////////////////////////////////
    /// Set the locking of the widget
    ////////////////////////////////////////////////////////////
    void setLocking(bool isLocked);

    ////////////////////////////////////////////////////////////
    /// Set the child on the top
    ////////////////////////////////////////////////////////////
    void setTopChild(Widget* widget);

protected:

    ////////////////////////////////////////////////////////////
    /// Default constructor
    ////////////////////////////////////////////////////////////
    Widget();

    ////////////////////////////////////////////////////////////
    /// Draw the widget in the rendering target
    ////////////////////////////////////////////////////////////
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    ////////////////////////////////////////////////////////////
    /// Virtual method called when the widget is focused
    ////////////////////////////////////////////////////////////   
    virtual void onFocusGained() {}

    ////////////////////////////////////////////////////////////
    /// Virtual method called when the widget is unfocused
    ////////////////////////////////////////////////////////////
    virtual void onFocusLost() {}

    ////////////////////////////////////////////////////////////
    /// Virtual method called when the widget is resized
    ////////////////////////////////////////////////////////////  
    virtual void onResizing() {}

    ////////////////////////////////////////////////////////////
    /// Virtual method called when the widget is locked
    ////////////////////////////////////////////////////////////  
    virtual void onLocking() {}

    ////////////////////////////////////////////////////////////
    /// Virtual method called when the widget is unlocked
    ////////////////////////////////////////////////////////////  
    virtual void onUnlocking() {}

    ////////////////////////////////////////////////////////////
    /// Return the transform of the widget
    //////////////////////////////////////////////////////////// 
    sf::Vector2f transform(sf::Vector2f point);

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    std::vector<Widget*> m_children;
    Drawing              m_drawing; 

private:

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    Widget*             m_parent;
    std::list<Trigger*> m_triggers;
    sf::Vector2f        m_size;
    size_t              m_id;
    bool                m_isVisible;
    bool                m_isFocused;
    bool                m_isLocked;
};

}

#endif // WIDGET_HPP