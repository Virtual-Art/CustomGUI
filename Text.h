#ifndef THISTEXT
#define THISTEXT

#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include "ElementGroup.h"

using namespace std;

struct TextData
{
	string Phrase;
	string FontFile;
	float FontSize = 16.0;
	float CharSpacing = -10.0; //in pixels 0.535
	float LineSpacing = 1.0; //in pixels
	float LineLength = 0.5; // in.....
	glm::vec2 CursorPosition = { 0.0, 0.0 };
	float FontSlot = 2;
	bool List = true;
	bool Centered = false;
	bool EndStart = false;
};

class Text : public ShapeGroup
{

public:

	bool Editorized = false;
	bool BeenCentered = false;
	//Public Member Functions
	TextData CurrentTextData;
	CharacterData CurrentCharacterData;

	Text() { LoadedBook = nullptr; CurrentllShapeGroup = nullptr; };
	Text(llBookData* llBookData);
	Text(llBookData* llBookData, llShapeGroupData* llShapeGroup, TextData& TextData);
	Text(llShapeGroupData* llShapeGroup);

	//Basic Text Constructors
	Text(Page& Page);
	Text(Page& Page, ShapeGroupData& ShapeGroupData, TextData& TextData);
	Text(Page& Page, ShapeData& ShapeData, TextData& TextData);
	Text(Page& Page, int GroupID);
	void llInit(llBookData* llBook) { LoadedBook = llBook; Editorized = true; };
	void llInit(llBookData* llBookData, llShapeGroupData* llShapeGroup, TextData& TextData);

	void Add_Default() override;
	//void Add_Duplicate() override;
	void Add_Insert() override;
	void Delete() override;


	glm::vec2 GetSize() { return CurrentllShapeGroup->Size; };
	glm::vec2 GetSize(int xPixels, int yPixels) {return { CurrentllShapeGroup->Size[X_AXIS] + xPixels * PIXEL, CurrentllShapeGroup->Size[Y_AXIS] + yPixels * PIXEL };};

	Text(Page& Page, string Text, glm::vec2 Position);

	//Single Value Text Constructors
	Text(Page& Page, int Integer, string Description, glm::vec2 Position);
	//Text(Page& Page, GroupData& GroupData, TextData& TextData, int Integer, string Description);
	Text(Page& Page, int GroupID, int Integer, string Description);

	void ShapeToGroup(ShapeData& ShapeData);
	void Init(Page& Page, string Text, glm::vec2 Position);
	string GetText() { return CurrentllShapeGroup->Shape->Text; };
	
	//Retreives the last state of the ShapeGroup and loads the object
	ShapeData& Switch(int ShapeID) override
	{
		if (Initialized == true)
		{
			if (IsInBounds(ShapeID) == true)
			{
				if (SetInStone != true)
				{
					LoadedShape = CurrentPage->GetShapeDataR(ShapeID);
					CurrentShapeGroup = LoadedShape.ShapeGroup;
					Log::LogString("Setting phrase to: " + LoadedShape.Text);
					CurrentTextData.Phrase = LoadedShape.Text;
					CurrentTextData.Centered = LoadedShape.TextCentered;
					CurrentTextData.EndStart = LoadedShape.EndStart;
					return LoadedShape;
				}
			}
			else
			{
				Log::LogString("Switch Error:: ID out of bounds");
			}
		}
		else
		{
			Log::LogString("Switch Error:: Shape Group Not Initialized");
		}
		return LoadedShape;
	}

	//Create
	void SetShape();
	void SetTextGroup(ShapeData& ShapeData, TextData& TextData);
	void SetllTextGroup(llShapeGroupData* llShapeGroup, TextData& TextData);
	void SetTextGroup(ShapeGroupData& ShapeGroup, TextData& TextData);
	
	void CreateText();
	void AddText();

	void CreatellText();
	void AddllText();

	//Update
    void NewReplaceText();
	void NewReplacellText();
	void Update(); 
	void llUpdate();

	//MemberFunctions
	void SetText(string Text);
	void SetllText(string Text);
	void SetFont(int FontSize);
	void CenterText();
	void OffsetFont(int FontSize);
	void SetCharSpacing(float LineWidth) {};
	void SetLineWidth(float LineWidth) {};
	void SetLineSpacing(float LineWidth) {};


private:

	//Private Functions
	void SetTextSize();
	void SetllTextSize();



	bool QueryLineRestart(glm::vec2 CursorPosition, float MaxLine);
	float AdvanceCursor(CharacterData& CharacterData, TextData& TextData);
	glm::vec2 NextLine(glm::vec2 StartPosition, CharacterData CharacterData, glm::vec2 CurrentPosition, float FontSize, float Spacing, float xStart);
	glm::vec2 GetCharacterPosition(CharacterData& CharacterData, glm::vec2 Pos, float FontSize, bool LineStart);
	glm::vec2 GetCharacterSize(CharacterData& CharacterData, glm::vec2 CharPosition, int SCR_Height, int SCR_Width, float FontSize);

};


#endif


//TextBoxFunctions
//int PrintVector2(glm::vec2 Vector, glm::vec2 Position, glm::vec4 Color);
//int PrintVector3(glm::vec3 Vector, glm::vec2 Position, glm::vec4 Color);
//int PrintVector4(glm::vec4 Vector, glm::vec2 Position, glm::vec4 Color);
//int PrintFloat(float Float, glm::vec2 Position, glm::vec4 Color);
//int PrintInt(int Int, glm::vec2 Position, glm::vec4 Color);
//int PrintBool(bool Bool, glm::vec2 Position, glm::vec4 Color);
//
//void ChangeVector2(int TextStart, glm::vec2 Vector, glm::vec2 Position, glm::vec4 Color);
//void ChangeVector3(int TextStart, glm::vec2 Vector, glm::vec2 Position, glm::vec4 Color);
//void ChangeVector4(int TextStart, glm::vec4 Vector, glm::vec2 Position, glm::vec4 Color);
//void ChangeFloat(int TextStart, float Float, glm::vec2 Position, glm::vec4 Color);
//void ChangeInt(int TextStart, int Int, glm::vec2 Position, glm::vec4 Color);
//void LoadText(Page* Page, int ElementID);