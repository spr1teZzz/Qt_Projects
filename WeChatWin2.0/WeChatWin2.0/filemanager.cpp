#include "filemanager.h"
#include <QDebug>
FileManager::FileManager(QObject *parent)
	: QObject(parent)
{
	//创建当前目录上一级文件夹 data
	QString curpath = QDir::currentPath() + "/..";
	QString Dirpath = curpath + "/userData";
	QDir dir(Dirpath);
	if (!dir.exists()) {
		if (!dir.mkpath(Dirpath)) {
			qDebug() << "Error: Failed to create directory: " << Dirpath;
		}
		else
		{
			qDebug() << " create directory: " << Dirpath;
		}
	}
	//创建data下的img
	QString ImgDirpath = curpath + "/userData/image";
	QDir imgdir(ImgDirpath);
	if (!imgdir.exists()) {
		if (!imgdir.mkpath(ImgDirpath)) {
			qDebug() << "Error: Failed to create directory: " << ImgDirpath;
		}
		else
		{
			qDebug() << " create directory: " << ImgDirpath;
		}
	}
	//创建文件 userdata.ini
	QString filepath = curpath + "/userData/userdata.ini";
	QFile  userdata(filepath);
	if (!userdata.exists()) {
		if (userdata.open(QIODevice::WriteOnly | QIODevice::Text))
		{
			qDebug() << " create directory: " << filepath;
		}
		else
		{
			qDebug() << "Error: Failed to create file: " << filepath;
		}

	}
}

FileManager::~FileManager()
{}
