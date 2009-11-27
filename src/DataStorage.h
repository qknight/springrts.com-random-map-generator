// //
// // C++ Interface: DataStorage
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
// #ifndef TREEITEM_H
// #define TREEITEM_H
//
// #include <QList>
// #include <QVariant>
//
//  class TreeItem
// {
//   public:
//     TreeItem(const QList<QVariant> &data, TreeItem *parent = 0);
//     ~TreeItem();
//
//     void appendChild(TreeItem *child);
//
//     TreeItem *child(int row);
//     int childCount() const;
//     int columnCount() const;
//     QVariant data(int column) const;
//     int row() const;
//     TreeItem *parent();
//
//   private:
//     QList<TreeItem*> childItems;
//     QList<QVariant> itemData;
//     TreeItem *parentItem;
// };
//
// #endif