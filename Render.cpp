#include "Render.h"

void Render::DrawPage(ShaderProgram ShaderProgram, RawTexture RawTexture1, RawTexture RawTexture2, RawTexture RawTexture3, Page& Page)
{
	Page.LoadThisPage();
	glUseProgram(ShaderProgram.ID);
	glBindVertexArray(Page.VA);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Page::WhiteTexture);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, RawTexture1.GetTextureID());
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, RawTexture2.GetTextureID());
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, RawTexture3.GetTextureID());
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDrawElements(GL_TRIANGLES, Page.PageIndexCount, GL_UNSIGNED_INT, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

//void Render::DrawCircle(ShaderProgram ShaderProgram, Page Page)
//{
//	glUseProgram(ShaderProgram.ID);
//	glBindVertexArray(Page.VA);
//	glEnable(GL_ALPHA_TEST);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//	glDrawElements(GL_TRIANGLE_FAN, Page.IndexContainer.CurrentContainerAmount - 1, GL_UNSIGNED_INT, 0);
//	glBindVertexArray(0);
//}


//void Render::Prepare(GLclampf Red, GLclampf Green, GLclampf Blue, GLclampf Opacity)
//{
//
//}
//
//
//void Render::render(RawModel RawModel)
//{
//	glBindVertexArray(RawModel.getVaoID());
//	glEnableVertexAttribArray(0);
//	glDrawElements(GL_TRIANGLES, RawModel.GetIndicesCount(), GL_UNSIGNED_INT, 0);
//	glDisableVertexAttribArray(0);
//	glBindVertexArray(0);
//}
//
////Render Entity?
//void Render::RenderTexture(RawTexture RawTexture, RawModel RawModel)
//{
//	glBindVertexArray(RawModel.getVaoID());
//	glActiveTexture(RawTexture.GetActiveTexture());
//	glBindTexture(GL_TEXTURE_2D, RawTexture.GetTextureID());
//	glEnable(GL_BLEND);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//	glDrawElements(GL_TRIANGLES, RawModel.GetIndicesCount(), GL_UNSIGNED_INT, nullptr);
//	glBindTexture(GL_TEXTURE_2D, 0);
//	glBindVertexArray(0);
//}

//void Render::TextInit(ShaderProgram ShaderProgram, RawTexture RawTexture)
//{
//
//	//Quad Buffer is a container of 4000 Vertices
//	S_TextData.TextVertexContainer = new TextVertex[MaxVertexCount];
//
//	glGenVertexArrays(1, &S_TextData.QuadVA);
//	glBindVertexArray(S_TextData.QuadVA);
//
//	glGenBuffers(1, &S_TextData.QuadVB);
//	glBindBuffer(GL_ARRAY_BUFFER, S_TextData.QuadVB);
//	glBufferData(GL_ARRAY_BUFFER, MaxVertexCount * sizeof(TextVertex), nullptr, GL_DYNAMIC_DRAW);
//
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(TextVertex), (const void*)offsetof(TextVertex, Position));
//	glEnableVertexAttribArray(1);
//	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(TextVertex), (const void*)offsetof(TextVertex, TexCoords));
//	glEnableVertexAttribArray(2);
//	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(TextVertex), (const void*)offsetof(TextVertex, Color));
//
//	uint32_t indices[MaxIndexCount];
//	uint32_t offset = 0;
//
//	for (int i = 0; i < MaxIndexCount; i += 6)
//	{                         //Where i + (1-6) is each quad index' set
//		// example i = 39000, 39,001, 39,002, 39,003, 39,004, 39,005, 39,006 
//		indices[i + 0] = 0 + offset;
//		indices[i + 1] = 1 + offset;
//		indices[i + 2] = 2 + offset;
//						 
//		indices[i + 3] = 0 + offset;
//		indices[i + 4] = 2 + offset;
//		indices[i + 5] = 3 + offset;
//
//		//2, 0, 3, 3, 0, 1
//		// += Quad( 4 Vertices )
//		offset += 4;
//	}
//
//	glGenBuffers(1, &S_TextData.QuadIB);
//	glBindBuffer(GL_Element_ARRAY_BUFFER, S_TextData.QuadIB);
//	glBufferData(GL_Element_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//	Texture Texture;
//    
//	S_TextData.ActiveTexture = RawTexture.GetActiveTexture();
//	S_TextData.TextureID = RawTexture.GetTextureID();
//
//	ShaderProgram.LoadTexture(RawTexture);
//
//	
//}
//
////Sets the VertexPointer back to the first vertex
//void Render::BeginTextBatch()
//{
//	S_TextData.TextVertexPointer = S_TextData.TextVertexContainer;
//}
//
//
//void Render::DrawNewTextBatch()
//{
//	glBindVertexArray(S_TextData.QuadVA);
//	glDrawElements(GL_TRIANGLES, S_TextData.IndexCount, GL_UNSIGNED_INT, nullptr);
//	S_TextData.IndexCount = 0;
//	S_TextData.QuadCount = 0;
//}
//void Render::DrawNewQuadBatch()
//{
//	glBindVertexArray(S_QuadData.QuadVA);
//	glDrawElements(GL_TRIANGLES, S_QuadData.IndexCount, GL_UNSIGNED_INT, nullptr);
//	S_QuadData.IndexCount = 0;
//	S_QuadData.QuadCount = 0;
//}
//void Render::LoadTextBatch()
//{
//	GLsizeiptr size = (uint8_t*)S_TextData.TextVertexPointer -(uint8_t*)S_TextData.TextVertexContainer; // tracker really is where it's stored
//	glBindBuffer(GL_ARRAY_BUFFER, S_TextData.QuadVB);
//	glBufferSubData(GL_ARRAY_BUFFER, 0 , size, S_TextData.TextVertexContainer);
//}
//
//void Render::LoadQuadBatch()
//{
//	GLsizeiptr size = (uint8_t*)S_QuadData.QuadVertexPointer - (uint8_t*)S_QuadData.QuadVertexContainer; // tracker really is where it's stored
//	glBindBuffer(GL_ARRAY_BUFFER, S_QuadData.QuadVB);
//	glBufferSubData(GL_ARRAY_BUFFER, 0, size, S_QuadData.QuadVertexContainer);
//}
//
////where to replace, how much do you want to replace, the newdata that is replacing the old one 
//
//void Render::UpdateBatchQuad(int Quad)
//{
//	GLsizeiptr BatchSize = (uint8_t*)S_QuadData.QuadVertexPointer - (uint8_t*)S_QuadData.QuadVertexContainer; // tracker really is where it's stored
//	GLsizeiptr QuadDataSize = BatchSize / S_QuadData.QuadCount;
//	int Offset = QuadDataSize * Quad;
//	glBindBuffer(GL_ARRAY_BUFFER, S_QuadData.QuadVB);
//	glBufferSubData(GL_ARRAY_BUFFER, Offset, QuadDataSize, S_QuadData.QuadPointer);
//}
//void Render::ShutDown()
//{
//	glDeleteVertexArrays(1, &S_QuadData.QuadVA);
//	glDeleteBuffers(1, &S_QuadData.QuadVB);
//	glDeleteBuffers(1, &S_QuadData.QuadIB);
//	glDeleteVertexArrays(1, &S_TextData.QuadVA);
//	glDeleteBuffers(1, &S_TextData.QuadVB);
//	glDeleteBuffers(1, &S_TextData.QuadIB);
//
//	delete[] S_TextData.TextVertexContainer;
//	delete[] S_QuadData.QuadVertexContainer;
//}
//
////Takes in an active texture. the picture bound to the indexed active texture will be the image that is displayed
////need to do that outside of the loop
//
//
//void Render::StoreChar(const glm::vec3& Position, CharVertices& Vertices, CharTexCoords& TexCoords, glm::vec4& Color)
//{
//	if (S_TextData.IndexCount >= MaxIndexCount)
//	{
//		cout << "IndexCount acheived" << endl;
//		LoadTextBatch();
//		DrawNewTextBatch();
//		BeginTextBatch();
//	}
//
//	S_TextData.TextVertexPointer->Position = { Vertices.BottomLeft, 0.0 };  //bottom left
//	S_TextData.TextVertexPointer->TexCoords = { TexCoords.BottomLeft };     //Top Left
//	S_TextData.TextVertexPointer->Color = { Color };     
//	S_TextData.TextVertexPointer++; // + address of 1 verticy // we are controlling the address of each vertex
//			   
//	S_TextData.TextVertexPointer->Position = { Vertices.BottomRight, 0.0}; // bottom right
//	S_TextData.TextVertexPointer->TexCoords = { TexCoords.BottomRight };       //Top Right
//	S_TextData.TextVertexPointer->Color = { Color };
//	S_TextData.TextVertexPointer++;
//			   
//	S_TextData.TextVertexPointer->Position = { Vertices.TopRight, 0.0 }; // Top Right
//	S_TextData.TextVertexPointer->TexCoords = { TexCoords.TopRight };        //Bottom Right
//	S_TextData.TextVertexPointer->Color = { Color };
//	S_TextData.TextVertexPointer++;
//			   
//	S_TextData.TextVertexPointer->Position = { Vertices.TopLeft, 0.0 }; // Top left
//	S_TextData.TextVertexPointer->TexCoords = { TexCoords.TopLeft };        // Bottom Left
//	S_TextData.TextVertexPointer->Color = { Color };
//	S_TextData.TextVertexPointer++;
//
//	S_TextData.IndexCount += 6;
//	// 0, 1, 2, 3, 2, 0
//}
//
//void Render::ReplaceQuad(int QuadIndex, QuadVertices& Vertices, QuadTexCoords& TexCoords, glm::vec4& Color, float ActiveTexture)
//{
//
//	if (S_QuadData.IndexCount >= MaxIndexCount)
//	{
//		cout << "IndexCount acheived" << endl;
//		LoadQuadBatch();
//		DrawNewQuadBatch();
//		BeginQuadBatch();
//	}
//
//	// 160 is the size of the quad, be careful here!!!
//	int PointerOffset = QuadIndex * 160;
//	//Keeps track of the location of the last vertex data in the batch 
//	QuadVertex* EndOfBatch = S_QuadData.QuadVertexPointer;
//	//Do not Change this order
//	QuadVertex* StartOfQuad = S_QuadData.QuadVertexContainer + PointerOffset;
//
//	S_QuadData.QuadPointer = StartOfQuad;
//	S_QuadData.QuadVertexPointer = StartOfQuad;
//
//	S_QuadData.QuadVertexPointer->Position = { Vertices.BottomLeft, 0.0 };  //bottom left
//	S_QuadData.QuadVertexPointer->TexCoords = { TexCoords.BottomLeft };     //Top Left
//	S_QuadData.QuadVertexPointer->Color = { Color };
//	S_QuadData.QuadVertexPointer->TexIndex = ActiveTexture;
//	S_QuadData.QuadVertexPointer++; // + address of 1 verticy // we are controlling the address of each vertex
//
//	S_QuadData.QuadVertexPointer->Position = { Vertices.BottomRight, 0.0 }; // bottom right
//	S_QuadData.QuadVertexPointer->TexCoords = { TexCoords.BottomRight };       //Top Right
//	S_QuadData.QuadVertexPointer->Color = { Color };
//	S_QuadData.QuadVertexPointer->TexIndex = ActiveTexture;
//	S_QuadData.QuadVertexPointer++;
//
//	S_QuadData.QuadVertexPointer->Position = { Vertices.TopRight, 0.0 }; // Top Right
//	S_QuadData.QuadVertexPointer->TexCoords = { TexCoords.TopRight };        //Bottom Right
//	S_QuadData.QuadVertexPointer->Color = { Color };
//	S_QuadData.QuadVertexPointer->TexIndex = ActiveTexture;
//	S_QuadData.QuadVertexPointer++;
//
//	S_QuadData.QuadVertexPointer->Position = { Vertices.TopLeft, 0.0 }; // Top left
//	S_QuadData.QuadVertexPointer->TexCoords = { TexCoords.TopLeft };        // Bottom Lef
//	S_QuadData.QuadVertexPointer->TexIndex = ActiveTexture;
//	S_QuadData.QuadVertexPointer->Color = { Color };
//	S_QuadData.QuadVertexPointer++;
//	
//    //Sets the vertex back to it's position at the end of the batch before the function started 
//	S_QuadData.QuadVertexPointer = EndOfBatch;
//}
//
//
//
//
//void Render::ReplaceQuadData(int QuadIndex ,float xPos, float yPos, float xSize, float ySize, glm::vec4 Color, int ActiveTexture)
//{
//	//setup
//	Maths maths;
//	glm::vec3 QuadPosition = { xPos, yPos, 0 };
//
//	//create proper data
//	QuadVertices QuadVertices = maths.GetQuadVertices(QuadPosition, xSize, ySize);
//	QuadTexCoords QuadTexCoords = maths.GetBasicTexCoords();
//
//	ReplaceQuad(QuadIndex, QuadVertices, QuadTexCoords, Color, ActiveTexture);
//	UpdateBatchQuad(QuadIndex);
//
//}
//

