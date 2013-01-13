#include "Storage.h"
#include "QFile"
#include "QDir"
#include "QStringList"
#include <stdexcept>
#include "QXmlStreamReader"
#include "QXmlStreamWriter"
#include "QFileInfo"


Storage::Storage()
{
	QDir dir(getCollectionsDirectoryName());
	if (!dir.exists())
		return;

	auto list = dir.entryList(QStringList("*.xml"));
	for(auto filename: list)
		_collectionNames.push_back(QFileInfo(filename).baseName());
}

Collection Storage::getCollection(const QString& name) const
{
	auto filename = getCollectionFilename(name);
	QFile file(filename);
	if (!file.exists() || !file.open(QIODevice::ReadOnly))
	{
		std::string msg = std::string("can't find filename") + name.toStdString();
		throw std::invalid_argument(msg);
	}

	Collection collection(name);

	QXmlStreamReader xml(&file);

	while(!xml.atEnd() && !xml.hasError())
	{
		QXmlStreamReader::TokenType token = xml.readNext();

		if(token == QXmlStreamReader::StartDocument)
			continue;

		if(token == QXmlStreamReader::StartElement)
		{
			if (xml.name() == "Record")
			{
				collection.push_back(parseRecord(xml));
			}
		}
	}

	if(xml.hasError())
	{
		throw std::runtime_error( xml.errorString().toStdString());
	}

	xml.clear();

	return collection;
}

Record Storage::parseRecord(QXmlStreamReader& xml) const
{
	Record rec;
	const auto& attributes = xml.attributes();
	rec.Eng = attributes.value("Eng").toString();
	rec.Transcription = attributes.value("Transcription").toString();

	while(!xml.atEnd() && !xml.hasError())
	{
		QXmlStreamReader::TokenType token = xml.readNext();

		if(token == QXmlStreamReader::EndElement && xml.name() == "Record")
			break;

		if(token == QXmlStreamReader::StartElement && xml.name() == "Rus")
		{
			rec.RusList.push_back(xml.readElementText());
		}
	}

	return rec;
}

void Storage::saveCollection(const Collection& collection) const
{
	QDir(QDir::currentPath()).mkdir(CollectionsDirectoryName);

	auto filename = getCollectionFilename(collection.getName());
	QFile file(filename);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
	{
		std::string msg = std::string("can't open filename ") + collection.getName().toStdString();
		throw std::invalid_argument(msg);
	}

	QXmlStreamWriter stream(&file);
	stream.setAutoFormatting(true);
	stream.writeStartDocument();

	stream.writeStartElement("Collection");

	for(auto rec: collection)
	{
		stream.writeStartElement("Record");
		stream.writeAttribute("Eng", rec.Eng);
		stream.writeAttribute("Transcription", rec.Transcription);

		for(auto rus: rec.RusList)
		{
			stream.writeTextElement("Rus", rus);
		}

		stream.writeEndElement(); //Record
	}

	stream.writeEndElement(); //Collection

	stream.writeEndDocument();
}

void Storage::createCollection(const QString &name)
{
	saveCollection(Collection(name));
}

void Storage::deleteCollection(const QString &name)
{
	auto filename = getCollectionFilename(name);
	QFile::remove(filename);
}

QString Storage::getCollectionsDirectoryName() const
{
	return QDir::currentPath() + QDir::separator() + CollectionsDirectoryName;
}

QString Storage::getCollectionFilename(const QString& name) const
{
	return getCollectionsDirectoryName() + QDir::separator() + name + ".xml";
}


