# "RPG GAME"
- flexible library, which allows user to create any game based on moving through rooms. User can create his own rooms, depend on his needs. Every room contains events, which can be modified too.
- connections between rooms and order of events in room is defined by user.
## creating room
To be able to create new room, user has to inherit from abstract class "chamber", located in file "chambers.h" and define it in file "chambers.cpp"
## creating event
To be able to create new event, user has to inherit from abstract class "event", located in file "event.h" and define it in file "events.cpp"
## preparing order of events in room
To achieve a given configuration of room, user must overload function "prepareEventsGraph" for given chamber and connect events in the room using "EventNode" and return first event in the order.
![prepareEventsGraph](https://github.com/MientusJJ/RPG-GAME-CPP/tree/main/photos/prepareEventsGraph.png?raw=true)
## preparing map of rooms
To prepare map user has to use function "prepareMap" in file "Game.h". User connects chambers using ChamberNode and return first chamber of the map, similar like in "prepareEventsGraph"
![prepareMap](https://github.com/MientusJJ/RPG-GAME-CPP/tree/main/photos/prepareMap.png?raw=true)
## changing output
In the project user the display method by implementing own method in "Views.h", console is default output.
## example game
As an example we created turn-bsen rpg game, where player impersonate a hero, whose goal is to kill the final boss
Player walks through rooms, where he defeats monsters, finds items and has some other events as well. In the final room "The Boss" waits for him.
User can become one of three heros: warrior, scout or mage.
### warrior
Warrior has the highest level of health and highest defense. He is able to block opponents' attacks
### scout
Scout has decent damage and decent health. He is also able to avoid opponents' attacks
### mage
Highest damage. Mage's attacks can't be avoided.
### type of rooms:
- health room - player can restore his health to 100% in this room
- merchant room - player if he has enough money, can but up to 3 items from the merchant
- trap room - room with trap, where player loses part of his health
- monster room - room with monster, player has to slay it. After fight there is a chest with the item and some amount of gold. After every victorious fight player gets level up and increases his stats
- empty room - nothing to do here, just go forward
- treasure room - room with chest, where player can find item and some amount of gold
![game](https://github.com/MientusJJ/RPG-GAME-CPP/tree/main/photos/game.png?raw=true)
