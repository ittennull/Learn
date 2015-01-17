#ifndef STORAGE_H
#define STORAGE_H

#include <vector>
#include <QString>
#include <QStringList>


class QXmlStreamReader;


class Record
{
public:
    QString Eng;
    QString Transcription;
    QStringList RusList;
};

typedef std::vector<Record> Collection;


class Storage
{
    const QString DatabaseName = "Collections.xml";

    Collection _records;

public:
	Storage();

    void save() const;

    Collection& getCollection() { return _records; }

private:
	Record parseRecord(QXmlStreamReader& xml) const;
    QString getDatabasePath() const;
};

#endif // STORAGE_H
