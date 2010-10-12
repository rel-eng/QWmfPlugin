/* Font object definition.

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

#ifndef FONTOBJECT_H
#define FONTOBJECT_H

#include <QtGlobal>
#include <QIODevice>
#include <QTextCodec>
#include <QString>

enum PitchFont : quint8
{
    //По-умолчанию
    DEFAULT_PITCH = 0x00,
    //Фиксированная ширина символа
    FIXED_PITCH = 0x01,
    //Переменная ширина символа
    VARIABLE_PITCH = 0x02
};

enum FamilyFont : quint8
{
    //По-умолчанию
    FF_DONTCARE = 0x00,
    //Serif
    FF_ROMAN = 0x01,
    //Sans-Serif
    FF_SWISS = 0x02,
    //Monospace
    FF_MODERN = 0x03,
    //Cursive
    FF_SCRIPT = 0x04,
    //Fantasy
    FF_DECORATIVE = 0x05
};

enum FontCharset : quint32
{
    //Английский
    ANSI_CHARSET = 0x00000000,
    //По-умолчанию
    DEFAULT_CHARSET = 0x00000001,
    //Символы
    SYMBOL_CHARSET = 0x00000002,
    //Японский
    SHIFTJIS_CHARSET = 0x00000080,
    //Корейский
    HANGUL_CHARSET = 0x00000081,
    //Китайский
    GB2312_CHARSET = 0x00000086,
    //Китайский
    CHINESEBIG5_CHARSET = 0x00000088,
    //OEM набор символов
    OEM_CHARSET = 0x000000FF,
    //Корейский
    JOHAB_CHARSET = 0x00000082,
    //Иврит
    HEBREW_CHARSET = 0x000000B1,
    //Арабский
    ARABIC_CHARSET = 0x000000B2,
    //Греческий
    GREEK_CHARSET = 0x000000A1,
    //Турецкий
    TURKISH_CHARSET = 0x000000A2,
    //Вьетнамский
    VIETNAMESE_CHARSET = 0x000000A3,
    //Тайский
    THAI_CHARSET = 0x000000DE,
    //Восточно-европейский набор символов
    EASTEUROPE_CHARSET = 0x000000EE,
    //Русский
    RUSSIAN_CHARSET = 0x000000CC,
    //Макинтош
    MAC_CHARSET = 0x0000004D,
    //Балтийский набор символов
    BALTIC_CHARSET = 0x000000BA
};

enum OutPrecision : quint32
{
    //По-умолчанию
    OUT_DEFAULT_PRECIS = 0x00000000,
    //Растровые шрифты
    OUT_STRING_PRECIS = 0x00000001,
    //TrueType, контурные и векторные шрифты
    OUT_STROKE_PRECIS = 0x00000003,
    //TrueType шрифты
    OUT_TT_PRECIS = 0x00000004,
    //Шрифты устройства
    OUT_DEVICE_PRECIS = 0x00000005,
    //Растровые шрифты
    OUT_RASTER_PRECIS = 0x00000006,
    //Только TueType шрифты
    OUT_TT_ONLY_PRECIS = 0x00000007,
    //TueType, контурные шрифты
    OUT_OUTLINE_PRECIS = 0x00000008,
    //TueType, контурные шрифты
    OUT_SCREEN_OUTLINE_PRECIS = 0x00000009,
    //Только PostScript шрифты
    OUT_PS_ONLY_PRECIS = 0x0000000A
};

enum ClipPrecision : quint32
{
    //По-умолчанию
    CLIP_DEFAULT_PRECIS = 0x00000000,
    //Не используется
    CLIP_CHARACTER_PRECIS = 0x00000001,
    //Растровые, TrueType и векторные шрифты
    CLIP_STROKE_PRECIS = 0x00000002,
    //Вращение всех шрифтов определяется ориентацией системы координат, иначе шрифты устройства нужно вращать всегда против часовой стрелки
    CLIP_LH_ANGLES = 0x00000010,
    //Не используется
    CLIP_TT_ALWAYS = 0x00000020,
    //Отключает ассоциирование шрифтов (ассоциирование шрифтов означает, что отсутствующие в шрифте символы берутся из ассоциированного шрифта)
    CLIP_DFA_DISABLE = 0x00000040,
    //Включает внедрение шрифтов
    CLIP_EMBEDDED = 0x00000080
};

enum FontQuality : quint8
{
    //Качество шрифта не имеет значения
    DEFAULT_QUALITY = 0x00,
    //Соответствие размерам важнее качества символов, используется масштабирование растровых шрифтов
    DRAFT_QUALITY = 0x01,
    //Качество символов важнее соответствия размерам, масштабирование растровых шрифтов отключено
    PROOF_QUALITY = 0x02,
    //Сглаживание отключено
    NONANTIALIASED_QUALITY = 0x03,
    //Сглаживание включено
    ANTIALIASED_QUALITY = 0x04,
    //Используется ClearType
    CLEARTYPE_QUALITY = 0x05
};

class FontObject
{
private:
    //Высота знакоместа в логических единицах
    qint16 height;
    //Средняя ширина символов в логических единицах
    qint16 width;
    //Наклон строки текста, в десятых долях градуса
    qint16 escapement;
    //Ориентация символа, в десятых долях градуса
    qint16 orientation;
    //Толщина шрифта, от 0 до 1000
    qint16 weight;
    //Курсив
    bool italic;
    //Подчеркивание
    bool underline;
    //Перечеркивание
    bool strikeOut;
    //Набор символов
    quint8 charset;
    //Точность вывода
    quint8 outPrecision;
    //Точность отсечения
    quint8 clipPrecision;
    //Качество
    quint8 quality;
    //Ширина смвола
    quint8 pitch;
    //Семейство шрифтов
    quint8 family;
    //Имя шрифта
    QString faceName;
    //Размер объекта в 16-битных словах
    quint32 sizeInWords;
public:
    FontObject();
    FontObject(qint16 height, qint16 width, qint16 escapement, qint16 orientation, qint16 weight, bool italic, bool underline, bool strikeOut, quint8 charset, quint8 outPrecision, quint8 clipPrecision, quint8 quality, quint8 pitch, quint8 family, const QString &faceName);
    FontObject(QIODevice &device);
    FontObject(const FontObject &rhs);
    virtual ~FontObject();
    FontObject &operator=(const FontObject &rhs);
    qint16 getHeight() const;
    qint16 getWidth() const;
    qint16 getEscapement() const;
    qint16 getOrientation() const;
    qint16 getWeight() const;
    bool isItalic() const;
    bool isUnderline() const;
    bool isStrikeOut() const;
    QTextCodec *getTextCodec() const;
    quint8 getOutPrecision() const;
    quint8 getClipPrecision() const;
    quint8 getQuality() const;
    quint8 getPitch() const;
    quint8 getFamily() const;
    QString getFaceName() const;
    quint32 getSizeInWords() const;
};

#endif // FONTOBJECT_H
