/*
 * InspireBrowser is an open source browser for Kiosk and STB style 
 * applications, providing a JS library for easily including multimedia
 * content.
 *
 * Copyright (C) 2010  mike
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Filename: %FILENAME%
 * Class: %CLASS%
 * Description: <insert description here>
 * Created: 28/12/2010
 * ChangeLog:
 *     28/12/2010 - mike - Initial Creation
 */

#include "GenericLayout.h"

/*! @brief Constructs a new top-level QLayout, with parent parent. parent may not be 0.
 *         There can be only one top-level layout for a widget. It is returned by QWidget::layout().
 */
GenericLayout::GenericLayout(QWidget* parent) :
    QLayout(parent)
{
}

/*! @brief Returns the number of items currently in the layout
 *  @return The number of items currently in the layout
 */
int GenericLayout::count() const
{
    // QList::size() returns the number of QLayoutItems in the list
    return list.size();
}

/*! @brief Returns the layout item at the specified index
 *  @param index The index to return the item from
 *  @return The item at the specified index
 */
QLayoutItem* GenericLayout::itemAt(int index) const
{
    // QList::value() performs index checking, and returns 0 if we are
    // outside the valid range
    return list.value(index);
}

/*! @brief Removes and returns the layout item at the specified index
 *  @param index The index to remove and return the item from
 *  @return The item at the specified index
 */
QLayoutItem* GenericLayout::takeAt(int index)
{
    // QList::take does not do index checking
    return index >= 0 && index < list.size() ? list.takeAt(index) : 0;
}

/*! @brief Adds a layout item to the layout
 *         This function is not usually called in application code. To add a widget to a layout, use
 *         the addWidget() function; to add a child layout, use the addLayout() function provided by
 *         the relevant QLayout subclass.
 */
void GenericLayout::addItem(QLayoutItem *item)
{
    list.append(item);
}

/*! @brief Sets the geometry for the Layout and resizes and positions the first widget
 *  @param rect The bounds of the new geometry
 */
void GenericLayout::setGeometry(const QRect &rect)
{
    QLayout::setGeometry(rect);

    if(count() > 0)
        list[0]->setGeometry(rect);
}

/*! @brief Returns the size hint for the layout
 *         Just returns the size hint for the first component if there is one
 *  @return The size hint of the first component
 */
QSize GenericLayout::sizeHint() const
{
    if(count() > 0)
        return list[0]->sizeHint();
    else
        return QSize();
}

/*! @brief Returns the minimum size for the layout
 *         Just returns the minimum size for the first component if there is one
 *  @return The minimum size of the first component
 */
QSize GenericLayout::minimumSize() const
{
    if(count() > 0)
        return list[0]->minimumSize();
    else
        return QSize();
}
