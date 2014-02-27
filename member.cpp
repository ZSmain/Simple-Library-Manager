#include "member.h"
#include "mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>


Member::Member()
{
}

void Member::addMember(QString index, QString firstName, QString lastName)
{
    if( !findIndex( index ) )
    {
        QFile file( membersFile );

        if (!file.open(QFile::Append | QFile::Text))
        {
            QWidget *parent = new QWidget;
            QMessageBox::warning(parent,"Warning", "Cannot open members.txt!");
        }
        QTextStream out(&file);
        out << index << ';' << firstName << ';' << lastName << ';' << '0' << '\n';

        file.flush();
        file.close();
    }
    else
    {
        QWidget *parent = new QWidget;
        QMessageBox::warning(parent,"Warning", "Member already exist!");
    }

}

void Member::modifyMember(QString index )
{
    QFile file( membersFile );

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

    QString line = getIndex() + ';'
            + getFirstName() + ';'
            + getLastName() + ';'
            + getBorrowingNumber();

    QString replaceLine = getTempIndex() + ';'
            + getTempFirstName() + ';'
            + getTempLastName() + ';'
            + getTempBorrowingNumber();

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

void Member::removeMember(QString index)
{
    QFile file( membersFile );

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

    QString line = getIndex() + ';'
            + getFirstName() + ';'
            + getLastName() + ';'
            + getBorrowingNumber();

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

void Member::memberBorrowBook(QString index)
{
}

void Member::incDecBorrowingNumber(bool incDec , QString index)
{
    extractInformation( index );

    QString str = getBorrowingNumber();

    int number = str.toInt();

    if (incDec == true )
    {
        number++;

        str = str.number( number, 10);

        setTempIndex( getIndex());
        setTempFirstName( getFirstName() );
        setTempLastName( getLastName() );
        setTempBorrowingNumber( str );

        modifyMember( index );
    }
    else
    {
        number--;

        str = str.number( number, 10);

        setTempIndex( getIndex());
        setTempFirstName( getFirstName() );
        setTempLastName( getLastName() );
        setTempBorrowingNumber( str );

        modifyMember( index );
    }
}

QString Member::extractIndexLine(QString index)
{
    QFile file( membersFile );

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

void Member::extractInformation(QString index)
{
    QString line = extractIndexLine( index );
    int semicolonCount = 0;
    int semicolonIndex = 0;

    QString firstName = "";
    QString lastName = "";
    QString borrowingNumber = "";

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
                        firstName += line[i];
                    }
                }
            }
            else if( semicolonCount == 2 )
            {
                for(int i = semicolonIndex+1; line[i] != ';'; i++)
                {
                    if( line[i] != ';' )
                    {
                        lastName += line[i];
                    }
                }
            }
            else
            {
                for(int i = semicolonIndex+1; i < line.length(); i++)
                {
                    borrowingNumber += line[i];
                }
            }
        }
    }

    setMemberIndex( index );
    setMemberFirstName( firstName );
    setMemberLastName( lastName );
    setMemberBorrowingNumber( borrowingNumber );
}

bool Member::findIndex(QString index)
{
    QFile file( membersFile );

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

void Member::updateFile(QStringList text)
{
    QFile file( membersFile );

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

QString Member::alphabeticalFileArraning()
{
    QFile file( membersFile );

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

QString Member::lineWithMovedIndex(QString line)
{
    QString indexStr = "";
    for( int i = 0; line[i] != ';'; i++ )
    {
        indexStr += line[i];
    }

    extractInformation( indexStr );

    indexStr = getIndex();
    QString firstNameStr = getFirstName();
    QString lastNameStr = getLastName();
    QString borrowingNumberStr = getBorrowingNumber();

    return firstNameStr + ';'
            + lastNameStr + ';'
            + indexStr + ';'
            + borrowingNumberStr;
}

QString Member::borrowersList()
{
    QFile file( membersFile );

    // Geting the information (coping from the file)
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QWidget *parent = new QWidget;
        QMessageBox::warning(parent,"Cannot open the file!", "Error: Cannot open the file to read the information!");
    }
    QTextStream in(&file);

    QStringList allLines;
    QStringList borrowers;

    while (!in.atEnd())
    {
        allLines.append( in.readLine() );
    }

    for ( int i = 0; i < allLines.length(); i++ )
    {
        if ( isBorrower( allLines[i] ) )
        {
            borrowers.append( allLines[i] );
        }
    }

    file.flush();
    file.close();

    QString str;
    for ( int i = 0; i < borrowers.length(); i++ )
    {
        str += borrowers[i] + '\n';
    }

    return str;
}

bool Member::isBorrower( QString line )
{
    QString index = "";

    for( int i = 0; line[i] != ';'; i++ )
    {
        index += line[i];
    }

    extractInformation( index );

    if ( getBorrowingNumber() != "0")
    {
        return true;
    }
    else
    {
        return false;
    }
}
