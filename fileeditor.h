#ifndef FILEEDITOR_H
#define FILEEDITOR_H

#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QStringList>

class FileEditor : public QObject
{
    Q_OBJECT
public:
    FileEditor();
    FileEditor(QString WORKING_DIR);

    QString WORKING_DIR = "";

    bool selectFile(QFile *file);
    bool selectFile(QString filepath);

    bool createFile(QString filepath);
    bool deleteFile();
    void findAndReplace(QString toFind, QString toReplaceWith);
    QStringList findLines(QString containingString);

    bool selectedFileExists();

private:
    QFile *file = NULL;

public slots:

};

#endif // FILEEDITOR_H
