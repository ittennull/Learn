#include "App.h"
#include <QtWidgets/QApplication>
#include <QWindow>
#include <QMessageBox>

App::App()
{
    QObject::connect(&_dictionaryMode, &DictionaryMode::markCollectionDirty, [this]()
    {
        _isDirty = true;
        auto title = _window->title();
        if(!title.endsWith("*"))
            _window->setTitle(title.append("*"));
    });
    QObject::connect(this, &App::sigCollectionSaved, [this]()
    {
        _isDirty = false;
        auto title = _window->title();
        _window->setTitle(title.left(title.length() - 1));
    });

    _timer->setInterval(10*1000);
    QObject::connect(_timer.get(), &QTimer::timeout, [this]() { saveCollection(); });

    _currentCollection = &_storage.getCollection();

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
        _checkMode.setCollection(_currentCollection);
		break;

	case AppMode::Remember:
        _rememberMode.setCollection(_currentCollection);
		break;

	case AppMode::Dictionary:
        _dictionaryMode.setCollection(_currentCollection);
		break;
    }
}

void App::saveCollection()
{
    if(_appMode == AppMode::Dictionary && _isDirty)
	{
        _storage.save();
        emit sigCollectionSaved();
	}
}


