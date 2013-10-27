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
void Arc::RenderTarget::drawShape( const float x, 
								   const float y, 
								   const float radius,
								   const float shapeValue,
								   const Color color /*= Color::WHITE*/,
								   const Angle rotation /*= Angle::ZERO*/,
								   const Vector2 scale /*= Vector2::ONE*/, 
								   const Origin origin /*= Origin::ZERO*/ ) const
{
	Point originPoint = origin.getPoint();

    glPushMatrix();
    glTranslatef(x - originPoint.X, y - originPoint.Y, 0.0f);

    glTranslatef(originPoint.X, originPoint.Y, 0.0f);
    glRotatef(rotation.getDeg() - 90.0f, 0.0f, 0, 1.0f);
    glTranslatef(-originPoint.X, -originPoint.Y, 0.0f);

    glColor4f(color.fracR(), color.fracG(), color.fracB(), color.fracA());

    glBegin(GL_LINE_LOOP);

    for (float i = 0; i < PI2; i += (float)(PI / shapeValue))
    {
        glVertex2f(cosf(i) * radius * scale.X, sinf(i) * radius * scale.Y);
    }

    glEnd();

    glPopMatrix();
}

void Arc::RenderTarget::fillShape( const float x, 
								   const float y,
								   const float radius,
								   const float shapeValue,
								   const Color color /*= Color::WHITE*/,
								   const Angle rotation /*= Angle::ZERO*/,
								   const Vector2 scale /*= Vector2::ONE*/,
								   const Origin origin /*= Origin::ZERO*/ ) const
{
	Point originPoint = origin.getPoint();

    glPushMatrix();
    glTranslatef(x - originPoint.X, y - originPoint.Y, 0.0f);

    glTranslatef(originPoint.X, originPoint.Y, 0.0f);
    glRotatef(rotation.getDeg() - 90.0f, 0.0f, 0.0f, 1.0f);
    glTranslatef(-originPoint.X, -originPoint.Y, 0.0f);

    glColor4f(color.fracR(), color.fracG(), color.fracB(), color.fracA());

    glBegin(GL_POLYGON);

    for (float i = 0; i < PI2; i += (float)(PI / shapeValue))
    {
        glVertex2f(cosf(i) * radius * scale.X, sinf(i) * radius * scale.Y);
    }

    glEnd();

    glPopMatrix();
}

void Arc::RenderTarget::drawText( const float x,
								  const float y, 
								  const RenderedText* pRenderedText,
								  const Color color /*= Color::WHITE*/, 
								  const Angle rotation /*= Angle::ZERO*/,
								  const Vector2 scale /*= Vector2::ONE*/,
								  const Origin origin /*= Origin::ZERO*/ ) const
{
	Point originPoint = origin.getPoint();

    if (pRenderedText->getText().length() == 0)
        return;

    if (pRenderedText->getTexture() == nullptr)
    {
        ERROR(toString(), "Invalid Rendered Text");
        return;
    }

    draw(x, y, pRenderedText->getTexture(), color, rotation, scale, origin);
}

void Arc::RenderTarget::draw( const float x,
							  const float y, 
							  const Texture* pTexture,
							  const Rect sourceRect, 
							  const Color color /*= Color::WHITE*/,
							  const Angle rotation /*= Angle::ZERO*/,
							  const Vector2 scale /*= Vector2::ONE*/,
							  const Origin origin /*= Origin::ZERO*/ ) const
{
	Point originPoint = origin.getPoint();

    glEnable(GL_TEXTURE_2D);

    glPushMatrix();
    glTranslatef(x - originPoint.X, y - originPoint.Y, 0);

    glTranslatef(originPoint.X, originPoint.Y, 0);
    glRotatef(rotation.getDeg(), 0.0f, 0, 1.0f);
    glTranslatef(-originPoint.X, -originPoint.Y, 0);

    glBindTexture(GL_TEXTURE_2D, pTexture->getGLTexture());

    glColor4f(color.fracR(), color.fracG(), color.fracB(), color.fracA());

    glBegin(GL_QUADS);

    Size texSize = pTexture->getSize();
    Rect convSrcRect = Rect(sourceRect.getLeft() / texSize.getWidth(), sourceRect.getTop() / texSize.getHeight(), sourceRect.Width / texSize.getWidth(), sourceRect.Height / texSize.getHeight());

	glTexCoord2d(convSrcRect.getLeft(),    convSrcRect.getTop());     glVertex2f(0.0f,						0.0f);
	glTexCoord2d(convSrcRect.getRight(),   convSrcRect.getTop());     glVertex2f(sourceRect.Width * scale.X,  0.0f);
	glTexCoord2d(convSrcRect.getRight(),   convSrcRect.getBottom());  glVertex2f(sourceRect.Width * scale.X,  sourceRect.Height * scale.Y);
	glTexCoord2d(convSrcRect.getLeft(),    convSrcRect.getBottom());  glVertex2f(0.0f,						sourceRect.Height * scale.Y);

    glEnd();

    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}

