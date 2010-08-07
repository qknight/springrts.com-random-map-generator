#ifndef FILTERPROXYMODEL__HH
#define FILTERPROXYMODEL__HH

#include <QSortFilterProxyModel>

class FilterProxyModel : public QSortFilterProxyModel {
  Q_OBJECT;
protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const;
};

#endif
