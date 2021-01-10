#include "NewRender.h"

void NewRender::DrawPage(ShaderProgram ShaderProgram, RawTexture RawTexture1, RawTexture RawTexture2, RawTexture RawTexture3, Page Page)
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
   glDrawArrays(GL_TRIANGLES, Page.PageIndexCount, GL_UNSIGNED_INT);
   glBindTexture(GL_TEXTURE_2D, 0);
   glBindVertexArray(0);
}

void NewRender::Prepare(GLclampf Red, GLclampf Green, GLclampf Blue, GLclampf Opacity)
{

}
