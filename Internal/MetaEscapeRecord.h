/* META_ESCAPE record definition.

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

#ifndef METAESCAPERECORD_H
#define METAESCAPERECORD_H

#include <QtGlobal>
#include <QIODevice>

#include "MetafileRecord.h"

enum MetafileEscapes : quint16
{
    //Закончилась страница
    NEWFRAME = 0x0001,
    //Завершение обработки документа
    ABORTDOC = 0x0002,
    //Закончилась полоса
    NEXTBAND = 0x0003,
    //Устанавливает таблицу цветов
    SETCOLORTABLE = 0x0004,
    //Получает таблицу цветов
    GETCOLORTABLE = 0x0005,
    //Сброс вывода на устройство
    FLUSHOUT = 0x0006,
    //Черновой режим
    DRAFTMODE = 0x0007,
    //Поддерживается ли заданная функция
    QUERYESCSUPPORT = 0x0008,
    //Задает функцию, позволяющую прервать вывод
    SETABORTPROC = 0x0009,
    //Начало нового задания
    STARTDOC = 0x000A,
    //Конец задания
    ENDDOC = 0x000B,
    //Получает физический размер страницы
    GETPHYSPAGESIZE = 0x000C,
    //Получает смещение вывода от левого верхнего угла страницы
    GETPRINTINGOFFSET = 0x000D,
    //Получает масштабные коэффициенты по осям абсцисс и ординат
    GETSCALINGFACTOR = 0x000E,
    //Внедренный EMF-файл
    META_ESCAPE_ENHANCED_METAFILE = 0x000F,
    //Задает ширину пера в пикселах
    SETPENWIDTH = 0x0010,
    //Задает количество копий
    SETCOPYCOUNT = 0x0011,
    //Задает источник бумаги
    SETPAPERSOURCE = 0x0012,
    //Передает произвольные данные
    PASSTHROUGH = 0x0013,
    //Получает сведения о графической технолгии поддерживаемой устройством
    GETTECHNOLOGY = 0x0014,
    //Задает режим рисования линий
    SETLINECAP = 0x0015,
    //Задает режим соединения линий
    SETLINEJOIN = 0x0016,
    //Задает предельную длину угловых стыков
    SETMITERLIMIT = 0x0017,
    //Получает сведения о разбиении на полосы
    BANDINFO = 0x0018,
    //Выводит прямоугольник с заданным шаблоном
    DRAWPATTERNRECT = 0x0019,
    //Получает размер пера
    GETVECTORPENSIZE = 0x001A,
    //Получает размер кисти
    GETVECTORBRUSHSIZE = 0x001B,
    //Включает двухсторонний вывод
    ENABLEDUPLEX = 0x001C,
    //Получает или задает источник бумаги
    GETSETPAPERBINS = 0x001D,
    //Получает или задает ориентацию бумаги
    GETSETPRINTORIENT = 0x001E,
    //Получает список источников бумаги
    ENUMPAPERBINS = 0x001F,
    //Задает масштабирование независимых от устройства битмапов
    SETDIBSCALING = 0x0020,
    //Задает начало и конец EPS-секции
    EPSPRINTING = 0x0021,
    //Получает список размеров бумаги
    ENUMPAPERMETRICS = 0x0022,
    //Получает или задает размер бумаги
    GETSETPAPERMETRICS = 0x0023,
    //Отсылает данные PostScript данные
    POSTSCRIPT_DATA = 0x0025,
    //Игнорировать данные PostScript
    POSTSCRIPT_IGNORE = 0x0026,
    //Получает единицы измерения
    GETDEVICEUNITS = 0x002A,
    //Получает расширенные метрики текста
    GETEXTENDEDTEXTMETRICS = 0x0100,
    //Получает таблицу кернинга шрифта
    GETPAIRKERNTABLE = 0x0102,
    //Выводит текст с заданными параметрами
    EXTTEXTOUT = 0x0200,
    //Получает имя шрифта
    GETFACENAME = 0x0201,
    //Задает имя шрифта
    DOWNLOADFACE = 0x0202,
    //Определяют, поддерживаются ли метафайлы драйвером устройства
    METAFILE_DRIVER = 0x0801,
    //Определяют, поддерживаются ли драйвером устройства независимые от устройства битмапы
    QUERYDIBSUPPORT = 0x0C01,
    //Начать путь
    BEGIN_PATH = 0x1000,
    //Задает регион отсечения, ограниченный путем
    CLIP_TO_PATH = 0x1001,
    //Завершить путь
    END_PATH = 0x1002,
    //Начать пустое задание
    OPEN_CHANNEL = 0x100E,
    //Загрузить набор процедур PostScript
    DOWNLOADHEADER = 0x100F,
    //Завершить пустое задание
    CLOSE_CHANNEL = 0x1010,
    //Пересылка произвольных данных в режиме PostScript
    POSTSCRIPT_PASSTHROUGH = 0x1013,
    //Пересылка произвольных данных
    ENCAPSULATED_POSTSCRIPT = 0x1014,
    //Переключение между режимами PostScript и GDI
    POSTSCRIPT_IDENTIFY = 0x1015,
    //Вставляет блок данных в поток PostScript
    POSTSCRIPT_INJECTION = 0x1016,
    //Проверка, поддерживается ли формат JPEG
    CHECKJPEGFORMAT = 0x1017,
    //Проверка, поддерживается ли формат PNG
    CHECKPNGFORMAT = 0x1018,
    //Получает значение параметра PostScript
    GET_PS_FEATURESETTING = 0x1019,
    //Вывод в файл или в формат XPS
    MXDC_ESCAPE = 0x101A,
    //Включение в документ приватных процедур и прочих данных произвольного типа
    SPCLPASSTHROUGH2 = 0x11D8
};

class MetaEscapeRecord : public MetafileRecord
{
private:
    quint16 escapeFunction;
    quint16 byteCount;
public:
    MetaEscapeRecord();
    MetaEscapeRecord(quint16 escapeFunction, quint16 byteCount);
    MetaEscapeRecord(QIODevice &device);
    MetaEscapeRecord(const MetaEscapeRecord &rhs);
    virtual ~MetaEscapeRecord();
    MetaEscapeRecord &operator=(const MetaEscapeRecord &rhs);
    quint16 getEscapeFunction() const;
    quint16 getByteCount() const;
};

#endif // METAESCAPERECORD_H
