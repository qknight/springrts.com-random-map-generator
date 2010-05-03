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

#include "GraphicsItemModelExtension.h"
#include "GraphicsScene.h"
#include "Model.h"

GraphicsItemModelExtension::GraphicsItemModelExtension(Model* model, QPersistentModelIndex index) {
  this->model=model;
  m_index = index;
}

QVariant GraphicsItemModelExtension::modelData(int role ) const {
  return model->data( m_index, role );
}

bool GraphicsItemModelExtension::setModelData( const QVariant & value, int role ) {
  return model->setData( m_index, value, role );
}

QPersistentModelIndex GraphicsItemModelExtension::index() {
//   qDebug() << m_index;
  return m_index;
}
