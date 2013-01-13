#include "App.h"


App::App()
	: _appMode(AppMode::Dictionary)
{
	QStringList collectionNames;
	for(const QString& s: _storage.getCollectionsNames())
	{
		collectionNames.append(s);
	}

	_collectionNamesModel = new QStringListModel(collectionNames);

	QObject::connect(this, SIGNAL(sigCollectionSaved(QString)), &_checkMode, SLOT(onCollectionSaved(QString)));

	if (collectionNames.size() != 0)
		setCollection(collectionNames[0]);
}

App::~App()
{
	saveCollection();
}

void App::setAppMode(App::AppMode mode)
{
	if(_appMode != mode)
	{
		setMode(mode);
		emit appModeChanged();
	}
}

void App::createCollection(const QString &name)
{
	_storage.createCollection(name);

	int newRowIndex = _collectionNamesModel->rowCount();
	_collectionNamesModel->insertRows(newRowIndex, 1);
	_collectionNamesModel->setData(_collectionNamesModel->index(newRowIndex, 0), name, Qt::DisplayRole);

	setCollection(name);

	emit newCollectionCreated();
}

void App::deleteCollection(int index)
{
	QVariant name = _collectionNamesModel->data(_collectionNamesModel->index(index, 0), Qt::DisplayRole);
	_storage.deleteCollection(name.toString());
	_collectionNamesModel->removeRows(index, 1);
}

void App::setMode(AppMode appMode)
{
	if(_appMode == appMode)
		return;

	if(_appMode == AppMode::Dictionary)
	{
		saveCollection();
	}

	_appMode = appMode;

	setCollection();
}

void App::setCollection()
{
	switch(_appMode)
	{
	case AppMode::Check:
		_checkMode.setCollection(&_currentCollection);
		break;

	case AppMode::Remember:
		_rememberMode.setCollection(&_currentCollection);
		break;

	case AppMode::Dictionary:
		_dictionaryMode.setCollection(&_currentCollection);
		break;
	}
}

void App::setCollection(QString name)
{
	if(_currentCollection.getName() != name)
	{
		saveCollection();

		_currentCollection = _storage.getCollection(name);

		setCollection();
	}
}

void App::saveCollection()
{
	if(_appMode == AppMode::Dictionary && _dictionaryMode.hasCollectionChanged())
	{
		_storage.saveCollection(_currentCollection);
		emit sigCollectionSaved(_currentCollection.getName());
	}
}


