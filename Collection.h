#ifndef RECORD_H
#define RECORD_H

#include <QStringList>


class Record
{
public:
	QString Eng;
	QString Transcription;
	QStringList RusList;
};


class Collection : public std::vector<Record>
{
	QString _name;

public:
	Collection(){}
	Collection(const QString& name) {setName(name);}

	void setName(const QString& name) {_name = name;}
	const QString& getName() const {return _name;}

};

#endif // RECORD_H
