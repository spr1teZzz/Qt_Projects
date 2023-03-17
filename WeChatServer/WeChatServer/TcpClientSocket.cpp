#include "TcpClientSocket.h"
#pragma execution_character_set("utf-8")
TcpClientSocket::TcpClientSocket(QObject *parent)
	: QTcpSocket(parent)
{
	//�ͻ��˷������ݹ����ͻᴥ��readyRead�ź�
	connect(this, &TcpClientSocket::readyRead, this, &TcpClientSocket::receivedata);
	connect(this, &TcpClientSocket::disconnected, this, &TcpClientSocket::slotclientdisconnected);
    QTextCodec* codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);
}

TcpClientSocket::~TcpClientSocket()
{
	
}
void TcpClientSocket::receivedata()
{
    QByteArray array = readAll();
    QString msg = array;
    //���������������ݸ�ʽ��from:2,to:3,hhh
    qDebug() <<"receivedata:"<<msg;
    QStringList list = msg.split("&");
    int type = (list[0].split("="))[1].toInt();
    if (type == 1)
    {
        //��¼����
        QString phone = (list[1].split("="))[1];
        QString password = (list[2].split("="))[1];
        qDebug() << "phone:" << phone << " password:" << password;
        //��ѯ���ݿ�
        QSqlDatabase login_db = QSqlDatabase::addDatabase("QMYSQL", "login");  //���ӵ�MYSQL�����ݿ�����
		login_db.setHostName("localhost");         //������
		login_db.setPort(3306);                    //�˿�
		login_db.setDatabaseName("test");          //���ݿ���
		login_db.setUserName("root");              //�û���
		login_db.setPassword("123456");            //����
		login_db.open();

        //������¼  �����ź�
        QSqlQuery login_query(login_db);
        QString login_sql = "select * from wc_user where phone = '" + phone + "'and password = '" + password + "' ;";
        qDebug() << login_sql;
        bool login_res = login_query.exec(login_sql);
        int user_id = 0;
        QString user_url;
        if (login_res)
        {
            //qDebug() << "login success!";
            while (login_query.next())
            {
                user_id = login_query.value("uid").toInt();
                QString name = login_query.value("username").toString();
                QString pwd = login_query.value("password").toString();
                QString wechatid = login_query.value("wechatid").toString();
                QString phone = login_query.value("phone").toString();
                QString address = login_query.value("address").toString();
                user_url = login_query.value("image").toString();
            }
            if (user_id == 0)
            {
                //�˺Ż��������
                qDebug() << "�˺Ż��������";
				//QString send_msg = "type=true&user_id=" + QString::number(user_id) + "&user_url=" + user_url;
				QString send_msg = "type=false&user_id=0&user_url=NULL";
				this->write(send_msg.toUtf8());
				return;
            }
        }
        else
        {
            qDebug() << "��ѯʧ��";
        }
		login_db.close();
        //friendInfo��message��ѯ
		//��ȡ��Ϣ�б�
		//db
		QMap<int, QList<Message>> message_map;
		QMap<int, userInfo> userinfo_map;

		QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL", "pageChat");  //���ӵ�MYSQL�����ݿ�����
		db.setHostName("localhost");         //������
		db.setPort(3306);                    //�˿�
		db.setDatabaseName("test");          //���ݿ���
		db.setUserName("root");              //�û���
		db.setPassword("123456");            //����
		db.open();

		//meg_db
		QSqlDatabase db_msg = QSqlDatabase::addDatabase("QMYSQL", "pageChatMessage");  //���ӵ�MYSQL�����ݿ�����
		db_msg.setHostName("localhost");         //������
		db_msg.setPort(3306);                    //�˿�
		db_msg.setDatabaseName("test");          //���ݿ���
		db_msg.setUserName("root");              //�û���
		db_msg.setPassword("123456");            //����
		db_msg.open();

		QSqlQuery query(db);
		QSqlQuery query_msg(db_msg);
		QString sql = "select wc_friend.friendid as uid , wc_user.username,remarkname as remark_name,\
		sex,wechatid as wechat_id,image,address,source from wc_friend LEFT JOIN wc_user ON (wc_friend.friendid = wc_user.uid) where wc_friend.uid = " + QString::number(user_id);
		bool res = query.exec(sql);

		if (res)
		{
			qDebug() << "chatPage success! uid:" << user_id;
			while (query.next())
			{
				int uid = query.value("uid").toInt();
				QString username = query.value("username").toString();
				QString remark_name = query.value("remark_name").toString();
				int sex = query.value("sex").toInt();
				QString wechat_id = query.value("wechat_id").toString();
				QString image = query.value("image").toString();
				QString address = query.value("address").toString();
				int source = query.value("source").toInt();
				//qDebug() << "search data!";
				QList<Message> messageList;
				//��ȡ�Ի���Ϣ
				//SELECT* FROM wc_messagerecords  WHERE fromid = 1 and toid = 2 or fromid = 2 and toid = 1 ORDER BY msgdate DESC LIMIT 5;
				QString sql_message("select * from wc_messagerecords  WHERE fromid = " + QString::number(user_id) + " and toid = " + QString::number(uid) + " or toid = " + QString::number(user_id) + " and fromid = " + QString::number(uid) + " ORDER BY msgdate DESC LIMIT 5; ");
				qDebug() << user_id << " uid:" << uid;

				bool res_msg = query_msg.exec(sql_message);
				if (res_msg)
				{
					qDebug() << "chatPage message success!";
					while (query_msg.next())
					{
						int from_id = query_msg.value("fromid").toInt();
						int to_id = query_msg.value("toid").toInt();
						QString content = query_msg.value("content").toString();
						QString msg_date = query_msg.value("msgdate").toString();
						messageList.append(Message(from_id, to_id,  msg_date, image, content));
					}
				}
				else
				{
					qDebug() << "chatPage messagefailed";
				}
				Message m;
				if (messageList.size() != 0)
				{
					m = messageList[0];
				}
				userinfo_map.insert(uid, userInfo(uid, username, remark_name, sex, wechat_id, image, address, source, m.msg_date, m.content));
				message_map.insert(uid, messageList);
			}
		}
		else
		{
			qDebug() << "chatPage failed";
		}
		//���ݷ�װ����
		QString send_msg = "type=true&user_id=" + QString::number(user_id) + "&user_url=" + user_url;
		QString friendInfo="{";
		QString info;
		for (auto it = userinfo_map.begin(); it != userinfo_map.end(); ++it)
		{
			//int uid, QString username, QString remark_name, int sex, QString wechat_id, 
			//QString image, QString address, int source, QString msg_date, QString content
			info += "{" + QString::number(it.value().uid) + ","+ it.value().username+"," + it.value().remark_name + "," + QString::number(it.value().sex) + ","
			+ it.value().wechat_id + "," + it.value().image + "," + it.value().address + "," + QString::number(it.value().source) + "," + it.value().msg_date + "," + it.value().content+"}/r";
		}
		friendInfo = friendInfo+info+"}";
		QString message = "{";
		for (auto it = message_map.begin(); it != message_map.end(); ++it)
		{
			QString m;
			for (auto i : it.value())
			{
				//from_id, to_id, msg_date, img, content
				m += "{" + QString::number(i.from_id) + "," + QString::number(i.to_id) + "," + i.msg_date + "," + i.img + "," + i.content + "}/r";
			}
			message = message+ "{uid="+ QString::number(it.key())+","+ m + "}/r/r";
		}
		message = message +"}";

		QString all_send_msg = send_msg +"&friendInfo="+friendInfo +"&message="+ message;
		this->write(all_send_msg.toUtf8());

		emit connectsuccess(user_id, this->socketDescriptor());
		/*��Ҫע����ǽṹ����������ַ�����Ա(QString)����Ȼ�ó�Ա��ͨ������¿��Ա��������ʣ�
		����һ���漰���ṹ�巢�ͣ���Ҫ���ṹ�忽������һƬ�ڴ��ַ��
		������Tcp���ͽṹ�壬�ڴ湲���ṹ�壬����Ҫ�õ�memcpy��memmove���п�����
		����QString��Ա�Ľṹ�忽��֮������ݱ��������������³������ˡ�  */

	}
	else if (type == 2)
	{
		//A ������Ϣ�� B
		for (auto it : list)
		{
			qDebug() << it;
		}
		int fid = (list[1].split("="))[1].toInt();
		int tid = (list[2].split("="))[1].toInt();
		QString recv_msg = list[3];
		//meg_db
		QSqlDatabase db_insert_msg = QSqlDatabase::addDatabase("QMYSQL", "insertMsg");  //���ӵ�MYSQL�����ݿ�����
		db_insert_msg.setHostName("localhost");         //������
		db_insert_msg.setPort(3306);                    //�˿�
		db_insert_msg.setDatabaseName("test");          //���ݿ���
		db_insert_msg.setUserName("root");              //�û���
		db_insert_msg.setPassword("123456");            //����
		db_insert_msg.open();
		QSqlQuery insert_query(db_insert_msg);
		//�������ݿ�
		QString sql = QString("insert into wc_messagerecords(fromid,toid,msgdate,content) values('%1','%2',now(),'%3')").arg(fid).arg(tid).arg(recv_msg);
		qDebug() << sql;
		insert_query.exec(sql);
		emit updateserver(recv_msg,fid, tid);
	}
}
void TcpClientSocket::slotclientdisconnected()//����readyRead�źŶ�ȡ����
{
	emit clientdisconnected(this->socketDescriptor());
}
