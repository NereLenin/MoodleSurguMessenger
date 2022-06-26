#include "src/network/moodlenetworkmanager.h"
//#include <QFile>



//-----------Parcing Functions
bool ParsString(QString RegExp,QByteArray StringForPars,QString& result,int from)
{
    QRegularExpression re(RegExp);
    QRegularExpressionMatchIterator match = re.globalMatch(StringForPars,from);

    if(match.hasNext())
    {
        result = match.next().captured(1);
        return true;
    }

    return false;
}

//-----------constructor
MoodleNetworkManager::MoodleNetworkManager(QObject *parent): QObject{parent}
{ 

    isGoodAuthorisation = false;

    ResponseTimer.setInterval(5000);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    manager.setCookieJar(&cookieJar);
}

//-----------set func
void MoodleNetworkManager::SetLogin(const QString& Login)
{
    current_account.SetLogin(Login);
}
void MoodleNetworkManager::SetPassword(const QString &Password)
{
    current_account.SetPassword(Password);
}

//----------GetPost function
bool MoodleNetworkManager::CreateGetWaitiedResponse(QString url,QByteArray *GetReply)
{
    CurrentUrl.setUrl(url);
    request.setUrl(CurrentUrl);


    QObject::connect(&manager, &QNetworkAccessManager::finished,
            &ResponseLoop, &QEventLoop::quit);

    QObject::connect(&ResponseTimer, &QTimer::timeout,
           &ResponseLoop, &QEventLoop::quit);


    ResponseTimer.start();

    QObject::connect(&ResponseTimer, &QTimer::timeout,
           &ResponseTimer, &QTimer::stop);

    QNetworkReply *current_reply = manager.get(request);

    ResponseLoop.exec();//waiting

    if(ResponseTimer.remainingTime() <= 0)
    {
        qDebug() << "Ошибка сети. Ошибка периода ожидания ответа на запрос.";

        QObject::disconnect(&manager, &QNetworkAccessManager::finished,
                &ResponseLoop, &QEventLoop::quit);

        QObject::disconnect(&ResponseTimer, &QTimer::timeout,
               &ResponseTimer, &QTimer::stop);

        QObject::disconnect(&ResponseTimer, &QTimer::timeout,
               &ResponseLoop, &QEventLoop::quit);


        return false;
    }

    if(current_reply->error() != QNetworkReply::NoError)
    {
        qDebug() << "Ошибка подключения к сети";
        delete current_reply;

        QObject::disconnect(&manager, &QNetworkAccessManager::finished,
                   &ResponseLoop, &QEventLoop::quit);
        QObject::disconnect(&manager, &QNetworkAccessManager::finished,
                &ResponseLoop, &QEventLoop::quit);

        QObject::disconnect(&ResponseTimer, &QTimer::timeout,
               &ResponseTimer, &QTimer::stop);

        return false;
    }


    if(GetReply != nullptr)
        *GetReply = current_reply->readAll();


    delete current_reply;


    QObject::disconnect(&manager, &QNetworkAccessManager::finished,
               &ResponseLoop, &QEventLoop::quit);
    QObject::disconnect(&manager, &QNetworkAccessManager::finished,
            &ResponseLoop, &QEventLoop::quit);

    QObject::disconnect(&ResponseTimer, &QTimer::timeout,
           &ResponseTimer, &QTimer::stop);

    return true;
}


