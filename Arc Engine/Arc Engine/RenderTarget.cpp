#include "RenderTarget.h"
#include "GraphicsSystem.h"

RenderTarget::RenderTarget( void )
{
}

RenderTarget::~RenderTarget( void )
{
    term();
}

void RenderTarget::init( GraphicsSystem* pGraphicsSystem )
{
    _pGraphicsSystem = pGraphicsSystem;
}

void RenderTarget::term( void )
{
}

std::string RenderTarget::toString( void ) const
{
    return "Render Target";
}

void RenderTarget::beginDraw( void )
{
    Color clearColor = _pGraphicsSystem->clearColor();

    glClearColor(clearColor.fracR(), clearColor.fracG(), clearColor.fracB(), clearColor.fracA());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
}

void RenderTarget::endDraw( void )
{
    SDL_GL_SwapBuffers();
}

// ShapeValue 1.5 - Draws Triangle
// ShapeValue 2   - Draws Square
// ShapeValue 3   - Draws Hexagon
// ShapeValue 4   - Draws Octagon
// ShapeValue 5   - Draws Decagon
// ShapeValue 6   - Draws Circle
// ShapeValue 12  - Draws Better Circle
void RenderTarget::drawShape( float x, float y, float radius, float shapeValue, Color color /*= Color::WHITE*/, float rotation /*= 0.0f */, Vector2 origin /*= Vector2::ZERO*/ )
{
    glPushMatrix();
    glTranslatef(x, y, 0.0f);

    glTranslatef(origin.X, origin.Y, 0.0f);
    glRotatef(toDeg(rotation) - 90.0f, 0.0f, 0, 1.0f);
    glTranslatef(-origin.X, -origin.Y, 0.0f);

    glColor4f(color.fracR(), color.fracG(), color.fracB(), color.fracA());

    glBegin(GL_LINE_LOOP);

    for (float i = 0; i < PI2; i += (float)(PI / shapeValue))
    {
        glVertex2f(cosf(i) * radius, sinf(i) * radius);
    }

    glEnd();

    glPopMatrix();
}

void RenderTarget::fillShape( float x, float y, float radius, float shapeValue, Color color /*= Color::WHITE*/, float rotation /*= 0.0f */, Vector2 origin /*= Vector2::ZERO*/ )
{
    glPushMatrix();
    glTranslatef(x, y, 0.0f);

    glTranslatef(origin.X, origin.Y, 0.0f);
    glRotatef(toDeg(rotation) - 90.0f, 0.0f, 0.0f, 1.0f);
    glTranslatef(-origin.X, -origin.Y, 0.0f);

    glColor4f(color.fracR(), color.fracG(), color.fracB(), color.fracA());

    glBegin(GL_POLYGON);

    for (float i = 0; i < PI2; i += (float)(PI / shapeValue))
    {
        glVertex2f(cosf(i) * radius, sinf(i) * radius);
    }

    glEnd();

    glPopMatrix();
}

void RenderTarget::drawText( Vector2 pos, string text, Font* pFont, Color color /*= Color::WHITE*/, Align align /*= Align::INVALID_ALIGN*/, float rotation /*= 0.0f */, Vector2 origin /*= Vector2::ZERO*/ )
{
    drawText(pos.X, pos.Y, text, pFont, color, align, rotation, origin);
}

void RenderTarget::drawText( float x, float y, string text, Font* pFont, Color color /*= Color::WHITE*/, Align align /*= Align::INVALID_ALIGN*/, float rotation /*= 0.0f */, Vector2 origin /*= Vector2::ZERO*/ )
{
    CachedText cachedText;
    cachedText.init(text, pFont);

    drawText(x, y, &cachedText, color, align, rotation, origin);
}

void RenderTarget::drawText( Vector2 pos, CachedText* pCachedText, Color color /*= Color::WHITE*/, Align align /*= Align::INVALID_ALIGN*/, float rotation /*= 0.0f */, Vector2 origin /*= Vector2::ZERO*/ )
{
    drawText(pos.X, pos.Y, pCachedText, color, align, rotation, origin);
}

