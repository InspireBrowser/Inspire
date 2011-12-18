/*
 * InspireBrowser is an open source browser for Kiosk and STB style
 * applications, providing a JS library for easily including multimedia
 * content.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * Filename: GenericLayout.h
 * Class: GenericLayout
 * Description: A UI layout class that manages 1 maximised component and
 *              multiple floating components
 */
#ifndef GENERICLAYOUT_H
#define GENERICLAYOUT_H

#include <QLayout>

/*! @brief A layout class for managing 1 maximised component and multiple floating components
 *         A layout class that has 1 component that is always maximised to fill the whole of the
 *         parent widget and a number of other components that position is manually set.
 */
class GenericLayout : public QLayout
{
    Q_OBJECT

private:
    /*! @brief The list of items to be laid out in the widget */
    QList<QLayoutItem*> list;

public:
    /*! @brief Constructs a new top-level QLayout, with parent parent. parent may not be 0.
     *         There can be only one top-level layout for a widget. It is returned by QWidget::layout().
     */
    GenericLayout(QWidget* parent = 0);

    /*! @brief Returns the number of items currently in the layout
     *  @return The number of items currently in the layout
     */
    int count() const;

    /*! @brief Returns the layout item at the specified index
     *  @param index The index to return the item from
     *  @return The item at the specified index
     */
    QLayoutItem* itemAt(int index) const;

    /*! @brief Removes and returns the layout item at the specified index
     *  @param index The index to remove and return the item from
     *  @return The item at the specified index
     */
    QLayoutItem* takeAt(int index);

    /*! @brief Adds a layout item to the layout
     *         This function is not usually called in application code. To add a widget to a layout, use
     *         the addWidget() function; to add a child layout, use the addLayout() function provided by
     *         the relevant QLayout subclass.
     */
    void addItem(QLayoutItem* item);

    /*! @brief Sets the geometry for the Layout and resizes and positions the first widget
     *  @param rect The bounds of the new geometry
     */
    void setGeometry(const QRect& rect);

    /*! @brief Returns the size hint for the layout
     *         Just returns the size hint for the first component if there is one
     *  @return The size hint of the first component
     */
    QSize sizeHint() const;

    /*! @brief Returns the minimum size for the layout
     *         Just returns the minimum size for the first component if there is one
     *  @return The minimum size of the first component
     */
    QSize minimumSize() const;

signals:

public slots:

};

#endif // GENERICLAYOUT_H
