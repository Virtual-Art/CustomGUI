#include <iostream>
#include <fstream>
#include <sstream>
#include <GL/glew.h>
#include "GLFW/glfw3.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Loader.h"
#include "Render.h"
#include "ShaderProgram.h"
#include "Maths.h"
#include "System.h"
#include "Texture.h"
#include "RawTexture.h"
#include "FontMath.h"
#include "FontFileReader.h"
#include "Character.h"
#include "TextSpecification.h"
#include "MouseManager.h"
#include "MemoryManagement.h"
#include "Page.h"
#include "Container.h"
#include "Selection.h"
#include "FileProcessor.h"
#include <Math.h>
#include <sstream>
#include <fileapi.h>
#include <tchar.h>
#include <stdio.h>
#include <strsafe.h>
#include "KeyboardManager.h"
#include "Text.h"
#include "Grid.h"
#include "ElementGroup.h"
#include "PageGroup.h"
#include "Action.h"
#include "Oscillation.h"
#include "Linear.h"
#include "Exponential.h"
#include "Logarithmic.h"
#include "ElementAction.h"
#include "Quad.h"
#include "NewCharacter.h"
#include "Slider.h"
#include "Controls.h"
#include "Toggle.h"
#include "PageCreator.h"
#include "PageGroup.h"
#include "MasterElement.h"
#include "NewPage.h"

//string ProcessInputString(GLFWwindow* window);
//void MouseCallback(GLFWwindow* window, double xPos, double yPos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

using namespace std;


