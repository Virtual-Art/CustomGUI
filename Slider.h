#ifndef	SLIDER
#define SLIDER

#include <iostream>
#include "PageGroupItem.h"

#define RAIL 0
#define SLIDER 1
#define DESCRIPTION 2
#define RATIO 3

using namespace std;

struct SliderData
{
	double Min = 0;
	double Max = 100;
	double Controller = 50;
	string Description = "";
	string Ratio = "0.0";
};

class Slider : public PageGroupItem
{
public:

	SliderData CurrentSliderData;

	Slider(Page& Page);
	Slider(Page& Page, PageGroupItemData& PageGroupItemData, SliderData& SliderData);
	Slider(Page& Page, int PageItemID);


	void SwitchToSlider(int SliderStartID);

	//Returns start of group ID
	unsigned int operator[] (int Index)
	{
		return GetShapeGroup(Index);
	}
	
	

	void Update();
	void AddSlider();
	void SetShapeGroup();
	void CreateSlider();
	void ReplaceSlider();
	//ShapeData Editing
	void Add_Default() override;
	void Add_Duplicate() override;
	void Add_Insert() override;

	void SetDescription(string Description);

	

private:



};

#endif
