#include "RenderTarget.h"
#include "GraphicsSystem.h"

Arc::RenderTarget::RenderTarget( void )
{
    _pGraphicsSystem = nullptr;
}

void Arc::RenderTarget::init( GraphicsSystem* pGraphicsSystem )
{
    _pGraphicsSystem = pGraphicsSystem;
}

void Arc::RenderTarget::beginDraw( void ) const
{
    Color clearColor = _pGraphicsSystem->getClearColor();

    glClearColor(clearColor.fracR(), clearColor.fracG(), clearColor.fracB(), clearColor.fracA());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
}

void Arc::RenderTarget::endDraw( void ) const
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
void Arc::RenderTarget::drawShape( const float x, const float y, const float radius, const float shapeValue, const Color color /*= Color::WHITE*/, const float rotation /*= 0.0f */, const Vector2 origin /*= Vector2::ZERO*/ ) const
{
    glPushMatrix();
    glTranslatef(x - origin.X + radius, y - origin.Y - radius, 0.0f);

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

void Arc::RenderTarget::fillShape( const float x, const float y, const float radius, const float shapeValue, const Color color /*= Color::WHITE*/, const float rotation /*= 0.0f */, const Vector2 origin /*= Vector2::ZERO*/ ) const
{
    glPushMatrix();
    glTranslatef(x - origin.X + radius, y - origin.Y - radius, 0.0f);

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

void Arc::RenderTarget::drawText( const Vector2 pos, const string text, Font* pFont, const Color color /*= Color::WHITE*/, const float rotation /*= 0.0f */, const Vector2 origin /*= Vector2::ZERO*/ ) const
{
    drawText(pos.X, pos.Y, text, pFont, color, rotation, origin);
}

void Arc::RenderTarget::drawText( const float x, const float y, const string text, Font* pFont, const Color color /*= Color::WHITE*/, const float rotation /*= 0.0f */, const Vector2 origin /*= Vector2::ZERO*/ ) const
{
    CachedText cachedText;
    cachedText.init(text, pFont);

    drawText(x, y, &cachedText, color, rotation, origin);
}

void Arc::RenderTarget::drawText( const Vector2 pos, const CachedText* pCachedText, const Color color /*= Color::WHITE*/, const float rotation /*= 0.0f */, const Vector2 origin /*= Vector2::ZERO*/ ) const
{
    drawText(pos.X, pos.Y, pCachedText, color, rotation, origin);
}

void Arc::RenderTarget::drawText( const float x, const float y, const CachedText* pCachedText, const Color color /*= Color::WHITE*/, const float rotation /*= 0.0f */, const Vector2 origin /*= Vector2::ZERO*/ ) const
{
    if (pCachedText->getText().length() == 0)
        return;

    if (pCachedText->getTexture() == nullptr)
    {
        ERROR(toString(), "Invalid Cached Text");
        return;
    }

    draw(x, y, pCachedText->getTexture(), color, rotation, origin);
}

void Arc::RenderTarget::draw( const Vector2 pos, const Texture* pTexture, const Color color /*= Color::WHITE*/, const float rotation /*= 0.0f */, const Vector2 origin /*= Vector2::ZERO*/ ) const
{
    draw(pos.X, pos.Y, pTexture, color, rotation, origin);
}

void Arc::RenderTarget::draw( const float x, const float y, const Texture* pTexture, const Color color /*= Color::WHITE*/, const float rotation /*= 0.0f */, const Vector2 origin /*= Vector2::ZERO*/ ) const
{
    draw(x, y, pTexture, Rect(Vector2::ZERO, pTexture->size()), color, rotation, origin);
}

void Arc::RenderTarget::draw( const Vector2 pos, const Texture* pTexture, const Rect sourceRect, const Color color /*= Color::WHITE*/, const float rotation /*= 0.0f */, const Vector2 origin /*= Vector2::ZERO*/, const bool flip /*= false*/ ) const
{
    draw(pos.X, pos.Y, pTexture, sourceRect, color, rotation, origin, flip);
}

void Arc::RenderTarget::draw( const float x, const float y, const Texture* pTexture, const Rect sourceRect, const Color color /*= Color::WHITE*/, const float rotation /*= 0.0f */, const Vector2 origin /*= Vector2::ZERO*/, const bool flip /*= false*/ ) const
{
    glEnable(GL_TEXTURE_2D);

    glPushMatrix();
    glTranslatef(x - origin.X, y - origin.Y, 0);

    glTranslatef(origin.X, origin.Y, 0);
    glRotatef(toDeg(rotation), 0.0f, 0, 1.0f);
    glTranslatef(-origin.X, -origin.Y, 0);

    glBindTexture(GL_TEXTURE_2D, pTexture->getGLTexture());

    glColor4f(color.fracR(), color.fracG(), color.fracB(), color.fracA());

    glBegin(GL_QUADS);

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

void Arc::RenderTarget::drawLine( const Vector2 start, const Vector2 end, const Color color /*= Color::WHITE*/, const float thickness /*= 1.0f*/ ) const
{
    drawLine(start.X, start.Y, end.X, end.Y, color, thickness);
}

void Arc::RenderTarget::drawLine( const float x1, const float y1, const float x2, const float y2, const Color color /*= Color::WHITE*/, const float thickness /*= 1.0f*/ ) const
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

void Arc::RenderTarget::drawRect( const float x, const float y, const float width, const float height, const Color color /*= Color::WHITE*/, const float rotation /*= 0.0f */, const Vector2 origin /*= Vector2::ZERO*/ ) const
{
    Rect rect = Rect(x, y, width, height);
    drawRect(rect, color, rotation, origin);
}

void Arc::RenderTarget::drawRect( const Rect rect, const Color color /*= Color::WHITE*/, const float rotation /*= 0.0f */, const Vector2 origin /*= Vector2::ZERO*/ ) const
{
    glPushMatrix();
    glTranslatef(rect.X - origin.X, rect.Y - origin.Y, 0.0f);

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

void Arc::RenderTarget::fillRect( const float x, const float y, const float width, const float height, const Color color /*= Color::WHITE*/, const float rotation /*= 0.0f */, const Vector2 origin /*= Vector2::ZERO*/ ) const
{
    Rect rect = Rect(x, y, width, height);
    fillRect(rect, color, rotation, origin);
}

void Arc::RenderTarget::fillRect( const Rect rect, const Color color /*= Color::WHITE*/, const float rotation /*= 0.0f */, const Vector2 origin /*= Vector2::ZERO*/ ) const
{
    glPushMatrix();
    glTranslatef(rect.X - origin.X, rect.Y - origin.Y, 0.0f);

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

void Arc::RenderTarget::drawCircle( const float x, const float y, const float radius, const Color color /*= Color::WHITE*/, const float rotation /*= 0.0f */, const Vector2 origin /*= Vector2::ZERO*/ ) const
{
    Circle circle = Circle(x, y, radius);
    drawCircle(circle, color, rotation, origin);
}

void Arc::RenderTarget::drawCircle( const Circle circle, const Color color /*= Color::WHITE*/, const float rotation /*= 0.0f */, const Vector2 origin /*= Vector2::ZERO*/ ) const
{
    drawShape(circle.X, circle.Y, circle.Radius, 24, color, rotation, origin);
}

void Arc::RenderTarget::fillCircle( const float x, const float y, const float radius, const Color color /*= Color::WHITE*/, const float rotation /*= 0.0f */, const Vector2 origin /*= Vector2::ZERO*/ ) const
{
    Circle circle = Circle(x, y, radius);
    fillCircle(circle, color, rotation, origin);
}

void Arc::RenderTarget::fillCircle( const Circle circle, const Color color /*= Color::WHITE*/, const float rotation /*= 0.0f */, const Vector2 origin /*= Vector2::ZERO*/ ) const
{
    fillShape(circle.X, circle.Y, circle.Radius, 24, color, rotation, origin);
}

void Arc::RenderTarget::drawTriangle( const Vector2 pos, const float radius, const Color color /*= Color::WHITE*/,  const float rotation /*= 0.0f */, const Vector2 origin /*= Vector2::ZERO*/ ) const
{
    drawTriangle(pos.X, pos.Y, radius, color, rotation, origin);
}

void Arc::RenderTarget::fillTriangle( const Vector2 pos, const float radius, const Color color /*= Color::WHITE*/,  const float rotation /*= 0.0f */, const Vector2 origin /*= Vector2::ZERO*/ ) const
{
    fillTriangle(pos.X, pos.Y, radius, color, rotation, origin);
}

void Arc::RenderTarget::drawTriangle( const float x, const float y, const float radius, const Color color /*= Color::WHITE*/, const float rotation /*= 0.0f */, const Vector2 origin /*= Vector2::ZERO*/ ) const
{
    drawShape(x, y, radius, 1.5, color, rotation, origin);
}

void Arc::RenderTarget::fillTriangle( const float x, const float y, const float radius, const Color color /*= Color::WHITE*/, const float rotation /*= 0.0f */, const Vector2 origin /*= Vector2::ZERO*/ ) const
{
    fillShape(x, y, radius, 1.5, color, rotation, origin);
}

void Arc::RenderTarget::drawPentagon( const Vector2 pos, const float radius, const Color color /*= Color::WHITE*/, const float rotation /*= 0.0f */, const Vector2 origin /*= Vector2::ZERO*/ ) const
{
    drawPentagon(pos.X, pos.Y, radius, color, rotation, origin);
}

void Arc::RenderTarget::fillPentagon( const Vector2 pos, const float radius, const Color color /*= Color::WHITE*/, const float rotation /*= 0.0f */, const Vector2 origin /*= Vector2::ZERO*/ ) const
{
    fillPentagon(pos.X, pos.Y, radius, color, rotation, origin);
}

void Arc::RenderTarget::drawPentagon( const float x, const float y, const float radius, const Color color /*= Color::WHITE*/, const float rotation /*= 0.0f */, const Vector2 origin /*= Vector2::ZERO*/ ) const
{
    drawShape(x, y, radius, 2.5, color, rotation, origin);
}

void Arc::RenderTarget::fillPentagon( const float x, const float y, const float radius, const Color color /*= Color::WHITE*/, const float rotation /*= 0.0f */, const Vector2 origin /*= Vector2::ZERO*/ ) const
{
    fillShape(x, y, radius, 2.5, color, rotation, origin);
}

void Arc::RenderTarget::drawHexagon( const Vector2 pos, const float radius, const Color color /*= Color::WHITE*/, const float rotation /*= 0.0f */, const Vector2 origin /*= Vector2::ZERO*/ ) const
{
    drawShape(pos.X, pos.Y, radius, 3, color, rotation, origin);
}

void Arc::RenderTarget::fillHexagon( const Vector2 pos, const float radius, const Color color /*= Color::WHITE*/, const float rotation /*= 0.0f */, const Vector2 origin /*= Vector2::ZERO*/ ) const
{
    fillShape(pos.X, pos.Y, radius, 3, color, rotation, origin);
}

void Arc::RenderTarget::drawHexagon( const float x, const float y, const float radius, const Color color /*= Color::WHITE*/, const float rotation /*= 0.0f */, const Vector2 origin /*= Vector2::ZERO*/ ) const
{
    drawShape(x, y, radius, 3, color, rotation, origin);
}

void Arc::RenderTarget::fillHexagon( const float x, const float y, const float radius, const Color color /*= Color::WHITE*/, const float rotation /*= 0.0f */, const Vector2 origin /*= Vector2::ZERO*/ ) const
{
    fillShape(x, y, radius, 3, color, rotation, origin);
}