int main(int argc, char** argv)
{
	MouseManager Mouse;
	Keyboard Keyboard;
	Keyboard::CreateKeyFuncContainer();

	MemoryManagment<int> VertexContainer;
	System System;
	FileSystem FileSystem;
	Book MainBook("ProgramFiles/FirstGUI.Book");

	cout << " System: Width:  " << System.Width << endl;
	cout << " System: Height:  " << System.Height << endl;
	cout << " System: MouseButtonNumber  " << System.MouseButtonNumber << endl;
	cout << " System: last thing  " << System.NumberofMonitors << endl;
	GLFWwindow* window;
	int SCR_WIDTH = 1200;//System.Width;
	int SCR_HEIGHT = 600;//System.Height;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "GUI Library", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glewInit();
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	Mouse.ScrollInput(window);
	Maths Maths;
	FontMath Font;
	Render Renderer;
	Texture Texture;

	ShaderProgram FontShader("Shaders/FontVS.txt", "Shaders/FontFS.txt");
	ShaderProgram ShapeShader("Shaders/VertexShader.txt", "Shaders/FragmentShader.txt");
	Page GUI(4000);
	GUI.Init(ShapeShader);

	PageCreator::Init(MainBook.Page[0], GUI, MainBook);

	FileSystem.LoadBook(MainBook, ShapeShader);

	RawTexture Segoe = Texture.CreateTexture("Resources/segoe.png", "FontAtlas", GL_TEXTURE0, 0, GL_RGBA);
	RawTexture ColorCube = Texture.CreateTexture("Resources/color-cube.png", "FontAtlas", GL_TEXTURE2, 2, GL_RGB);
	NewCharacter AnyCharacter(MainBook.Page[0], "Resources/segoe.fnt");

	Page Editor(400); 
	Editor.Init(ShapeShader);

	Page* PageSelected = &MainBook.Page[0];

	

	PageItemData PageItem_FirstSlider;
	SliderData Slider_FirstSlider;

	//Slider 1
	PageItem_FirstSlider.Position = { 0.0, -0.2 };
	Slider_FirstSlider.Description = "Hello";
	Slider_FirstSlider.Ratio = "14.35";
	PageItem_FirstSlider.Position = { 0.0, -0.3 };
	Slider FirstSlider1(MainBook.Page[0], PageItem_FirstSlider, Slider_FirstSlider);

	//Slider 2
	Slider_FirstSlider.Description = "Hello";
	Slider_FirstSlider.Ratio = "14.37";
	PageItem_FirstSlider.Position = { 0.0, -0.4 };
	Slider FirstSlider2(MainBook.Page[0], PageItem_FirstSlider, Slider_FirstSlider);

	//Slider 3
	Slider_FirstSlider.Description = "Hello";
	Slider_FirstSlider.Ratio = "14.38";
	PageItem_FirstSlider.Position = { 0.0, -0.5 };
	Slider FirstSlider3(MainBook.Page[0], PageItem_FirstSlider, Slider_FirstSlider);

	PageItem_FirstSlider.Position = { 0.0, -0.6 };
	Slider UnusedSlider(GUI, PageItem_FirstSlider, Slider_FirstSlider);
	//UnusedSlider.SetPosition({ 0.6, -0.7 });
	//UnusedSlider.SetPosition({ 0.6, -0.7 }); // Slider Replace adds 10 shape offset every replace
	//UnusedSlider.SetPosition({ 0.6, -0.7 }); // to fix this we need to have the slider shape group count go back to it's spot in the shape group
	UnusedSlider.SetSize({ 0.2, 0.1 });
	UnusedSlider.SetDescription("HelloWorld");
//	UnusedSlider.PrintGroupShapes();
	//UnusedSlider.ReCalibrateID();

	float Time;
	float PreviousTime;
	unsigned int EditorShapeDataHovered;
	unsigned int GUIShapeDataHovered;

	llBookData Gamee;

	
	NewPage FistPage(&Gamee, &ShapeShader, &ColorCube, &Segoe, &ColorCube);

	//MasterElement::AddPageToBook(&Gamee);
	//MasterElement::AddPageToBook(&Gamee);
	//MasterElement::AddPageToBook(&Gamee);
	//MasterElement::AddPageToBook(&Gamee);
	//MasterElement::AddPageToBook(&Gamee);
	//MasterElement::AddPageToBook(&Gamee);
	//MasterElement::AddPageToBook(&Gamee);
	//MasterElement::AddPageToBook(&Gamee);
	//MasterElement::AddPageToBook(&Gamee);
	//MasterElement::AddPageToBook(&Gamee);
	//MasterElement::AddPageToBook(&Gamee);
	//MasterElement::AddPageToBook(&Gamee);
	//MasterElement::AddPageToBook(&Gamee);
	//MasterElement::AddPageToBook(&Gamee);
	//MasterElement::PrintBook(&Gamee);
	//
	////Gamee would keep track of the counts 
	////As well as the current element it's on regardless on insertion and deletion
	//Slider llSlider(&Gamee);
	TextData yaat_t;
	yaat_t.Phrase = "Walmart";
	llShapeGroupData yaat;
	yaat.Position = { 0.0, 0.0 };
	Quad llQuad0(&Gamee);
	Quad llQuad1(&Gamee);
	Quad llQuad3(&Gamee);
	Quad llQuad2(&Gamee);
	Text llText0(&Gamee, &yaat, yaat_t);
	Text llText1(&Gamee, &yaat, yaat_t);

	//llText1.SetllPosition({ 0.0, -0.888 });

	//MasterElement::PrintShapeGroupShapes(*llText1);

	SliderData llSD;
	llSD.Description = "Desp";
	llSD.Ratio = "34.3";
	llPageItemData PID;
	PID.Position = {0.3, 0.3};

	Slider llSlider(&Gamee, &PID, llSD);

	////////Last Spot//////////
	//llSlider.SetllPosition({ - 0.7, 0.7, });
	///////////////////////////

	//NewCharacter SwitchChar(llText1.GetShapeGroup()->Shape);

	llPageItemData* CurrentWorkingPageItem = Gamee.Page->PageGroup->PageItem;

	//Print As Second
	//MasterElement::PrintPageItemShapeGroups(llSlider.GetPageItem());
	//MasterElement::PrintPageItemShapes(llSlider.GetPageItem());

	//Find Head
	while (CurrentWorkingPageItem->Previous != nullptr)
	{
		CurrentWorkingPageItem = CurrentWorkingPageItem->Previous;
	}
	int ShapeGroupCount = 0;
	//Print to tail
	while (CurrentWorkingPageItem != nullptr)
	{
		//MasterElement::PrintPageItemShapes(CurrentWorkingPageItem);
		CurrentWorkingPageItem = CurrentWorkingPageItem->Next;
		cout << ShapeGroupCount++ << endl;
	}

	//MasterElement::PrintBookStats(&Gamee);

	typedef void(*Master_P)();
	while (!glfwWindowShouldClose(window))
	{
		glm::vec2 MousePosition = {Mouse.xPos, Mouse.yPos};
		Time = glfwGetTime();
		PreviousTime = glfwGetTime();
		glClearColor(0.1, 0.1, 0.1, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		//Setup
		int MouseState = Mouse.GetMouseState(window, glfwGetTime(), 0.3, 0.4);
		KeyResult KeyState = Keyboard.GetKeyBoardState(window, glfwGetTime(), 0.3, 0.4);
		EditorShapeDataHovered = MainBook.Page[0].FindShapeData(Mouse.xPos, Mouse.yPos, false);
		GUIShapeDataHovered = GUI.FindShapeData(Mouse.xPos, Mouse.yPos, false);

		PageCreator::OnUpdate(KeyState, MouseState);

		llSlider.SetllPosition(MousePosition);

		PageGroupItem* jaj = &llSlider;
		Slider Complex(jaj->GetData());

		FistPage.DrawPage();

		//Renderer.DrawPage(ShapeShader, ColorCube, Segoe, ColorCube, GUI);
		//Renderer.DrawPage(ShapeShader, ColorCube, Segoe, ColorCube, *PageSelected);

		Mouse.GetMousePosition(window);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	Editor.DeletePage();
	GUI.DeletePage();
	return 0;
}
