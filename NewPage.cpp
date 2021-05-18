#include "NewPage.h"

NewPage::NewPage()
{
	LoadedBook = nullptr;
	CurrentllPage = nullptr;
}

void NewPage::llInit(llBookData* llBook, ShaderProgram* ShaderProgram, RawTexture* Texture0, RawTexture* Texture1, RawTexture* Texture2)
{
	CurrentShader = ShaderProgram;
	this->Texture0 = Texture0;
	this->Texture1 = Texture1;
	this->Texture2 = Texture2;

	if (llBook != nullptr)
	{
		CurrentllPage = new llPageData;

		CurrentllPage->VA = 0;
		CurrentllPage->VB = 0;
		CurrentllPage->IB = 0;

		llPageData* CurrentPage = llBook->Page;

		//Completely new object
		if (CurrentPage == nullptr)
		{
			Log::LogString("Book Empty New Page Linked");
			llBook->Page = CurrentllPage;
			llBook->PageHead = CurrentllPage;
		}
		else //Page already created
		{

			//Find tail then add
			while (CurrentPage->Next != nullptr)
			{
				CurrentPage = CurrentPage->Next;
				Log::LogString("Passed a Page");
			}
			Log::LogString("New Page Linked");
			CurrentPage->Next = CurrentllPage;
			CurrentllPage->Previous = CurrentPage;
			llBook->Page = CurrentllPage;
		}
		//TestingPage->Type = TYPE_CUSTOM;
		LoadedBook = llBook;
	}

	if (llBook->Page != nullptr)
	{
		CurrentllPage = llBook->Page;
		CurrentllPage->CreateContainer();
		glGenVertexArrays(1, &CurrentllPage->VA);
		glBindVertexArray(CurrentllPage->VA);

		glGenBuffers(1, &CurrentllPage->VB);
		glBindBuffer(GL_ARRAY_BUFFER, CurrentllPage->VB);
		glBufferData(GL_ARRAY_BUFFER, CurrentllPage->MaxVertexCount * sizeof(llVertexData), nullptr, GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(llVertexData), (const void*)offsetof(llVertexData, Position));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(llVertexData), (const void*)offsetof(llVertexData, TexCoords));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(llVertexData), (const void*)offsetof(llVertexData, Color));
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(llVertexData), (const void*)offsetof(llVertexData, TexIndex));
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, sizeof(llVertexData), (const void*)offsetof(llVertexData, CentralPoint));
		glEnableVertexAttribArray(5);
		glVertexAttribPointer(5, 1, GL_FLOAT, GL_FALSE, sizeof(llVertexData), (const void*)offsetof(llVertexData, GUIAction));

		GLsizeiptr LastSize = 0;
		uint32_t offset = 0;

		for (int i = 0; i < CurrentllPage->MaxIndexCount; i += 6)
		{
			CurrentllPage->IndexContainer[i] = 0 + offset;   //0
			CurrentllPage->IndexContainer[i + 1] = 2 + offset;	//1
			CurrentllPage->IndexContainer[i + 2] = 1 + offset;	//2
			CurrentllPage->IndexContainer[i + 3] = 3 + offset;	//0
			CurrentllPage->IndexContainer[i + 4] = 2 + offset;	//2
			CurrentllPage->IndexContainer[i + 5] = 0 + offset;   //3

			//PageIndexCount += 6;
			//2, 0, 3, 3, 0, 1
			offset += 4;
		}


		glGenBuffers(1, &CurrentllPage->IB);
		glBindBuffer(GL_Element_ARRAY_BUFFER, CurrentllPage->IB);
		glBufferData(GL_Element_ARRAY_BUFFER, CurrentllPage->MaxIndexCount * sizeof(int), CurrentllPage->IndexContainer, GL_STATIC_DRAW);

		glGenTextures(1, &CurrentllPage->WhiteTexture);
		glBindTexture(GL_TEXTURE_2D, CurrentllPage->WhiteTexture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		GLubyte Pixels[4] = { 255, 255, 255, 255 };
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, &Pixels);
		glGenerateMipmap(GL_TEXTURE_2D);

		for (size_t i = 1; i < CurrentllPage->MaxTextures; i++)
		{
			CurrentllPage->TextureSlots[i] = 0;
		}

		CurrentllPage->TextureSlots[0] = CurrentllPage->WhiteTexture;
		CurrentllPage->TextureSlots[1] = CurrentllPage->WhiteTexture;
		CurrentllPage->TextureSlots[2] = CurrentllPage->WhiteTexture;//WhiteTexture is just the texture ID of image 1 (white)
		//this->TextureSlots[1] = RawTexture.GetTextureID();
		glUseProgram(CurrentShader->ID);
		////this code basically converts our textureslot to an actual number we can reference in the shader 
		//ShaderProgram.LoadSample0();
		//ShaderProgram.LoadSample1();
		//ShaderProgram.LoadSample2();
		CurrentShader->LoadAllSamples();
		glUseProgram(0);
	}
}

