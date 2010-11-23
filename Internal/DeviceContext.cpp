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

#include <QSharedPointer>

#include "GraphicsObject.h"
#include "GraphicsObjectBrush.h"
#include "GraphicsObjectFont.h"
#include "GraphicsObjectPen.h"
#include "GraphicsObjectPalette.h"
#include "GraphicsObjectRegion.h"

DeviceContext::DeviceContext(size_t numberOfObjects) : graphicsObjects(numberOfObjects), windowOriginX(0.0), windowOriginY(0.0), windowExtentX(1.0), windowExtentY(1.0), viewportOriginX(0.0), viewportOriginY(0.0), viewportExtentX(1.0), viewportExtentY(1.0), mappingMode(MM_ANISOTROPIC)
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
        this->viewportExtentX = 1.0;
        this->viewportExtentY = 1.0;
        this->windowExtentX = 1.0;
        this->windowExtentY = -1.0;
        break;
    //Произвольные масштабные коэффициенты для осей абсцисс и ординат
    case MM_ANISOTROPIC:
        this->viewportExtentX = 1.0;
        this->viewportExtentY = 1.0;
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

qreal DeviceContext::pageToDeviceX(qreal x) const
{
    return ((x - windowOriginX) * viewportExtentX / windowExtentX) + viewportOriginX;
}

qreal DeviceContext::pageToDeviceY(qreal y) const
{
    return ((y - windowOriginY) * viewportExtentY / windowExtentY) + viewportOriginY;
}
