# "RPG GAME"
- flexible library, which allows user to create any game based on moving through rooms. User can create his own rooms, depend on his needs. Every room contains events, which can be modified too.
- connections between rooms and order of events in room is defined by user.
## creating room
To be able to create new room, user has to inherit from abstract class "chamber", located in file "chambers.h" and define it in file "chambers.cpp"
## creating event
To be able to create new event, user has to inherit from abstract class "event", located in file "event.h" and define it in file "events.cpp"
## preparing order of events in room
to achieve a given configuration of room, user must overload function "prepareEventsGraph" for given chamber and connect events in the room using "EventNode" and return first event in the order.
![prepareEventsGraph](https://github.com/MientusJJ/RPG-GAME-CPP/tree/main/photos/prepareEventsGraph.png?raw=true)
## preparing map of rooms

As an example we created turn-bsen rpg game, where player impersonate a hero, whose goal is to kill the final boss