void RenderTarget::drawText( float x, float y, CachedText* pCachedText, Color color /*= Color::WHITE*/, Align align /*= Align::INVALID_ALIGN*/, float rotation /*= 0.0f */, Vector2 origin /*= Vector2::ZERO*/ )
{
    if (pCachedText->text().length() == 0)
        return;

    if (pCachedText->texture() == nullptr)
    {
        ERROR(toString(), "Invalid Cached Text");
        return;
    }

    switch (align)
    {
    case ALIGN_LEFT:

        origin.X = 0;

        break;
    case ALIGN_CENTER:

        origin.X = pCachedText->texture()->size().halfWidth();

        break;
    case ALIGN_RIGHT:

        origin.X = pCachedText->texture()->size().width();

        break;
    }

    if (align != INVALID_ALIGN)
        x -= origin.X;

    draw(x, y, pCachedText->texture(), color, rotation, origin);
}

void RenderTarget::draw( Vector2 pos, Texture* pTexture, Color color /*= Color::WHITE*/, float rotation /*= 0.0f */, Vector2 origin /*= Vector2::ZERO*/ )
{
    draw(pos.X, pos.Y, pTexture, color, rotation, origin);
}

void RenderTarget::draw( float x, float y, Texture* pTexture, Color color /*= Color::WHITE*/, float rotation /*= 0.0f */, Vector2 origin /*= Vector2::ZERO*/ )
{
    draw(x, y, pTexture, Rect(Vector2::ZERO, pTexture->size()), color, rotation, origin);
}

void RenderTarget::draw( Vector2 pos, Texture* pTexture, Rect sourceRect, Color color /*= Color::WHITE*/, float rotation /*= 0.0f */, Vector2 origin /*= Vector2::ZERO*/, bool flip /*= false*/ )
{
    draw(pos.X, pos.Y, pTexture, sourceRect, color, rotation, origin, flip);
}

void RenderTarget::draw( float x, float y, Texture* pTexture, Rect sourceRect, Color color /*= Color::WHITE*/, float rotation /*= 0.0f */, Vector2 origin /*= Vector2::ZERO*/, bool flip /*= false*/ )
{
    glEnable(GL_TEXTURE_2D);

    glPushMatrix();
    glTranslatef(x, y, 0);

    glTranslatef(origin.X, origin.Y, 0);
    glRotatef(toDeg(rotation), 0.0f, 0, 1.0f);
    glTranslatef(-origin.X, -origin.Y, 0);

    glBindTexture(GL_TEXTURE_2D, pTexture->GLTexture());

    glBegin(GL_QUADS);

    glColor4f(color.fracR(), color.fracG(), color.fracB(), color.fracA());

    Size texSize = pTexture->size();
    Rect convSrcRect = Rect(sourceRect.left() / texSize.width(), sourceRect.top() / texSize.height(), sourceRect.Width / texSize.width(), sourceRect.Height / texSize.height());

    if (flip)
    {
        glTexCoord2d(convSrcRect.right(),   convSrcRect.top());     glVertex2f(0.0f,                0.0f);
        glTexCoord2d(convSrcRect.left(),    convSrcRect.top());     glVertex2f(sourceRect.Width,    0.0f);
        glTexCoord2d(convSrcRect.left(),    convSrcRect.bottom());  glVertex2f(sourceRect.Width,    sourceRect.Height);
        glTexCoord2d(convSrcRect.right(),   convSrcRect.bottom());  glVertex2f(0.0f,                sourceRect.Height);
    }
    else
    {
        glTexCoord2d(convSrcRect.left(),    convSrcRect.top());     glVertex2f(0.0f,                0.0f);
        glTexCoord2d(convSrcRect.right(),   convSrcRect.top());     glVertex2f(sourceRect.Width,    0.0f);
        glTexCoord2d(convSrcRect.right(),   convSrcRect.bottom());  glVertex2f(sourceRect.Width,    sourceRect.Height);
        glTexCoord2d(convSrcRect.left(),    convSrcRect.bottom());  glVertex2f(0.0f,                sourceRect.Height);
    }

    glEnd();

    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}