NewPage::NewPage(llBookData* llBook, ShaderProgram* ShaderProgram, RawTexture* Texture0, RawTexture* Texture1, RawTexture* Texture2)
{
	llInit(llBook, ShaderProgram, Texture0, Texture1,  Texture2);

	CurrentShader = ShaderProgram;
	this->Texture0 = Texture0;
	this->Texture1 = Texture1;
	this->Texture2 = Texture2;

	if (llBook != nullptr)
	{
		CurrentllPage = new llPageData;

		CurrentllPage->VA = 0;
		CurrentllPage->VB = 0;
		CurrentllPage->IB = 0;

		llPageData* TestingPage = llBook->Page;

		//Completely new object
		if (TestingPage == nullptr)
		{
			Log::LogString("New Page Linked");
			llBook->Page = CurrentllPage;
			llBook->PageHead = CurrentllPage;
		}
		else //Shapes already created
		{
			llPageData* FoundTail = TestingPage;

			//Find tail then add
			while (FoundTail->Next != nullptr)
			{
				FoundTail = FoundTail->Next;
			}
			Log::LogString("New Page Linked");
			FoundTail->Next = TestingPage;
			TestingPage->Previous = FoundTail;
			llBook->Page = CurrentllPage;
		}
		//TestingPage->Type = TYPE_CUSTOM;
		LoadedBook = llBook;
	}

	if (llBook->Page != nullptr)
	{
		CurrentllPage = llBook->Page;
		CurrentllPage->CreateContainer();
		glGenVertexArrays(1, &CurrentllPage->VA);
		glBindVertexArray(CurrentllPage->VA);

		glGenBuffers(1, &CurrentllPage->VB);
		glBindBuffer(GL_ARRAY_BUFFER, CurrentllPage->VB);
		glBufferData(GL_ARRAY_BUFFER, CurrentllPage->MaxVertexCount * sizeof(llVertexData), nullptr, GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(llVertexData), (const void*)offsetof(llVertexData, Position));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(llVertexData), (const void*)offsetof(llVertexData, TexCoords));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(llVertexData), (const void*)offsetof(llVertexData, Color));
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(llVertexData), (const void*)offsetof(llVertexData, TexIndex));
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, sizeof(llVertexData), (const void*)offsetof(llVertexData, CentralPoint));
		glEnableVertexAttribArray(5);
		glVertexAttribPointer(5, 1, GL_FLOAT, GL_FALSE, sizeof(llVertexData), (const void*)offsetof(llVertexData, GUIAction));

		GLsizeiptr LastSize = 0;
		uint32_t offset = 0;

		for (int i = 0; i < CurrentllPage->MaxIndexCount; i += 6)
		{
			CurrentllPage->IndexContainer[i] = 0 + offset;   //0
			CurrentllPage->IndexContainer[i + 1] = 2 + offset;	//1
			CurrentllPage->IndexContainer[i + 2] = 1 + offset;	//2
			CurrentllPage->IndexContainer[i + 3] = 3 + offset;	//0
			CurrentllPage->IndexContainer[i + 4] = 2 + offset;	//2
			CurrentllPage->IndexContainer[i + 5] = 0 + offset;   //3

			//PageIndexCount += 6;
			//2, 0, 3, 3, 0, 1
			offset += 4;
		}


		glGenBuffers(1, &CurrentllPage->IB);
		glBindBuffer(GL_Element_ARRAY_BUFFER, CurrentllPage->IB);
		glBufferData(GL_Element_ARRAY_BUFFER, CurrentllPage->MaxIndexCount * sizeof(int), CurrentllPage->IndexContainer, GL_STATIC_DRAW);

		glGenTextures(1, &CurrentllPage->WhiteTexture);
		glBindTexture(GL_TEXTURE_2D, CurrentllPage->WhiteTexture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		GLubyte Pixels[4] = { 255, 255, 255, 255 };
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, &Pixels);
		glGenerateMipmap(GL_TEXTURE_2D);

		for (size_t i = 1; i < CurrentllPage->MaxTextures; i++)
		{
			CurrentllPage->TextureSlots[i] = 0;
		}

		CurrentllPage->TextureSlots[0] = CurrentllPage->WhiteTexture;
		CurrentllPage->TextureSlots[1] = CurrentllPage->WhiteTexture;
		CurrentllPage->TextureSlots[2] = CurrentllPage->WhiteTexture;//WhiteTexture is just the texture ID of image 1 (white)
		//this->TextureSlots[1] = RawTexture.GetTextureID();
		glUseProgram(CurrentShader->ID);
		////this code basically converts our textureslot to an actual number we can reference in the shader 
		//ShaderProgram.LoadSample0();
		//ShaderProgram.LoadSample1();
		//ShaderProgram.LoadSample2();
		CurrentShader->LoadAllSamples();
		glUseProgram(0);
	}
}

