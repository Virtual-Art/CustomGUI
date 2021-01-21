CustomGUI - Customize a Graphical User Interface to your specific needs.

The motivation behind this program was to be able to quickly create a Graphical User Interface with the option of Customizable Buttons, Sliders, DropDown Lists, Toggles, Progress bars, TextFeild (Elements). Once created, a byte file will contain all the code to use the Elements in a C++ Program. There will also be a feature to convert all UI Desgins to html format for further use on a Website.

The Current Status of the project is still in a dormant state. Functionality to this project should be completed within the next following week. This will allow the user to create and edit Text, Sliders, and Basic Squares using the Keyboard and limited Mouse Support.

Built with OpenGl, GLFW, GLEW, glm libraries. 

When the program is no longer in it's dormant state, the user will be able to use the arrow keys to affect certain attributes of each 'Element'. The keyoard actions we're specifically designed to allow the user to switch between attributes such as Position, Size, Color, writing Text via the Shift + Arrow Keys and switch between different Element Groupings (Shape, ShapeGroup (ex. Text), PageItem(ex. Slider), PageGroup( ex. group of Sliders, Toggles etc), Page (ex. group of PageGroups) and finally Book) via the Alt + Arrow Keys. This was acheived by using Multiple Inheritance, Composition and virtual functions which allows not only a fast but intuitive way for the user to create Elements, but a very quick learning curve.

This ReadMe is updated each contribution, typically every 1-2 days. The Next steps for the CustomGUI is to finish the Element State stat system to be able to Edit all attributes without detrimental errors. Converting from heap array to a link list is currently being worked on which will be integrated into the project at a later date. This will improve speed as well as solve the ID system issues due to insertion and deletion (The ID system is based on consecutive numbers that act as the ID to each element, which involves iterations to all the shapes on the page after insertion/ deletion, this is terribly inefficient).
