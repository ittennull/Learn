#include "DictionaryMode.h"

DictionaryMode::DictionaryMode(QObject *parent) :
    QObject(parent)
{
}

void DictionaryMode::setCollection(Collection *collection)
{
	_currentCollectionModel = std::make_shared<CollectionModel>(collection);
    QObject::connect(_currentCollectionModel.get(), &CollectionModel::makeDirty, [this]() { emit markCollectionDirty(); });
	emit currentCollectionModelChanged();
}