bool MoodleNetworkManager::CreatePostWaitiedResponse(QString url,QString data,QByteArray *PostReply)
{
    CurrentUrl.setUrl(url);
    request.setUrl(CurrentUrl);


    QObject::connect(&manager, &QNetworkAccessManager::finished,
            &ResponseLoop, &QEventLoop::quit);

    QObject::connect(&ResponseTimer, &QTimer::timeout,
           &ResponseLoop, &QEventLoop::quit);

    ResponseTimer.start();

    QObject::connect(&ResponseTimer, &QTimer::timeout,
           &ResponseTimer, &QTimer::stop);


    //переписать это как нормальное потом
    QByteArray PostData = data.toUtf8();

    QNetworkReply *current_reply = manager.post(request,PostData);

    ResponseLoop.exec();//waiting

    if(ResponseTimer.remainingTime() <= 0)
    {
        qDebug() << "Ошибка сети. Ошибка периода ожидания ответа на запрос.";
        QObject::disconnect(&manager, &QNetworkAccessManager::finished,
                   &ResponseLoop, &QEventLoop::quit);
        QObject::disconnect(&manager, &QNetworkAccessManager::finished,
                &ResponseLoop, &QEventLoop::quit);

        QObject::disconnect(&ResponseTimer, &QTimer::timeout,
               &ResponseTimer, &QTimer::stop);

        return false;
    }
    if(current_reply->error() != QNetworkReply::NoError)
    {
        qDebug() << "Ошибка подключения к сети";
        delete current_reply;

        QObject::disconnect(&manager, &QNetworkAccessManager::finished,
                   &ResponseLoop, &QEventLoop::quit);
        QObject::disconnect(&manager, &QNetworkAccessManager::finished,
                &ResponseLoop, &QEventLoop::quit);

        QObject::disconnect(&ResponseTimer, &QTimer::timeout,
               &ResponseTimer, &QTimer::stop);

        return false;
    }

    if(PostReply != nullptr)
        *PostReply = current_reply->readAll();

    delete current_reply;

    QObject::disconnect(&manager, &QNetworkAccessManager::finished,
               &ResponseLoop, &QEventLoop::quit);
    QObject::disconnect(&manager, &QNetworkAccessManager::finished,
            &ResponseLoop, &QEventLoop::quit);

    QObject::disconnect(&ResponseTimer, &QTimer::timeout,
           &ResponseTimer, &QTimer::stop);

    return true;
}

bool MoodleNetworkManager::CreatePostWaitiedResponse(QString url, QByteArray data,QByteArray *PostReply)
{
    CurrentUrl.setUrl(url);
    request.setUrl(CurrentUrl);


    QObject::connect(&manager, &QNetworkAccessManager::finished,
            &ResponseLoop, &QEventLoop::quit);

    QObject::connect(&ResponseTimer, &QTimer::timeout,
           &ResponseLoop, &QEventLoop::quit);

    ResponseTimer.start();

    QObject::connect(&ResponseTimer, &QTimer::timeout,
           &ResponseTimer, &QTimer::stop);

    QNetworkReply *current_reply = manager.post(request,data);

    ResponseLoop.exec();//waiting

    if(ResponseTimer.remainingTime() <= 0)
    {
        qDebug() << "Ошибка сети. Ошибка периода ожидания ответа на запрос.";
        QObject::disconnect(&manager, &QNetworkAccessManager::finished,
                   &ResponseLoop, &QEventLoop::quit);
        QObject::disconnect(&manager, &QNetworkAccessManager::finished,
                &ResponseLoop, &QEventLoop::quit);

        QObject::disconnect(&ResponseTimer, &QTimer::timeout,
               &ResponseTimer, &QTimer::stop);

        return false;
    }
    if(current_reply->error() != QNetworkReply::NoError)
    {
        qDebug() << "Ошибка подключения к сети";
        delete current_reply;

        QObject::disconnect(&manager, &QNetworkAccessManager::finished,
                   &ResponseLoop, &QEventLoop::quit);
        QObject::disconnect(&manager, &QNetworkAccessManager::finished,
                &ResponseLoop, &QEventLoop::quit);

        QObject::disconnect(&ResponseTimer, &QTimer::timeout,
               &ResponseTimer, &QTimer::stop);

        return false;
    }

    if(PostReply != nullptr)
        *PostReply = current_reply->readAll();

    delete current_reply;

    QObject::disconnect(&manager, &QNetworkAccessManager::finished,
               &ResponseLoop, &QEventLoop::quit);
    QObject::disconnect(&manager, &QNetworkAccessManager::finished,
            &ResponseLoop, &QEventLoop::quit);

    QObject::disconnect(&ResponseTimer, &QTimer::timeout,
           &ResponseTimer, &QTimer::stop);

    return true;
}


