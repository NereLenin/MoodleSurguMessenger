#ifndef COURSE_H
#define COURSE_H

#include <QObject>
#include <QImage>

class Course : public QObject
{
    Q_OBJECT
private:
    int id;
    QString fullName;
    QString shortName;

    QImage courseImage;
    QString URL;
public:
    explicit Course(QObject *parent = nullptr);

    int getId() const;
    void setId(int newId);

    const QString &getFullName() const;
    void setFullName(const QString &newFullName);

     const QString &getShortName() const;
    void setShortName(const QString &newShortName);

    const QImage &getCourseImage() const;
    void setCourseImage(const QImage &newCourseImage);

    const QString &getURL() const;
    void setURL(const QString &newURL);

signals:

};

#endif // COURSE_H
