#include <QtWidgets/QApplication>
#include "qtquick2applicationviewer.h"
#include "QDir"
#include "App.h"
#include "Storage.h"
#include <QtGui/QGuiApplication>
#include <QtQml/QQmlContext>
#include <QtQml>
#include "CollectionModel.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	QDir::setCurrent(QCoreApplication::applicationDirPath());

	App application;

	qmlRegisterType<App>("App", 1, 0, "App");
	qmlRegisterType<CollectionModel>("CollectionModel", 1, 0, "CollectionModel");
	qmlRegisterType<QStringListModel>("QStringListModel", 1, 0, "QStringListModel");

	QtQuick2ApplicationViewer viewer;
	viewer.rootContext()->setContextProperty("app", &application);
	viewer.rootContext()->setContextProperty("checkModeCpp", &application.getCheckMode());
	viewer.rootContext()->setContextProperty("dictionaryModeCpp", &application.getDictionaryMode());
	viewer.rootContext()->setContextProperty("rememberModeCpp", &application.getRememberMode());
	viewer.setMainQmlFile(QStringLiteral("qml/Learn/main.qml"));
	viewer.showExpanded();

	viewer.setIcon(QIcon(":/new/g/dictionary-icon.png"));
    viewer.setTitle("Learn");

    application.setWindow(&viewer);

    return app.exec();
}