//-----------Json response pars
void MoodleNetworkManager::ReadJsonConversation(QJsonValue conv, Conversation &RewritedConv, bool parseMembers)
{
    if(conv.isNull())
    {
       qDebug() << "Пустой диалог";
       return;
    }



    if(parseMembers)
    {
    RewritedConv.SetId(conv.toObject().value("id").toInt());

    QJsonArray Members = conv.toObject().value("members").toArray();
    //создание Json массива members

    qDebug() << Members;

    for(int j = 0; j< Members.size();j++)
    {

        if(Members[j].toObject().value("id").toInt() == current_account.GetId())
        {
            current_account.AddConversation(&RewritedConv);
        }
        else
        {
        Member *NewMember = new Member;

        NewMember->SetId(Members[j].toObject().value("id").toInt());
        NewMember->SetFullName(Members[j].toObject().value("fullname").toString());
        NewMember->SetProfileURL(Members[j].toObject().value("profileurl").toString());
        NewMember->SetAvatarURL(Members[j].toObject().value("profileimageurl").toString());
        NewMember->SetOnline(Members[j].toObject().value("isonline").toBool());
        NewMember->AddConversation(&RewritedConv);
        RewritedConv.AddMember(NewMember);
        }
    }

    if(RewritedConv.MembersSize() == 0)
    {
        Member *myAcc = new Member;
        myAcc->SetId(current_account.GetId());
        myAcc->SetFullName(current_account.GetFullName());
        myAcc->SetProfileURL(current_account.GetProfileURL());
        myAcc->SetAvatarURL(current_account.GetAvatarURL());
        myAcc->SetOnline(true);
        myAcc->AddConversation(&RewritedConv);
        //myAcc->set
        RewritedConv.AddMember(myAcc);

    }

    }

    QJsonArray Messages = conv.toObject().value("messages").toArray();
    //создание Json массива messagies

    //парсинг данных массива messagies[j]
    for(int j=0; j<Messages.size();j++)
    {
        Message *NewMessage = new Message;

        NewMessage->SetId(QString::number(Messages[j].toObject().value("id").toInt()));
        int idfrom = Messages[j].toObject().value("useridfrom").toInt();

        //установка автора сообщения
        if(idfrom == current_account.GetId())
        {
            NewMessage->SetSender(&current_account);
            NewMessage->setIsMine(true);
        }
        else
        {
            //если это не мы отправили, ищем кто из членов диалога
            for(int k=0;k<RewritedConv.MembersSize();k++)
                if(RewritedConv.GetMember(k)->GetId()==idfrom)
                    NewMessage->SetSender((RewritedConv.GetMember(k)));
        }

        NewMessage->SetTimeCreated(Messages[j].toObject().value("timecreated").toInt());
        NewMessage->SetText(Messages[j].toObject().value("text").toString());

        RewritedConv.AddMessage(NewMessage);
    }//end add mesage
}

void MoodleNetworkManager::ReadJsonCourse(QJsonValue course, Course &newCourse)
{
    if(course.isNull())
    {
       qDebug() << "Пустой диалог";
       return;
    }

    newCourse.setId(course.toObject().value("id").toInt());
    newCourse.setFullName(course.toObject().value("fullname").toString());
    newCourse.setShortName(course.toObject().value("shortname").toString());
    newCourse.setURL(course.toObject().value("viewurl").toString());

    if(!course.toObject().value("courseimage").isNull())
    {
        QImage *newImage = new QImage;
        newImage->loadFromData(course.toObject().value("courseimage").toString().toUtf8(),"SVG");
        newCourse.setCourseImage(*newImage);
    }

}

bool MoodleNetworkManager::ReadJson(const QByteArray &pars,QList<Conversation*> &ConversationToRead)
{
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(pars,&error);

    if(error.error != QJsonParseError::NoError)
    {
        qDebug() << "Ошибка чтения ответа";
        qDebug() << error.errorString();
        return false;
    }

    QJsonArray Conversations = doc.array()[0].toObject().value("data").toObject().value("conversations").toArray();

    if(Conversations.isEmpty())
        return true;


    for(int i=0; i< Conversations.size();i++)
    {
        Conversation *NewConversation = new Conversation;
        ReadJsonConversation(Conversations[i],*NewConversation);
        ConversationToRead.append(NewConversation);
    }

    return true;
}

