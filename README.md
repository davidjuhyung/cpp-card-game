# What is this game?
#### Please refer to “Hearthstone: Heroes of Warcraft” or “Magic: the Gathering” for instructions on how to play the game! 
#### If you would like to request a complete demo of this game, please message any one of us! :)

### Overview
The overall structure of this game can be classified as Board, Player, and Card class. The Board class uses two pointers of Player class to represent Player 1 and Player 2, and each player can use 0 or more cards of Card class. The Card class is an abstract class whose child classes are AbstractMinion, Spell, and Ritual. Since all child classes are a “card” and share similar properties such as the name and magic cost, we used inheritance to represent such a relationship. By simply inheriting the properties and functionalities of a Card class, we were able to maximize code reusability in the child classes and enhanced the overall readability and structure of our project.

The AbstractMinion, as the name suggests, is an abstract class that can be either a minion itself or a decorator to a minion, known as an enchantment. Since enchantment adds an additional functionality to a minion dynamically, and a minion should be able to decouple from the additional functionalities, we introduced a decorator design pattern. We were fully aware of the drawbacks by the incorporation of this design (i.e. complex code, abstract information manipulation), but we realized that there were at least 6 decorators (by default) and subclassing the minion class to each decorator would result in an explosion of subclasses to support every combination of decorators. By introducing this design pattern in our game, we were able to diligently handle any type of enchantment in any combination, including adding, removing, and printing their extended abilities.


### Design
The overall design of our classes enables us to use polymorphism for the Card and AbstractMinion classes. We thought this was the best way to implement it as this simplifies our player and board classes, and also improves functionality of the card class.

We recognized that the flow of information for maximum efficiency should be as follows:
The main controller should call the Board's methods.
Board class should handle the player’s actions.
Player’s should be responsible for activating the Cards’ methods
The Cards’ affect the board in some way. 
As you can notice, this leads to a sort of circular dependency issue which we solved by using a forward declaration of the Player class. This issue arises because the cards need a pointer to a board to be able to affect the board.

We designed to have high cohesion and low coupling. All of our methods and fields in a class are strictly related to their own classes. Combined with this, we also minimized the use of public fields and only added getters and setters when absolutely necessary. For example, instead of having a display function in one class that displays everything, we created display functions for each class so that the board only had to simply call their functions, without necessarily knowing their structures and fields of each class, leading to even higher cohesion and less coupling (i.e. didn't have to use the getCardType).
