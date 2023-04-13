#pragma once

#include <QObject>
#include <QDir>
#include <QFile>
class FileManager  : public QObject
{
	Q_OBJECT

public:
	FileManager(QObject *parent=nullptr);
	~FileManager();
};
