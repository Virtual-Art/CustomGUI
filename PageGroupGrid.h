#ifndef	 PAGEGROUPGRID
#define  PAGEGROUPGRID

#include <iostream>
#include "NewPage.h"

#define NEVER_SWITCH -2

using namespace std;

struct PageGroupGridData
{
	glm::vec2 Position;
	int ResultCount = 1;
	int RowCount = 0;
	int ColumnCount = 0;
	int xPadding = 10;
	int yPadding = 10;
	int InputType = INPUT_CENTER;
	glm::vec4 last_edges;        //(Object) Graphic Reference for the form filler to position with
	glm::vec4 first_edges;        //(Object) Graphic Reference for the form filler to position with
	bool first;
	int xMatchType = MATCH_CENTERS;
	int yMatchType = MATCH_CENTERS;
};

typedef void(PageGroup::*PlacementFunction2)(const glm::vec4&, int, int);

class PageGroupGrid : public NewPage
{
public:

	PlacementFunction2 CurrentPlacement;
	PageGroupGridData CurrentGrid;
	llPageGroupData* Grid_Template;
	llPageGroupData* First_PageGroup;

	PageGroupGrid() {};
	PageGroupGrid(llBookData* llBook, llPageData* Page, llPageGroupData* PageGroup_Template, PageGroupGridData PageGroupGrid, ShaderProgram* ShaderProgram, RawTexture* Texture0, RawTexture* Texture1, RawTexture* Texture2);
	void llInit(llBookData* llBook, llPageData* Page, llPageGroupData* PageGroup_Template, PageGroupGridData PageGroupGrid, ShaderProgram* ShaderProgram, RawTexture* Texture0, RawTexture* Texture1, RawTexture* Texture2);


	void AddPageGroupGrid();
	void ReplacePageGroupGrid();
	void llUpdate();

	void SetResultCount(int NewResultCount);
	void SetColumnRow(int Column, int Row);
	llPageGroupData* GetFirst();
	//+-----------------------+//

private:

	int CurrentMatchType;
	int CurrentPadding;
	int SetPlacementDirection();
	void SwapPlacementDirection();

};



#endif