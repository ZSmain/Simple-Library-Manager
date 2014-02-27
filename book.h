#ifndef BOOK_H
#define BOOK_H

#include <QFile>

class Book
{
public:
    Book();

    void addBook( QString index, QString title, QString author );
    void modifyBook( QString index );
    void removeBook( QString index);
    void addBookBorrower(QString bookIndex, QString borrowerIndex);
    void removeBookBorrower( QString bookIndex );

    void setBookIndex( QString index ){
        bookIndex = index;
    }
    void setBookTitle( QString title ){
        bookTitle = title;
    }
    void setBookAuthor( QString author ){
        bookAuthor = author;
    }
    void setBookBorrower( QString borrower ){
        bookBorrower = borrower;
    }

    QString getBookIndex(){     return bookIndex;       }
    QString getBookTitle(){     return bookTitle;       }
    QString getBookAuthor(){    return bookAuthor;      }
    QString getBookBorrower(){  return bookBorrower;    }

    void setTempBookIndex( QString index ){
        tempBookIndex = index;
    }
    void setTempBookTitle( QString title ){
        tempBookTitle = title;
    }
    void setTempBookAuthor( QString author ){
        tempBookAuthor = author;
    }
    void setTempBookBorrower( QString borrower ){
        tempBookBorrower = borrower;
    }

    QString getTempBookIndex(){     return tempBookIndex;       }
    QString getTempBookTitle(){     return tempBookTitle;       }
    QString getTempBookAuthor(){    return tempBookAuthor;      }
    QString getTempBookBorrower(){  return tempBookBorrower;    }

    bool findIndex( QString index );

    QString extractIndexLine(QString index );

    void extractInformation( QString index );

    void updateFile( QStringList text );

    QString alphabeticalFileArraning();
    QString lineWithMovedIndex( QString line );

    QString borrowedBooksList();
    bool isBorrowed( QString line );

private:
    QString bookIndex;
    QString bookTitle;
    QString bookAuthor;
    QString bookBorrower;

    QString tempBookIndex;
    QString tempBookTitle;
    QString tempBookAuthor;
    QString tempBookBorrower;

    QString const booksFile = "Books.txt";
};

#endif // BOOK_H
