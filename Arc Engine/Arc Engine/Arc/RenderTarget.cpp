#include "RenderTarget.h"
#include "GraphicsSystem.h"

Arc::RenderTarget::RenderTarget( GraphicsSystem* pGraphicsSystem )
	: _pGraphicsSystem(pGraphicsSystem)
{
}

void Arc::RenderTarget::beginDraw( void ) const
{
    Color clearColor = _pGraphicsSystem->getClearColor();

    glClearColor(clearColor.fracR(), clearColor.fracG(), clearColor.fracB(), clearColor.fracA());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
}

// ShapeValue 1.5 - Draws Triangle
// ShapeValue 2   - Draws Square
// ShapeValue 3   - Draws Hexagon
// ShapeValue 4   - Draws Octagon
// ShapeValue 5   - Draws Decagon
// ShapeValue 6   - Draws Circle
// ShapeValue 12  - Draws Better Circle
void Arc::RenderTarget::drawShape( const float x, const float y, const float radius, const float shapeValue, const Color color /*= Color::WHITE*/, const Angle rotation /*= Angle::ZERO*/, const Vector2 scale /*= Vector2::ONE*/, const Vector2 origin /*= Vector2::ZERO*/ ) const
{
    glPushMatrix();
    glTranslatef(x - origin.X, y - origin.Y, 0.0f);

    glTranslatef(origin.X, origin.Y, 0.0f);
    glRotatef(rotation.getDeg() - 90.0f, 0.0f, 0, 1.0f);
    glTranslatef(-origin.X, -origin.Y, 0.0f);

    glColor4f(color.fracR(), color.fracG(), color.fracB(), color.fracA());

    glBegin(GL_LINE_LOOP);

    for (float i = 0; i < PI2; i += (float)(PI / shapeValue))
    {
        glVertex2f(cosf(i) * radius * scale.X, sinf(i) * radius * scale.Y);
    }

    glEnd();

    glPopMatrix();
}

void Arc::RenderTarget::fillShape( const float x, const float y, const float radius, const float shapeValue, const Color color /*= Color::WHITE*/, const Angle rotation /*= Angle::ZERO*/, const Vector2 scale /*= Vector2::ONE*/, const Vector2 origin /*= Vector2::ZERO*/ ) const
{
    glPushMatrix();
    glTranslatef(x - origin.X, y - origin.Y, 0.0f);

    glTranslatef(origin.X, origin.Y, 0.0f);
    glRotatef(rotation.getDeg() - 90.0f, 0.0f, 0.0f, 1.0f);
    glTranslatef(-origin.X, -origin.Y, 0.0f);

    glColor4f(color.fracR(), color.fracG(), color.fracB(), color.fracA());

    glBegin(GL_POLYGON);

    for (float i = 0; i < PI2; i += (float)(PI / shapeValue))
    {
        glVertex2f(cosf(i) * radius * scale.X, sinf(i) * radius * scale.Y);
    }

    glEnd();

    glPopMatrix();
}

void Arc::RenderTarget::drawText( const float x, const float y, const RenderedText* pRenderedText, const Color color /*= Color::WHITE*/, const Angle rotation /*= Angle::ZERO*/, const Vector2 scale /*= Vector2::ONE*/, const Vector2 origin /*= Vector2::ZERO*/ ) const
{
    if (pRenderedText->getText().length() == 0)
        return;

    if (pRenderedText->getTexture() == nullptr)
    {
        ERROR(toString(), "Invalid Rendered Text");
        return;
    }

    draw(x, y, pRenderedText->getTexture(), color, rotation, scale, origin);
}

void Arc::RenderTarget::draw( const float x, const float y, const Texture* pTexture, const Rect sourceRect, const Color color /*= Color::WHITE*/, const Angle rotation /*= Angle::ZERO*/, const Vector2 scale /*= Vector2::ONE*/, const Vector2 origin /*= Vector2::ZERO*/ ) const
{
    glEnable(GL_TEXTURE_2D);

    glPushMatrix();
    glTranslatef(x - origin.X, y - origin.Y, 0);

    glTranslatef(origin.X, origin.Y, 0);
    glRotatef(rotation.getDeg(), 0.0f, 0, 1.0f);
    glTranslatef(-origin.X, -origin.Y, 0);

    glBindTexture(GL_TEXTURE_2D, pTexture->getGLTexture());

    glColor4f(color.fracR(), color.fracG(), color.fracB(), color.fracA());

    glBegin(GL_QUADS);

    Size texSize = pTexture->getSize();
    Rect convSrcRect = Rect(sourceRect.left() / texSize.width(), sourceRect.top() / texSize.height(), sourceRect.Width / texSize.width(), sourceRect.Height / texSize.height());

	glTexCoord2d(convSrcRect.left(),    convSrcRect.top());     glVertex2f(0.0f,						0.0f);
	glTexCoord2d(convSrcRect.right(),   convSrcRect.top());     glVertex2f(sourceRect.Width * scale.X,  0.0f);
	glTexCoord2d(convSrcRect.right(),   convSrcRect.bottom());  glVertex2f(sourceRect.Width * scale.X,  sourceRect.Height * scale.Y);
	glTexCoord2d(convSrcRect.left(),    convSrcRect.bottom());  glVertex2f(0.0f,						sourceRect.Height * scale.Y);

    glEnd();

    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
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

void Arc::RenderTarget::drawRect( const Rect rect, const Color color /*= Color::WHITE*/, const Angle rotation /*= Angle::ZERO*/, const Vector2 scale /*= Vector2::ONE*/, const Vector2 origin /*= Vector2::ZERO*/ ) const
{
    glPushMatrix();
    glTranslatef(rect.X - origin.X, rect.Y - origin.Y, 0.0f);

    glTranslatef(origin.X, origin.Y, 0.0f);
    glRotatef(rotation.getDeg(), 0.0f, 0.0f, 1.0f);
    glTranslatef(-origin.X, -origin.Y, 0.0f);

    glColor4f(color.fracR(), color.fracG(), color.fracB(), color.fracA());

    glBegin(GL_LINE_LOOP);

    glVertex2f(0.0f,				 0.0f);
    glVertex2f(rect.Width * scale.X, 0.0f);
	glVertex2f(rect.Width * scale.X, rect.Height * scale.Y);
	glVertex2f(0.0f,				 rect.Height * scale.Y);

    glEnd();

    glPopMatrix();
}

void Arc::RenderTarget::fillRect( const Rect rect, const Color color /*= Color::WHITE*/, const Angle rotation /*= Angle::ZERO*/, const Vector2 scale /*= Vector2::ONE*/, const Vector2 origin /*= Vector2::ZERO*/ ) const
{
    glPushMatrix();
    glTranslatef(rect.X - origin.X, rect.Y - origin.Y, 0.0f);

    glTranslatef(origin.X, origin.Y, 0.0f);
    glRotatef(rotation.getDeg(), 0.0f, 0.0f, 1.0f);
    glTranslatef(-origin.X, -origin.Y, 0.0f);

    glColor4f(color.fracR(), color.fracG(), color.fracB(), color.fracA());

    glBegin(GL_QUADS);

    glVertex2f(0.0f,				 0.0f);
    glVertex2f(rect.Width * scale.X, 0.0f);
	glVertex2f(rect.Width * scale.X, rect.Height * scale.Y);
	glVertex2f(0.0f,				 rect.Height * scale.Y);

    glEnd();

    glPopMatrix();
}