void NewPage::InitiatePage(llBookData* llBook, ShaderProgram ShaderProgram)
{
	if (llBook->Page != nullptr)
	{
		CurrentllPage = llBook->Page;
		CurrentllPage->CreateContainer();
		glGenVertexArrays(1, &CurrentllPage->VA);
		glBindVertexArray(CurrentllPage->VA);

		glGenBuffers(1, &CurrentllPage->VB);
		glBindBuffer(GL_ARRAY_BUFFER, CurrentllPage->VB);
		glBufferData(GL_ARRAY_BUFFER, CurrentllPage->MaxVertexCount * sizeof(llVertexData), nullptr, GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(llVertexData), (const void*)offsetof(llVertexData, Position));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(llVertexData), (const void*)offsetof(llVertexData, TexCoords));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(llVertexData), (const void*)offsetof(llVertexData, Color));
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(llVertexData), (const void*)offsetof(llVertexData, TexIndex));
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, sizeof(llVertexData), (const void*)offsetof(llVertexData, CentralPoint));
		glEnableVertexAttribArray(5);
		glVertexAttribPointer(5, 1, GL_FLOAT, GL_FALSE, sizeof(llVertexData), (const void*)offsetof(llVertexData, GUIAction));

		GLsizeiptr LastSize = 0;
		uint32_t offset = 0;

		for (int i = 0; i < CurrentllPage->MaxIndexCount; i += 6)
		{
			CurrentllPage->IndexContainer[i] = 0 + offset;   //0
			CurrentllPage->IndexContainer[i + 1] = 2 + offset;	//1
			CurrentllPage->IndexContainer[i + 2] = 1 + offset;	//2
			CurrentllPage->IndexContainer[i + 3] = 3 + offset;	//0
			CurrentllPage->IndexContainer[i + 4] = 2 + offset;	//2
			CurrentllPage->IndexContainer[i + 5] = 0 + offset;   //3

			//PageIndexCount += 6;
			//2, 0, 3, 3, 0, 1
			offset += 4;
		}


		glGenBuffers(1, &CurrentllPage->IB);
		glBindBuffer(GL_Element_ARRAY_BUFFER, CurrentllPage->IB);
		glBufferData(GL_Element_ARRAY_BUFFER, CurrentllPage->MaxIndexCount * sizeof(int), CurrentllPage->IndexContainer, GL_STATIC_DRAW);

		glGenTextures(1, &CurrentllPage->WhiteTexture);
		glBindTexture(GL_TEXTURE_2D, CurrentllPage->WhiteTexture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		GLubyte Pixels[4] = { 255, 255, 255, 255 };
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, &Pixels);
		glGenerateMipmap(GL_TEXTURE_2D);

		for (size_t i = 1; i < CurrentllPage->MaxTextures; i++)
		{
			CurrentllPage->TextureSlots[i] = 0;
		}

		CurrentllPage->TextureSlots[0] = CurrentllPage->WhiteTexture;
		CurrentllPage->TextureSlots[1] = CurrentllPage->WhiteTexture;
		CurrentllPage->TextureSlots[2] = CurrentllPage->WhiteTexture;//WhiteTexture is just the texture ID of image 1 (white)
		//this->TextureSlots[1] = RawTexture.GetTextureID();
		glUseProgram(ShaderProgram.ID);
		////this code basically converts our textureslot to an actual number we can reference in the shader 
		//ShaderProgram.LoadSample0();
		//ShaderProgram.LoadSample1();
		//ShaderProgram.LoadSample2();
		ShaderProgram.LoadAllSamples();
		glUseProgram(0);
	}
}



