// //
// // C++ Interface: Model
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
// #ifndef MODEL_H
// #define MODEL_H
//
// #include <QAbstractItemModel>
// #include <QModelIndex>
// #include <QVariant>
//
// class Model;
//
// class TreeModel : public QAbstractItemModel {
//     Q_OBJECT
//
// public:
//     TreeModel(const QString &data, QObject *parent = 0);
//     ~TreeModel();
//
//     QVariant data(const QModelIndex &index, int role) const;
//     Qt::ItemFlags flags(const QModelIndex &index) const;
//     QVariant headerData(int section, Qt::Orientation orientation,
//                         int role = Qt::DisplayRole) const;
//     QModelIndex index(int row, int column,
//                       const QModelIndex &parent = QModelIndex()) const;
//     QModelIndex parent(const QModelIndex &index) const;
//     int rowCount(const QModelIndex &parent = QModelIndex()) const;
//     int columnCount(const QModelIndex &parent = QModelIndex()) const;
//
// private:
//     void setupModelData(const QStringList &lines, Model *parent);
//
//     Model *rootItem;
// };
//
// #endif
