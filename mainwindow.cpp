#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "member.h"
#include "book.h"
#include "aboutdialog.h"
#include <QMessageBox>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Simple Library Manager V1.0");
    this->setFixedSize(680, 424);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addMemberPB_clicked()
{
    memberObj.addMember(ui->indexAdd->text(),
                      ui->memberFirstNameAdd->text(),
                      ui->memberLastNameAdd->text());
}

void MainWindow::on_indexModifyMember_editingFinished()
{
    memberObj.extractInformation( ui->indexModifyMember->text() );

    ui->memberFirstNameModify->setText( memberObj.getFirstName() );
    ui->memberLastNameModify->setText( memberObj.getLastName() );
    ui->memberBorrowingModifyMember->setText( memberObj.getBorrowingNumber() );
}

void MainWindow::on_indexDeleteMember_editingFinished()
{
    memberObj.extractInformation( ui->indexDeleteMember->text() );

    ui->memberFirstNameDelete->setText( memberObj.getFirstName() );
    ui->memberLastNameDelete->setText( memberObj.getLastName() );
    ui->memberBorrowingDeleteMember->setText( memberObj.getBorrowingNumber() );
}

void MainWindow::on_modifyMemberPB_clicked()
{
    memberObj.setTempIndex( ui->indexModifyMember_2->text() );
    memberObj.setTempFirstName( ui->memberFirstNameModify_2->text() );
    memberObj.setTempLastName( ui->memberLastNameModify_2->text() );
    memberObj.setTempBorrowingNumber( ui->memberBorrowingModifyMember_2->text() );

    on_indexModifyMember_editingFinished();
    memberObj.modifyMember( ui->indexModifyMember->text() );
}

void MainWindow::on_deleteMemberPB_clicked()
{
    on_indexDeleteMember_editingFinished();
    memberObj.removeMember( ui->indexDeleteMember->text() );
}

void MainWindow::on_addBookPB_clicked()
{
    bookObj.addBook( ui->indexAddBook->text(),
                     ui->titleAddBook->text(),
                     ui->authorAddBook->text() );
}

void MainWindow::on_indexModifyBook_editingFinished()
{
    bookObj.extractInformation( ui->indexModifyBook->text() );

    ui->titleModifyBook->setText( bookObj.getBookTitle() );
    ui->authorModifyBook->setText( bookObj.getBookAuthor() );
    ui->borrowerModifyBook->setText( bookObj.getBookBorrower() );
}

void MainWindow::on_indexDeleteBook_editingFinished()
{
    bookObj.extractInformation( ui->indexDeleteBook->text() );

    ui->titleDeleteBook->setText( bookObj.getBookTitle() );
    ui->authorDeleteBook->setText( bookObj.getBookAuthor() );
    ui->borrowerDeleteBook->setText( bookObj.getBookBorrower() );
}

void MainWindow::on_modifyBookPB_clicked()
{
    bookObj.setTempBookIndex( ui->indexModifyBook_2->text() );
    bookObj.setTempBookTitle( ui->titleModifyBook_2->text() );
    bookObj.setTempBookAuthor( ui->authorModifyBook_2->text() );
    bookObj.setTempBookBorrower( ui->borrowerModifyBook_2->text() );

    on_indexModifyBook_editingFinished();
    bookObj.modifyBook( ui->indexModifyBook->text() );
}

void MainWindow::on_deleteBookPB_clicked()
{
    on_indexDeleteBook_editingFinished();
    bookObj.removeBook( ui->indexDeleteBook->text() );
}

void MainWindow::on_viewMembersPB_clicked()
{
    ui->membersListView->clear();
    ui->membersListView->appendPlainText( memberObj.alphabeticalFileArraning() );
}

void MainWindow::on_viewBooksPB_clicked()
{
    ui->booksListView->clear();
    ui->booksListView->appendPlainText( bookObj.alphabeticalFileArraning() );
}

void MainWindow::on_action_Quit_triggered()
{
    this->close();
}

void MainWindow::on_action_About_triggered()
{
    aboutDialog = new AboutDialog(this);

    aboutDialog->setModal( true );
    aboutDialog->setWindowTitle("About!");
    aboutDialog->show();

}

void MainWindow::on_indexBorrowBook_editingFinished()
{
    bookObj.extractInformation( ui->indexBorrowBook->text() );

    ui->titleBorrowBook->setText( bookObj.getBookTitle() );
    ui->authorBorrowBook->setText( bookObj.getBookAuthor() );
}

void MainWindow::on_indexGiveBackBook_editingFinished()
{
    bookObj.extractInformation( ui->indexGiveBackBook->text() );

    ui->titleGiveBackBook->setText( bookObj.getBookTitle() );
    ui->authorGiveBackBook->setText( bookObj.getBookAuthor() );

    if( bookObj.getBookBorrower() != 0 )
    {
        ui->indexGiveBackMember->setText( bookObj.getBookBorrower() );

        memberObj.extractInformation( ui->indexGiveBackMember->text() );

        ui->firstNameGiveBackMember->setText( memberObj.getFirstName() );
        ui->lastNameGiveBackMember->setText( memberObj.getLastName() );

    }
    else
    {
        ui->indexGiveBackMember->setText( "" );
    }
}

void MainWindow::on_borrowPB_clicked()
{
    bookObj.extractInformation( ui->indexBorrowBook->text() );

    if ( bookObj.getBookBorrower() == "0" )
    {
        bookObj.addBookBorrower( ui->indexBorrowBook->text(), ui->indexBorrowMember->text() );

        memberObj.incDecBorrowingNumber( true, ui->indexBorrowMember->text());
    }
    else
    {
        QMessageBox::warning(this,"Warning!", "This book is already borrower by anouthor member!");
    }
}

void MainWindow::on_indexBorrowMember_editingFinished()
{
    memberObj.extractInformation( ui->indexBorrowMember->text() );

    ui->firstNameBorrowMember->setText( memberObj.getFirstName() );
    ui->lastNameBorrowMember->setText( memberObj.getLastName() );
}

void MainWindow::on_giveBackPB_clicked()
{
    bookObj.extractInformation( ui->indexGiveBackBook->text() );

    if ( bookObj.getBookBorrower() != "0" )
    {
        bookObj.removeBookBorrower( ui->indexGiveBackBook->text() );

        memberObj.incDecBorrowingNumber( false, ui->indexGiveBackMember->text());
    }
    else
    {
        QMessageBox::warning(this,"Warning!", "This book is not taken by any member!");
    }
}

void MainWindow::on_viewBorrowedBooksPB_clicked()
{
    ui->BorrowedBooksListView->clear();
    ui->BorrowedBooksListView->appendPlainText( bookObj.borrowedBooksList() );
}

void MainWindow::on_viewBorrowersPB_clicked()
{
    ui->BorrowersListView->clear();
    ui->BorrowersListView->appendPlainText( memberObj.borrowersList() );
}
