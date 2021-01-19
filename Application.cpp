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

namespace BookCreator
{

	void DeletePage() { cout << "Deleting Page " << endl; };
}

void MakePage() { cout << "Making Page " << endl; };

void FirstPointerFunction(int INT)
{
	cout << "First Pointer Function" << INT << endl;
}

void SecondPointerFunction(int INT)
{
	cout << "Second Pointer Function" << INT << endl;
}

void Keyboardworking()
{
	cout << " keyboar working " << endl;
}

class Node
{
public:

	int Posx;
	int Posy;
	int Color;
	bool Visited;

	Node()
	{
		this->Posx    = -1;
		this->Posy    = -1;
		this->Color   = -1;
		this->Visited = -1;
	}

	void Set(int Posx, int Posy, int Color, bool Visited)
	{
		this->Posx = Posx;
		this->Posy = Posy;
		this->Color = Color;
		this->Visited = Visited;
	}
};

bool Switch(bool Switch);
glm::vec2 Pixellength(double SCR_Height, double SCR_Width);

string ProcessInputString(GLFWwindow* window);
void MouseCallback(GLFWwindow* window, double xPos, double yPos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

void FindMaxColor(Node** EngGrid);
int DFS(int x, int y, Node **EngGrid);

int ProcessInput(GLFWwindow* window);
int tlly = 0;
double MouseX;
double MouseY;

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
	//PixelLength = Pixellength(SCR_HEIGHT, SCR_WIDTH);

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
	char UserInput[100] = "New Game";
	Render Renderer;
	float FontSIZE = 0.30;
	float xPos = -0.9;
	float yPos = 0.2;
	glm::vec4 Color = { 0.3, 0.7, 0.3, 1.0 };
	float LineLength = 1.0;
	Texture Texture;
	//WorkingFile.SetDirectory("VisualizationImages");
	//WorkingFile.DisplayDirectoryFiles();
	//WorkingFile.ForwardDirectory(WorkingFile.FileList[8]);
	//WorkingFile.DisplayDirectoryFiles();
	//WorkingFile.WriteShapeDataToFile("ProgramFiles/GUIData.txt", FileHelper);
	//WorkingFile.ReadFileToShapeData("ProgramFiles/GUIData.txt", FileHelper);
	ShaderProgram FontShader("Shaders/FontVS.txt", "Shaders/FontFS.txt");
	ShaderProgram ShapeShader("Shaders/VertexShader.txt", "Shaders/FragmentShader.txt");
	Page GUI(4000);
	GUI.Init(ShapeShader);

	PageCreator::Init(MainBook.Page[0], GUI, MainBook);

	FileSystem.LoadBook(MainBook, ShapeShader);

	float CharSpacing = 0.4;
	float LineSpacing = 1.5;
	RawTexture Eye = Texture.CreateTexture("Resources/images (5).jpg", "FontAlas", GL_TEXTURE1, 1, GL_RGB);
	RawTexture Characters = Texture.CreateTexture("Resources/arial.png", "FontAtlas", GL_TEXTURE2, 2, GL_RGBA);
	TextSpecification Text_Welcome("what", "Resources/calibri (1).fnt", xPos, yPos, FontSIZE, Color, false, LineSpacing, LineLength);
	TextSpecification Updating("The program will stop and you will need to put in some text.", "Resources/calibri (1).fnt", xPos - 0.9, yPos + 0.5, FontSIZE, Color, false, 1.5, LineLength);
	cout << "Loading Texture" << endl;

	//FONTS
	//RawTexture Calibri = Texture.CreateTexture("Resources/calibri.png", "FontAtlas", GL_TEXTURE0, 0, GL_RGBA);
	RawTexture Segoe = Texture.CreateTexture("Resources/segoe.png", "FontAtlas", GL_TEXTURE0, 0, GL_RGBA);
	//RawTexture candara = Texture.CreateTexture("Resources/candara.png", "FontAtlas", GL_TEXTURE0, 0, GL_RGBA);
	//RawTexture Arial = Texture.CreateTexture("Resources/arial.png", "FontAtlas", GL_TEXTURE0, 0, GL_RGBA);
	////

	RawTexture Gears = Texture.CreateTexture("Resources/images.png", "FontAtlas", GL_TEXTURE1, 1, GL_RGB);
	RawTexture ColorCube = Texture.CreateTexture("Resources/color-cube.png", "FontAtlas", GL_TEXTURE2, 2, GL_RGB);
	RawTexture PositiveIcon = Texture.CreateTexture("Resources/hiclipart.com.png", "FontAtlas", GL_TEXTURE3, 3, GL_RGBA);

	cout << "Texture Successfully Loaded" << endl;
	//Text is still just a bunch of verticies
	TextSpecification NewGame(UserInput, "Resources/calibri (1).fnt", xPos, yPos + 0.5, FontSIZE, Color, false, LineSpacing, LineLength);
	TextSpecification Play("Play", "Resources/calibri (1).fnt", xPos, yPos + 0.7, FontSIZE, Color, false, LineSpacing, LineLength);
	TextSpecification Exit("Exit Game", "Resources/calibri (1).fnt", xPos, yPos + 0.1, FontSIZE, Color, false, LineSpacing, LineLength);
	TextSpecification Settings("Settings", "Resources/calibri (1).fnt", xPos, yPos + 0.3, FontSIZE, Color, false, LineSpacing, LineLength);
	TextSpecification Description(" Welcome to my program. Currently, the buttons don't have any functionality, they are just for display. This took a lot of time but the next step is mouse input to make the boxes/text react when the Mouse hovers                                                                        over it.", "Resources/calibri (1).fnt", -0.68, 0.5, 0.31, { 0.0, 0.0, 0.0, 0.5 }, false, LineSpacing, 1.345); //0.8, 0.8, 1.0, 1.0
	TextSpecification GameTitle("Heroes Of The Dead", "Resources/calibri (1).fnt", -0.4, 0.8, 1.0, { 0.75, 0.7, 0.8, 1.0 }, LineSpacing, false, LineLength);
	//File     Edit     View    Project    Build
	//TEXTBOX
	TextSpecification SelectorOpacity("Opacity", "Resources/calibri (1).fnt", { -0.827, -0.83 }, { 0.25, 0.5 }, 0.3, { 1.0, 1.0, 1.0, 1.0 }, 1, CharSpacing, true, false, true);
	TextSpecification SelectorSize("Size", "Resources/calibri (1).fnt", { -0.807, -0.65 }, { 0.25, 0.5 }, 0.31, { 1.0, 1.0, 1.0, 1.0 }, 1, CharSpacing, true, false, true);
	TextSpecification SelectorPosition("Position", "Resources/calibri (1).fnt", { -0.827, -0.475 }, { 0.25, 0.5 }, 0.3, { 1.0, 1.0, 1.0, 1.0 }, 1, CharSpacing, true, false, true);
	TextSpecification SelectorTexture("Texture", "Resources/calibri (1).fnt", { -0.827, -0.30 }, { 0.25, 0.5 }, 0.3, { 1.0, 1.0, 1.0, 1.0 }, 1, CharSpacing, true, false, true);
	TextSpecification SaveBook("Save Book", "Resources/calibri (1).fnt", { 0.891, 1.0 }, { 1.0, 0.1 }, 0.3, { 1.0, 1.0, 1.0, 1.0 }, 1, CharSpacing, false, false, false);
	TextSpecification EraseBook("Erase Book", "Resources/calibri (1).fnt", { 0.770, 1.0 }, { 1.0, 0.1 }, 0.3, { 1.0, 1.0, 1.0, 1.0 }, 1, CharSpacing, false, false, false);
	TextSpecification TaskBarText("       File             Edit            View         Custom1      Custom2      Custom3", "Resources/calibri (1).fnt", { -1.0, 1.0 }, { 2.0, 0.1 }, 0.3, { 1.0, 1.0, 1.0, 1.0 }, 1, CharSpacing, false, false, false);
	TextSpecification FileText("  New  Open  Save  Save As  Erase  Print  Exit", "Resources/calibri (1).fnt", { -0.95, 1.01 }, { 2.0, 0.1 }, 0.3, { 1.0, 1.0, 1.0, 1.0 }, 1, 0.535, true, true, false);
	//                     Text,           FontFilePath,          Position,      Size,    FontSize,     Color,   int FontSlot|CharSpacing|MouseAccess|List|Centered
	TextSpecification ThisGUI(" GUI ", "Resources/calibri (1).fnt", { -0.89, 0.87 }, { 2.0, 0.1 }, 0.3, { 0.0, 0.5, 0.0, 1.0 }, 1, 0.535, false, true, false);
	TextSpecification ThisEditor(" Editor ", "Resources/calibri (1).fnt", { -0.79, 0.87 }, { 2.0, 0.1 }, 0.3, { 0.0, 1.0, 0.0, 1.0 }, 1, 0.535, false, true, false);
	float DetailsPosition = -0.96;
	glm::vec4 DetailsColor = { 0.1, 1.0, 1.0, 1.0 };
	//TextSpecification DetailsPage         ("Page ", "Resources/calibri (1).fnt", { DetailsPosition, 0.8 }, { 2.0, 0.1 }, 0.3, White, 1, 0.4, true, false, false);
	//Text
	TextSpecification DetailsNumberOfShapeDatas("Total ShapeDatas", "Resources/calibri (1).fnt", { DetailsPosition, 0.77 }, { 2.0, 0.1 }, 0.3, DetailsColor, 1, 0.535, true, true, false);
	TextSpecification DetailsShapeDataSelected("ShapeData", "Resources/calibri (1).fnt", { DetailsPosition, 0.71 }, { 2.0, 0.1 }, 0.3, DetailsColor, 1, 0.535, true, true, false);
	TextSpecification DetailsPositionSelected("Position", "Resources/calibri (1).fnt", { DetailsPosition, 0.65 }, { 2.0, 0.1 }, 0.3, DetailsColor, 1, 0.535, true, true, false);
	TextSpecification DetailsSizeSelected("Size", "Resources/calibri (1).fnt", { DetailsPosition, 0.59 }, { 2.0, 0.1 }, 0.3, DetailsColor, 1, 0.535, true, true, false);
	TextSpecification DetailsActiveTextureSelected("ActiveTexture", "Resources/calibri (1).fnt", { DetailsPosition, 0.53 }, { 2.0, 0.1 }, 0.3, DetailsColor, 1, 0.535, true, true, false);
	TextSpecification DetailsActionSelected("Action", "Resources/calibri (1).fnt", { DetailsPosition, 0.47 }, { 2.0, 0.1 }, 0.3, DetailsColor, 1, 0.535, true, true, false);
	TextSpecification DetailsColorSelected("Color", "Resources/calibri (1).fnt", { -0.84, 0.35 }, { 2.0, 0.1 }, 0.3, DetailsColor, 1, 0.535, true, true, false);
	glm::vec4 GroupDetailsColor = { 0.1, 1.0, 1.0, 1.0 };
	TextSpecification DetailsGroup("Group Details", "Resources/calibri (1).fnt", { DetailsPosition + 0.075, -0.345 }, { 2.0, 0.1 }, 0.3, PageCreator::White, 1, 0.535, true, true, false);
	TextSpecification TypeGroup("Type", "Resources/calibri (1).fnt", { DetailsPosition, -0.42 }, { 2.0, 0.1 }, 0.3, GroupDetailsColor, 1, 0.535, true, true, false);
	TextSpecification StartGroup("Start", "Resources/calibri (1).fnt", { DetailsPosition, -0.48 }, { 2.0, 0.1 }, 0.3, GroupDetailsColor, 1, 0.535, true, true, false);
	TextSpecification SizeGroup("Size", "Resources/calibri (1).fnt", { DetailsPosition, -0.54 }, { 2.0, 0.1 }, 0.3, GroupDetailsColor, 1, 0.535, true, true, false);
	TextSpecification OffsetGroup("ShapeData Offset", "Resources/calibri (1).fnt", { DetailsPosition, -0.60 }, { 2.0, 0.1 }, 0.3, GroupDetailsColor, 1, 0.535, true, true, false);
	TextSpecification TEXT_FPS("FPS", { DetailsPosition, -0.28 }, false, PageCreator::Purple);
	TextSpecification TEXT_PerPixel("PixelLength", { DetailsPosition, -0.21 }, false, PageCreator::Purple);
	ShapeData Circlest;



	//static 


	//GroupData FileTextGroup;
	//FileTextGroup.Color = Green;
	//FileTextGroup.Position = { -0.95, 0.9 };
	//TextData FileTextNEW;
	//FileTextNEW.Phrase = "Save";
	//
	//Text Text_Save(GUI);
	//Text_Save.
	//
	//Text Text_Erase(GUI);
	//Text_Erase.SetPosition({ -0.88, 0.9 });
	//Text_Erase.SetText("Erase");


	//TextData TextData_WelcomeDefault;
	//TextData_WelcomeDefault.Phrase = { " " };
	//
	//GroupData GroupData_WelcomeDefault;
	//GroupData_WelcomeDefault.Position = { -0.5, 0.0 };
	//GroupData_WelcomeDefault.Color = Rose;

	//GroupData Main_Default;
	//Main_Default.Position = { PageCreator::Origin };
	//Main_Default.Size = { 0.4, 0.8 };
	//Main_Default.Color = PageCreator::Green;
	//Main_Default.XYShapesPerRow = { 2, 2 };
	//Main_Default.ShapeDataSize = { 0.8, 0.8 };

	//Toggle NewToggle(GUI);


	//Grid_Testing.SetPosition();

	//Grid_Testing.PrintGroupShapes();

	TextData Annoying;
	Annoying.Phrase = "";
	Annoying.FontSize = 50;
	Annoying.Centered = false;

	//Main_Default.Position = { 0.0, 0.5 };
	//Main_Default.Color = PageCreator::White;

	bool YesCircle = true;
	Page Circles(5000);
	Circles.Init(ShapeShader);
	//Circles.AddCircle({ -0.65, 0.2 }, { 0.05, 0.05 }, 1.0);
	//Circles.AddShapeData(Circlest, true, false);
	//Circles.LoadThisPage();
	int xShapeDataPerRow = 2; //fine
	int yShapeDataPerRow = 6; //fine
	float xShapeDataGroupSize = 0.5;
	float yShapeDataGroupSize = 1.0;
	float xGridPos = -0.8; //fine
	float yGridPos = 0.5; //fine
	float xBoarderSize = 0.015;
	float yBoarderSize = 0.03;
	float xShapeDataSpacing = 0.025;
	float yShapeDataSpacing = 0.05;

	Loader Loader;



	//              XYShapeDatasPerRow, ShapeDataGroupSize,    ShapeDataGroupPosition,    ShapeDataSize,          Color,           Centered
	Grid TextureSelector({ 8, 1 }, { 2.0, 0.2 }, { -0.01, -0.85 }, { 0.54, 0.96 }, { 0.3, 0.55, 0.6, 1.0 }, true);
	Grid TextureSelectorOutline({ 8, 1 }, { 2.0, 0.2 }, { -0.01, -0.85 }, { 0.5, 0.9 }, { 0.5, 0.75, 0.8, 0.8 }, true);
	//Grid MultipleButtons({ 2, 9 }, { 0.3, 1.6 }, { -0.84, 0.1 }, { 0.52, 0.52 }, { 0.2, 0.3, 0.5, 1.0 }, true);
	//Grid MultipleButtonsOutline({ 2, 9 }, { 0.3, 1.6 }, { -0.84, 0.1 }, { 0.6, 0.6 }, { 0.0, 0.25, 0.3, 1.0 }, true);
	Grid LayersOutline1({ 1, 15 }, { 0.255, 1.55 }, { 0.68, 0.1 }, { 0.76, 0.80 }, { 0.9, 0.9, 0.9, 0.8 }, true);
	Grid LayersOutline2({ 1, 15 }, { 0.255, 1.55 }, { 0.88, 0.1 }, { 0.76, 0.80 }, { 0.9, 0.9, 0.9, 0.8 }, true);
	Grid Layers1({ 1, 15 }, { 0.255, 1.55 }, { 0.68, 0.1 }, { 0.74, 0.74 }, { 0.0, 0.15, 0.2, 1.0 }, true);
	Grid Layers2({ 1, 15 }, { 0.255, 1.55 }, { 0.88, 0.1 }, { 0.74, 0.74 }, { 0.0, 0.15, 0.2, 1.0 }, true);
	Grid Nodes({ 1, 15 }, { 0.225, 1.55 }, { 0.78, 0.1 }, { 0.02, 0.06 }, { 1.0, 1.0, 1.0, 1.0 }, true);
	Grid TaskBar({ 17, 1 }, { 2.0, 0.05 }, { 0.0, 0.97 }, { 1.0, 1.0 }, { 0.1, 0.1, 0.1, 1.0 }, true);

	glm::vec2 TaskPosition = { -0.874, 0.705 };
	glm::vec2 TaskSize = { 0.25, 0.48 };

	Grid TaskFile({ 1, 7 }, TaskSize, TaskPosition, { 1.0, 0.95 }, { 0.1, 0.1, 0.1, 1.0 }, true);


	ShapeData Color4;
	Color4.Color = { 64, 0.32, 0.76, 1.0 };

	ShapeData DeleteTest;
	DeleteTest.Position = { -0.5, -0.5 };
	DeleteTest.Size = { 0.5, 0.5 };

	ShapeData DeleteTest1;
	DeleteTest1.Position = { 0.5, 0.5 };
	DeleteTest1.Size = { 0.5, 0.5 };

	ShapeData DeleteTest2;
	DeleteTest2.Position = { -0.5, 0.5 };
	DeleteTest2.Size = { 0.5, 0.5 };

	ShapeData DeleteTest3;
	DeleteTest3.Position = { 0.5, -0.5 };
	DeleteTest3.Size = { 0.5, 0.5 };

	unsigned int Size = 4;
	int Position = 4;
	int NewPosition = 10;


	Page Editor(400); //
	Editor.Init(ShapeShader);
	Page PageFromFile(1000);
	PageFromFile.Init(ShapeShader);

	//MainBook.AddPage("Editor", ShapeShader);
	//cout << "got to point" << endl;

	//ShapeData Buffer1({ 0.0, 0.5 }, { 0.25, 0.5 });
	//Buffer1.Color = { 1.0, 1.0, 1.0, 1.0 };
	//Buffer1.ShapeDataisHighlight = false;
	//Buffer1.ActiveTexture = 3;
	//MainBook.Page[0].AddShapeData(Buffer1, true, false);
	//MainBook.Page[0].LoadThisPage();
	//
	//ShapeData Buffer2({ 0.0, -0.2 }, { 0.25, 0.5 });
	//Buffer2.Color = { 1.0, 1.0, 1.0, 1.0 };
	//Buffer2.ShapeDataisHighlight = false;
	//Buffer2.ActiveTexture = 3;
	//MainBook.Page[0].AddShapeData(Buffer2, true, false);
	//MainBook.Page[0].LoadThisPage();
	//
	//ShapeData Buffer3({ 0.0, -0.8 }, { 0.25, 0.5 });
	//Buffer3.Color = { 1.0, 1.0, 1.0, 1.0 };
	//Buffer3.ShapeDataisHighlight = false;
	//Buffer3.ActiveTexture = 3;
	//MainBook.Page[0].AddShapeData(Buffer3, true, false);
	//MainBook.Page[0].LoadThisPage();



	//NewGrid PolyGrid1(MainBook.Page[0]);
	//NewGrid PolyGrid2(MainBook.Page[0]);
	////NewGrid PolyGrid3(MainBook.Page[0]);
	//
	//PolyGrid1.SetPosition(Origin);
	//PolyGrid1.SetSize({ 0.5, 0.5,});
	//PolyGrid2.SetPosition({0.6, 0.6});
	//PolyGrid2.SetSize({ 0.5, 0.5, });


	//FileSystem.SaveBook(MainBook);
	//FileSystem.LoadBook(MainBook);




	///////////////////////////TESTING TESTING/////////////////////////////////////////


	//This ^^ makes a grid of ShapeDatas that you specifiy by rows/columns, and has now filled part of the ShapeData container



	// xBoxOffset, yBoxOffset;
	//Loader.AddShapeDataGridToPage(MainScreen, GridButton, 4, 4, 0.5, 1.0, -0.3, 0.7, 0.1, 0.1, 0.05, 0.05, { 0.15, 0.2, 0.3, 1.0});

	//Renderer.TextInit(FontShader, Calibri);
	//Renderer.BeginTextBatch();
	//Renderer.AddTextToBatch(NewGame);
	//Renderer.AddTextToBatch(Settings);
	//Renderer.AddTextToBatch(Play);
	//Renderer.AddTextToBatch(Exit);
	//Renderer.AddTextToBatch(Description);
	//Renderer.AddTextToBatch(GameTitle);
	//Renderer.AddTextToBatch(Header);
	//Renderer.LoadQuadBatch();

	//GUI.ChangeShapeDataTexture(23, 0, true);
	//GUI.ChangeShapeDataTexture(24, 1, true);
	//GUI.ChangeShapeDataTexture(25, 2, true);
	//GUI.ChangeShapeDataTexture(26, 3, true);
	//GUI.ChangeShapeDataTexture(27, 3, true);
	//GUI.ChangeShapeDataTexture(28, 3, true);
	//GUI.ChangeShapeDataTexture(29, 3, true);
	//GUI.ChangeShapeDataTexture(30, 3, true);



	//RenderData S_TextData;

	int LoopCounter = 0;
	int i = 0;
	float x = -1.0;

	int state = 0;
	bool MousePress = false;
	int Marker = 0;
	int PressTracker = false;
	bool Move = false;
	glm::vec4 PrepareColor;
	//M_InputSpecs M_Details;
	//MouseStats MouseStats;

	float StartTime = 0.0;
	bool TimerReady = false;
	bool Once = true;

	bool BeginAction = false;

	bool Init = false;
	bool ggColor = true;
	int Counter = 0;

	bool ScreenController = false;
	bool ToggleController = false;


	double xScroll = 0;
	double yScroll = 0;
	glm::vec2 LastSize;

	int TopCap = 10;
	Mouse.ScrollAutoSet(5);
	int DefaultCap = 10;
	glm::vec2 GridShapeDataSize = { 0.0, 0.0 };

	ShapeData* GUIShapeDataHoveredOLD = nullptr;
	ShapeData* GUIShapeDataSelectedOLD = nullptr;
	ShapeData* EDITShapeDataHoveredOLD = nullptr;
	ShapeData* EDITShapeDataSelectedOLD = nullptr;

	int EditorShapeDataHovered = 0;
	int EditorShapeDataSelected = 0;
	int EditorGridSelected = 0;
	int GUIShapeDataSelected = 0;
	int GUIShapeDataHovered = 0;

	int EDITCurrentLayer = 1;
	int LayerLevel = 48;


	int AllSelections[100];
	int* SelectionsResult = nullptr;

	for (int i = 0; i < 100; i++)
	{
		AllSelections[i] = -1;
	}

	float ResizeSpeed = 0.04;


	bool MultiSelector = false;
	int MultiSelectID = -1;
	glm::vec2 MultiSelectPos = { 0.0, 0.0 };
	bool SizeSelector = 0;
	bool ShapeDataGroupSizeSelector = 0;
	bool GridToggle = 0;

	int HighlightCount = 0;
	bool Highlight = false;
	int HighlightShapeData = 0;
	bool TaskBarList = false;


	int ShapeData0 = 0;

	//ShapeData Buffer1({ -0.84, 0.82 }, { 0.025, 0.05 });
	//Buffer1.Color = { 1.0, 1.0, 1.0, 1.0 };
	//Buffer1.ShapeDataisHighlight = false;
	//Buffer1.ActiveTexture = 3;
	//Editor.AddShapeData(Buffer1, true, false);
	//Loader.LoadPage(Editor);
	//
	//ShapeData Buffer2({ -0.84, 0.64 }, { 0.025, 0.05 });
	//Buffer2.Color = { 1.0, 1.0, 1.0, 1.0 };
	//Buffer2.ShapeDataisHighlight = false;
	//Buffer2.ActiveTexture = 3;
	//Editor.AddShapeData(Buffer2, true, false);
	//Loader.LoadPage(Editor);
	//
	//ShapeData Buffer3({ -0.84, 0.46 }, { 0.025, 0.05 });
	//Buffer3.Color = { 1.0, 1.0, 1.0, 1.0 };
	//Buffer3.ShapeDataisHighlight = false;
	//Buffer3.ActiveTexture = 3;
	//Editor.AddShapeData(Buffer3, true, false);
	//Loader.LoadPage(Editor);

	//ShapeData Buffer4({ 0.0, 0.0 }, { 1.0, 1.0 });
	//Buffer4.Color = { 1.0, 1.0, 1.0, 1.0 };
	//Buffer4.ShapeDataisHighlight = false;
	//Buffer4.ActiveTexture = 1;
	//GUI.AddShapeData(Buffer4, true, false);
	//Loader.LoadPage(GUI);
	//GUI.PrintShapeDataSheet();
	float CurrentScrollPosition = 0.0;
	float LastScrollPosition = 0.0;

	float LastTimeStamp = 0.0;
	bool ChangeGrid = false;

	bool YesChangeColor = false;
	bool OneWay = false;

	int XYX = 1;
	int YXY = 2;

	int Sup = 100;
	glm::vec2 ListPosition = { 0.4, -0.015 };

	float FramesPerSecond = 0.0;
	float TotalFramesPerSecond = 0.0;

	glm::vec2 HSize = { -0.8457, -0.53454 };
	TextSpecification SizeText(" -1 ", "Resources/calibri (1).fnt", { 0.0, 0.0 }, { 1.0, 1.0 }, 0.3, { 1.0, 0.0, 1.0, 1.0 }, 1, LineSpacing, true, false, true);


	Page* PageSelected = &MainBook.Page[0];
	//Selection EditorSelector(*PageSelected);

	glm::vec4 NewSelectedColor = { 0.0, 0.0, 0.0, 0.0 };
	glm::vec4 LastSelectedColor = { 0.0, 0.0, 0.0, 1.0 };


	bool HighlightHover = true;

	float PreviousTime = 0.0;
	float CurrentTime = 0.0;
	float FrameTime = 0.0;
	int FPSCount;
	const int NUM_SAMPLES = 10;
	float FrameTimes[NUM_SAMPLES];
	int CurrentFrame = 0;
	float AverageFrameTime = 0;
	int FrameCount = 0;
	float FPS = 0;

	int PixelOffset = 8;
	bool ShowGUI = true;



	string StringSelected = "";
	int TextCount = 0;

	bool PlayAction = false;
	float ActionTest1 = 0.8;
	float ActionTest2 = 0.8;
	float ActionTest3 = 0.8;

	double Time = 0.00;
	Oscillation MyAction;

	ElementAction CreateGrid_Act;

	CreateGrid_Act[SIZE][1] = &MyAction;

	MyAction.Speed = 1.0;
	MyAction.PausedTime = 0.00;
	MyAction.TotalTimePaused = 0.00;
	MyAction.OutputOffset = -1.0;
	MyAction.LastResult = 0.00;
	MyAction.Play();

	NewCharacter AnyCharacter(MainBook.Page[0], "Resources/segoe.fnt");
	//NewCharacter AnyCharacter2(MainBook.Page[0], "Resources/arial.fnt");

	int X;

	//Set
	//Keyboard::KeyButton[GUI_LEFT_PRESSED][WITH_DEFAULT] = CreatorFunctions[SHAPE_1][POSITION][X];
	//Keyboard::KeyButton[GUI_LEFT_PRESSED][WITH_DEFAULT]();

	int CurrentAttribute = 0;

	PageItemData PageItem_FirstSlider;
	PageItem_FirstSlider.Position = { 0.0, -0.2 };

	SliderData Slider_FirstSlider;
	Slider_FirstSlider.Description = " Hello";
	//Slider_FirstSlider.Ratio = "14.32";
//	Slider FirstSlider(GUI);
	//Slider FirstSlider0(MainBook.Page[0], PageItem_FirstSlider, Slider_FirstSlider);

	Slider_FirstSlider.Description = " Hello";
	//Slider_FirstSlider.Ratio = "14.35";
	PageItem_FirstSlider.Position = { 0.0, -0.3 };
	//Slider FirstSlider1(MainBook.Page[0], PageItem_FirstSlider, Slider_FirstSlider);
	
	Slider_FirstSlider.Description = " Hello";
	//Slider_FirstSlider.Ratio = "14.37";
	PageItem_FirstSlider.Position = { 0.0, -0.4 };
	//Slider FirstSlider2(MainBook.Page[0], PageItem_FirstSlider, Slider_FirstSlider);
	
	Slider_FirstSlider.Description = " Hello";
	//Slider_FirstSlider.Ratio = "14.38";
	PageItem_FirstSlider.Position = { 0.0, -0.5 };
	//Slider FirstSlider3(MainBook.Page[0], PageItem_FirstSlider, Slider_FirstSlider);
	
	
	Quad FontReference(MainBook.Page[0]);
	FontReference.SetColor(PageCreator::Purple);
	FontReference.SetSize(FontReference.ApplySizeConversion({ 1, 4000 }, S_PIXEL_TO_COMPUTER));
	FontReference.SetPosition({0.0, 0.0});
	
	Quad FontReference2(MainBook.Page[0]);
	FontReference2.SetColor(PageCreator::Purple);
	FontReference2.SetSize(FontReference.ApplySizeConversion({ 4000, 1 }, S_PIXEL_TO_COMPUTER));

	ShapeGroupData FontRefGroup;
	FontRefGroup.Position = { 0.0, 0.0 };
	FontRefGroup.Size = FontReference.ApplySizeConversion({ 100, 25 }, S_PIXEL_TO_COMPUTER);
	FontRefGroup.Color = PageCreator::White;
	//FontRefGroup.PageItemID = 98867;
	TextData FontRefText;
	string String_FixFont = " Hello";
	FontRefText.Phrase = String_FixFont;
	FontRefText.FontSize = 50;
	FontRefText.Centered = false;
	FontRefText.EndStart = true;
	
	Text FixFont(MainBook.Page[0], FontRefGroup, FontRefText);
	glm::vec4 TextLook = { 0.2, 0.5, 0.0, 1.0 }; // 0.34, 0.76, 100px

	glm::vec2 lineSize = FontReference2.ApplySizeConversion({0, 100}, S_PIXEL_TO_COMPUTER);

	//Taymor
	//FirstSlider0.SetDescription("i don't know what to do right now");
	//FirstSlider1.SetDescription("tryreuuosey");
	//FirstSlider2.SetDescription("Testing");
	//FirstSlider3.SetDescription("Hoping");
	//FirstSlider0.SetDescription("your fucked");

	//Text UpdateDesc(MainBook.Page[0], FirstSlider0[RATIO]);
	//
	//UpdateDesc.SetText("This is dope");

	//PageGroup Test_PageGroup(MainBook.Page[0]);

	//MainBook.Page[0].PrintShape(23);
	//FirstSlider0.PrintGroupShapes();

	//See.SetColor({0.0, 1.0, 0.6, 1.0});
	//See.SetText("Saturation");
	//See.SetColor(PageCreator::Orange);

	//FirstSlider2.ReCalibrateID();
	//FirstSlider0.PrintGroupShapes();

	//Quad ThisShape(GUI, 57);
	//ThisShape.SetColor(PageCreator::White);
	//ThisShape.SetPosition({0.0, 0.0});

	//Slider RetreivedSlider(MainBook.Page[0], 22);
	//Log::LogInt("Shape start ID of page item",Test_PageGroup.FindPageItem(3));
	//RetreivedSlider.SetDescription("okay cool");
	//RetreivedSlider.SwitchToSlider(46);
	//RetreivedSlider.SetDescription("yesssss");

	//Quad Square(GUI);
	//Square.SetPosition({-0.5, 0.0});

	Log::LogString("Before Slider editing");
	//FirstSlider1.SetPosition({ 0.4, 0.3 });
	//FirstSlider2.SetPosition({ -0.4, 0.3 });
	//FirstSlider3.SetPosition({ 0.4, -0.3 });

	//FirstSlider0.PrintGroupShapes();
	Log::LogString("Before Copy");
	//Slider CopySlider(MainBook.Page[0], 22);
	
	//CopySlider.SetPosition({ 0.4, 0.3 });
	//MasterElement& TheMaster = Square;

	cout << "Look here! " << endl;
	PageItem_FirstSlider.Position = { 0.0, -0.9 };
	Log::LogInt("unused slider start id", MainBook.Page[0].ShapeAmount());
	Slider UnusedSlider(MainBook.Page[0], PageItem_FirstSlider, Slider_FirstSlider);
	
	UnusedSlider.SetPosition({ 0.6, -0.7 });
	//UnusedSlider.SetDescription("what the fuck");
	//UnusedSlider.PrintGroupShapes();
	//UnusedSlider.ReCalibrateID();
	ShapeGroupData Debug_Shape;
	Debug_Shape.Position = {-0.5, -0.5};
	Debug_Shape.Size = {0.35, 0.25};


	lPageGroup l_PageGroup;
	lPageItem RetreivePageItem;
	lShapeGroup l_ShapeGroup;
	lShapeData ShapeDataHolder;

	lPageItem NewPageItem;
	NewPageItem.Position = 4;


	//LoadedShape = ShapeGroup.Switch(i);
	//CurrentShapeGroup.Position = 10;
	//CurrentShapeGroup.Size = 43;
	//CurrentShapeGroup.Color = 35;
	//LoadedShape.ShapeGroup.PageItem = CurrentPageItem;
	//ShapeGroup.SetShapeGroup(CurrentPageItem);






	typedef void(*Master_P)();
	while (!glfwWindowShouldClose(window))
	{

		Time = glfwGetTime();
		PreviousTime = glfwGetTime();
		//BackgroundColor & Refresh

		glClearColor(0.1, 0.1, 0.1, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		//Setup
		int MouseState = Mouse.GetMouseState(window, glfwGetTime(), 0.3, 0.4);
		KeyResult KeyState = Keyboard.GetKeyBoardState(window, glfwGetTime(), 0.3, 0.4);
		EditorShapeDataHovered = MainBook.Page[0].FindShapeData(Mouse.xPos, Mouse.yPos, false);
		GUIShapeDataHovered = GUI.FindShapeData(Mouse.xPos, Mouse.yPos, false);

		//Shape = 1
		//ShapeGRoup = 2
		//PageItem = 3
		//PageGroup = 4
		if (KeyState.Key1 == GUI_1_CLICKED)
		{
			cout << "Tried" << endl;
			Quad Shape_0(GUI);
		}

	//	UnusedSlider.SetPosition({Mouse.xPos, Mouse.yPos});

		if (KeyState.Key1 == GUI_2_CLICKED)
		{
			//ShapeGroup ShapeGroup_0(GUI);
		}

		if (KeyState.Key1 == GUI_3_CLICKED)
		{
			//PageGroupItem PageItem_0(GUI);
		}

		if (KeyState.Key1 == GUI_4_CLICKED)
		{
			//PageGroup PageGroup_0(GUI);
		}

		
		//FirstSlider0.SetPosition({Mouse.xPos,Mouse.yPos});

		//PageCreator::SetQuadSelected(MouseState, EditorShapeDataHovered);

		//Text_Master.SetPosition({ Mouse.xPos, Mouse.yPos});

		//FirstSlider0.SetPosition({Mouse.xPos, Mouse.yPos});

		//cout << "PageItem ID: " << Test_PageGroup.FindPageItem(true, Mouse.xPos, Mouse.yPos) << endl;
       //  cout << "PageGroupID: " << FirstSlider0.FindShapeGroup(true, Mouse.xPos, Mouse.yPos) << endl;
		//if (MouseState == GUI_RIGHT_CLICKED)
		//{
		//	cout << Mouse.xPos << " " << Mouse.yPos << endl;
		//}
		//cout << KeyState.Alt << "  " << KeyState.Shift << "  " << KeyState.Ctrl << "  " << KeyState.Caps << "  " << KeyState.Key1 << "  " << endl;
		
		//int SliderID = Test_PageGroup.FindPageItem(true, Mouse.xPos, Mouse.yPos);

		//TheMaster.SetPosition({Mouse.xPos, Mouse.yPos});

		//if (MouseState != 0)
		//{
		//	cout << MouseState << endl;
		//}

		//if (MouseState == GUI_MOUSELEFT_CLICKED && SliderID > -1)
		//{
		//	cout << "Slider switched" << endl;
		//	RetreivedSlider.SwitchToSlider(SliderID);
		//}
		//
		//if (KeyState.CurrentAscii != -1 && KeyState.Key1 != 0)
		//{
		//	//NewCharacter::PrintCharacter(KeyState.CurrentAscii);
		//}

		///////////////////Left/////////////
	
		if (KeyState.Key1 == GUI_F1_CLICKED || KeyState.Key1 == GUI_F1_PRESSED)
		{
			if (TextLook[0] >= 1 )
			{
				TextLook[0] -= 1;
			}
		}

		if (KeyState.Key1 == GUI_F2_CLICKED || KeyState.Key1 == GUI_F2_PRESSED)
		{
			if (TextLook[0] <= 9 )
			{
				TextLook[0] += 1;
			}
				cout << TextLook[0] << " " << TextLook[1] << " " << TextLook[2] << " " << TextLook[3] << endl;
		}

		if (KeyState.Key1 == GUI_F3_CLICKED || KeyState.Key1 == GUI_F3_PRESSED)
		{
			if (TextLook[1] > 1)
			{
				TextLook[1] -= 1;
			}
				cout << TextLook[0] << " " << TextLook[1] << " " << TextLook[2] << " " << TextLook[3] << endl;
		}

		if (KeyState.Key1 == GUI_F4_CLICKED || KeyState.Key1 == GUI_F4_PRESSED)
		{
			if (TextLook[1] <= 9 )
			{
				TextLook[1] += 1;
			}
				cout << TextLook[0] << " " << TextLook[1] << " " << TextLook[2] << " " << TextLook[3] << endl;
		}

		///////////////////Right//////////////////////////

		if (KeyState.Key1 == GUI_F5_CLICKED || KeyState.Key1 == GUI_F5_PRESSED)
		{
			if (TextLook[2] >= 1)
			{
				TextLook[2] -= 1;
			}
				cout << TextLook[0] << " " << TextLook[1] << " " << TextLook[2] << " " << TextLook[3] << endl;
		}

		if (KeyState.Key1 == GUI_F6_CLICKED || KeyState.Key1 == GUI_F6_PRESSED)
		{
			if (TextLook[2] <= 9)
			{
				TextLook[2] += 1;
			}
				cout << TextLook[0] << " " << TextLook[1] << " " << TextLook[2] << " " << TextLook[3] << endl;
		}

		if (KeyState.Key1 == GUI_F7_CLICKED || KeyState.Key1 == GUI_F7_PRESSED)
		{
			if (TextLook[3] > 1)
			{
				TextLook[3] -= 1;
			}
				cout << TextLook[0] << " " << TextLook[1] << " " << TextLook[2] << " " << TextLook[3] << endl;
		}

		if (KeyState.Key1 == GUI_F8_CLICKED || KeyState.Key1 == GUI_F8_PRESSED)
		{
			if (TextLook[3] <= 9)
			{
				TextLook[3] += 1;
			}
			cout << TextLook[0] << " " << TextLook[1] << " " << TextLook[2] << " " << TextLook[3] << endl;
		}

		////////////////////Font Size//////////////////////////////////

		if (KeyState.Key1 == GUI_F9_CLICKED || KeyState.Key1 == GUI_F9_PRESSED)
		{
			//FixFont.OffsetFont(-1);
			cout << TextLook[0] << " " << TextLook[1] << " " << TextLook[2] << " " << TextLook[3] << endl;
		}

		if (KeyState.Key1 == GUI_F10_CLICKED || KeyState.Key1 == GUI_F10_PRESSED)
		{
			//FixFont.OffsetFont(1);
			cout << TextLook[0] << " " << TextLook[1] << " " << TextLook[2] << " " << TextLook[3] << endl;
		}

		ShapeShader.SetVec4f("TextLook", TextLook);

		//FixFont.SetPosition({Mouse.xPos, Mouse.yPos});
		//

		//if (KeyState.Key1 == GUI_U_CLICKED)
		//{
		//	//MainBook.Page[0].PrintShape(EditorShapeDataHovered);
		//	FirstSlider.OffsetPosition({0.0, -0.1});
		//}

		//FirstSlider.SetPosition({Mouse.xPos, Mouse.yPos});

		//cout << GUIShapeDataHovered << endl;
		//cout << EditorShapeDataHovered << endl;

		//cout << Mouse.xPos << " " << Mouse.yPos << endl;


		//cout << Creator.QuadSelected.CurrentShapeData.Position[0] << endl;

		//Alternate Attributes go up
		//if (KeyState.Key1 == GUI_DOWN_CLICKED && KeyState.Alt == true)
		//{
		//	if (CurrentAttribute > 0)
		//	{
		//		CurrentAttribute--;
		//	}
		//}
		//
		////Alternate Attributes go down
		//if (KeyState.Key1 == GUI_UP_CLICKED && KeyState.Alt == true)
		//{
		//	if (CurrentAttribute < 5)
		//	{
		//		CurrentAttribute++;
		//	}
		//	else
		//	{
		//		CurrentAttribute = 0;
		//	}
		//}
		//
		//if (KeyState.Key1 == GUI_UP_PRESSED || KeyState.Key1 == GUI_UP_CLICKED && KeyState.Alt != true)
		//{
		//	if (CreatorFunctions[SHAPE_1][CurrentAttribute][0] != nullptr)
		//	{
		//		//(Creator.*CreatorFunctions[SHAPE_1][CurrentAttribute][0])();
		//		//Traitor.OffsetPosition({0.0, 0.00166}, {false, true});
		//	}
		//}
		//
		//if (KeyState.Key1 == GUI_DOWN_PRESSED || KeyState.Key1 == GUI_DOWN_CLICKED && KeyState.Alt != true)
		//{
		//	if (CreatorFunctions[SHAPE_1][CurrentAttribute][1] != nullptr)
		//	{
		//		//(Creator.*CreatorFunctions[SHAPE_1][CurrentAttribute][1])();
		//	}
		//}
		//
		//if (KeyState.Key1 == GUI_RIGHT_PRESSED || KeyState.Key1 == GUI_RIGHT_CLICKED && KeyState.Alt != true)
		//{
		//	if (CreatorFunctions[SHAPE_1][CurrentAttribute][2] != nullptr)
		//	{
		//		//(Creator.*CreatorFunctions[SHAPE_1][CurrentAttribute][2])();
		//	}
		//}
		//
		//
		//cout << CurrentAttribute << endl;
		//
		////Left
		//if (KeyState.Key1 == GUI_LEFT_PRESSED || KeyState.Key1 == GUI_LEFT_CLICKED && KeyState.Alt != true)
		//{
		//	//Check
		//	if (CreatorFunctions[SHAPE_1][CurrentAttribute][3] != nullptr)
		//	{
		//		//PlayFunction
		//		//(Creator.*CreatorFunctions[SHAPE_1][CurrentAttribute][3])();
		//	}
		//}
		//
		////cout << Mouse.xPos << " " << Mouse.yPos << endl;
		//

		//if (KeyState.CurrentAscii != -1)
		//{
		//	string& SliderDescripion = RetreivedSlider.CurrentSliderData.Description;
		//	SliderDescripion += char(KeyState.CurrentAscii);
		//	RetreivedSlider.SetDescription(SliderDescripion);
		//}
		//if (KeyState.Key1 == GUI_BACKSPACE_CLICKED || KeyState.Key1 == GUI_BACKSPACE_PRESSED)
		//{
		//	string& SliderDescripion = RetreivedSlider.CurrentSliderData.Description;
		//	if (SliderDescripion.size()> 1)
		//	{
		//		SliderDescripion.erase(SliderDescripion.size() - 1);
		//		RetreivedSlider.SetDescription(SliderDescripion);
		//	}
		//}
	   ///
		//
		//if (MouseState == GUI_MOUSERIGHT_CLICKED)
		//{
		//	EditorFunction[0](4078);
		//}
		//else if(MouseState == GUI_MOUSELEFT_CLICKED)
		//{
		//	EditorFunction[1](63);
		//}

		//PageCreator.PlayFunction();
	
		Renderer.DrawPage(ShapeShader, ColorCube, Segoe, PositiveIcon, GUI);
		Renderer.DrawPage(ShapeShader, ColorCube, Segoe, PositiveIcon, *PageSelected);
		//Renderer.DrawCircle(ShapeShader, Circles);


		Mouse.GetMousePosition(window);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

		glfwTerminate();
		Editor.DeletePage();
		GUI.DeletePage();

	return 0;
}

int ProcessInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	//Up
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		//Translation = { 0.0, 0.01, 0.0 };
		return 1;
	}

	//Down
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		//Translation = { 0.0, -0.01, 0.0 };
		return 1;
	}

	//Right
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		//Translation = { 0.01, 0.0, 0.0 };
		return 1;
	}

	//Left 
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		//Translation = { -0.01, 0.0, 0.0 };
		return 1;
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		//Translation = { -0.01, 0.0, 0.0 };
		return 1;
	}

	

}