void NewPage::DrawPage()
{

	LoadedBook->Page = CurrentllPage;

	CurrentllPage->LoadPage(); //Sets all book data into page
	LoadGPU(); //loads that data to the gpu

	glUseProgram(CurrentShader->ID);
	glBindVertexArray(CurrentllPage->VA);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, CurrentllPage->WhiteTexture);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, Texture0->GetTextureID());
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, Texture1->GetTextureID());
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, Texture2->GetTextureID());
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDrawElements(GL_TRIANGLES, CurrentllPage->MaxIndexCount, GL_UNSIGNED_INT, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);

	FindElements();
}

void NewPage::DrawPage(ShaderProgram ShaderProgram, RawTexture RawTexture1, RawTexture RawTexture2, RawTexture RawTexture3)
{

	CurrentllPage->LoadPage(); //Sets all book data into page
	LoadGPU(); //loads that data to the gpu
	glUseProgram(ShaderProgram.ID);
	glBindVertexArray(CurrentllPage->VA);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, CurrentllPage->WhiteTexture);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, RawTexture1.GetTextureID());
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, RawTexture2.GetTextureID());
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, RawTexture3.GetTextureID());
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDrawElements(GL_TRIANGLES, CurrentllPage->MaxIndexCount, GL_UNSIGNED_INT, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);

}


void NewPage::LoadGPU()
{
	glBindBuffer(GL_ARRAY_BUFFER, CurrentllPage->VB);
	glBufferSubData(GL_ARRAY_BUFFER, 0, CurrentllPage->GetMaxSize(), CurrentllPage->VertexContainer); //
}


