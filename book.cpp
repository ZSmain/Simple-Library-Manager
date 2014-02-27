#include "book.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

Book::Book()
{
}

void Book::addBook(QString index, QString title, QString author)
{
    if( !findIndex( index ) )
    {
        QFile file( booksFile );

        if (!file.open(QFile::Append | QFile::Text))
        {
            QWidget *parent = new QWidget;
            QMessageBox::warning(parent,"Warning!", "Cannot open Books.txt!");
        }
        QTextStream out(&file);
        out << index << ';' << title << ';' << author << ';' << '0' << '\n';

        file.flush();
        file.close();
    }
    else
    {
        QWidget *parent = new QWidget;
        QMessageBox::warning(parent,"Warning!", "Book already exist!");
    }
}

void Book::modifyBook(QString index)
{
    QFile file( booksFile );

    // Geting the information (coping from the file)
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QWidget *parent = new QWidget;
        QMessageBox::warning(parent,"Cannot open the file!", "Error: Cannot open the file to read the information!");
    }
    QTextStream in(&file);

    QStringList allLines;

    while (!in.atEnd())
    {
        allLines.append( in.readLine() );
    }

    file.flush();
    file.close();

    extractInformation( index );

    QString line = getBookIndex() + ';'
            + getBookTitle() + ';'
            + getBookAuthor() + ';'
            + getBookBorrower();

    QString replaceLine = getTempBookIndex() + ';'
            + getTempBookTitle() + ';'
            + getTempBookAuthor() + ';'
            + getTempBookBorrower();

    for( int i = 0; i < allLines.length(); i++ )
    {
        if( allLines[i] == line)
        {
            allLines[i].clear();
            allLines[i].resize( replaceLine.length() );

            allLines[i] = replaceLine;
            break;
        }
    }

    // Updating the information (update the file)
    updateFile( allLines );

    file.flush();
    file.close();
}

void Book::removeBook(QString index)
{
    QFile file( booksFile );

    // Geting the information (coping from the file)
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QWidget *parent = new QWidget;
        QMessageBox::warning(parent,"Cannot open the file!", "Error: Cannot open the file to read the information!");
    }
    QTextStream in(&file);

    QStringList allLines;

    while (!in.atEnd())
    {
        allLines.append( in.readLine() );
    }

    file.flush();
    file.close();

    extractInformation( index );

    QString line = getBookIndex() + ';'
            + getBookTitle() + ';'
            + getBookAuthor() + ';'
            + getBookBorrower();

    QStringList strList;
    for( int i = 0; i < allLines.length(); i++ )
    {
        if( allLines[i] != line)
        {
            strList.append( allLines[i] );
        }
    }

    // Updating the information (update the file)
    updateFile( strList );

    file.flush();
    file.close();
}

void Book::addBookBorrower( QString bookIndex, QString borrowerIndex)
{
    extractInformation( bookIndex );

    setTempBookIndex( getBookIndex() );
    setTempBookTitle( getBookTitle() );
    setTempBookAuthor( getBookAuthor() );
    setTempBookBorrower( borrowerIndex );

    modifyBook( bookIndex );
}

void Book::removeBookBorrower( QString bookIndex )
{
    extractInformation( bookIndex );

    setTempBookIndex( getBookIndex() );
    setTempBookTitle( getBookTitle() );
    setTempBookAuthor( getBookAuthor() );
    setTempBookBorrower( "0" );

    modifyBook( bookIndex );
}


bool Book::findIndex(QString index)
{
    QFile file( booksFile );

    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QWidget *parent = new QWidget;
        QMessageBox::warning(parent,"Cannot open the file!", "Error: Cannot open the file to read the information!");
    }
    QTextStream in(&file);

    bool findIt = false;

    while ( !in.atEnd())
    {
        QString line = in.readLine();
        QString str = "";

        for ( int i = 0; i < line.length(); i++ )
        {
            if( line[i] != ';' )
            {
                str +=  line[i];
            }
            else {  break;  }
        }
        if ( str == index )
        {
            findIt = true;
            break;
        }
    }
    file.flush();
    file.close();

    return findIt;
}

