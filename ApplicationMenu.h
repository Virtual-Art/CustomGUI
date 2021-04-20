#ifndef	APPMENU
#define APPMENU

#include <iostream>
#include "SubmitOrder.h"


#define PAGE_SUBMIT_ORDER 0
#define PAGE_MENU_CREATOR 1
#define PAGE_INGREDIENT_LIST 2


namespace ApplicationMenu
{
	static Selector Selector_App_Menu;
	static Button Button_Set_Current_Page;
	static int CurrentPage;
	static NewPage Page_ApplicationMenu;
	static BookDirectory BD_ApplicationMenu;
	static BookDirectory ElementsHovered;
	static llBookData* RestaurantBook;

	void Prepare(llBookData* Restaurant_POS, ShaderProgram* ShaderProgram, RawTexture* Texture0, RawTexture* Texture1, RawTexture* Texture2);
	int Update();

	void CreateSelectorMenu();
	void SetCurrentPage();
}

#endif