void NewPage::FindElements()
{
	if (CurrentllPage == nullptr) { Log::LogString("ERROR FindElement FAILED:: No CurrentllPage Provided"); }

	float xMouse = MouseManager::xPos;
	float yMouse = MouseManager::yPos;

	int VertexIndex = 0;
	int PageCount = 0;
	int PageGroupCount = 0;
	int PageItemCount = 0;
	int ShapeGroupCount = 0;
	int ShapeCount = 0;
	int VertexCount = 0;

	llPageGroupData* SavedPageGroup = nullptr;
	llPageItemData* SavedPageItem = nullptr;
	llShapeGroupData* SavedShapeGroup = nullptr;
	llShapeData* SavedShape = nullptr;
	llVertexData* SavedVertex = nullptr;

	//Nothing in PageGroup
	SavedPageGroup = CurrentllPage->PageGroup;
	if (SavedPageGroup != nullptr)
	{
		SavedPageItem = CurrentllPage->PageGroup->PageItem;
		if (SavedPageItem != nullptr)
		{
			SavedShapeGroup = CurrentllPage->PageGroup->PageItem->ShapeGroup;
			if (SavedShapeGroup != nullptr)
			{
				SavedShape = CurrentllPage->PageGroup->PageItem->ShapeGroup->Shape;
				if (SavedShape != nullptr)
				{
					SavedVertex = CurrentllPage->PageGroup->PageItem->ShapeGroup->Shape->Vertexx;
				}
			}
		}
	}	


	//while (CurrentllPage != nullptr && CurrentllPage->PageGroup != nullptr)
	//{
	//	PageCount++;
		//Page Group
		llPageGroupData* CurrentPageGroup = CurrentllPage->PageGroup;

		//Set PageGroup Beginning
		/////////////////////////////////////////////////////
		while (CurrentPageGroup->Previous != nullptr)
		{
			CurrentPageGroup = CurrentPageGroup->Previous;

		}
		/////////////////////////////////////////////////////
		while (CurrentPageGroup != nullptr && CurrentPageGroup->PageItem != nullptr)
		{
			//if (ElementLevel == LEVEL_PAGEITEM)
			//{
			if (xMouse < CurrentPageGroup->Right && xMouse >  CurrentPageGroup->Left&& yMouse < CurrentPageGroup->Top && yMouse >  CurrentPageGroup->Bottom&& CurrentPageGroup->MouseAccess == true)
			{
				//cout << " [PageGroup Found] | P:" << PageCount << " | PG:" << PageGroupCount << endl;
				ElementsHovered.PageGroup = CurrentPageGroup;
			}
			//}

			PageGroupCount++;
			//PageItem
			llPageItemData* CurrentPageItem = CurrentPageGroup->PageItem;
			//Set PageItem Beginning
			/////////////////////////////////////////////////////
			while (CurrentPageItem->Previous != nullptr)
			{
				CurrentPageItem = CurrentPageItem->Previous;
			}
			/////////////////////////////////////////////////////
			while (CurrentPageItem != nullptr && CurrentPageItem->ShapeGroup != nullptr)
			{
				if (xMouse < CurrentPageItem->Right && xMouse >  CurrentPageItem->Left&& yMouse < CurrentPageItem->Top && yMouse >  CurrentPageItem->Bottom&& CurrentPageItem->MouseAccess == true)
				{
					//cout << " [PageItem Found] | P:" << PageCount << " | PG:" << PageGroupCount << " | PI:" << PageItemCount << endl;
					ElementsHovered.PageItem = CurrentPageItem;
					if (CurrentPageItem->PageItemButton != nullptr)
					{
						CurrentPageItem->PageItemButton->ProcessMouseButtons(MouseManager::CurrentMouseState);
					}
				}

				PageItemCount++;
				//ShapeGroup
				llShapeGroupData* CurrentShapeGroup = CurrentPageItem->ShapeGroup;
				//Set ShapeGroup to beginning
				/////////////////////////////////////////////////////
				while (CurrentShapeGroup->Previous != nullptr)
				{
					CurrentShapeGroup = CurrentShapeGroup->Previous;
				}

				/////////////////////////////////////////////////////
				while (CurrentShapeGroup != nullptr)
				{
					ShapeGroupCount++;
					//Shape
					llShapeData* CurrentShape = CurrentShapeGroup->Shape;
					if (CurrentShapeGroup->Shape != nullptr)
					{

						if (xMouse < CurrentShapeGroup->Right && xMouse >  CurrentShapeGroup->Left&& yMouse < CurrentShapeGroup->Top && yMouse >  CurrentShapeGroup->Bottom&& CurrentShapeGroup->MouseAccess == true)
						{
								//cout << "[ShapeGroup Found] |P:" << PageCount << " | PG:" << PageGroupCount << " | PI:" << PageItemCount << " | SG:" << ShapeGroupCount << endl;
							ElementsHovered.ShapeGroup = CurrentShapeGroup;
							if (CurrentShapeGroup->ShapeGroupButton != nullptr)
							{
								CurrentShapeGroup->ShapeGroupButton->ProcessMouseButtons(MouseManager::CurrentMouseState);
							}
						}
						//Set shape to beginning
						/////////////////////////////////////////////////////
						while (CurrentShape->Previous != nullptr)
						{
							CurrentShape = CurrentShape->Previous;
						}
						/////////////////////////////////////////////////////
						while (CurrentShape != nullptr && CurrentShape->Vertexx != nullptr)
						{
							ShapeCount++;
							if (xMouse < CurrentShape->Right && xMouse >  CurrentShape->Left&& yMouse < CurrentShape->Top && yMouse >  CurrentShape->Bottom&& CurrentShape->MouseAccess == true)
							{
								ElementsHovered.Shape;

								if (CurrentShape->ShapeButton != nullptr)
								{
									//cout << "[Shape Found] | P:" << PageCount << " | PG:" << PageGroupCount << " | PI:" << PageItemCount << " | SG:" << ShapeGroupCount << " | S:" << ShapeCount << " | Char: " << char(CurrentShape->Ascii) << endl;
									CurrentShape->ShapeButton->ProcessMouseButtons(MouseManager::CurrentMouseState);

								}

							}
							CurrentShape = CurrentShape->Next;
						}
					}
					ShapeCount = -1;
					CurrentShapeGroup = CurrentShapeGroup->Next;
				}
				ShapeGroupCount = -1;
				CurrentPageItem = CurrentPageItem->Next;
			}
			PageItemCount = -1;
			CurrentPageGroup = CurrentPageGroup->Next;
		}
		PageGroupCount = -1;
	//}

	CurrentllPage->PageGroup = SavedPageGroup;
	if (CurrentllPage->PageGroup != nullptr)
	{
		CurrentllPage->PageGroup->PageItem = SavedPageItem;
		if (CurrentllPage->PageGroup->PageItem != nullptr)
		{
			CurrentllPage->PageGroup->PageItem->ShapeGroup = SavedShapeGroup;
			if (CurrentllPage->PageGroup->PageItem->ShapeGroup != nullptr)
			{
				CurrentllPage->PageGroup->PageItem->ShapeGroup->Shape = SavedShape;
				if (CurrentllPage->PageGroup->PageItem->ShapeGroup->Shape != nullptr)
				{
					CurrentllPage->PageGroup->PageItem->ShapeGroup->Shape->Vertexx = SavedVertex;
				}
			}
		}
	}

}
