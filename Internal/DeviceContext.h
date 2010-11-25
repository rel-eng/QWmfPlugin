/* DeviceContext definition.

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

#ifndef DEVICECONTEXT_H
#define DEVICECONTEXT_H

#include <QtGlobal>
#include <QPointF>
#include <QPainter>
#include <QSharedPointer>

#include <cstddef>

#include "ObjectTable.h"
#include "MetaPlaceableRecord.h"
#include "MetaCreatebrushindirectRecord.h"
#include "MetaCreatepatternbrushRecord.h"
#include "MetaDibcreatepatternbrushRecord.h"
#include "MetaCreatefontindirectRecord.h"
#include "MetaCreatepenindirectRecord.h"
#include "MetaCreatepaletteRecord.h"
#include "MetaCreateregionRecord.h"
#include "MetaSetviewportorgRecord.h"
#include "MetaSetviewportextRecord.h"
#include "MetaSetwindoworgRecord.h"
#include "MetaSetwindowextRecord.h"
#include "MetaSetmapmodeRecord.h"
#include "MetaOffsetviewportorgRecord.h"
#include "MetaOffsetwindoworgRecord.h"
#include "MetaScaleviewportextRecord.h"
#include "MetaScalewindowextRecord.h"
#include "MetaSelectobjectRecord.h"
#include "MetaDeleteobjectRecord.h"
#include "MetaMovetoRecord.h"
#include "MetaLinetoRecord.h"
#include "MetaSetbkcolorRecord.h"
#include "MetaSetbkmodeRecord.h"
#include "MetaRectangleRecord.h"
#include "MetaEllipseRecord.h"
#include "GraphicsObject.h"
#include "GraphicsObjectBrush.h"
#include "GraphicsObjectFont.h"
#include "GraphicsObjectPalette.h"
#include "GraphicsObjectPen.h"
#include "GraphicsObjectRegion.h"

class DeviceContext
{
private:
    Q_DISABLE_COPY(DeviceContext)
    ObjectTable graphicsObjects;
    MetaPlaceableRecord placeableHeader;
    qreal windowOriginX;
    qreal windowOriginY;
    qreal windowExtentX;
    qreal windowExtentY;
    qreal viewportOriginX;
    qreal viewportOriginY;
    qreal viewportExtentX;
    qreal viewportExtentY;
    quint16 mappingMode;
    QSharedPointer<GraphicsObjectBrush> selectedBrush;
    QSharedPointer<GraphicsObjectFont> selectedFont;
    QSharedPointer<GraphicsObjectPen> selectedPen;
    QSharedPointer<GraphicsObjectPalette> selectedPalette;
    QSharedPointer<GraphicsObjectRegion> selectedRegion;
    bool useDefaultBrush;
    bool useDefaultFont;
    bool useDefaultPen;
    bool useDefaultPalette;
    bool useDefaultRegion;
    QPointF currentPoint;
public:
    DeviceContext(size_t numberOfObjects, const MetaPlaceableRecord &placeableHeader);
    virtual ~DeviceContext();
    void CreateBrushIndirect(const MetaCreatebrushindirectRecord &record);
    void CreatePatternBrush(const MetaCreatepatternbrushRecord &record);
    void DibCreatePatternBrush(const MetaDibcreatepatternbrushRecord &record);
    void CreateFontIndirect(const MetaCreatefontindirectRecord &record);
    void CreatePenIndirect(const MetaCreatepenindirectRecord &record);
    void CreatePalette(const MetaCreatepaletteRecord &record);
    void CreateRegion(const MetaCreateregionRecord &record);
    void SetViewportOrg(const MetaSetviewportorgRecord &record);
    void SetViewportExt(const MetaSetviewportextRecord &record);
    void SetWindowOrg(const MetaSetwindoworgRecord &record);
    void SetWindowExt(const MetaSetwindowextRecord &record);
    void SetMapMode(const MetaSetmapmodeRecord &record);
    void OffsetViewportOrg(const MetaOffsetviewportorgRecord &record);
    void OffsetWindowOrg(const MetaOffsetwindoworgRecord &record);
    void ScaleViewportExt(const MetaScaleviewportextRecord &record);
    void ScaleWindowExt(const MetaScalewindowextRecord &record);
    void SelectObject(const MetaSelectobjectRecord &record);
    void DeleteObject(const MetaDeleteobjectRecord &record);
    void MoveTo(const MetaMovetoRecord &record);
    void LineTo(const MetaLinetoRecord &record, QPainter &painter);
    void SetBkColor(const MetaSetbkcolorRecord &record, QPainter &painter);
    void SetBkMode(const MetaSetbkmodeRecord &record, QPainter &painter);
    void Rectangle(const MetaRectangleRecord &record, QPainter &painter);
    void Ellipse(const MetaEllipseRecord &record, QPainter &painter);
    qreal pageToDeviceX(qreal x) const;
    qreal pageToDeviceY(qreal y) const;
    qreal pageToDeviceRescaleX(qreal x) const;
    qreal pageToDeviceRescaleY(qreal y) const;
    QBrush getSelectedBrush() const;
    QFont getSelectedFont() const;
    QPen getSelectedPen() const;
    PaletteObject getSelectedPalette() const;
    QRegion getSelectedRegion() const;
};

#endif // DEVICECONTEXT_H
