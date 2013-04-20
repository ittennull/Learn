#ifndef APP_H
#define APP_H

#include <QObject>
#include <QStringList>
#include <QStringListModel>
#include <QTimer>
#include <QWindow>
#include "Storage.h"
#include "CollectionModel.h"
#include "CheckMode.h"
#include "DictionaryMode.h"
#include "RememberMode.h"
#include <memory>
#include <functional>

class App : public QObject
{
	Q_OBJECT

public:
    enum class AppMode {Check, Remember, Dictionary, None};
	Q_ENUMS(AppMode)

private:
    AppMode _appMode = AppMode::None;

	Storage _storage;
	Collection _currentCollection;
	QStringListModel* _collectionNamesModel;

	CheckMode _checkMode;
	DictionaryMode _dictionaryMode;
	RememberMode _rememberMode;

    bool _collectionIsDirty = false;
    QWindow* _window;

    std::shared_ptr<QTimer> _timer = std::make_shared<QTimer>();

public:
	App();
	~App();

	Q_PROPERTY(AppMode AppMode READ getAppMode WRITE setAppMode NOTIFY appModeChanged)
	AppMode getAppMode() const {return _appMode;}
	void setAppMode(AppMode mode);

	Q_INVOKABLE void createCollection(const QString& name);
	Q_INVOKABLE void deleteCollection(int index);

	Q_INVOKABLE QStringListModel* getCollectionsNamesModel() {return _collectionNamesModel;}

	CheckMode& getCheckMode() {return _checkMode;}
	DictionaryMode& getDictionaryMode() {return _dictionaryMode;}
	RememberMode& getRememberMode() {return _rememberMode;}

    void setWindow(QWindow* p) {_window = p;}
	
signals:
	void sigCollectionSaved(const QString& name);
	void appModeChanged();
	void newCollectionCreated();
	
public slots:
	void setCollection(QString name);

private:
	void saveCollection();
	void setMode(AppMode appMode);
	void setCollection();
};

#endif // APP_H
