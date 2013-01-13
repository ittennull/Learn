#include "DictionaryMode.h"

DictionaryMode::DictionaryMode(QObject *parent) :
    QObject(parent)
{
}

void DictionaryMode::setCollection(Collection *collection)
{
	_currentCollectionModel = std::make_shared<CollectionModel>(collection);
	emit currentCollectionModelChanged();
}

bool DictionaryMode::hasCollectionChanged() const
{
	return _currentCollectionModel ? _currentCollectionModel->isChanged() : false;
}