string ProcessInputString(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
	{
		
		return "T";
	}
	else
	{
		return "";
	}
}


void MouseCallback(GLFWwindow* window, double xPos, double yPos)
{
	MouseX = xPos;
	MouseY = yPos;
}

bool Switch(bool Switch)
{
	
	cout << Switch << endl;

	if (Switch == true)
	{
		return false;
	}
	if (Switch == false)
	{
		cout << "Hit" << endl;
		
		return true;
	}
	
}

//Returns x and y length of each pixel based on coordinate state
glm::vec2 Pixellength(double SCR_Height, double SCR_Width)
{
	return { 1.0/SCR_Width, 1.0 / SCR_Height};
}






int DFS(int x, int y, Node** EngGrid)
{
	int Found = 1;
	Node& Current = EngGrid[x][y];
	Current.Visited = true;

	Node* Right = nullptr;
	Node* Bottom = nullptr;
	Node* Left = nullptr;
	Node* Top = nullptr;

	if ((y + 1) <= 4)
	{
		Right = &EngGrid[x][y + 1];
	}
	if ((x + 1) <= 4)
	{
		Bottom = &EngGrid[x + 1][y];
	}
	if ((y - 1) > 0)
	{
	    Left = &EngGrid[x][y - 1];
	}
	if ((x - 1) > 0)
	{
	    Top = &EngGrid[x - 1][y];
	}

	//Right
	if (Right != nullptr)
	{
		if (Current.Color == Right->Color && Right->Visited != true)
		{
			Found += DFS(Right->Posx, Right->Posy, EngGrid);
		}
	}
	

	//Bottom
	if (Bottom != nullptr)
	{
		if (Current.Color == Bottom->Color && Bottom->Visited != true)
		{
			Found += DFS(Bottom->Posx, Bottom->Posy, EngGrid);
		}
	}

	//Left
	if (Left != nullptr)
	{
		if (Current.Color == Left->Color && Left->Visited != true)
		{
			Found += DFS(Left->Posx, Left->Posy, EngGrid);
		}
	}

	//Top
	if (Top != nullptr)
	{
		if (Current.Color == Top->Color && Top->Visited != true)
		{
			Found += DFS(Top->Posx, Top->Posy, EngGrid);
		}
	}
	return Found;
}

void FindMaxColor(Node** EngGrid)
{
	double Time1 = glfwGetTime();
	
	int MaxColorCount = 0;
	int MaxColor = -1;
	int DFSCount = 0;

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (EngGrid[i][j].Visited == false)
			{
				DFSCount++;
				int DFSResult = DFS(i, j, EngGrid);
				if (DFSResult > MaxColorCount)
				{
					MaxColorCount = DFSResult;
					MaxColor = EngGrid[i][j].Color;
				}
			}
			else
			{
				cout << "Already Visited: " << i << " " << j << endl;
			}
		}
	}
    
	cout << "MaxColorCount: " << MaxColorCount << endl;
	cout << "MaxColor: " << MaxColor << endl;

	double Time2 = glfwGetTime();

	double FinalTime = Time2 - Time1;
	cout << "Total Time " << FinalTime << endl;
	cout << DFSCount << endl;

}
