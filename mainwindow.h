#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>

#include "member.h"
#include "book.h"
#include "aboutdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_addMemberPB_clicked();

    void on_indexModifyMember_editingFinished();

    void on_indexDeleteMember_editingFinished();

    void on_modifyMemberPB_clicked();

    void on_deleteMemberPB_clicked();

    void on_addBookPB_clicked();

    void on_indexModifyBook_editingFinished();

    void on_indexDeleteBook_editingFinished();

    void on_modifyBookPB_clicked();

    void on_deleteBookPB_clicked();

    void on_viewMembersPB_clicked();

    void on_viewBooksPB_clicked();

    void on_action_Quit_triggered();

    void on_action_About_triggered();

    void on_indexBorrowBook_editingFinished();

    void on_indexGiveBackBook_editingFinished();

    void on_borrowPB_clicked();

    void on_indexBorrowMember_editingFinished();

    void on_giveBackPB_clicked();

    void on_viewBorrowedBooksPB_clicked();

    void on_viewBorrowersPB_clicked();

private:
    Ui::MainWindow *ui;
    AboutDialog *aboutDialog;

    Member memberObj;
    Book bookObj;

};

#endif // MAINWINDOW_H
