#ifndef MEMBER_H
#define MEMBER_H

#include <QFile>

class Member
{
public:
    Member();

    void addMember( QString index, QString firstName, QString lastName);
    void modifyMember(QString index);
    void removeMember(QString index );
    void memberBorrowBook( QString index );
    void incDecBorrowingNumber( bool incDec, QString index );

    void setMemberIndex( QString index ){
        memberIndex = index;
    }

    void setMemberFirstName( QString firstName ){
        memberFirstName = firstName;
    }

    void setMemberLastName( QString lastName){
        memberLastName = lastName;
    }

    void setMemberBorrowingNumber( QString borrowingNumber){
        memberBorrowingNumber = borrowingNumber;
    }

    QString getIndex(){ return memberIndex; }
    QString getFirstName(){ return memberFirstName; }
    QString getLastName(){ return memberLastName; }
    QString getBorrowingNumber(){ return memberBorrowingNumber; }

    void setTempIndex( QString index ){
        tempIndex = index;
    }

    void setTempFirstName( QString firstName ){
        tempFirstName = firstName;
    }

    void setTempLastName( QString lastName){
        tempLastName = lastName;
    }

    void setTempBorrowingNumber( QString borrowingNumber){
        tempBorrowingNumber = borrowingNumber;
    }

    QString getTempIndex(){ return tempIndex; }
    QString getTempFirstName(){ return tempFirstName; }
    QString getTempLastName(){ return tempLastName; }
    QString getTempBorrowingNumber(){ return tempBorrowingNumber; }

    bool findIndex( QString index );

    QString extractIndexLine(QString index );

    void extractInformation( QString index );

    void updateFile( QStringList text );

    QString alphabeticalFileArraning();
    QString lineWithMovedIndex( QString line );

    QString borrowersList();
    bool isBorrower( QString line );

private:
    QString memberIndex;
    QString memberFirstName;
    QString memberLastName;
    QString memberBorrowingNumber;

    QString tempIndex;
    QString tempFirstName;
    QString tempLastName;
    QString tempBorrowingNumber;

    QString const membersFile = "Members.txt";

};

#endif // MEMBER_H
