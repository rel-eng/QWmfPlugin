/* Metafile record definition.

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

#ifndef METAFILERECORD_H
#define METAFILERECORD_H

#include <QtGlobal>
#include <QIODevice>

enum RecordType : quint16
{
    //Конец файла
    META_EOF = 0x0000,
    //Отображает записи из логической палитры в системную
    META_REALIZEPALETTE = 0x0035,
    //Задает значения цветов в логической палитре
    META_SETPALENTRIES = 0x0037,
    //Задает режим смешения растровой операции заднего плана
    META_SETBKMODE = 0x0102,
    //Задает режим отображения
    META_SETMAPMODE = 0x0103,
    //Задает режим смешения растровой операции переднего плана
    META_SETROP2 = 0x0104,
    //Не определена, игнорируем
    META_SETRELABS = 0x0105,
    //Задает режим заливки полигона
    META_SETPOLYFILLMODE = 0x0106,
    //Задает режим масштабирования битмапа
    META_SETSTRETCHBLTMODE = 0x0107,
    //Задает межбуквенный интервал для выключки текста
    META_SETTEXTCHAREXTRA = 0x0108,
    //Восстанавливает сохраненный контекст устройства
    META_RESTOREDC = 0x0127,
    //Изменяет размер логической палитры
    META_RESIZEPALETTE = 0x0139,
    //Создает кисть из битмапа
    META_DIBCREATEPATTERNBRUSH = 0x0142,
    //Задает ориентацию макета
    META_SETLAYOUT = 0x0149,
    //Задает цвет заднего плана
    META_SETBKCOLOR = 0x0201,
    //Задает цвет текста
    META_SETTEXTCOLOR = 0x0209,
    //Перемещает начало координат окна просмотра
    META_OFFSETVIEWPORTORG = 0x0211,
    //Рисует линию
    META_LINETO = 0x0213,
    //Устанавливает позицию вывода
    META_MOVETO = 0x0214,
    //Перемещает регион отсечения
    META_OFFSETCLIPRGN = 0x0220,
    //Заливает регион
    META_FILLREGION = 0x0228,
    //Задает алгоритм используемый при отображении шрифтов
    META_SETMAPPERFLAGS = 0x0231,
    //Задает логическую палитру
    META_SELECTPALETTE = 0x0234,
    //Рисует полигон
    META_POLYGON = 0x0324,
    //Рисует последовательность отрезков ломаной линии
    META_POLYLINE = 0x0325,
    //Задает значение интервала для выключки текста
    META_SETTEXTJUSTIFICATION = 0x020A,
    //Задает начало координат окна вывода
    META_SETWINDOWORG = 0x020B,
    //Задает оси окна вывода
    META_SETWINDOWEXT = 0x020C,
    //Задает начало координат окна просмотра
    META_SETVIEWPORTORG = 0x020D,
    //Задает оси окна просмотра
    META_SETVIEWPORTEXT = 0x020E,
    //Перемещает начало координат окна вывода
    META_OFFSETWINDOWORG = 0x020F,
    //Масштабирует оси окна вывода
    META_SCALEWINDOWEXT = 0x0410,
    //Масштабирует оси окна просмотра
    META_SCALEVIEWPORTEXT = 0x0412,
    //Вычитает заданный прямоугольник из региона отсечения
    META_EXCLUDECLIPRECT = 0x0415,
    //Устанавливает регион отсечения равным пересечению текущего региона отсечения с заданным прямоугольником
    META_INTERSECTCLIPRECT = 0x0416,
    //Задает эллипс
    META_ELLIPSE = 0x0418,
    //Заливка
    META_FLOODFILL = 0x0419,
    //Задает границу региона
    META_FRAMEREGION = 0x0429,
    //Переопределяет записи логической палитры
    META_ANIMATEPALETTE = 0x0436,
    //Выводит строку символов
    META_TEXTOUT = 0x0521,
    //Рисует последовательность полигонов
    META_POLYPOLYGON = 0x0538,
    //Заливка
    META_EXTFLOODFILL = 0x0548,
    //Рисует прямоугольник
    META_RECTANGLE = 0x041B,
    //Устанавливает цвет пиксела
    META_SETPIXEL = 0x041F,
    //Рисует прямоугольник со скругленными углами
    META_ROUNDRECT = 0x061C,
    //Рисует прямоугольник, использую растровую операцию
    META_PATBLT = 0x061D,
    //Сохраняет контекст устройства
    META_SAVEDC = 0x001E,
    //Рисует сектор
    META_PIE = 0x081A,
    //Задает перенос блока пикселов в соответствии с растровой операцией, при этом возможно растяжение или сжатие
    META_STRETCHBLT = 0x0B23,
    //Предоставляет доступ к возмостям печатающего устройства
    META_ESCAPE = 0x0626,
    //Инвертирует цвета в заданном регионе
    META_INVERTREGION = 0x012A,
    //Рисует указанный регион
    META_PAINTREGION = 0x012B,
    //Задает регион отсечения
    META_SELECTCLIPREGION = 0x012C,
    //Выбирает графический объект
    META_SELECTOBJECT = 0x012D,
    //Задает режим выравнивания текста
    META_SETTEXTALIGN = 0x012E,
    //Рисует дугу эллипса
    META_ARC = 0x0817,
    //Рисует хорду
    META_CHORD = 0x0830,
    //Задает перенос блока пикселов в соответствии с растровой операцией
    META_BITBLT = 0x0922,
    //Выводит строку символов
    META_EXTTEXTOUT = 0x0A32,
    //Выводит блок пикселов
    META_SETDIBTODEV = 0x0D33,
    //Задает перенос блока пикселов в соответствии с растровой операцией
    META_DIBBITBLT = 0x0940,
    //Задает перенос блока пикселов в соответствии с растровой операцией, при этом возможно растяжение или сжатие
    META_DIBSTRETCHBLT = 0x0B41,
    //Задает перенос блока пикселов в соответствии с растровой операцией, при этом возможно растяжение или сжатие
    META_STRETCHDIB = 0x0F43,
    //Удаляет графический объект
    META_DELETEOBJECT = 0x01F0,
    //Задает логическую палитру
    META_CREATEPALETTE = 0x00F7,
    //Создает кисть из битмапа
    META_CREATEPATTERNBRUSH = 0x01F9,
    //Создает перо
    META_CREATEPENINDIRECT = 0x02FA,
    //Создает шрифт
    META_CREATEFONTINDIRECT = 0x02FB,
    //Создает кисть
    META_CREATEBRUSHINDIRECT = 0x02FC,
    //Создает регион
    META_CREATEREGION = 0x06FF
};

class MetafileRecord
{
private:
    //Размер записи в 16-битных словах
    quint32 recordSizeInWords;
    //Тип записи
    quint16 recordFunction;
public:
    MetafileRecord();
    MetafileRecord(quint32 recordSizeInWords, quint16 recordFunction);
    MetafileRecord(QIODevice &device);
    MetafileRecord(const MetafileRecord &rhs);
    virtual ~MetafileRecord();
    MetafileRecord &operator=(const MetafileRecord &rhs);
    quint32 getRecordSizeInWords() const;
    quint16 getRecordFunction() const;
};

#endif // METAFILERECORD_H
