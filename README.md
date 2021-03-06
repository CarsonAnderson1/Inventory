#Inventory 
This personal project's purpose is to act as a practice exercise, and display my skills involving linked lists, dynamically allocated data, file processing, classes, and clean code.
###What is it?
This project is simply a linked list consisting of nodes that point to different "items" based off of the video game Minecraft. The idea is to replicate its inventory system and mess around with creating and deleting items from the inventory itself.
###Plan:
My plan is to continue developing this program to refresh older skills including creating attractive displays, and file-processing, while refining my newer skills including working with linked lists.

##Created: March 19, 2022
Created a linked list with a clean display that I can add items to, remove items from, and reduce the amount of.
###Bugs to fix:
* Can add items outside of Minecraft. 
* Can go over the maximum amount of an item in Minecraft (generally 64).
* Display glitches when its size is too large
* Can't add amount to an item once created

##Update: March 22, 2022
###Fixed:
* Created "NonStackItem" function to fix amount maximum problem
* Created "FilterAnotherList" function to fix items outside of Minecraft problem
###Bugs to fix still:
* Display can be nicer
* Display glitches when its size is too large
* Can't add amount to an item once created
* Possibly can add too many items?
* Having the idea to make the menu go multiple menus deep
* When you go to add an item, and it exists, it should add to the currently existing item
* If an item is maxed out, and you try to add to it, it will ask you if you want to add to it
##Update: March 25, 2022
###Fixed:
* Display no longer glitches when size is too large, I created another format of output.
* Can add amount to an item when it is created.
* Display is nicer, and the dividers don't have weird lengths
* Can't add more than 32 items
* Can add and remove duplicates (up to 9 per item)
* When you go to add an item that already exists, it will give you the option to put the amount towards that existing item.