void Arc::RenderTarget::drawLine( const float x1,
								  const float y1, 
								  const float x2, 
								  const float y2, 
								  const Color color /*= Color::WHITE*/,
								  const float thickness /*= 1.0f*/ ) const
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

void Arc::RenderTarget::drawRect( const Rect rect,
								  const Color color /*= Color::WHITE*/,
								  const Angle rotation /*= Angle::ZERO*/,
								  const Vector2 scale /*= Vector2::ONE*/,
								  const Origin origin /*= Origin::ZERO*/ ) const
{
	Point originPoint = origin.getPoint();

    glPushMatrix();
    glTranslatef(rect.X - originPoint.X, rect.Y - originPoint.Y, 0.0f);

    glTranslatef(originPoint.X, originPoint.Y, 0.0f);
    glRotatef(rotation.getDeg(), 0.0f, 0.0f, 1.0f);
    glTranslatef(-originPoint.X, -originPoint.Y, 0.0f);

    glColor4f(color.fracR(), color.fracG(), color.fracB(), color.fracA());

    glBegin(GL_LINE_LOOP);

    glVertex2f(0.0f,				 0.0f);
    glVertex2f(rect.Width * scale.X, 0.0f);
	glVertex2f(rect.Width * scale.X, rect.Height * scale.Y);
	glVertex2f(0.0f,				 rect.Height * scale.Y);

    glEnd();

    glPopMatrix();
}

void Arc::RenderTarget::fillRect( const Rect rect, 
								  const Color color /*= Color::WHITE*/,
								  const Angle rotation /*= Angle::ZERO*/,
								  const Vector2 scale /*= Vector2::ONE*/,
								  const Origin origin /*= Origin::ZERO*/ ) const
{
	Point originPoint = origin.getPoint();

    glPushMatrix();
    glTranslatef(rect.X - originPoint.X, rect.Y - originPoint.Y, 0.0f);

    glTranslatef(originPoint.X, originPoint.Y, 0.0f);
    glRotatef(rotation.getDeg(), 0.0f, 0.0f, 1.0f);
    glTranslatef(-originPoint.X, -originPoint.Y, 0.0f);

    glColor4f(color.fracR(), color.fracG(), color.fracB(), color.fracA());

    glBegin(GL_QUADS);

    glVertex2f(0.0f,				 0.0f);
    glVertex2f(rect.Width * scale.X, 0.0f);
	glVertex2f(rect.Width * scale.X, rect.Height * scale.Y);
	glVertex2f(0.0f,				 rect.Height * scale.Y);

    glEnd();

    glPopMatrix();
}

void Arc::RenderTarget::drawTriangle( const Vector2 pointA,
									  const Vector2 pointB, 
									  const Vector2 pointC, 
									  const Color color /*= Color::WHITE*/ ) const
{
	glPushMatrix();

	glColor4f(color.fracR(), color.fracG(), color.fracB(), color.fracA());

	glBegin(GL_LINE_LOOP);

	glVertex2f(pointA.X, pointA.Y);
	glVertex2f(pointB.X, pointB.Y);
	glVertex2f(pointC.X, pointC.Y);

	glEnd();

	glPopMatrix();
}

void Arc::RenderTarget::fillTriangle( const Vector2 pointA,
									  const Vector2 pointB, 
									  const Vector2 pointC,
									  const Color color /*= Color::WHITE*/ ) const
{
	glPushMatrix();

	glColor4f(color.fracR(), color.fracG(), color.fracB(), color.fracA());

	glBegin(GL_POLYGON);

	glVertex2f(pointA.X, pointA.Y);
	glVertex2f(pointB.X, pointB.Y);
	glVertex2f(pointC.X, pointC.Y);

	glEnd();

	glPopMatrix();
}

void Arc::RenderTarget::drawPolygon( const ArrayList<Point> &points, const Color color /*= Color::WHITE */ ) const
{
	glPushMatrix();

	glColor4f(color.fracR(), color.fracG(), color.fracB(), color.fracA());

	glBegin(GL_LINE_LOOP);

	for (unsigned int i = 0; i < points.getSize(); ++i)
		glVertex2f(points[i].X, points[i].Y);

	glEnd();

	glPopMatrix();
}

void Arc::RenderTarget::fillPolygon( const ArrayList<Point> &points, const Color color /*= Color::WHITE */ ) const
{
	glPushMatrix();

	glColor4f(color.fracR(), color.fracG(), color.fracB(), color.fracA());

	glBegin(GL_POLYGON);

	for (unsigned int i = 0; i < points.getSize(); ++i)
		glVertex2f(points[i].X, points[i].Y);

	glEnd();

	glPopMatrix();
}
