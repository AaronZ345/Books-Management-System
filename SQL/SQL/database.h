#ifndef DATABASE_H
#define DATABASE_H


#include <QObject>
#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVector>
#include <QtSql>
#include <QIcon>
#include <QImageReader>
#include <QMovie>
#include <QWidget>
#include <QTabWidget>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QComboBox>
#include <QPalette>
#include <QDir>
#include <QFileDialog>
#include <QIODevice>
#include <QList>
#include <QCheckBox>
#include <QTimer>
#include <QImage>
#include <QScrollArea>
#include <QMessageBox>
#include <QLineEdit>
#include <QDebug>
#include <QPixmap>
#include <QStringList>
#include <QHeaderView>
#include <QCryptographicHash>
#include <QDateTime>
#include <algorithm>
#include <QFileDialog>
#include <QCommandLinkButton>
#include <QDesktopServices>
#include <QToolButton>
#include <QApplication>
#include <QFont>

using namespace std;


class Database : public QObject{
    Q_OBJECT

public:
    Database(QObject *parent = 0);
    virtual ~Database();

private:
    enum {GRANT, RELEASE};
    enum {BORROW, RETURN};
    enum {BORROWABLE, BORROWED};
    enum {USER, MANAGER, TOURIST, NEWUSER};
    int borrowBookNum;
    int returnBookNum;
    QCheckBox *allBooks[50];
    QCheckBox *borrowedBooks[3];
    int allBooksMark[50];
    int borrowedBooksMark[3];
    QString msgManageUser;
    int selectedUsers[1000];
    bool ifCanDeleteUser;

    //interfaces
    QWidget *mainWindow;
    QTabWidget *loginWindow; //interface of login users or managers
    QWidget *registerWindow; //interface of register for new users
    QTabWidget *mainTabWidget;
    QWidget *AboutWidget; //interface of About information
    QWidget *SearchWidget; //interface of seraching for books interace
    QWidget *userReturnWidget;
    QWidget *ManageUserWidget; //interface to manage users
    QWidget *manageBookWidget; //interface to manage books
    QWidget *manageMultiBookWidget; //book batch storage
    QWidget *searchUserWidget;

    //managers seachers needed information
    QLineEdit *ManageUserNameText;
    QLineEdit *ManageUserAuthority;

    //manager intereface widgets
    QTableWidget *manageUser;
    QTableWidget *manageBook;
    QTableWidget *manageMultiBook;

    //database connection
    QSqlDatabase DB;

    //information field widgets and labels
    QWidget *titleImage;
    QLabel *userType;
    QLabel *showTime;
    QPushButton *loginButton;
    QPushButton *registerButton;
    QPushButton *quitButton;

    //login_name and password
    QLineEdit *regisNameText;
    QLineEdit *regisPassText;
    QLineEdit *regisRepeatPassText;
    QLineEdit *loginAccountText;
    QLineEdit *loginUserPassText;
    QLineEdit *loginManageAccountText;
    QLineEdit *loginManagePassText;

    //books information
    QLineEdit *ISBNText;
    QLineEdit *bookNameText;
    QLineEdit *authorText;
    QComboBox *bookTypeText;
    QComboBox *publishDateText;
    QLineEdit *publisherText;
    QTableWidget *borrowableBookTable;
    QTableWidget *borrowedBookTable;

    //layouts of interfaces
    QVBoxLayout *verticalLayoutMain;
    QVBoxLayout *verticalLayoutInfor;
    QHBoxLayout *horizontalLayout;

    bool connectDB(); //function of connection to database
    void initMainWindow();
    void setMainTabWidget(int type); //set the main window referring to user types
    void setAboutWidget();
    void setTableWidget(QTableWidget *table);
    QWidget *createLoginWindow(int type);
    void setSearchWidget(bool type);
    void setUserReturnWidget();
    void setManageUserWidget();
    void initInfor();
    void updateBorrowedBooks();
    QCheckBox *setCheckBox(QString text, int type, int row);
    void updateManageUser();
    void updateManageBook();
    void clearTableWidget(QTableWidget *table);
    void recordSelectedUsers();
    void grantOrRelease(bool type);
    void setMultiBookWidget();

signals:
    void WindowClosed();

//slot functions to About the UI
private slots:
    void updateTime();
    void setLoginWindow();
    void setRegisterWindow();
    void registerRequest();
    void registerCancel();
    void loginCancel();
    void loginUser();
    void loginManager();
    void showBorrowableBooks();
    void BorrowBook();
    void ReturnBook();
    void quitRegister();
    void judgeBorrowable();
    void judgeReturned();
    void showMSearchWindow();
    void quitManageUser();
    void searchManageUser();
    void showAskDeleteUserWindow();
    void DeleteUser();
    void grantUser();
    void releaseUserAuthority();
    void insertBooks();
    void showManageBooks();
    void linkToZJU();
    void linkToHZ();
    void linkToZJ();
    void linkToCN();
    void insertMultiBooks();
    void readFileBooks();
};

#endif // DATABASE_H