void RenderTarget::drawLine( Vector2 start, Vector2 end, Color color /*= Color::WHITE*/, float thickness /*= 1.0f*/ )
{
    drawLine(start.X, start.Y, end.X, end.Y, color, thickness);
}

void RenderTarget::drawLine( float x1, float y1, float x2, float y2, Color color /*= Color::WHITE*/, float thickness /*= 1.0f*/ )
{
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f);

    glColor4f(color.fracR(), color.fracG(), color.fracB(), color.fracA());

    glLineWidth(thickness);

    glBegin(GL_LINES);

    glVertex2f(x1, y1);
    glVertex2f(x2, y2);

    glEnd();

    glPopMatrix();
}

void RenderTarget::drawRect( float x, float y, float width, float height, Color color /*= Color::WHITE*/, float rotation /*= 0.0f */, Vector2 origin /*= Vector2::ZERO*/ )
{
    Rect rect = Rect(x, y, width, height);
    drawRect(rect, color, rotation, origin);
}

void RenderTarget::drawRect( Rect rect, Color color /*= Color::WHITE*/, float rotation /*= 0.0f */, Vector2 origin /*= Vector2::ZERO*/ )
{
    glPushMatrix();
    glTranslatef(rect.X, rect.Y, 0.0f);

    glTranslatef(origin.X, origin.Y, 0.0f);
    glRotatef(toDeg(rotation), 0.0f, 0.0f, 1.0f);
    glTranslatef(-origin.X, -origin.Y, 0.0f);

    glColor4f(color.fracR(), color.fracG(), color.fracB(), color.fracA());

    glBegin(GL_LINE_LOOP);

    glVertex2f(0.0f,       0.0f);
    glVertex2f(rect.Width, 0.0f);
    glVertex2f(rect.Width, rect.Height);
    glVertex2f(0.0f,       rect.Height);

    glEnd();

    glPopMatrix();
}

void RenderTarget::fillRect( float x, float y, float width, float height, Color color /*= Color::WHITE*/, float rotation /*= 0.0f */, Vector2 origin /*= Vector2::ZERO*/ )
{
    Rect rect = Rect(x, y, width, height);
    fillRect(rect, color, rotation, origin);
}

void RenderTarget::fillRect( Rect rect, Color color /*= Color::WHITE*/, float rotation /*= 0.0f */, Vector2 origin /*= Vector2::ZERO*/ )
{
    glPushMatrix();
    glTranslatef(rect.X, rect.Y, 0.0f);

    glTranslatef(origin.X, origin.Y, 0.0f);
    glRotatef(toDeg(rotation), 0.0f, 0.0f, 1.0f);
    glTranslatef(-origin.X, -origin.Y, 0.0f);

    glColor4f(color.fracR(), color.fracG(), color.fracB(), color.fracA());

    glBegin(GL_QUADS);

    glVertex2f(0.0f,       0.0f);
    glVertex2f(rect.Width, 0.0f);
    glVertex2f(rect.Width, rect.Height);
    glVertex2f(0.0f,       rect.Height);

    glEnd();

    glPopMatrix();
}

void RenderTarget::drawCircle( float x, float y, float radius, Color color /*= Color::WHITE*/, float rotation /*= 0.0f */, Vector2 origin /*= Vector2::ZERO*/ )
{
    Circle circle = Circle(x, y, radius);
    drawCircle(circle, color, rotation, origin);
}

void RenderTarget::drawCircle( Circle circle, Color color /*= Color::WHITE*/, float rotation /*= 0.0f */, Vector2 origin /*= Vector2::ZERO*/ )
{
    drawShape(circle.X, circle.Y, circle.Radius, 12, color, rotation, origin);
}

