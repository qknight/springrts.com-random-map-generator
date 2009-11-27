// //
// // C++ Implementation: DataStorage
// //
// // Description:
// //
// //
// // Author: Joachim Schiele <js@lastlog.de>, (C) 2009
// //
// // Copyright: See COPYING file that comes with this distribution
// //
// //
//
// #include <QStringList>
//
// #include "treeitem.h"
//
//  TreeItem::TreeItem(const QList<QVariant> &data, TreeItem *parent)
// {
//   parentItem = parent;
//   itemData = data;
// }
//
//  TreeItem::~TreeItem()
// {
//   qDeleteAll(childItems);
// }
//
//  void TreeItem::appendChild(TreeItem *item)
// {
//   childItems.append(item);
// }
//
//  TreeItem *TreeItem::child(int row)
// {
//   return childItems.value(row);
// }
//
//  int TreeItem::childCount() const
// {
//   return childItems.count();
// }
//
//  int TreeItem::columnCount() const
// {
//   return itemData.count();
// }
//
//  QVariant TreeItem::data(int column) const
// {
//   return itemData.value(column);
// }
//
//  TreeItem *TreeItem::parent()
// {
//   return parentItem;
// }
//
//  int TreeItem::row() const
// {
//   if (parentItem)
//     return parentItem->childItems.indexOf(const_cast<TreeItem*>(this));
//
//   return 0;
// }