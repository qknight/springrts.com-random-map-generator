/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) <year>  <name of author>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef GRAPHICSITEMMODELEXTENSION_H
#define GRAPHICSITEMMODELEXTENSION_H

#include <QPersistentModelIndex>
#include <QGraphicsScene>
#include "Model.h"

/*!
 * and this is a central place for all items to query the model for data/setData
 */
class GraphicsItemModelExtension {
  public:
    GraphicsItemModelExtension(Model* model);
  protected:
    /*! a wrapper function for all items in the scene, so that they can call data() directly */
    QVariant modelData( const QModelIndex &index, int role ) const;
    /*! a wrapper function for all items in the scene, so that they can call setData() directly */
    bool setModelData( const QModelIndex & index, const QVariant & value, int role = Qt::EditRole );
  private:
    Model* model;
};

#endif // GRAPHICSITEMMODELEXTENSION_H
