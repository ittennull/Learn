#ifndef STORAGE_H
#define STORAGE_H

#include <vector>
#include "QString"
#include "Collection.h"


class QXmlStreamReader;

class Storage
{
	const QString CollectionsDirectoryName = "Collections";

	std::vector<QString> _collectionNames;

public:
	Storage();

	std::vector<QString> getCollectionsNames() const {return _collectionNames;}
	Collection getCollection(const QString& name) const;
	void saveCollection(const Collection& collection) const;
	void createCollection(const QString& name);
	void deleteCollection(const QString& name);

private:
	QString getCollectionsDirectoryName() const;
	QString getCollectionFilename(const QString& name) const;

	Record parseRecord(QXmlStreamReader& xml) const;
};

#endif // STORAGE_H
