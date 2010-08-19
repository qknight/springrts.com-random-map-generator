#include "FilterProxyModel.h"
#include "Model.h"
#include "DataAbstractItem.h"

/*! only show modules and their properties in the treeView */
bool FilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const {
//     qDebug() << __PRETTY_FUNCTION__ << sourceModel()->data(sourceParent, customRole::TypeRole).toInt();
    
    // this is somehow a bug, why is that filter called with an QModelIndex which is invalid?
    if (!sourceParent.isValid()) {
        return true;
    }
    
    switch (sourceModel()->data(sourceParent, customRole::TypeRole).toInt()) {
    case DataItemType::ROOT:
        return true;
    case DataItemType::MODULE: {
        QModelIndex child = sourceModel()->index(sourceRow, 0, sourceParent);
        if (sourceModel()->data(child, customRole::TypeRole).toInt() == DataItemType::PROPERTY)
            return true;
    }
    return false;
    default:
        return false;
    }
}
