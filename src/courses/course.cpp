#include "course.h"

Course::Course(QObject *parent)
    : QObject{parent}
{

}

int Course::getId() const
{
    return id;
}

void Course::setId(int newId)
{
    id = newId;
}

const QString &Course::getShortName() const
{
    return shortName;
}

void Course::setShortName(const QString &newShortName)
{
    shortName = newShortName;
}

const QImage &Course::getCourseImage() const
{
    return courseImage;
}

void Course::setCourseImage(const QImage &newCourseImage)
{
    courseImage = newCourseImage;
}

const QString &Course::getURL() const
{
    return URL;
}

void Course::setURL(const QString &newURL)
{
    URL = newURL;
}

const QString &Course::getFullName() const
{
    return fullName;
}

void Course::setFullName(const QString &newFullName)
{
    fullName = newFullName;
}
