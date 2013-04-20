#include "App.h"
#include <QtWidgets/QApplication>
#include <QWindow>
#include <QMessageBox>

App::App()
{
	QStringList collectionNames;
	for(const QString& s: _storage.getCollectionsNames())
	{
		collectionNames.append(s);
	}

    QObject::connect(&_dictionaryMode, &DictionaryMode::markCollectionDirty, [this]()
    {
        _collectionIsDirty = true;
        _window->setTitle(_window->title().append("*"));
    });
    QObject::connect(this, &App::sigCollectionSaved, [this](const QString&)
    {
        _collectionIsDirty = false;
        auto title = _window->title();
        _window->setTitle(title.left(title.length() - 1));
    });

	_collectionNamesModel = new QStringListModel(collectionNames);

    _timer->setInterval(10*1000);
    QObject::connect(_timer.get(), &QTimer::timeout, [this]() { saveCollection(); });

	if (collectionNames.size() != 0)
		setCollection(collectionNames[0]);

    setMode(AppMode::Dictionary);
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
    if(_appMode == AppMode::Dictionary)
	{
		saveCollection();
        _timer->stop();
	}

	_appMode = appMode;

    if(_appMode == AppMode::Dictionary)
        _timer->start();

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
    if(_appMode == AppMode::Dictionary && _collectionIsDirty)
	{
		_storage.saveCollection(_currentCollection);
		emit sigCollectionSaved(_currentCollection.getName());
	}
}


