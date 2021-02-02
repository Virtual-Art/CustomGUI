#include "NewPage.h"

NewPage::NewPage(llBookData* llBook, ShaderProgram* ShaderProgram)
{
	CurrentShader = ShaderProgram;
	if (llBook != nullptr && llBook->Page != nullptr)
	{
		CurrentllPage = llBook->Page;
		CurrentllPage->CreateContainer();
		glGenVertexArrays(1, &CurrentllPage->VA);
		glBindVertexArray(CurrentllPage->VA);

		glGenBuffers(1, &CurrentllPage->VB);
		glBindBuffer(GL_ARRAY_BUFFER, CurrentllPage->VB);
		glBufferData(GL_ARRAY_BUFFER, CurrentllPage->MaxVertexCount * sizeof(ShapeVertex), nullptr, GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const void*)offsetof(ShapeVertex, Position));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const void*)offsetof(ShapeVertex, TexCoords));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const void*)offsetof(ShapeVertex, Color));
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const void*)offsetof(ShapeVertex, TexIndex));
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const void*)offsetof(ShapeVertex, CentralPoint));
		glEnableVertexAttribArray(5);
		glVertexAttribPointer(5, 1, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const void*)offsetof(ShapeVertex, GUIAction));

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
		//Might have to add +2 to the sizeof slot
		glBufferData(GL_Element_ARRAY_BUFFER, CurrentllPage->MaxIndexCount * sizeof(ShapeVertex), CurrentllPage->IndexContainer, GL_STATIC_DRAW);

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
	if (llBook != nullptr && llBook->Page != nullptr)
	{
		CurrentllPage = llBook->Page;
		CurrentllPage->CreateContainer();
		glGenVertexArrays(1, &CurrentllPage->VA);
		glBindVertexArray(CurrentllPage->VA);

		glGenBuffers(1, &CurrentllPage->VB);
		glBindBuffer(GL_ARRAY_BUFFER, CurrentllPage->VB);
		glBufferData(GL_ARRAY_BUFFER, CurrentllPage->MaxVertexCount * sizeof(ShapeVertex), nullptr, GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const void*)offsetof(ShapeVertex, Position));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const void*)offsetof(ShapeVertex, TexCoords));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const void*)offsetof(ShapeVertex, Color));
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const void*)offsetof(ShapeVertex, TexIndex));
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const void*)offsetof(ShapeVertex, CentralPoint));
		glEnableVertexAttribArray(5);
		glVertexAttribPointer(5, 1, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const void*)offsetof(ShapeVertex, GUIAction));

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
		//Might have to add +2 to the sizeof slot
		glBufferData(GL_Element_ARRAY_BUFFER, CurrentllPage->MaxIndexCount * sizeof(ShapeVertex), CurrentllPage->IndexContainer, GL_STATIC_DRAW);

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

}

void NewPage::LoadGPU()
{
	glBindBuffer(GL_ARRAY_BUFFER, CurrentllPage->VB);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(llVertexData) * CurrentllPage->MaxVertexCount, CurrentllPage->VertexContainer); //
}