bool MoodleNetworkManager::ReadJson(const QByteArray &pars,QList<Course*> &courses)
{
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(pars,&error);

    if(error.error != QJsonParseError::NoError)
    {
        qDebug() << "Ошибка чтения ответа";
        qDebug() << error.errorString();
        return false;
    }

    QJsonArray coursesData = doc.array()[0].toObject().value("data").toArray();

    if(coursesData.isEmpty())
        return true;


    for(int i=0; i< coursesData.size();i++)
    {
        Course *newCourse = new Course;
        ReadJsonCourse(coursesData[i],*newCourse);
        courses.append(newCourse);
    }

    return true;
}

bool MoodleNetworkManager::ReadJson(const QByteArray &pars,Conversation& WriteTo)
{
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(pars,&error);

    if(error.error != QJsonParseError::NoError)
    {
        qDebug() << "Ошибка чтения ответа";
        qDebug() << error.errorString();
        return false;
    }

    QJsonValue Conversation = doc.array()[0].toObject().value("data");

    ReadJsonConversation(Conversation,WriteTo,false);

    return true;
}


bool MoodleNetworkManager::isNetworkAccessible()
{
    return CreateGetWaitiedResponse("http://moodle.surgu.ru");
}

bool MoodleNetworkManager::isLogIn()
{
    return isGoodAuthorisation;
}

//------------network
void MoodleNetworkManager::Authorisation()
{
    setlocale(LC_ALL,"Russian");

    if(isGoodAuthorisation) LogOut();


    //------------------------GET LOGINTOKEN BLOCK
    qDebug() << "   1.Получение значения logintoken...";
    QByteArray pars;

    if(!CreateGetWaitiedResponse("https://moodle.surgu.ru/login/index.php",&pars))
    {
        qDebug() << "Ошибка авторизации. Проверьте подключение";
        isGoodAuthorisation = false;
        return;
    }


    QString LoginToken;
    if(!ParsString("<input type=\"hidden\" name=\"logintoken\" value=\"(.*?)\">",pars,LoginToken))
    {
        qDebug() << "Ошибка авторизации. Ошибка получения поля logintoken";
        isGoodAuthorisation = false;
        return;
    }
    current_account.SetLoginToken(LoginToken);

    qDebug() << "     Значение получено.Текущий logintoken: " << LoginToken;


    qDebug() << "   2.Отправка запроса на авторизацию с параметрами: username: " << current_account.GetLogin() << " password: " << current_account.GetPassword();

    if(!CreatePostWaitiedResponse("https://moodle.surgu.ru/login/index.php",QString("anchor=&logintoken=%1&username=%2&password=%3").arg(LoginToken).arg(current_account.GetLogin()).arg(current_account.GetPassword()),&pars))
    {
        qDebug() << "Ошибка авторизации. Проверте подключение к сети";
        isGoodAuthorisation = false;
        return;
    }

    if(pars.contains("id=\"loginerrormessage\""))
    {
        qDebug() << "Ошибка авторизации. Проверте правильность логина и пароля.";
        isGoodAuthorisation = false;
        return;
    }


    //-------------------HELLO BLOCK-----------------------------
    if(!CreateGetWaitiedResponse("https://moodle.surgu.ru/",&pars))
    {
        qDebug() << "Ошибка авторизации. Проверте подключение";
        isGoodAuthorisation = false;
        return;
    }

    QString ProfileName;

    if(!ParsString("<span class=\"userbutton\"><span class=\"usertext mr-1\">([^>]+)</span>",pars,ProfileName))
    {
        qDebug() << "Ошибка авторизации. Проверьте правильность данных. Ошибка получения полного имени профиля";
        isGoodAuthorisation = false;
        return;
    }

    current_account.SetFullName(ProfileName);
     qDebug() << "Welcome to Surgut State University, " << current_account.GetFullName() << "\n";

    //----------------------Get userid and sesskey------------------

     qDebug() << "   3.Получение информации о профиле (поля userid и sesskey)";

    QString UserId;
    ParsString("<div class=\"hidden h-100\" data-region=\"view-contacts\" aria-hidden=\"true\" data-user-id=\"([^>]+)\">",pars,UserId);
    current_account.SetId(UserId.toInt());

    QString SessKey;
    ParsString("sesskey=([^\"]+)\" class=\"dropdown-item menu-action\" role=\"menuitem\" data-title=\"logout,moodle\" aria-labelledby=\"actionmenuaction-6\">",pars,SessKey);
    current_account.SetSessKey(SessKey);

    qDebug() << " UserId:|" << current_account.GetId() << "|";
    qDebug() << " Sesskey:|" << current_account.GetSessKey()  <<  "|";

    isGoodAuthorisation = true;
}