//void Render::DrawPageWire(ShaderProgram ShaderProgram, RawTexture RawTexture1, RawTexture RawTexture2, RawTexture RawTexture3, Page Page)
//{
//	Page.LoadThisPage();
//	glUseProgram(ShaderProgram.ID);
//	glBindVertexArray(Page.VA);
//	glActiveTexture(GL_TEXTURE0);
//	glBindTexture(GL_TEXTURE_2D, Page::WhiteTexture);
//	glActiveTexture(GL_TEXTURE2);
//	glBindTexture(GL_TEXTURE_2D, RawTexture1.GetTextureID());
//	glActiveTexture(GL_TEXTURE1);
//	glBindTexture(GL_TEXTURE_2D, RawTexture2.GetTextureID());
//	glActiveTexture(GL_TEXTURE3);
//	glBindTexture(GL_TEXTURE_2D, RawTexture3.GetTextureID());
//	glEnable(GL_BLEND);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//	//cout << Page.IndexContainer << endl;
//	glDrawElements(GL_WIRE_FRAME, Page.PageIndexCount, GL_UNSIGNED_INT, 0);
//	glBindTexture(GL_TEXTURE_2D, 0);
//	glBindVertexArray(0);
//}



//void Render::AddTextToBatch(TextSpecification TextSpecs)
//{
//	FontMath Font;
//
//	//set up
//	//BeginTextBatch();
//	glm::vec3 CurrentCursorPos = {TextSpecs.xPos, TextSpecs.yPos, 0.0};
//	glm::vec3 CharacterPosition = {0.0, 0.0, 0.0};
//	bool LineRestart = true;
//	//S_TextData.QuadCount = 0;
//
//	//Sets all the vertex data for the entire sentence AKA Making VBOdata,
//	for (int n = 0; n < TextSpecs.Text.size(); n++)
//	{
//		//creates the specified character
//		Character Char(TextSpecs.FontFile, TextSpecs.Text[n]);
//
//		//retrieves texture coordinates for character
//		CharTexCoords CharTexCoords = Font.GetCharacterTexCoords(Char);
//
//		//calculate and include offsets of character
//		CharacterPosition = Font.CharacterOffset(Char, CurrentCursorPos, TextSpecs.FontSize, LineRestart);
//
//		////calculates when to return line
//		float Maxline = (TextSpecs.xPos + TextSpecs.LineLength);
//
//		////Checks if line needs to be returned 
//		LineRestart = QueryLineRestart(CurrentCursorPos, Maxline);
//
//		////if true,
//		if (LineRestart == true)
//		{   ////Move CursorPosition to the next line
//			CurrentCursorPos = Font.NextLine(Char, CurrentCursorPos, TextSpecs.FontSize, TextSpecs.xPos);
//		}
//
//		//Calculates characters final position on the screen
//		CharVertices CharVertices = Font.GetCharacterVertices(Char, CharacterPosition, SCR_Height, SCR_Width, TextSpecs.FontSize);
//	
//		//Stores Char from text in buffer to then be passed to the GPU
//	    StoreChar(CharacterPosition, CharVertices, CharTexCoords, TextSpecs.Color);
//
//		////Advances the cursor
//		CurrentCursorPos = Font.AdvanceCursor(Char, TextSpecs.FontSize, { CurrentCursorPos }, TextSpecs.CharSpacing);
//
//		// Reflect number of quads loaded
//		S_TextData.QuadCount++;
//	}
////
////}
////
////void Render::DrawTText(ShaderProgram ShaderProgram, RawTexture RawTexture)
////{
////LoadTextBatch();
////
//////Render Batch
////glUseProgram(ShaderProgram.ID);
//////cout << S_Data.IndexCount << endl;
////glBindVertexArray(S_TextData.QuadVA);
////glActiveTexture(RawTexture.GetActiveTexture());
////glBindTexture(GL_TEXTURE_2D, RawTexture.GetTextureID());
////glEnable(GL_BLEND);
////glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
////glDrawElements(GL_TRIANGLES, (S_TextData.QuadCount * 6), GL_UNSIGNED_INT, nullptr);
////glBindTexture(GL_TEXTURE_2D, 0);
////glBindVertexArray(0);
////
////}
//
//
//


