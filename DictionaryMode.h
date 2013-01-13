#ifndef DICTIONARYMODE_H
#define DICTIONARYMODE_H

#include <QObject>
#include "CollectionModel.h"
#include <memory>

class DictionaryMode : public QObject
{
	Q_OBJECT

	std::shared_ptr<CollectionModel> _currentCollectionModel;

public:
	explicit DictionaryMode(QObject *parent = 0);

	Q_PROPERTY(CollectionModel* CurrentCollectionModel READ getCurrentCollectionModel NOTIFY currentCollectionModelChanged)
	CollectionModel* getCurrentCollectionModel() const {return _currentCollectionModel.get();}

	void setCollection(Collection* collection);

	bool hasCollectionChanged() const;
	
signals:
	void currentCollectionModelChanged();

public slots:
	
};

#endif // DICTIONARYMODE_H
