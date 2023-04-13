#include "filemanager.h"
#include <QDebug>
FileManager::FileManager(QObject *parent)
	: QObject(parent)
{
	//������ǰĿ¼��һ���ļ��� data
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
	//����data�µ�img
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
	//�����ļ� userdata.ini
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