void RenderTarget::fillCircle( float x, float y, float radius, Color color /*= Color::WHITE*/, float rotation /*= 0.0f */, Vector2 origin /*= Vector2::ZERO*/ )
{
    Circle circle = Circle(x, y, radius);
    fillCircle(circle, color, rotation, origin);
}

void RenderTarget::fillCircle( Circle circle, Color color /*= Color::WHITE*/, float rotation /*= 0.0f */, Vector2 origin /*= Vector2::ZERO*/ )
{
    fillShape(circle.X, circle.Y, circle.Radius, 12, color, rotation, origin);
}

void RenderTarget::drawTriangle( Vector2 pos, float radius, Color color /*= Color::WHITE*/,  float rotation /*= 0.0f */, Vector2 origin /*= Vector2::ZERO*/ )
{
    drawTriangle(pos.X, pos.Y, radius, color, rotation, origin);
}

void RenderTarget::fillTriangle( Vector2 pos, float radius, Color color /*= Color::WHITE*/,  float rotation /*= 0.0f */, Vector2 origin /*= Vector2::ZERO*/ )
{
    fillTriangle(pos.X, pos.Y, radius, color, rotation, origin);
}

void RenderTarget::drawTriangle( float x, float y, float radius, Color color /*= Color::WHITE*/, float rotation /*= 0.0f */, Vector2 origin /*= Vector2::ZERO*/ )
{
    drawShape(x, y, radius, 1.5, color, rotation, origin);
}

void RenderTarget::fillTriangle( float x, float y, float radius, Color color /*= Color::WHITE*/, float rotation /*= 0.0f */, Vector2 origin /*= Vector2::ZERO*/ )
{
    fillShape(x, y, radius, 1.5, color, rotation, origin);
}

void RenderTarget::drawPentagon( Vector2 pos, float radius, Color color /*= Color::WHITE*/,  float rotation /*= 0.0f */, Vector2 origin /*= Vector2::ZERO*/ )
{
    drawPentagon(pos.X, pos.Y, radius, color, rotation, origin);
}

void RenderTarget::fillPentagon( Vector2 pos, float radius, Color color /*= Color::WHITE*/,  float rotation /*= 0.0f */, Vector2 origin /*= Vector2::ZERO*/ )
{
    fillPentagon(pos.X, pos.Y, radius, color, rotation, origin);
}

void RenderTarget::drawPentagon( float x, float y, float radius, Color color /*= Color::WHITE*/, float rotation /*= 0.0f */, Vector2 origin /*= Vector2::ZERO*/ )
{
    drawShape(x, y, radius, 2.5, color, rotation, origin);
}

void RenderTarget::fillPentagon( float x, float y, float radius, Color color /*= Color::WHITE*/, float rotation /*= 0.0f */, Vector2 origin /*= Vector2::ZERO*/ )
{
    fillShape(x, y, radius, 2.5, color, rotation, origin);
}

void RenderTarget::drawHexagon( Vector2 pos, float radius, Color color /*= Color::WHITE*/,  float rotation /*= 0.0f */, Vector2 origin /*= Vector2::ZERO*/ )
{
    drawShape(pos.X, pos.Y, radius, 3, color, rotation, origin);
}

void RenderTarget::fillHexagon( Vector2 pos, float radius, Color color /*= Color::WHITE*/,  float rotation /*= 0.0f */, Vector2 origin /*= Vector2::ZERO*/ )
{
    fillShape(pos.X, pos.Y, radius, 3, color, rotation, origin);
}

void RenderTarget::drawHexagon( float x, float y, float radius, Color color /*= Color::WHITE*/, float rotation /*= 0.0f */, Vector2 origin /*= Vector2::ZERO*/ )
{
    drawShape(x, y, radius, 3, color, rotation, origin);
}

void RenderTarget::fillHexagon( float x, float y, float radius, Color color /*= Color::WHITE*/, float rotation /*= 0.0f */, Vector2 origin /*= Vector2::ZERO*/ )
{
    fillShape(x, y, radius, 3, color, rotation, origin);
}