//-----------Conversation Func
void MoodleNetworkManager::ReadExistConversations(QList<Conversation*> &ConversationToRead)
{

    if(!isGoodAuthorisation)
    {
       qDebug() << "Ошибка авторизации. Войдите в свой аккаунт";
       return;
    }

    QByteArray PersonalConversationsResponse;
    QByteArray MarkedConversationsResponse;
    QByteArray GroupConversationsResponse;

    QString GetConversationsUrl = QString("https://moodle.surgu.ru/lib/ajax/service.php?sesskey=%1&info=core_message_get_conversations").arg(current_account.GetSessKey());

    QString GetPersonalConvData = QString(("[{\"index\":0,\"methodname\":\"core_message_get_conversations\",\"args\":{\"userid\":\"%1\",\"type\":1,\"favourites\":false,\"mergeself\":true}}]")).arg(current_account.GetId());
    QString GetMarkedConvData = QString(("[{\"index\":0,\"methodname\":\"core_message_get_conversations\",\"args\":{\"userid\":\"%1\",\"type\":null,\"favourites\":true,\"mergeself\":true}}]")).arg(current_account.GetId());
    QString GetGroupConvData = QString(("[{\"index\":0,\"methodname\":\"core_message_get_conversations\",\"args\":{\"userid\":\"%1\",\"type\":2,\"favourites\":false,\"mergeself\":false}}]")).arg(current_account.GetId());

    qDebug() << "   1.Отправка запроса на получение списка диалогов";

    if((!CreatePostWaitiedResponse(GetConversationsUrl,GetMarkedConvData,&MarkedConversationsResponse))||
       (!CreatePostWaitiedResponse(GetConversationsUrl,GetPersonalConvData,&PersonalConversationsResponse))||
       (!CreatePostWaitiedResponse(GetConversationsUrl,GetGroupConvData,&GroupConversationsResponse)) )
    {
        qDebug() << "Ошибка получения диалогов. Проверте подключение к сети";
        return;
    }


    /*
    QFile file("out.html");
        if (file.open(QIODevice::WriteOnly))
        {
            file.write(PersonalConversationsResponse);
            file.close();
        }
    */

    ConversationToRead.clear();

    if((!ReadJson(MarkedConversationsResponse,ConversationToRead))||
       (!ReadJson(PersonalConversationsResponse,ConversationToRead))||
       (!ReadJson(GroupConversationsResponse,ConversationToRead)) )
    {
        qDebug() << "Ошибка парсинга диалогов";
        return;
    }
}

void MoodleNetworkManager::ReadCourses(QList<Course*> &courses)
{
    if(!isGoodAuthorisation)
    {
       qDebug() << "Ошибка авторизации. Войдите в свой аккаунт";
       return;
    }

    QByteArray response;

    QString getCoursesURL= QString("https://moodle.surgu.ru/lib/ajax/service.php?sesskey=%1&info=core_course_get_recent_courses").arg(current_account.GetSessKey());
    QString getCoursesPostData = QString(("[{\"index\":0,\"methodname\":\"core_course_get_recent_courses\",\"args\":{\"userid\":\"%1\",\"limit\":0}}]")).arg(current_account.GetId());

    qDebug() << "   1.Отправка запроса на получение списка курсов";

    if(!(CreatePostWaitiedResponse(getCoursesURL,getCoursesPostData,&response)))
    {
        qDebug() << "Ошибка получения курсов. Проверте подключение к сети";
        return;
    }


    /*
    QFile file("out.html");
        if (file.open(QIODevice::WriteOnly))
        {
            file.write(PersonalConversationsResponse);
            file.close();
        }
    */

    courses.clear();

    if((!ReadJson(response,courses)) )
    {
        qDebug() << "Ошибка парсинга курсов";
        return;
    }

}

