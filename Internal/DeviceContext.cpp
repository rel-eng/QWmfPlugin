/* DeviceContext implementation.

   Copyright (C) 2010 rel-eng

   This file is part of QWmfPlugin.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

#include "DeviceContext.h"

DeviceContext::DeviceContext(size_t numberOfObjects, const MetaPlaceableRecord &placeableHeader) : graphicsObjects(numberOfObjects), placeableHeader(placeableHeader), windowOriginX(0.0), windowOriginY(0.0), windowExtentX(1.0), windowExtentY(1.0), viewportOriginX(0.0), viewportOriginY(0.0), viewportExtentX(1.0), viewportExtentY(1.0), mappingMode(MM_ANISOTROPIC), selectedBrush(), selectedFont(), selectedPen(), selectedPalette(), selectedRegion(), useDefaultBrush(true), useDefaultFont(true), useDefaultPen(true), useDefaultPalette(true), useDefaultRegion(true), currentPoint(0.0, 0.0)
{
}

DeviceContext::~DeviceContext()
{
}

void DeviceContext::CreateBrushIndirect(const MetaCreatebrushindirectRecord &record)
{
    this->graphicsObjects.insertObject(QSharedPointer<GraphicsObject>(dynamic_cast<GraphicsObject *>(new GraphicsObjectBrush(record))));
}

void DeviceContext::CreatePatternBrush(const MetaCreatepatternbrushRecord &record)
{
    this->graphicsObjects.insertObject(QSharedPointer<GraphicsObject>(dynamic_cast<GraphicsObject *>(new GraphicsObjectBrush(record))));
}

void DeviceContext::DibCreatePatternBrush(const MetaDibcreatepatternbrushRecord &record)
{
    this->graphicsObjects.insertObject(QSharedPointer<GraphicsObject>(dynamic_cast<GraphicsObject *>(new GraphicsObjectBrush(record))));
}

void DeviceContext::CreateFontIndirect(const MetaCreatefontindirectRecord &record)
{
    this->graphicsObjects.insertObject(QSharedPointer<GraphicsObject>(dynamic_cast<GraphicsObject *>(new GraphicsObjectFont(record))));
}

void DeviceContext::CreatePenIndirect(const MetaCreatepenindirectRecord &record)
{
    this->graphicsObjects.insertObject(QSharedPointer<GraphicsObject>(dynamic_cast<GraphicsObject *>(new GraphicsObjectPen(record))));
}

void DeviceContext::CreatePalette(const MetaCreatepaletteRecord &record)
{
    this->graphicsObjects.insertObject(QSharedPointer<GraphicsObject>(dynamic_cast<GraphicsObject *>(new GraphicsObjectPalette(record))));
}

void DeviceContext::CreateRegion(const MetaCreateregionRecord &record)
{
    this->graphicsObjects.insertObject(QSharedPointer<GraphicsObject>(dynamic_cast<GraphicsObject *>(new GraphicsObjectRegion(record))));
}

void DeviceContext::SetViewportOrg(const MetaSetviewportorgRecord &record)
{
    this->viewportOriginX = static_cast<qreal>(record.getPoint().x());
    this->viewportOriginY = static_cast<qreal>(record.getPoint().y());
}

void DeviceContext::SetViewportExt(const MetaSetviewportextRecord &record)
{
    if((this->mappingMode == MM_ANISOTROPIC) || (this->mappingMode == MM_ISOTROPIC))
    {
        this->viewportExtentX = static_cast<qreal>(record.getX());
        this->viewportExtentY = static_cast<qreal>(record.getY());
    }
}

void DeviceContext::SetWindowOrg(const MetaSetwindoworgRecord &record)
{
    this->windowOriginX = static_cast<qreal>(record.getPoint().x());
    this->windowOriginY = static_cast<qreal>(record.getPoint().y());
}

void DeviceContext::SetWindowExt(const MetaSetwindowextRecord &record)
{
    if((this->mappingMode == MM_ANISOTROPIC) || (this->mappingMode == MM_ISOTROPIC))
    {
        this->windowExtentX = static_cast<qreal>(record.getX());
        this->windowExtentY = static_cast<qreal>(record.getY());
    }
}

void DeviceContext::SetMapMode(const MetaSetmapmodeRecord &record)
{
    qreal widthLU = static_cast<qreal>(qAbs(placeableHeader.getRight() - placeableHeader.getLeft()));
    qreal heightLU = static_cast<qreal>(qAbs(placeableHeader.getBottom() - placeableHeader.getTop()));
    qreal tpi = qAbs(static_cast<qreal>(placeableHeader.getTpi()));
    int outWidth = qRound((widthLU / tpi) * static_cast<qreal>(72.0));
    int outHeight = qRound((heightLU / tpi) * static_cast<qreal>(72.0));
    this->mappingMode = record.getMapMode();
    switch(record.getMapMode())
    {
    //Одна логическая единица эквивалентна одному пикселу, ось абсцисс направлена вправо, ось ординат направлена вниз
    case MM_TEXT:
        this->viewportExtentX = 1.0;
        this->viewportExtentY = 1.0;
        this->windowExtentX = 1.0;
        this->windowExtentY = 1.0;
        break;
    //Одна логическая единица эквивалентна 0.1 миллиметра, ось абсцисс направлена вправо, ось ординат направлена вверх
    case MM_LOMETRIC:
        this->viewportExtentX = 72.0/254.0;
        this->viewportExtentY = 72.0/254.0;
        this->windowExtentX = 1.0;
        this->windowExtentY = -1.0;
        break;
    //Одна логическая единица эквивалентна 0.01 миллиметра, ось абсцисс направлена вправо, ось ординат направлена вверх
    case MM_HIMETRIC:
        this->viewportExtentX = 7.2/254.0;
        this->viewportExtentY = 7.2/254.0;
        this->windowExtentX = 1.0;
        this->windowExtentY = -1.0;
        break;
    //Одна логическая единица эквивалентна 0.01 дюйма, ось абсцисс направлена вправо, ось ординат направлена вверх
    case MM_LOENGLISH:
        this->viewportExtentX = 0.72;
        this->viewportExtentY = 0.72;
        this->windowExtentX = 1.0;
        this->windowExtentY = -1.0;
        break;
    //Одна логическая единица эквивалентна 0.001 дюйма, ось абсцисс направлена вправо, ось ординат направлена вверх
    case MM_HIENGLISH:
        this->viewportExtentX = 0.072;
        this->viewportExtentY = 0.072;
        this->windowExtentX = 1.0;
        this->windowExtentY = -1.0;
        break;
    //Одна логическая единица эквивалентна 1/1440 дюйма, ось абсцисс направлена вправо, ось ординат направлена вверх
    case MM_TWIPS:
        this->viewportExtentX = 72.0/1440.0;
        this->viewportExtentY = 72.0/1440.0;
        this->windowExtentX = 1.0;
        this->windowExtentY = -1.0;
        break;
    //Произвольные, но равные друг другу масштабные коэффициенты для осей абсцисс и ординат, задаются посредством команд META_SETWINDOWEXT и META_SETVIEWPORTEXT, необходимо обеспечивать равенство масштабных коэффициентов при любых преобразованиях
    case MM_ISOTROPIC:
        this->viewportExtentX = static_cast<qreal>(outWidth);
        this->viewportExtentY = static_cast<qreal>(outHeight);
        this->windowExtentX = 1.0;
        this->windowExtentY = -1.0;
        break;
    //Произвольные масштабные коэффициенты для осей абсцисс и ординат
    case MM_ANISOTROPIC:
        this->viewportExtentX = static_cast<qreal>(outWidth);
        this->viewportExtentY = static_cast<qreal>(outHeight);
        this->windowExtentX = 1.0;
        this->windowExtentY = -1.0;
        break;
    default:
        this->viewportExtentX = 1.0;
        this->viewportExtentY = 1.0;
        this->windowExtentX = 1.0;
        this->windowExtentY = 1.0;
    }
}

void DeviceContext::OffsetViewportOrg(const MetaOffsetviewportorgRecord &record)
{
    this->viewportOriginX += static_cast<qreal>(record.getXOffset());
    this->viewportOriginY += static_cast<qreal>(record.getYOffset());
}

void DeviceContext::OffsetWindowOrg(const MetaOffsetwindoworgRecord &record)
{
    this->windowOriginX += static_cast<qreal>(record.getXOffset());
    this->windowOriginY += static_cast<qreal>(record.getYOffset());
}

void DeviceContext::ScaleViewportExt(const MetaScaleviewportextRecord &record)
{
    if((this->mappingMode == MM_ANISOTROPIC) || (this->mappingMode == MM_ISOTROPIC))
    {
        this->viewportExtentX = (this->viewportExtentX * static_cast<qreal>(record.getXNum()))/static_cast<qreal>(record.getXDenom());
        this->viewportExtentY = (this->viewportExtentY * static_cast<qreal>(record.getYNum()))/static_cast<qreal>(record.getYDenom());
    }
}

void DeviceContext::ScaleWindowExt(const MetaScalewindowextRecord &record)
{
    if((this->mappingMode == MM_ANISOTROPIC) || (this->mappingMode == MM_ISOTROPIC))
    {
        this->windowExtentX = (this->windowExtentX * static_cast<qreal>(record.getXNum()))/static_cast<qreal>(record.getXDenom());
        this->windowExtentY = (this->windowExtentY * static_cast<qreal>(record.getYNum()))/static_cast<qreal>(record.getYDenom());
    }
}

void DeviceContext::SelectObject(const MetaSelectobjectRecord &record)
{
    switch(this->graphicsObjects.getObjectByHandle(static_cast<GraphicsObjectHandle>(record.getObjectIndex()))->getType())
    {
    case BRUSH_GRAPHICS_OBJECT:
        this->selectedBrush = this->graphicsObjects.getObjectByHandle(static_cast<GraphicsObjectHandle>(record.getObjectIndex())).dynamicCast<GraphicsObjectBrush>();
        this->useDefaultBrush = false;
        break;
    case FONT_GRAPHICS_OBJECT:
        this->selectedFont = this->graphicsObjects.getObjectByHandle(static_cast<GraphicsObjectHandle>(record.getObjectIndex())).dynamicCast<GraphicsObjectFont>();
        this->useDefaultFont = false;
        break;
    case PALETTE_GRAPHICS_OBJECT:
        this->selectedPalette = this->graphicsObjects.getObjectByHandle(static_cast<GraphicsObjectHandle>(record.getObjectIndex())).dynamicCast<GraphicsObjectPalette>();
        this->useDefaultPalette = false;
        break;
    case PEN_GRAPHICS_OBJECT:
        this->selectedPen = this->graphicsObjects.getObjectByHandle(static_cast<GraphicsObjectHandle>(record.getObjectIndex())).dynamicCast<GraphicsObjectPen>();
        this->useDefaultPen = false;
        break;
    case REGION_GRAPHICS_OBJECT:
        this->selectedRegion = this->graphicsObjects.getObjectByHandle(static_cast<GraphicsObjectHandle>(record.getObjectIndex())).dynamicCast<GraphicsObjectRegion>();
        this->useDefaultRegion = false;
        break;
    default:
        throw std::runtime_error("Empty graphics object");
    }
}

void DeviceContext::DeleteObject(const MetaDeleteobjectRecord &record)
{
    GraphicsObjectType objectType = this->graphicsObjects.getObjectByHandle(static_cast<GraphicsObjectHandle>(record.getObjectIndex()))->getType();
    this->graphicsObjects.removeObject(static_cast<GraphicsObjectHandle>(record.getObjectIndex()));
}

void DeviceContext::MoveTo(const MetaMovetoRecord &record)
{
    this->currentPoint.setX(this->pageToDeviceX(static_cast<qreal>(record.getPoint().x())));
    this->currentPoint.setY(this->pageToDeviceY(static_cast<qreal>(record.getPoint().y())));
}

void DeviceContext::LineTo(const MetaLinetoRecord &record, QPainter &painter)
{
    painter.setPen(this->getSelectedPen());
    qreal lineToX = this->pageToDeviceX(static_cast<qreal>(record.getPoint().x()));
    qreal lineToY = this->pageToDeviceY(static_cast<qreal>(record.getPoint().y()));
    painter.drawLine(this->currentPoint, QPointF(lineToX, lineToY));
}

void DeviceContext::SetBkColor(const MetaSetbkcolorRecord &record, QPainter &painter)
{
    painter.setBackground(QBrush(QColor(record.getColor()), Qt::SolidPattern));
}

void DeviceContext::SetBkMode(const MetaSetbkmodeRecord &record, QPainter &painter)
{
    switch(record.getBkMode())
    {
    case TRANSPARENT:
        painter.setBackgroundMode(Qt::TransparentMode);
        break;
    case OPAQUE:
        painter.setBackgroundMode(Qt::OpaqueMode);
        break;
    default:
        painter.setBackgroundMode(Qt::OpaqueMode);
    }
}

void DeviceContext::Rectangle(const MetaRectangleRecord &record, QPainter &painter)
{
    painter.setPen(this->getSelectedPen());
    painter.setBrush(this->getSelectedBrush());
    painter.drawRect(QRectF(QPointF(this->pageToDeviceX(static_cast<qreal>(record.getRect().left())), this->pageToDeviceY(static_cast<qreal>(record.getRect().top()))), QPointF(this->pageToDeviceX(static_cast<qreal>(record.getRect().right())), this->pageToDeviceY(static_cast<qreal>(record.getRect().bottom())))));
}

void DeviceContext::Ellipse(const MetaEllipseRecord &record, QPainter &painter)
{
    painter.setPen(this->getSelectedPen());
    painter.setBrush(this->getSelectedBrush());
    painter.drawEllipse(QRectF(QPointF(this->pageToDeviceX(static_cast<qreal>(record.getRect().left())), this->pageToDeviceY(static_cast<qreal>(record.getRect().top()))), QPointF(this->pageToDeviceX(static_cast<qreal>(record.getRect().right())), this->pageToDeviceY(static_cast<qreal>(record.getRect().bottom())))));
}

void DeviceContext::RoundRect(const MetaRoundrectRecord &record, QPainter &painter)
{
    painter.setPen(this->getSelectedPen());
    painter.setBrush(this->getSelectedBrush());
    painter.drawRoundedRect(QRectF(QPointF(this->pageToDeviceX(static_cast<qreal>(record.getRect().left())), this->pageToDeviceY(static_cast<qreal>(record.getRect().top()))), QPointF(this->pageToDeviceX(static_cast<qreal>(record.getRect().right())), this->pageToDeviceY(static_cast<qreal>(record.getRect().bottom())))), this->pageToDeviceRescaleX(static_cast<qreal>(record.getWidth())), this->pageToDeviceRescaleY(static_cast<qreal>(record.getHeight())), Qt::AbsoluteSize);
}

qreal DeviceContext::pageToDeviceX(qreal x) const
{
    return ((x - windowOriginX) * (viewportExtentX / windowExtentX)) + viewportOriginX;
}

qreal DeviceContext::pageToDeviceY(qreal y) const
{
    return ((y - windowOriginY) * (viewportExtentY / windowExtentY)) + viewportOriginY;
}

qreal DeviceContext::pageToDeviceRescaleX(qreal x) const
{
    return (x * (viewportExtentX / windowExtentX));
}

qreal DeviceContext::pageToDeviceRescaleY(qreal y) const
{
    return (y * (viewportExtentY / windowExtentY));
}

QBrush DeviceContext::getSelectedBrush() const
{
    if(this->useDefaultBrush)
    {
        return QBrush();
    }
    if(this->selectedBrush->isPaletteRequired())
    {
        if(this->useDefaultPalette)
        {
            throw std::runtime_error("Brush requires palette");
        }
        return this->selectedBrush->getBrush(this->selectedPalette->getPalette());
    }
    else
    {
        return this->selectedBrush->getBrush();
    }
}

QFont DeviceContext::getSelectedFont() const
{
    if(this->useDefaultFont)
    {
        return QFont();
    }
    qreal pointsInUnit = viewportExtentY / windowExtentY;
    return this->selectedFont->getFont(pointsInUnit);
}

QPen DeviceContext::getSelectedPen() const
{
    if(this->useDefaultPen)
    {
        return QPen();
    }
    qreal pixelInUnitHor = viewportExtentX / windowExtentX;
    return this->selectedPen->getPen(pixelInUnitHor);
}

PaletteObject DeviceContext::getSelectedPalette() const
{
    if(this->useDefaultPalette)
    {
        return PaletteObject();
    }
    return this->selectedPalette->getPalette();
}

QRegion DeviceContext::getSelectedRegion() const
{
    if(this->useDefaultRegion)
    {
        return QRegion();
    }
    qreal pixelInUnitHor = viewportExtentX / windowExtentX;
    qreal pixelInUnitVert = viewportExtentY / windowExtentY;
    return this->selectedRegion->getRegion(pixelInUnitHor, pixelInUnitVert);
}
