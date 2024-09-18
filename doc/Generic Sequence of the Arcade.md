title Arcade Sequence

control Arcade

box over Arcade:Launch of the Arcade
activate Arcade #grey


entity Graphical
create Graphical

Arcade->Graphical:Open the graphic library\ngiven in parameter
entity Running_Game
create Running_Game

Arcade->Running_Game:Open "arcade_menu.so" and create the menu

alt in case of error while loading the menu and the Graphic library
box over Arcade: Exit
deactivate Arcade
end
activate Arcade #grey
box over Arcade:Initialize the Event
==End of the initialization==
Arcade->Arcade:Start the game loop
activate Arcade
loop while the loop is not ready to be stopped
Arcade-#lightgreen>Graphical:<color:#green>IDisplayModule::getEvent</color>
activate Graphical
Graphical-->Arcade:return the events as parameter
deactivate Graphical
activate Arcade#grey
Arcade->Arcade:Manage the event specific to the core
activate Arcade
space
deactivate Arcade
Arcade-#lightgreen>Running_Game:<color:#green>IGameModule::manageEvent</color>
activate Running_Game
space
deactivate Running_Game
Arcade-#lightgreen> Running_Game:<color:#green>IGameModule::iterate</color>
activate Running_Game
space
deactivate Running_Game
Arcade->Arcade:Check if the arcade must quit
activate Arcade
space
alt if the game must quit
Arcade-#red>Arcade:<color:#red>Prepare the exit of the loop</color>
end
deactivate Arcade
space 
deactivate Arcade
Arcade-#lightgreen>Graphical:<color:#green>IDisplayModule::clear</color>
activate Graphical
space
deactivate Graphical

Arcade-#lightgreen>Running_Game:<color:#green>IGameModule::getMap</color>
activate Running_Game
Running_Game--#lightgreen>Graphical:<color:#green>IDisplayModule::display</color>
activate Graphical
space
deactivate Graphical
deactivate Running_Game
end
deactivate Arcade
==End of the program==
deactivate Arcade