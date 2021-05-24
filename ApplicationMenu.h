#ifndef	APPMENU
#define APPMENU

#include <iostream>
#include "SubmitOrder.h"


#define PAGE_SUBMIT_ORDER 0
#define PAGE_MENU_CREATOR 1
#define PAGE_INGREDIENT_LIST 2
#define PAGE_COMPLETE_ORDER 3


namespace ApplicationMenu
{
	static Selector Selector_App_Menu;
	static Button Button_Set_Current_Page;
	static int CurrentPage;
	static NewPage Page_ApplicationMenu;
	static BookDirectory BD_ApplicationMenu;
	//static BookDirectory ElementsHovered;
	static llBookData* RestaurantBook;

	void Prepare(llBookData* Restaurant_POS, ShaderProgram* ShaderProgram, RawTexture* Texture0, RawTexture* Texture1, RawTexture* Texture2);
	int Update();

	void CreatePageSelector();

	void Highlight_Page_Selector(llShapeGroupData* ShapeGroup_Section_Graphic);
	void Select_Page();

	const glm::vec4 Page_Color = { 0.52, 0.41, 0.0, 1.0 };
	const glm::vec4 Page_Highlight_Color = { 0.77, 0.66, 0.0, 1.0 };
	static llShapeGroupData* ShapeGroup_Page_Graphic_Selected;

}

#endif