QString Book::extractIndexLine(QString index)
{
    QFile file( booksFile );

    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QWidget *parent = new QWidget;
        QMessageBox::warning(parent,"Cannot open the file!", "Error: Cannot open the file to read the information!");
    }
    QTextStream in(&file);
    bool findIt = false;
    QString extractedLine = "";

    while ( !in.atEnd())
    {
        QString line = in.readLine();
        QString str = "";

        for ( int i = 0; i < line.length(); i++ )
        {
            if( line[i] != ';' )
            {
                str +=  line[i];
            }
            else {  break;  }
        }
        if ( str == index )
        {
            extractedLine = line;
            findIt = true;
            break;
        }
    }

    file.flush();
    file.close();

    if ( findIt == false )
    {

    }
    else
    {
        return extractedLine;
    }
}

void Book::extractInformation(QString index)
{
    QString line = extractIndexLine( index );
    int semicolonCount = 0;
    int semicolonIndex = 0;

    QString title = "";
    QString author = "";
    QString borrowerIndex = "";

    for ( int i = 0; i < line.length(); i++ )
    {
        if( line[i] == ';' )
        {
            semicolonCount++;
            semicolonIndex = i;

            if( semicolonCount == 1 )
            {
                for(int i = semicolonIndex+1; line[i] != ';'; i++)
                {
                    if( line[i] != ';' )
                    {
                        title += line[i];
                    }
                }
            }
            else if( semicolonCount == 2 )
            {
                for(int i = semicolonIndex+1; line[i] != ';'; i++)
                {
                    if( line[i] != ';' )
                    {
                        author += line[i];
                    }
                }
            }
            else
            {
                for(int i = semicolonIndex+1; i < line.length(); i++)
                {
                    borrowerIndex += line[i];
                }
            }
        }
    }

    setBookIndex( index );
    setBookTitle( title );
    setBookAuthor( author );
    setBookBorrower( borrowerIndex );
}

void Book::updateFile(QStringList text)
{
    QFile file( booksFile );

    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
        QWidget *parent = new QWidget;
        QMessageBox::warning(parent,"Cannot open the file!", "Error: Cannot open the file to update the information!");
    }
    QTextStream out(&file);

    for ( int i = 0; i < text.length(); i++ )
    {
        out << text[i] << '\n';
    }

    file.flush();
    file.close();
}

QString Book::alphabeticalFileArraning()
{
    QFile file( booksFile );

    // Geting the information (coping from the file)
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QWidget *parent = new QWidget;
        QMessageBox::warning(parent,"Cannot open the file!", "Error: Cannot open the file to read the information!");
    }
    QTextStream in(&file);

    QStringList allLines;

    while (!in.atEnd())
    {
        allLines.append( in.readLine() );
    }

    for ( int i = 0; i < allLines.length(); i++ )
    {
        allLines[i] = lineWithMovedIndex( allLines[i] );
    }

    allLines.sort();

    file.flush();
    file.close();

    QString str;
    for ( int i = 0; i < allLines.length(); i++ )
    {
        str += allLines[i] + '\n';
    }

    return str;
}

QString Book::lineWithMovedIndex(QString line)
{
    QString indexStr = "";
    for( int i = 0; line[i] != ';'; i++ )
    {
        indexStr += line[i];
    }

    extractInformation( indexStr );

    indexStr = getBookIndex();
    QString titleStr = getBookTitle();
    QString authorStr = getBookAuthor();
    QString borrowerStr = getBookBorrower();

    return titleStr + ';'
            + authorStr + ';'
            + indexStr + ';'
            + borrowerStr;
}

QString Book::borrowedBooksList()
{
    QFile file( booksFile );

    // Geting the information (coping from the file)
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QWidget *parent = new QWidget;
        QMessageBox::warning(parent,"Cannot open the file!", "Error: Cannot open the file to read the information!");
    }
    QTextStream in(&file);

    QStringList allLines;
    QStringList borrowedBooks;

    while (!in.atEnd())
    {
        allLines.append( in.readLine() );
    }

    for ( int i = 0; i < allLines.length(); i++ )
    {
        if ( isBorrowed( allLines[i] )) // ---------------->
        {
            borrowedBooks.append( allLines[i] );
        }
    }

    file.flush();
    file.close();

    QString str;
    for ( int i = 0; i < borrowedBooks.length(); i++ )
    {
        str += borrowedBooks[i] + '\n';
    }

    return str;
}

bool Book::isBorrowed( QString line )
{
    QString index = "";

    for( int i = 0; line[i] != ';'; i++ )
    {
        index += line[i];
    }

    extractInformation( index );

    if ( getBookBorrower() != "0")
    {
        return true;
    }
    else
    {
        return false;
    }
}
