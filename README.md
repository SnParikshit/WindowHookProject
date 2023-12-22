Overview: 
Created a console application which create a low level global windows OS mouse hook, to collect the information on every click done accross the application and printing the following information in console.
1. Mouse coordinates in pixels.
2. The focused application and type of application.

Design Document:
Technical Overview:
In CSetMouseHook class, SetMouseHook() method to create the low level mouse hook using SetWindowsHookEx api. If the successfully the hook created one message will be added to console. Also UnHookMosue() method, to destory the hook before closing the application.

In CWindowHook class, the mouse click information is retrieved in WindowHookProc() method. In GetFocusedElementInfo(), we are retrieving the element in focus and then PrintElementInfo() method will print the most of the details of the focused application like x and y coordinates. Later, we can use this class to enhance the project to handle keyboard or other hooks.

In WindowhookProject class, this class is starting point of the solution, in the main, the SetMouseHook and UnHookMouse methods are called and also to keep the application alive the while loop is being used using GeMessage() api.


![image](https://github.com/SnParikshit/WindowHookProject/assets/42135651/3acede5d-1dd8-4aa6-9b31-8a4c54bd052c)