void MoodleNetworkManager::ReadConversation(Conversation &ReadedConversation, int time,bool clear)
{

    if(!isGoodAuthorisation)
    {
       qDebug() << "Ошибка авторизации. Войдите в свой аккаунт";
       return;
    }


    QByteArray pars;

    QString GetMessagiesUrl = QString("https://moodle.surgu.ru/lib/ajax/service.php?sesskey=%1&info=core_message_get_conversation_messages").arg(current_account.GetSessKey());
    QString GetMessagiesPostData = QString(("[{\"index\":0,\"methodname\":\"core_message_get_conversation_messages\",\"args\":{\"currentuserid\":%1,\"convid\":%2,\"newest\":true,\"limitnum\":0,\"limitfrom\":0,\"timefrom\":%3}}]")).arg(current_account.GetId()).arg(ReadedConversation.GetId()).arg(QString::number(time));


    qDebug() << "   1.Отправка запроса на получение списка сообщений диалога";

    if(!CreatePostWaitiedResponse(GetMessagiesUrl,GetMessagiesPostData,&pars))
    {
        qDebug() << "Ошибка получения диалогов. Проверте подключение к сети";
        return;
    }

/*
    QFile file("out.html");
        if (file.open(QIODevice::WriteOnly))
        {
            file.write(pars.toStdString().c_str());
            file.close();
        }
*/
    if(!pars.contains("{\"error\":false"))
    {
        QString error_text;
        qDebug() << "Ответ на запрос пришел с ошибкой.";

        if(ParsString("\"error\":\"([^\"]+)\",",pars,error_text))
            qDebug() << error_text;
        return;
    }

    if(clear)
        ReadedConversation.ClearAllMessages();

    //ReadedConversation.ClearAllMembers();

    /*
    QFile file("out.html");
        if (file.open(QIODevice::WriteOnly))
        {
            file.write(pars.toStdString().c_str());
            file.close();
        }

*/


    qDebug() << "   2.Парсинг сообщений";

    if(!ReadJson(pars,ReadedConversation))
    {
        qDebug() << "Ошибка парсинга диалогов";
        return;
    }

    qDebug() << "   3.Помечаем все сообщения диалога как прочитаные";

    //-------------Mark all messagies as readed
    GetMessagiesUrl = QString("https://moodle.surgu.ru/lib/ajax/service.php?sesskey=%1&info=core_message_mark_all_conversation_messages_as_read").arg(current_account.GetSessKey());
    GetMessagiesPostData = QString(("[{\"index\":0,\"methodname\":\"core_message_mark_all_conversation_messages_as_read\",\"args\":{\"userid\":%1,\"conversationid\":%2}}]")).arg(current_account.GetId()).arg(ReadedConversation.GetId());

    if(!CreatePostWaitiedResponse(GetMessagiesUrl,GetMessagiesPostData,&pars))
    {
        qDebug() << "Ошибка получения диалогов. Проверте подключение к сети";
        return;
    }
    if(!pars.contains("{\"error\":false"))
    {
        QString error_text;
        qDebug() << "Ответ на запрос пришел с ошибкой.";

        if(ParsString("\"error\":\"([^\"]+)\",",pars,error_text))
            qDebug() << error_text;

        return;
    }
}

void MoodleNetworkManager::UpdateConversation(Conversation &WriteTo)
{
    ReadConversation(WriteTo,WriteTo[0]->GetTimeCreated(),false);
}


void MoodleNetworkManager::SendMessage(Conversation &Addressee, QString Text)
{
    if(!isGoodAuthorisation)
    {
       qDebug() << "Ошибка авторизации. Войдите в свой аккаунт";
       return;
    }

    QByteArray pars;//response?


    qDebug() << "   1.Отправляем запрос с сообщением";

    QString SendMessageUrl =  QString("https://moodle.surgu.ru/lib/ajax/service.php?sesskey=%1&info=core_message_send_messages_to_conversation").arg(current_account.GetSessKey());


    QJsonArray messages   {
      QJsonObject{{"text", Text}},
    };

    QJsonObject args;
    args["conversationid"] = Addressee.GetId();
    args["messages"] = messages;

    QJsonArray finalData   {
      QJsonObject{{"index", "0"},{"methodname", "core_message_send_messages_to_conversation"}, {"args",args}},
    };


    QJsonDocument doc(finalData);
    QByteArray data = doc.toJson();
    qDebug() << "Send message data: " << data << "\n";

    if(!CreatePostWaitiedResponse(SendMessageUrl,data,&pars))
    {
        qDebug() << "Ошибка отправки сообщения. Проверте подключение к сети";
        return;
    }


    qDebug() << "   2.Проверяем корректность ответа";

    if(!pars.contains("{\"error\":false"))
    {
        QString error_text;
        qDebug() << "Ответ на запрос пришел с ошибкой.";

        if(ParsString("\"error\":\"([^\"]+)\",",pars,error_text))
            qDebug() << error_text;

        return;
    }
}

