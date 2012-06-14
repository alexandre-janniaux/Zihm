////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include <Zihm/Button.hpp>
#include <Zihm/LineEdit.hpp>
#include <Zihm/Tick.hpp>
#include <Zihm/Slot.hpp>
#include <Zihm/List.hpp>
#include <Zihm/Menu.hpp>
#include <Zihm/Window.hpp>

using namespace zin;

////////////////////////////////////////////////////////////
/// Entry point of the application
////////////////////////////////////////////////////////////
int main()
{
   sf::RenderWindow App(sf::VideoMode(800, 600, 32), "Test");
   App.setFramerateLimit(40);

   sf::Clock clock;

   Button button0;
   button0.setString("Hello world !");
   button0.move(50, 50);
   
   Button button1;
   button1.setString("Traduire");
   button1.move(50, 100);

   button1.addTrigger(ClickTrigger(std::bind(&Button::setString, &button0, "Salut le monde !"), sf::Mouse::Button::Left, Hovering::Over));

   LineEdit edit;
   edit.setString("Write here");
   edit.move(50, 150);

   Tick tick;
   tick.move(50, 200);

   Slot slot;
   slot.setString("Je suis un slot !");
   slot.move(50, 250);

   List list01({"Fraise", "Tomate", "Pasteque"});

   List list02({"Kiwi", "Banane", "Pamplemousse", "Orange"});
   list02.attachSublist(list01, 1);

   Menu menu({"Groseille", "Raisin", "Prune", "Rubarbe", "Poire"});
   menu.attachSublist(list02, 1);

   Window window;
   window.move(50, 300);
   window.attachWidget(button0);

   while( App.isOpen() )
   {
      sf::Event Event;
   
      while( App.pollEvent(Event) )
      {     
         if( Event.type == sf::Event::Closed )
            App.close();
      
         if( Event.type == sf::Event::KeyPressed && Event.key.code == sf::Keyboard::Escape )
            App.close();

         button1.onEvent(Event);
         edit.onEvent(Event);
         tick.onEvent(Event);
         slot.onEvent(Event);
         menu.onEvent(Event);
         window.onEvent(Event);
      }

      sf::Time time = clock.restart();

      edit.update(time);

      App.clear(sf::Color(30, 30, 30));

      App.draw(button1);
      App.draw(edit);
      App.draw(tick);
      App.draw(slot);
      App.draw(menu);
      App.draw(window);
      
      App.display();
   }
   
   return EXIT_SUCCESS;
}