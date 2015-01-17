#ifndef COLLECTIONMODEL_H
#define COLLECTIONMODEL_H

#include <QAbstractListModel>
#include <QVariant>
#include <QStringList>
#include "Storage.h"


class CollectionModel : public QAbstractListModel
{
    Q_OBJECT

    Collection* _collection;

public:
    enum ERoles {
        EngRole = Qt::UserRole + 1,
        RusListRole,
        Transcription
    };

public:
    CollectionModel(){}
    CollectionModel(Collection* collection);

    Q_PROPERTY(int Count READ rowCount NOTIFY countChanged)

    const Collection* getCollection() const {return _collection;}

    virtual int rowCount( const QModelIndex & parent = QModelIndex() ) const override;
    virtual int columnCount( const QModelIndex & parent = QModelIndex() ) const override;
    virtual QVariant data( const QModelIndex & index, int role = Qt::DisplayRole ) const override;

    virtual Qt::ItemFlags flags ( const QModelIndex & index ) const override;

    Q_INVOKABLE void addRecord(const QString& eng, const QString& transcription, const QStringList& rusList);
    Q_INVOKABLE void removeRecord(int index);
    Q_INVOKABLE void setRecord(int idx, const QString &eng, const QString& transcription, const QStringList &rusList);

    Q_INVOKABLE QString getEng(int index) const;
    Q_INVOKABLE QString getTranscription(int index) const;
    Q_INVOKABLE QStringList getRusList(int index) const;

signals:
    void countChanged();
    void makeDirty();

public slots:

private:
    Record createRecord(const QString& eng, const QString& transcription, const QStringList& rusList);
    QString prepareTranscription(const QString& str);

    QHash<int, QByteArray> roleNames() const override;
};

#endif // COLLECTIONMODEL_H