void MoodleNetworkManager::DeleteMessage(Message& DeletedMessage)
{
    if(!isGoodAuthorisation)
    {
       qDebug() << "Ошибка авторизации. Войдите в свой аккаунт";
       return;
    }

    QByteArray pars;

    qDebug() << "   1.Отправляем запрос на удаление сообщения";

    QString DeleteMessageUrl =  QString("https://moodle.surgu.ru/lib/ajax/service.php?sesskey=%1&info=core_message_delete_message").arg(current_account.GetSessKey());
    QString DeleteMessageData = QString("[{\"index\":0,\"methodname\":\"core_message_delete_message\",\"args\":{\"messageid\":%1,\"userid\":%2}}]").arg(DeletedMessage.GetId()).arg(current_account.GetId());

    if(!CreatePostWaitiedResponse(DeleteMessageUrl,DeleteMessageData,&pars))
    {
        qDebug() << "Ошибка отправки сообщения. Проверте подключение к сети";
        return;
    }


    qDebug() << "   2.Проверяем корректность ответа";

    if(!pars.contains("{\"error\":false"))
    {
        QString error_text;
        qDebug() << "Ответ на запрос пришел с ошибкой.";

        if(ParsString("\"error\":\"([^\"]+)\",",pars,error_text))
            qDebug() << error_text;

        return;
    }
}


void MoodleNetworkManager::DeleteMessage(int MessageId)
{
    if(!isGoodAuthorisation)
    {
       qDebug() << "Ошибка авторизации. Войдите в свой аккаунт";
       return;
    }

    QByteArray pars;

    qDebug() << "   1.Отправляем запрос на удаление сообщения";

    QString DeleteMessageUrl =  QString("https://moodle.surgu.ru/lib/ajax/service.php?sesskey=%1&info=core_message_delete_message").arg(current_account.GetSessKey());
    QString DeleteMessageData = QString("[{\"index\":0,\"methodname\":\"core_message_delete_message\",\"args\":{\"messageid\":%1,\"userid\":%2}}]").arg(MessageId).arg(current_account.GetId());

    if(!CreatePostWaitiedResponse(DeleteMessageUrl,DeleteMessageData,&pars))
    {
        qDebug() << "Ошибка отправки сообщения. Проверте подключение к сети";
        return;
    }


    qDebug() << "   2.Проверяем корректность ответа";

    if(!pars.contains("{\"error\":false"))
    {
        QString error_text;
        qDebug() << "Ответ на запрос пришел с ошибкой.";

        if(ParsString("\"error\":\"([^\"]+)\",",pars,error_text))
            qDebug() << error_text;

        return;
    }
}

void MoodleNetworkManager::LogOut()
{
    QByteArray pars;
    if(!isGoodAuthorisation)
    {
        qDebug() << "Вы не авторизированы. Ошибка выхода";
        return;
    }

    QString LogOutUrl = QString("https://moodle.surgu.ru/login/logout.php?sesskey=%1").arg(current_account.GetSessKey());

    if(!CreateGetWaitiedResponse(LogOutUrl,&pars))
    {
        qDebug() << "Ошибка получения страницы деавторизации. Проверьте подключение к сети";
        return;
    }
    if(!CreateGetWaitiedResponse("https://moodle.surgu.ru",&pars))
    {
        qDebug() << "Ошибка получения страницы деавторизации. Проверьте подключение к сети";
        return;
    }

    isGoodAuthorisation = false;
}
