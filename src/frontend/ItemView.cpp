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

/**
  @author Joachim Schiele <js@lastlog.de>
*/

#include "ItemView.h"

ItemView::ItemView( GraphicsScene* scene, Model *model, QWidget * parent ) : QAbstractItemView( parent ) {
    connect(scene, SIGNAL(reset()), this, SLOT(reset()));
    connect(this, SIGNAL(clearScene()), scene, SLOT(clearScene()));

    this->model = model;
    this->scene = scene;
    setModel( model );
}

ItemView::~ItemView() { }

QRect ItemView::visualRect( const QModelIndex &/*index*/ ) const {
    qDebug() << __PRETTY_FUNCTION__;
    return QRect();
}

void ItemView::scrollTo( const QModelIndex &/*index*/, ScrollHint /*hint*/ ) {
    qDebug() << __PRETTY_FUNCTION__;
}

QModelIndex ItemView::indexAt( const QPoint &/*point*/ ) const {
    return QModelIndex();
}

QModelIndex ItemView::moveCursor( CursorAction /*cursorAction*/, Qt::KeyboardModifiers /*modifiers*/ ) {
    return QModelIndex();
}

int ItemView::horizontalOffset() const {
    return 0;
}

int ItemView::verticalOffset() const {
    return 0;
}

bool ItemView::isIndexHidden( const QModelIndex &/*index*/ ) const {
    return false;
}

void ItemView::setSelection( const QRect &/*rect*/, QItemSelectionModel::SelectionFlags /*command*/ ) {
    qDebug() << __PRETTY_FUNCTION__;
}

QRegion ItemView::visualRegionForSelection( const QItemSelection &/*selection*/ ) const {
    qDebug() << __PRETTY_FUNCTION__;
    return QRegion();
}

void ItemView::reset() {
//     qDebug() << __PRETTY_FUNCTION__;
    emit clearScene();
//   init();
}

void ItemView::rowsInserted( const QModelIndex & parent, int start, int end ) {
//     qDebug() << "rowsInserted in ItemView called: need to insert " << end - start + 1 << " item(s).";
    for ( int i = start; i <= end; ++i ) {
        QModelIndex item = model->index( i, 0, parent );
        switch (model->data( item, customRole::TypeRole ).toInt()) {
        case DataType::MODULE:
//             qDebug() << __FUNCTION__ << " DataType::MODULE " << model->data( item, customRole::TypeRole ).toInt();
            scene->moduleInserted( QPersistentModelIndex( item ) );
            break;
        case DataType::CONNECTION:
//             qDebug() << __FUNCTION__ << " DataType::CONNECTION " << model->data( item, customRole::TypeRole ).toInt();
            scene->connectionInserted( QPersistentModelIndex( item ));
            break;
        case DataType::PROPERTY:
            qDebug() << __PRETTY_FUNCTION__ << " DataProperty inserted, FIXME: we ignore this currently but we should not!";
            break;
        default:
            //FIXME why does that happen?!
            qDebug() << __PRETTY_FUNCTION__ << " UNKNOWN?! " << model->data( item, customRole::TypeRole ).toInt();
        }
    }
}

void ItemView::rowsAboutToBeRemoved( const QModelIndex & parent, int start, int end ) {
//   qDebug() << "rowsAboutToBeRemoved in ItemView called: need to remove " << end-start+1 << " item(s).";
    for ( int i = start; i <= end; ++i ) {
        QModelIndex item = model->index( i, 0, parent );
        if ( model->data( item, customRole::TypeRole ).toInt() == DataType::MODULE )
            scene->moduleRemoved( QPersistentModelIndex( item ) );
        else if ( model->data( item, customRole::TypeRole ).toInt() == DataType::CONNECTION )
            ;    //FIXME not implemented yet//scene->connectionRemoved( QPersistentModelIndex( item ) );
    }
}

/*!
** This algorithm traverses trough the QModelIndex hierarchy
**  topleft -- itemA -- connection1
**             \---- -- connection2       given the topLeft item it returns itemA
**          -- itemB                      given itemA it returns connection1
**             \---- -- connection1       given connection1 it returns itemB
**          -- itemC                      ...
**          -- itemD (bottomRight)        and so on
**             \---- -- connection1
**             \---- -- connection2     <- given this last item, it returns QModelIndex()
*/
QModelIndex ItemView::traverseTroughIndexes( QModelIndex index ) {
//   qDebug() << "  " << index.row() << " ";
    // 1. dive deep into the structure until we found the bottom (not bottomRight)
    QModelIndex childIndex = model->index(0,0,index);
//   qDebug() << "step a";
    if (childIndex.isValid())
        return childIndex;

    // 2. now traverse all elements in the lowest hierarchy
    QModelIndex tmpIndex = model->index(index.row()+1,0,model->parent(index));//index.sibling(index.row()+1,0);
//   qDebug() << "step b";
    if (tmpIndex.isValid())
        return tmpIndex;

    // 3. if no more childs are found, return QModelIndex()
//   qDebug() << "step c";
    return QModelIndex();
}

void ItemView::dataChanged( const QModelIndex & topLeft, const QModelIndex & bottomRight ) {
//   qDebug() << __FUNCTION__;
    QModelIndex tmpIndex = topLeft;
    do {
//     qDebug() << "dataChanged is now called()";
        switch (model->data( tmpIndex, customRole::TypeRole ).toInt()) {
        case DataType::MODULE:
            scene->moduleUpdated( QPersistentModelIndex( tmpIndex ) );
            break;
        case DataType::CONNECTION:
            //not implemented, but we probably don't need that
            break;
        case DataType::PROPERTY:
            //FIXME not implemented
            qDebug() << __PRETTY_FUNCTION__ << " FIXME: not implemented yet for PROPERTY";
            break;
        default:
            qDebug() << __PRETTY_FUNCTION__ << " didn't understand what i should be doing";
            exit(0);
        }
        if (tmpIndex == bottomRight)
            break;
        tmpIndex = traverseTroughIndexes( tmpIndex );
    } while ( tmpIndex.isValid() );
}

void ItemView::layoutChanged() {
    //FIXME do we need that?
    qDebug() << __PRETTY_FUNCTION__ << " is NOT implemented yet, please implement me!, exiting";
    exit(1);
}
