#include "fileeditor.h"

FileEditor::FileEditor()
{

}


FileEditor::FileEditor(QString WORKING_DIR)
{
    this->WORKING_DIR = WORKING_DIR;
}

bool FileEditor::selectedFileExists(){
    if(this->file != NULL){
        if(this->file->exists()){
            return true;
        }
    }

    return false;
}

bool FileEditor::selectFile(QFile *file){
    if(file->exists()){
        this->file = file;
        return true;
    }

    return false;
}

bool FileEditor::selectFile(QString filepath){
    QFile *file = new QFile(WORKING_DIR + filepath);
    return selectFile(file);
}

bool FileEditor::deleteFile(){
   return file->remove();
}

bool FileEditor::createFile(QString filepath){
    file = new QFile(filepath);
    bool result;

    result = file->open(QIODevice::ReadWrite);
    file->close();

    return result;
}

void FileEditor::findAndReplace(QString toFind, QString toReplaceWith){
    if(selectedFileExists()){
        if (file->open(QIODevice::ReadWrite)){
            QString name = file->fileName();
            QFile *temp = new QFile(name + "_temp");
            temp->open(QIODevice::ReadWrite | QIODevice::Text);

            QTextStream in(file);
            QTextStream out(temp);

            while (!in.atEnd())
            {
                QString line = in.readLine();
                line.replace(toFind, toReplaceWith);

                out << line << endl;
            }

            temp->flush();

            deleteFile();
            temp->rename(name);

            file = temp;
            file->close();
        }
    }
}

QStringList FileEditor::findLines(QString containingString){
    QStringList *result = new QStringList();

    if(selectedFileExists()){
        if (file->open(QIODevice::ReadWrite)){
            QTextStream in(file);
            while (!in.atEnd())
            {
                QString line = in.readLine();
                if(line.contains(containingString)){
                    result->append(line);
                }
            }
            file->close();
        }
    }

    return *result;
}
