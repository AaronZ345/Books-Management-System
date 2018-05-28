#include "database.h"


QStringList bookAttrs = {"ISBN", "Book Name", "Author", "Book Type", "Publish Date",
                      "Publisher", "ifBorrowable"};

//construct function
Database::Database(QObject *parent):
    QObject(parent),
    borrowBookNum(0),
    returnBookNum(0),
    mainWindow(nullptr),
    loginWindow(nullptr),
    registerWindow(nullptr),
    mainTabWidget(nullptr),
    SearchWidget(nullptr),
    userReturnWidget(nullptr),
    ManageUserWidget(nullptr),
    manageBookWidget(nullptr),
    msgManageUser("select * from users;"),
    ifCanDeleteUser(1){
    initMainWindow();
    connectDB();

    QSqlQuery query;
    query.exec(msgManageUser);
    qDebug() << query.value(0).toString();
    qDebug() << "start";
}

//destruct function
Database::~Database(){
    //DB.removeDatabase("QMYSQL");
}

//function of connecting to database
bool Database::connectDB(){
    //informatioin of database to connect
    DB = QSqlDatabase::addDatabase("input your database name here");
    DB.setHostName("localhost");
    DB.setDatabaseName("input your database name here");
    DB.setUserName("input your user name here");
    DB.setPassword("input your passwd here");

    if(!DB.open()){
        QMessageBox::critical(nullptr, tr("ERROR WHEN CONNECT DATABASE!"), DB.lastError().text());
        return false;
    }
    return true;
}

//------------------------------------------------------------------------------------------------------------
//-----------------------------------------initiallize the layout---------------------------------------------
void Database::initMainWindow(){
    //initiallize the widgets and labels of window
    userType = new QLabel();
    showTime = new QLabel();
    userType->setFixedSize(100, 40);
    showTime->setFixedSize(240, 40);
    userType->setAlignment(Qt::AlignCenter);
    showTime->setAlignment(Qt::AlignCenter);

    //set the background of top firld
    QPalette background;
    background.setBrush(QPalette::Background, QBrush(QPixmap("./title.JPG")));
    titleImage = new QWidget();
    titleImage->setAutoFillBackground(true);
    titleImage->setPalette(background);
    titleImage->setMinimumHeight(200);

    //set the time with the operating system
    QTimer *timer = new QTimer(this);
    timer->start(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()));

    verticalLayoutMain = new QVBoxLayout();
    verticalLayoutInfor = new QVBoxLayout();
    mainTabWidget = new QTabWidget();
    setMainTabWidget(TOURIST);

    //set the information of top field
    QPalette backText;
    backText.setColor(QPalette::WindowText, Qt::gray);
    QLabel *title = new QLabel("Books Manage System ");
    QLabel *message = new QLabel("Made By Aaron ");
    title->setAlignment(Qt::AlignLeft);
    title->setPalette(backText);
    message->setAlignment(Qt::AlignRight);
    message->setPalette(backText);

    horizontalLayout = new QHBoxLayout();
    horizontalLayout->addStretch();
    horizontalLayout->addWidget(userType);
    horizontalLayout->addWidget(showTime);

    //set the layout of top field
    verticalLayoutInfor->addWidget(title);
    verticalLayoutInfor->addWidget(message);
    verticalLayoutInfor->addLayout(horizontalLayout);
    initInfor();

    //the whole layout
    titleImage->setLayout(verticalLayoutInfor);
    verticalLayoutMain->addWidget(titleImage);
    verticalLayoutMain->addWidget(mainTabWidget);

    //innitialize the main window
    mainWindow = new QWidget();
    mainWindow->resize(960, 640);
    mainWindow->setLayout(verticalLayoutMain);
    mainWindow->setWindowTitle(tr("Book Manage System"));
    mainWindow->setWindowIcon(QIcon("./icon.JPG"));
    mainWindow->show();
}

//function of updating time
void Database::updateTime(){
    QDateTime currentTime = QDateTime::currentDateTime();
    showTime->setText(currentTime.toString("yyyy.MM.dd hh:mm:ss"));
}

//inintialize the information of login and register buttons
void Database::initInfor(){
    loginButton = new QPushButton(tr("Login"));
    registerButton = new QPushButton(tr("Register"));

    loginButton->setFlat(true);
    loginButton->setFixedSize(90, 40);
    registerButton->setFlat(true);
    registerButton->setFixedSize(100, 40);

    horizontalLayout->addWidget(loginButton);
    horizontalLayout->addWidget(registerButton);

    connect(loginButton, SIGNAL(clicked(bool)), this, SLOT(setLoginWindow()));
    connect(registerButton, SIGNAL(clicked(bool)), this, SLOT(setRegisterWindow()));
}

//funciton to set the main window referring to user types
void Database::setMainTabWidget(int type){
    mainTabWidget->clear();
    AboutWidget = new QWidget();
    setAboutWidget();
    if(type == TOURIST){
        userType->setText("Tourist");
        userType->setFixedSize(100, 40);
    }
    else{
        //if login succeed then change the layout
        delete registerButton;
        delete loginButton;
        registerButton = nullptr;
        loginButton = nullptr;

        //add a newbutton of sign out
        quitButton = new QPushButton(tr("Sign Out"));
        quitButton->setFixedSize(100, 40);
        quitButton->setFlat(true);
        horizontalLayout->addWidget(quitButton);

        connect(quitButton, SIGNAL(clicked(bool)), this, SLOT(quitRegister()));

        if(type == MANAGER){
            userType->setText("Manager : " + loginManageAccountText->text());
            userType->setFixedSize(200 + loginManageAccountText->text().length(), 40);

            ManageUserWidget = new QWidget();
            manageBookWidget = new QWidget();
            manageMultiBookWidget = new QWidget();
            setManageUserWidget();
            setSearchWidget(MANAGER);
            setMultiBookWidget();

            mainTabWidget->addTab(ManageUserWidget, tr("Manage users"));
            mainTabWidget->addTab(manageBookWidget, tr("Manage books"));
            mainTabWidget->addTab(manageMultiBookWidget, tr("Bulk Storage"));
        }
        else if(type == USER || type == NEWUSER){
            if(type == USER)
            {
                userType->setText("User : " + loginAccountText->text());
                userType->setFixedSize(200 + loginAccountText->text().length(), 40);
            }
            else if(type == NEWUSER)
            {
                userType->setText("User : " + regisNameText->text());
                userType->setFixedSize(200 + regisNameText->text().length(), 40);
            }

            //return and search interfaces
            SearchWidget = new QWidget();
            userReturnWidget = new QWidget();
            setSearchWidget(USER);
            setUserReturnWidget();

            mainTabWidget->addTab(SearchWidget, tr("Search Books"));
            mainTabWidget->addTab(userReturnWidget, tr("Return Books"));
        }
    }
    mainTabWidget->addTab(AboutWidget, "About");
}

//function to quit register
void Database::quitRegister(){
    //change the layout if quit register
    delete quitButton;
    quitButton = nullptr;

    initInfor();
    setMainTabWidget(TOURIST); //set the user as tourist when quit register
}

//---------------------------------------------------------------------------------------------------------------
//----------------------------------------------show About interface----------------------------------------------

//set About interface
void Database::setAboutWidget(){
    //four buttons to go to four tyes of library
    QCommandLinkButton *linkToZJU = new QCommandLinkButton("ZJU Library");
    linkToZJU->setDescription("Click this button and you can go to the ZJU Libry's websit");
    linkToZJU->setFixedSize(260, 100);
    linkToZJU->setFlat(true);
    linkToZJU->setIcon(QIcon("./images/arrowRight.png"));

    QCommandLinkButton *linkToHZ = new QCommandLinkButton("Hangzhou Library");
    linkToHZ->setDescription("Click this button and you can go to the Hangzhou Libry's websit");
    linkToHZ->setFixedSize(260, 100);
    linkToHZ->setFlat(true);
    linkToHZ->setIcon(QIcon("./images/arrowRight.png"));

    QCommandLinkButton *linkToZJ = new QCommandLinkButton("Zhejiang Library");
    linkToZJ->setDescription("Click this button and you can go to the Zhejiang Libry's websit");
    linkToZJ->setFixedSize(260, 100);
    linkToZJ->setFlat(true);
    linkToZJ->setIcon(QIcon("./images/arrowRight.png"));

    QCommandLinkButton *linkToCN = new QCommandLinkButton("China Library");
    linkToCN->setDescription("Click this button and you can go to the China Libry's websit");
    linkToCN->setFixedSize(260, 100);
    linkToCN->setFlat(true);
    linkToCN->setIcon(QIcon("./images/arrowRight.png"));

    //information of about interface
    QLabel *prompt = new QLabel();
    prompt->setStyleSheet("color:black;font-size:18px;");
    prompt->setText("There is a simple books manage system made by Aaron.\n"
                    "Please login first and then you can enjoy reading.\n"
                    "Also, managers can manage users and books by the system.\n"
                    "If you have no account yet, register first.\n"
                    "By the way, you can search for books available.\n"
                    "In this interface, you can go to four different libraries.\n"
                    );

    QLabel *gifLabel = new QLabel();
    QMovie *movie = new QMovie("./timg.gif");
    movie->setSpeed(100);
    gifLabel->setMovie(movie);
    movie->start();

    //horizontal layout for four buttons
    QHBoxLayout *horizontalLayoutAbout = new QHBoxLayout();
    horizontalLayoutAbout->addWidget(linkToZJU);
    horizontalLayoutAbout->addWidget(linkToHZ);
    horizontalLayoutAbout->addWidget(linkToZJ);
    horizontalLayoutAbout->addWidget(linkToCN);

    //horizontal layout for text and movie
    QHBoxLayout *horizontalLayoutInfo = new QHBoxLayout();
    horizontalLayoutInfo->addWidget(gifLabel);
    horizontalLayoutInfo->addWidget(prompt);

    //virtual layout for information and horizontal layout
    QVBoxLayout *virtualLayoutAbout = new QVBoxLayout();
    virtualLayoutAbout->addLayout(horizontalLayoutInfo);
    virtualLayoutAbout->addLayout(horizontalLayoutAbout);
    AboutWidget->setLayout(virtualLayoutAbout);

    connect(linkToZJU, SIGNAL(clicked(bool)), this, SLOT(linkToZJU()));
    connect(linkToHZ, SIGNAL(clicked(bool)), this, SLOT(linkToHZ()));
    connect(linkToZJ, SIGNAL(clicked(bool)), this, SLOT(linkToZJ()));
    connect(linkToCN, SIGNAL(clicked(bool)), this, SLOT(linkToCN()));
}

//link to zju library
void Database::linkToZJU(){
    QDesktopServices::openUrl(QUrl("http://libweb.zju.edu.cn/libweb/"));
}

//link to hangzhou library
void Database::linkToHZ(){
    QDesktopServices::openUrl(QUrl("http://www.hzlib.net/"));
}

//link to zhejiang library
void Database::linkToZJ(){
    QDesktopServices::openUrl(QUrl("http://www.zjlib.cn/"));
}

//link to china library
void Database::linkToCN(){
    QDesktopServices::openUrl(QUrl("http://www.chnlib.com/"));
}

//---------------------------------------------------------------------------------------------------------------
//--------------------------------------------show login interface-----------------------------------------------

//set the login interface
void Database::setLoginWindow(){
    //these two button can not work when login
    loginButton->setEnabled(false);
    registerButton->setEnabled(false);

    //two windows for users and managers
    loginWindow = new QTabWidget();
    QWidget *userLoginWindow = createLoginWindow(USER);
    QWidget *managerLoginWindow = createLoginWindow(MANAGER);

    loginWindow->addTab(userLoginWindow, tr("As User"));
    loginWindow->addTab(managerLoginWindow, tr("As Manager"));

    loginWindow->setWindowFlags(loginWindow->windowFlags() & ~Qt::WindowCloseButtonHint); //can not use the x when login
    mainWindow->setWindowFlags(mainWindow->windowFlags() & ~Qt::WindowCloseButtonHint);
    loginWindow->setWindowTitle(tr("Login"));
    loginWindow->resize(360, 240);
    loginWindow->setWindowIcon(QIcon("./icon.JPG"));
    mainWindow->show();
    loginWindow->show();
}

//create window for login referring to users
QWidget *Database::createLoginWindow(int type){
    //information for all types users
    QWidget *loginDifferTab = new QWidget();
    QLabel *loginName = new QLabel(tr("Account"));
    QLabel *loginPass = new QLabel(tr("Password"));
    QPushButton *submitButton = new QPushButton(tr("Login"));
    QPushButton *cancelButton = new QPushButton(tr("Cancel"));

    QGridLayout *gridLayoutLogin = new QGridLayout();
    gridLayoutLogin->setColumnStretch(1, 1);
    gridLayoutLogin->setColumnStretch(2, 4);

    gridLayoutLogin->addWidget(loginName, 1, 1);
    gridLayoutLogin->addWidget(loginPass, 2, 1);

    QHBoxLayout *horizontalLayoutLogin = new QHBoxLayout();
    horizontalLayoutLogin->addStretch();
    horizontalLayoutLogin->addWidget(submitButton);
    horizontalLayoutLogin->addStretch();
    horizontalLayoutLogin->addWidget(cancelButton);
    horizontalLayoutLogin->addStretch();

    if(type == USER){
        loginAccountText = new QLineEdit();
        loginUserPassText = new QLineEdit();
        loginUserPassText->setEchoMode(QLineEdit::Password);

        gridLayoutLogin->addWidget(loginAccountText, 1, 2);
        gridLayoutLogin->addWidget(loginUserPassText, 2, 2);
    }
    else if(type == MANAGER){
        loginManageAccountText = new QLineEdit();
        loginManagePassText = new QLineEdit();
        loginManagePassText->setEchoMode(QLineEdit::Password);

        gridLayoutLogin->addWidget(loginManageAccountText, 1, 2);
        gridLayoutLogin->addWidget(loginManagePassText, 2, 2);
    }

    QVBoxLayout *virtualLayoutMain = new QVBoxLayout();
    virtualLayoutMain->addLayout(gridLayoutLogin);
    virtualLayoutMain->addLayout(horizontalLayoutLogin);

    loginDifferTab->setLayout(virtualLayoutMain);

    connect(cancelButton, SIGNAL(clicked(bool)), this, SLOT(loginCancel()));
    if(type == USER){
        connect(submitButton, SIGNAL(clicked(bool)), this, SLOT(loginUser()));
    }
    else if(type == MANAGER){
        connect(submitButton, SIGNAL(clicked(bool)), this, SLOT(loginManager()));
    }

    return loginDifferTab;
}

//cancel login function
void Database::loginCancel(){
    loginWindow->close();

    loginButton->setEnabled(true);
    registerButton->setEnabled(true);
    mainWindow->setWindowFlags(mainWindow->windowFlags() & Qt::WindowCloseButtonHint);
    mainWindow->show();

    delete loginAccountText;
    delete loginUserPassText;
    delete loginManageAccountText;
    delete loginManagePassText;
    loginAccountText = nullptr;
    loginUserPassText = nullptr;
    loginManageAccountText = nullptr;
    loginManagePassText = nullptr;
}

//check the login information
void Database::loginUser(){
    //check if all blank is filled
    if(loginAccountText->text().isEmpty()){
        QMessageBox::warning(nullptr, tr("Incomplete Information!"), tr("Please input account!"));
        return;
    }
    if(loginUserPassText->text().isEmpty()){
        QMessageBox::warning(nullptr, tr("Incomplete Information!"), tr("Please input password!"));
        return;
    }

    //check if the user exists
    QSqlQuery query;
    query.exec("select * from users where username = \"" + loginAccountText->text() + "\";");
    if(!query.next()){
        QMessageBox::warning(nullptr, tr("Login failed!"), tr("Account doesn't exist!"));
        loginAccountText->clear();
        loginUserPassText->clear();
    }
    else{
        //check the password
        if(loginUserPassText->text() != query.value(1).toString()){
            QMessageBox::critical(nullptr, tr("Login failed!"), tr("Wrong Password!"));
            loginUserPassText->clear();
        }
        else{
            //go to user interface
            setMainTabWidget(USER);
            loginWindow->close();
            mainWindow->setWindowFlags(mainWindow->windowFlags() & Qt::WindowCloseButtonHint);
            mainWindow->show();
        }
    }
    return;
}

//check manager information
void Database::loginManager(){
    if(loginManageAccountText->text().isEmpty()){
        QMessageBox::warning(nullptr, tr("Incomplete Information!"), tr("Please input account!"));
        loginManagePassText->clear();
        return;
    }
    if(loginManagePassText->text().isEmpty()){
        QMessageBox::warning(nullptr, tr("Incomplete Information!"), tr("Please input password!"));
        loginManagePassText->clear();
        return;
    }

    QSqlQuery query;
    query.exec("select * from managers where managername = \"" + loginManageAccountText->text() + "\";");
    if(!query.next()){
        QMessageBox::warning(nullptr, tr("Login failed!"), tr("This manager don't exist!"));
        loginManageAccountText->clear();
        loginManagePassText->clear();
    }
    else{
        if(loginManagePassText->text() != query.value(1).toString()){
            QMessageBox::critical(nullptr, tr("Login failed!"), tr("Wrong Password!"));
            loginManagePassText->clear();
        }
        else{
            //go to manager interface
            setMainTabWidget(MANAGER);
            loginWindow->close();
            mainWindow->setWindowFlags(mainWindow->windowFlags() & Qt::WindowCloseButtonHint);
            mainWindow->show();
        }
    }
    return;
}

//-------------------------------------------------------------------------------------------------------------
//----------------------------------------show register interface----------------------------------------------

//register new user
void Database::setRegisterWindow(){
    loginButton->setEnabled(false);
    registerButton->setEnabled(false);

    registerWindow = new QWidget();
    QLabel *userName = new QLabel(tr("Account"));
    QLabel *Password = new QLabel(tr("Password"));
    QLabel *repeatPassword = new QLabel(tr("Repeat Password"));
    QPushButton *submitButton = new QPushButton(tr("Submit"));
    QPushButton *cancelButton = new QPushButton(tr("Cancel"));
    regisNameText = new QLineEdit();
    regisPassText = new QLineEdit();
    regisRepeatPassText = new QLineEdit();

    regisPassText->setEchoMode(QLineEdit::Password);
    regisRepeatPassText->setEchoMode(QLineEdit::Password);

    QGridLayout *gridLayoutRegister = new QGridLayout();
    gridLayoutRegister->setColumnStretch(1, 1);
    gridLayoutRegister->setColumnStretch(2, 4);

    gridLayoutRegister->addWidget(userName, 1, 1, Qt::AlignCenter);
    gridLayoutRegister->addWidget(regisNameText, 1, 2);
    gridLayoutRegister->addWidget(Password, 2, 1, Qt::AlignCenter);
    gridLayoutRegister->addWidget(regisPassText, 2, 2);
    gridLayoutRegister->addWidget(repeatPassword, 3, 1, Qt::AlignCenter);
    gridLayoutRegister->addWidget(regisRepeatPassText, 3, 2);

    QHBoxLayout *horizontalLayoutRegister = new QHBoxLayout();
    horizontalLayoutRegister->addStretch();
    horizontalLayoutRegister->addWidget(submitButton);
    horizontalLayoutRegister->addStretch();
    horizontalLayoutRegister->addWidget(cancelButton);
    horizontalLayoutRegister->addStretch();

    QVBoxLayout *virtualLayoutRegisterMain = new QVBoxLayout();
    virtualLayoutRegisterMain->addLayout(gridLayoutRegister);
    virtualLayoutRegisterMain->addLayout(horizontalLayoutRegister);

    registerWindow->setWindowFlags(registerWindow->windowFlags() & ~Qt::WindowCloseButtonHint);
    mainWindow->setWindowFlags(mainWindow->windowFlags() & ~Qt::WindowCloseButtonHint);
    registerWindow->setLayout(virtualLayoutRegisterMain);
    registerWindow->resize(360, 240);
    registerWindow->setWindowIcon(QIcon("./icon.JPG"));
    mainWindow->show();
    registerWindow->show();

    connect(submitButton, SIGNAL(clicked(bool)), this, SLOT(registerRequest()));
    connect(cancelButton, SIGNAL(clicked(bool)), this, SLOT(registerCancel()));
}

//function to check register information
void Database::registerRequest(){
    if(regisNameText->text().isEmpty()){
        QMessageBox::warning(nullptr, tr("Incomplete Information!"), tr("Please set your nickname!"));
        return;
    }
    if(regisPassText->text().isEmpty()){
        QMessageBox::warning(nullptr, tr("Incomplete Information!"), tr("Please set your password!"));
        return;
    }
    if(regisRepeatPassText->text().isEmpty()){
        QMessageBox::warning(nullptr, tr("Incomplete Information!"), tr("Please repeat your password!"));
        return;
    }
    if(regisPassText->text() != regisRepeatPassText->text()){
        QMessageBox::warning(nullptr, tr("Wrong Information!"), tr("Inconsistent password!"));
        regisRepeatPassText->clear();
        return;
    }

    //check if the user exists
    QSqlQuery query;
    query.exec("select username from users where username = \"" + regisNameText->text() + "\";");
    if(query.next()){
        //the user is registered before
        QMessageBox::warning(nullptr, tr("Registration Failed"), tr("User name have been occupied!"));
        regisNameText->clear();
        regisPassText->clear();
        regisRepeatPassText->clear();
        return;
    }
    else{
        //add the useer information
        query.exec("insert into users values(\"" + regisNameText->text() + "\", \"" + regisPassText->text()+ "\", 0);");
        if(query.isActive()){
            //go to user interface
            QMessageBox::about(nullptr, tr("Registration Success"), tr("You have registered successfully!"));
            setMainTabWidget(NEWUSER);
            registerWindow->close();
            mainWindow->setWindowFlags(mainWindow->windowFlags() & Qt::WindowCloseButtonHint);
            mainWindow->show();
            return;
        }
        else{
            QMessageBox::critical(nullptr, tr("Registration Failed"), tr("Check your information"));
            regisNameText->clear();
            regisPassText->clear();
            regisRepeatPassText->clear();
            return;
        }
    }
}

//cancel register
void Database::registerCancel(){
    registerWindow->close();

    loginButton->setEnabled(true);
    registerButton->setEnabled(true);
    mainWindow->setWindowFlags(mainWindow->windowFlags() & Qt::WindowCloseButtonHint);
    mainWindow->show();

    delete regisNameText;
    delete regisPassText;
    delete regisRepeatPassText;
    regisNameText = nullptr;
    regisPassText = nullptr;
    regisRepeatPassText = nullptr;
}

//--------------------------------------------------------------------------------------------------------------
//-------------------------------------------search for books---------------------------------------------------

//search for books interface
void Database::setSearchWidget(bool type){
    QLabel *ISBN = new QLabel(tr("ISBN"));
    QLabel *bookName = new QLabel(tr("Book Name"));
    QLabel *author = new QLabel(tr("Author"));
    QLabel *bookType = new QLabel(tr("Book Type"));
    QLabel *publishDate = new QLabel(tr("Publish Date"));
    QLabel *publisher = new QLabel(tr("Publisher"));
    QPushButton *searchButton = new QPushButton(tr("Search"));

    ISBN->setFixedSize(90, 40);
    bookName->setMinimumSize(110, 40);
    author->setMinimumSize(74, 40);
    bookType->setMinimumSize(100, 40);
    publishDate->setMinimumSize(120, 40);
    publisher->setMinimumSize(90, 40);

    //attributes of searching
    ISBNText = new QLineEdit();
    bookNameText = new QLineEdit();
    authorText = new QLineEdit();
    bookTypeText = new QComboBox();
    publishDateText = new QComboBox();
    publisherText = new QLineEdit();

    publishDateText->addItem("");
    for(int i = 0; i < 100; i++){
        publishDateText->addItem(QString::number(2018 - i));
    }

    QString bookTypeSet[] = {"", QString::fromUtf8("文学"), QString::fromUtf8("经济"), QString::fromUtf8("数学")};
    for(QString i : bookTypeSet){
        bookTypeText->addItem(i);
    }

    //show books information
    borrowableBookTable = new QTableWidget(0, 7);
    borrowableBookTable->setHorizontalHeaderLabels(bookAttrs);
    setTableWidget(borrowableBookTable);

    QHBoxLayout *horizontalLayout1 = new QHBoxLayout();
    horizontalLayout1->addWidget(ISBN);
    horizontalLayout1->addWidget(ISBNText);
    horizontalLayout1->addSpacing(10);
    horizontalLayout1->addWidget(bookName);
    horizontalLayout1->addWidget(bookNameText);
    horizontalLayout1->addSpacing(10);
    horizontalLayout1->addWidget(author);
    horizontalLayout1->addWidget(authorText);
    horizontalLayout1->addSpacing(10);
    horizontalLayout1->addWidget(publishDate);
    horizontalLayout1->addWidget(publishDateText);

    QHBoxLayout *horizontalLayout2 = new QHBoxLayout();
    horizontalLayout2->addWidget(publisher);
    horizontalLayout2->addWidget(publisherText);
    horizontalLayout2->addSpacing(10);
    horizontalLayout2->addWidget(bookType);
    horizontalLayout2->addWidget(bookTypeText);
    horizontalLayout2->addStretch();

    QVBoxLayout *virtualLayoutSearch = new QVBoxLayout();
    virtualLayoutSearch->addLayout(horizontalLayout1);
    virtualLayoutSearch->addLayout(horizontalLayout2);
    virtualLayoutSearch->addWidget(borrowableBookTable);

    if(type == USER){
        QPushButton *searchBorrow = new QPushButton(tr("Borrow"));
        horizontalLayout2->addWidget(searchButton);
        horizontalLayout2->addStretch();
        horizontalLayout2->addWidget(searchBorrow);
        SearchWidget->setLayout(virtualLayoutSearch);

        connect(searchBorrow, SIGNAL(clicked(bool)), this, SLOT(BorrowBook()));
        connect(searchButton, SIGNAL(clicked(bool)), this, SLOT(showBorrowableBooks()));
    }
    else{
        QPushButton *insertBook = new QPushButton(tr("Insert Books"));
        horizontalLayout2->addWidget(searchButton);
        horizontalLayout2->addStretch();
        horizontalLayout2->addWidget(insertBook);
        manageBookWidget->setLayout(virtualLayoutSearch);
        borrowableBookTable->horizontalHeaderItem(6)->setText("Borrower");

        connect(insertBook, SIGNAL(clicked(bool)), this, SLOT(insertBooks()));
        connect(searchButton, SIGNAL(clicked(bool)), this, SLOT(showManageBooks()));
    }
}

//set information table
void Database::setTableWidget(QTableWidget *table){
    table->setSelectionBehavior(QAbstractItemView::SelectRows);               //choose the whole line
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);                //can not edit
    table->setShowGrid(true);                                                 //choose grid on
    table->setFont(tr("楷体"));                                                //choose font form
    table->horizontalHeader()->setHighlightSections(false);                   //not highlighten the top line
    table->setFrameStyle(QFrame::Box | QFrame::Raised);
    table->setLineWidth(4);
    table->setMidLineWidth(2);
    table->horizontalHeader()->setStretchLastSection(true);
    table->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);          //choose center
    table->horizontalHeader()->setMinimumHeight(45);                          //choose table hight
    table->verticalHeader()->setVisible(false);                               //can not see table virtually
    table->verticalHeader()->setDefaultSectionSize(45);
    table->verticalHeader()->setDefaultAlignment(Qt::AlignCenter);
    table->setFocusPolicy(Qt::NoFocus);                                       //hide the grid when be chosen
    table->horizontalHeader()->setStyleSheet("border:1px solid #aaa;font-size:17px;font-weight:600;color:#677;");
    table->setStyleSheet("QTableWidget::Item:hover{background:#bde;}"
                         "QTableWidget::Item:selected{background:lightgray;");
}

//show books availabel
void Database::showBorrowableBooks(){
    //clear the results last
    borrowBookNum = 0;
    clearTableWidget(borrowableBookTable);
    for(int i = 0; i < 50; allBooks[i++] = nullptr);

    //input at least one key information
    if(authorText->text().isEmpty() && bookNameText->text().isEmpty()
       && publisherText->text().isEmpty() && ISBNText->text().isEmpty()
       && bookTypeText->currentText() == "" && publishDateText->currentText() == ""){
        QMessageBox::warning(nullptr, tr("Incomplete Information!"), tr("Please choose key information"));
        return;
    }

    QSqlQuery query;
    QString constraint;
    if(!ISBNText->text().isEmpty()){
        constraint += "ISBN like \"%" + ISBNText->text() + "%\"";
    }
    if(!authorText->text().isEmpty()){
        if(constraint != ""){
            constraint += " and ";
        }
        constraint += "author like \"%" + authorText->text() + "%\"";
    }
    if(!bookNameText->text().isEmpty()){
        if(constraint != ""){
            constraint += " and ";
        }
        constraint += "bookname like \"%" + bookNameText->text() + "%\"";
    }
    if(!publisherText->text().isEmpty()){
        if(constraint != ""){
            constraint += " and ";
        }
        constraint += "publisher like \"%" + publisherText->text() + "%\"";
    }
    if(bookTypeText->currentText() != ""){
        if(constraint != ""){
            constraint += " and ";
        }
        constraint += "booktype = \"" + bookTypeText->currentText() + "\"";
    }
    if(publishDateText->currentText() != ""){
        if(constraint != ""){
            constraint += " and ";
        }
        constraint += "publishdate = \"" + publishDateText->currentText() + "\"";
    }

    int row = 0;
    query.exec("select * from books where " + constraint + "order by ISBN;");
    while(query.next()){
        borrowableBookTable->insertRow(row);

        for(int column = 0; column < 6; column++){
            QString attr = query.value(column).toString();
            QTableWidgetItem *newItem = new QTableWidgetItem(attr);

            newItem->setFlags(newItem->flags() & ~Qt::ItemIsEditable);
            newItem->setTextAlignment(Qt::AlignCenter);
            borrowableBookTable->setItem(row, column, newItem);
        }

        //find if the book is avaliable
        QSqlQuery newQuery;
        newQuery.exec("select * from users where username =\""
                      + userType->text().replace("User : ", "") + "\";");
        newQuery.next();

        if(query.value("isBorrowed").toInt() == BORROWABLE && newQuery.value("authority").toInt() == 1){
            QCheckBox *ifBorrowable = setCheckBox("Borrowable", BORROW, row);
            allBooks[row] = ifBorrowable;

            connect(ifBorrowable, SIGNAL(clicked(bool)), this, SLOT(judgeBorrowable()));
        }
        else{
            QString msg = newQuery.value("authority").toInt() ? "Have been borrowed" : "You have no permission to borrow books";
            QTableWidgetItem *newItem = new QTableWidgetItem(msg);

            newItem->setFlags(newItem->flags() & ~Qt::ItemIsEditable);
            newItem->setTextAlignment(Qt::AlignCenter);
            borrowableBookTable->setItem(row, 6, newItem);
            borrowableBookTable->setColumnWidth(6, 360);

            allBooks[row] = nullptr;
        }

        row++;
    }
}

void Database::clearTableWidget(QTableWidget *table){
    int rowNum = table->rowCount();
    for(int i = 0; i < rowNum; i++){
        table->removeRow(0);
    }
}

//set the check box type
QCheckBox *Database::setCheckBox(QString text, int type, int row){
    QWidget *newWidget = new QWidget();
    QCheckBox *newChecBox = new QCheckBox();
    QHBoxLayout *horizontalLayoutNew = new QHBoxLayout();

    newChecBox->setText(text);
    horizontalLayoutNew->addWidget(newChecBox);
    horizontalLayoutNew->setAlignment(newChecBox, Qt::AlignCenter);
    newWidget->setLayout(horizontalLayoutNew);

    QTableWidget *temp;
    if(type == BORROW) temp = borrowableBookTable;
    else if(type == RETURN) temp = borrowedBookTable;
    temp->setCellWidget(row, 6, newWidget);
    temp->setColumnWidth(6, 240);

    return newChecBox;
}

//borrow books function
void Database::BorrowBook(){
    if(borrowBookNum == 0){
        QMessageBox::warning(nullptr, tr("Error"), tr("Please select books!"));
        return;
    }

    if(borrowBookNum + borrowedBookTable->rowCount() > 3){ //at most 3 books
        QMessageBox::critical(nullptr, tr("Borrow Failed!"), tr("Note:you can only borrow no more than 3 books"));
    }
    else{
        QSqlQuery update;
        QString msg;
        for(int i = 0; i < borrowBookNum; i++){
            //update information of users who borrow books
            msg = "insert into book_borrow values("
                  + borrowableBookTable->item(allBooksMark[i], 0)->text()
                  + ", \"" + userType->text().replace("User : ", "") + "\");";
            update.exec(msg);

            if(!update.isActive()){
                QMessageBox::critical(nullptr, tr("Borrow Failed!"), tr("Failed to borrow books!"));
                return;
            }
            else{
                //update books information
                QSqlQuery updateBookInfor;
                msg = "update books set isBorrowed = 1 where ISBN = "
                      + borrowableBookTable->item(allBooksMark[i], 0)->text() + ";";
                updateBookInfor.exec(msg);

                if(!updateBookInfor.isActive()){
                    QMessageBox::critical(nullptr, tr("Failed!"), tr("Update Failed"));
                    return;
                }
            }
        }

        //update book information in the interface
        QMessageBox::information(nullptr, tr("Borrow Books"), tr("Your borrow succeed").arg(borrowBookNum));
        showBorrowableBooks();
        updateBorrowedBooks();
    }
    return;
}

//function to check books which user wants
void Database::judgeBorrowable(){
    borrowBookNum = 0;
    for(int i = 0; i < 50; allBooksMark[i++] = -1);

    for(int i = 0; i < 50; i++){
        if(allBooks[i] != nullptr && allBooks[i]->isChecked()){
            allBooksMark[borrowBookNum++] = i;
        }
    }
}

//--------------------------------------------------------------------------------------------------------------
//-------------------------------------------return books-------------------------------------------------------

//set the return books interface
void Database::setUserReturnWidget(){
    borrowedBookTable = new QTableWidget(0, 7);
    borrowedBookTable->setHorizontalHeaderLabels(bookAttrs);
    borrowedBookTable->horizontalHeaderItem(6)->setText(tr("Return"));
    setTableWidget(borrowedBookTable);
    updateBorrowedBooks();

    QPushButton *returnButton = new QPushButton(tr("Return"));
    returnButton->setFixedSize(70, 40);

    QHBoxLayout *horizontalLayout = new QHBoxLayout();
    horizontalLayout->addStretch();
    horizontalLayout->addWidget(returnButton);

    QVBoxLayout *verticalLayoutMain = new QVBoxLayout();
    verticalLayoutMain->addWidget(borrowedBookTable);
    verticalLayoutMain->addLayout(horizontalLayout);
    userReturnWidget->setLayout(verticalLayoutMain);

    connect(returnButton, SIGNAL(clicked(bool)), this, SLOT(ReturnBook()));
}

//update list of borrowed books
void Database::updateBorrowedBooks(){
    returnBookNum = 0;
    clearTableWidget(borrowedBookTable);
    for(int i = 0; i < 3; borrowedBooks[i++] = nullptr);

    QSqlQuery query;
    QString msg = "select * from books natural join book_borrow where borrower = \""
                  + userType->text().replace("User : ", "") + "\";";
    query.exec(msg);

    int row = 0;
    while(query.next()){
        borrowedBookTable->insertRow(row);

        for(int column = 0; column < 6; column++){
            QString attr = query.value(column).toString();
            QTableWidgetItem *newItem = new QTableWidgetItem(attr);

            newItem->setFlags(newItem->flags() & ~Qt::ItemIsEditable);
            newItem->setTextAlignment(Qt::AlignCenter);
            borrowedBookTable->setItem(row, column, newItem);
        }

        QCheckBox *newCheckBox = setCheckBox("Return", RETURN, row);
        borrowedBooks[row++] = newCheckBox;

        connect(newCheckBox, SIGNAL(stateChanged(int)), this, SLOT(judgeReturned()));
    }
}

//funciton cot check which books are to borrow
void Database::judgeReturned(){
    returnBookNum = 0;
    for(int i = 0; i < 3; borrowedBooksMark[i++] = -1);

    for(int i = 0; i < 3; i++){
        if(borrowedBooks[i] != nullptr && borrowedBooks[i]->isChecked()){
            borrowedBooksMark[returnBookNum++] = i;
        }
    }
}

//return the books
void Database::ReturnBook(){
    if(returnBookNum == 0){
        QMessageBox::critical(nullptr, tr("Error!"), tr("Please select some books first"));
        return;
    }

    QSqlQuery query;
    for(int i = 0; i < returnBookNum; i++){
        QString msg = "delete from book_borrow where borrower = \""
                      + userType->text().replace("User : ", "") + "\" and ISBN = "
                      + borrowedBookTable->item(borrowedBooksMark[i], 0)->text() + ";";
        qDebug() << msg;
        query.exec(msg);

        if(!query.isActive()){
            QMessageBox::critical(nullptr, tr("Error"), tr("Failed to return books!"));
            return;
        }
        else{
            msg = "update books set isBorrowed = 0 where ISBN = "
                  + borrowedBookTable->item(borrowedBooksMark[i], 0)->text() + ";";
            query.exec(msg);

            if(!query.isActive()){
                QMessageBox::critical(nullptr, tr("Error"), tr("Failed to return books!"));
                return;
            }
        }
    }

    QMessageBox::information(nullptr, tr(""), tr("Return succeed"));
    updateBorrowedBooks();
    QString text = ISBNText->text();
    ISBNText->setText("");
    showBorrowableBooks();
    ISBNText->setText(text);
}

//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------manage users------------------------------------------------------

//set the interface to manage users
void Database::setManageUserWidget(){
    ManageUserNameText = new QLineEdit();
    ManageUserAuthority = new QLineEdit();

    ManageUserNameText->setPlaceholderText(tr("Input user name : "));
    ManageUserAuthority->setPlaceholderText(tr("Input user authority : "));

    QStringList userAttr = {"User Name", "First Borrowed Book", "Second Borrowed Book", "Third Borrowed Book", "Authority"};
    manageUser = new QTableWidget(0, 5);
    manageUser->setHorizontalHeaderLabels(userAttr);
    for(int i = 1; i < 4; manageUser->setColumnWidth(i++, 210));
    setTableWidget(manageUser);
    updateManageUser();

    QPushButton *searchUser = new QPushButton(tr("Search users"));
    QPushButton *deleteUser = new QPushButton(tr("Delete users"));
    QPushButton *grantUser = new QPushButton(tr("Grant authority"));
    QPushButton *releaseUser = new QPushButton(tr("Pelease authority"));

    QHBoxLayout *horizontalLayoutOP = new QHBoxLayout();
    horizontalLayoutOP->addStretch();
    horizontalLayoutOP->addWidget(searchUser);
    horizontalLayoutOP->addStretch();
    horizontalLayoutOP->addWidget(deleteUser);
    horizontalLayoutOP->addStretch();
    horizontalLayoutOP->addWidget(grantUser);
    horizontalLayoutOP->addStretch();
    horizontalLayoutOP->addWidget(releaseUser);
    horizontalLayoutOP->addStretch();

    QVBoxLayout *virtualLayoutManageUser = new QVBoxLayout;
    virtualLayoutManageUser->addWidget(manageUser);
    virtualLayoutManageUser->addLayout(horizontalLayoutOP);

    ManageUserWidget->setLayout(virtualLayoutManageUser);

    connect(searchUser, SIGNAL(clicked(bool)), this, SLOT(showMSearchWindow()));
    connect(deleteUser, SIGNAL(clicked(bool)), this, SLOT(showAskDeleteUserWindow()));
    connect(grantUser, SIGNAL(clicked(bool)), this, SLOT(grantUser()));
    connect(releaseUser, SIGNAL(clicked(bool)), this, SLOT(releaseUserAuthority()));
}

//update user interface
void Database::updateManageUser(){
    clearTableWidget(manageUser);

    int row = 0;
    QSqlQuery query;
    query.exec(msgManageUser);
    while(query.next()){
        manageUser->insertRow(row);

        //ignore the books information first
        int column;
        for(column = 0; column < 5; column++){
            QString attr = "NULL";
            if(column == 0) attr = query.value("username").toString();
            else if(column == 4) attr = query.value("authority").toString();

            QTableWidgetItem *newItem = new QTableWidgetItem(attr);
            newItem->setTextAlignment(Qt::AlignCenter);
            manageUser->setItem(row, column, newItem);
        }

        //care for books information
        column = 1;
        QSqlQuery temp;
        temp.exec("select * from book_borrow where borrower = \""
                  + query.value("username").toString() + "\";");
        while(temp.next()){
            manageUser->item(row, column)->setText(temp.value("ISBN").toString());
            column++;
        }

        row++;
    }
}

//search for users interface
void Database::showMSearchWindow(){
    QLabel *name = new QLabel(tr("User Name"));
    QLabel *authority = new QLabel(tr("User Authority"));
    QPushButton *search = new QPushButton(tr("Search"));
    QPushButton *cancel = new QPushButton(tr("Cancel"));

    name->setFixedSize(115, 40);
    authority->setFixedSize(115, 40);
    search->setFixedSize(90, 40);
    cancel->setFixedSize(90, 40);

    name->setAlignment(Qt::AlignCenter);
    authority->setAlignment(Qt::AlignCenter);

    QHBoxLayout *horizontalLayoutName = new QHBoxLayout();
    horizontalLayoutName->addWidget(name);
    horizontalLayoutName->addWidget(ManageUserNameText);

    QHBoxLayout *horizontalLayoutAuthority = new QHBoxLayout();
    horizontalLayoutAuthority->addWidget(authority);
    horizontalLayoutAuthority->addWidget(ManageUserAuthority);

    QHBoxLayout *horizontalLayoutButton = new QHBoxLayout();
    horizontalLayoutButton->addStretch();
    horizontalLayoutButton->addWidget(search);
    horizontalLayoutButton->addStretch();
    horizontalLayoutButton->addWidget(cancel);
    horizontalLayoutButton->addStretch();

    QVBoxLayout *virtualLayoutManager = new QVBoxLayout();
    virtualLayoutManager->addLayout(horizontalLayoutName);
    virtualLayoutManager->addLayout(horizontalLayoutAuthority);
    virtualLayoutManager->addLayout(horizontalLayoutButton);

    searchUserWidget = new QWidget();
    searchUserWidget->setWindowFlags(searchUserWidget->windowFlags() & ~Qt::WindowCloseButtonHint);
    searchUserWidget->setLayout(virtualLayoutManager);
    searchUserWidget->setWindowTitle(tr("Search User"));
    searchUserWidget->resize(360, 240);
    searchUserWidget->show();

    connect(search, SIGNAL(clicked(bool)), this, SLOT(searchManageUser()));
    connect(cancel, SIGNAL(clicked(bool)), this, SLOT(quitManageUser()));
}

//search and manage users
void Database::searchManageUser(){
    //key information to search
    QString constraintUser;
    if(!ManageUserNameText->text().isEmpty()){
        constraintUser += "username = \"" + ManageUserNameText->text() + "\"";
    }
    if(!ManageUserAuthority->text().isEmpty()){
        if(constraintUser != ""){
            constraintUser += " and ";
        }
        constraintUser += "authority = " + ManageUserAuthority->text();
    }

    msgManageUser = "select * from users";
    if(constraintUser != ""){
        msgManageUser += " where " + constraintUser;
    }
    msgManageUser += ";";

    updateManageUser();
    quitManageUser();
}

//quit search users
void Database::quitManageUser(){
    ManageUserNameText->clear();
    ManageUserAuthority->clear();
    searchUserWidget->close();
}

//delete user with quarry information
void Database::showAskDeleteUserWindow(){
    if(false){
        QMessageBox::warning(nullptr, tr("Delete Users"), tr("Please select some users first!"));
    }
    else{
        QDialog *askDeleteUserWindow = new QDialog();
        QPushButton *yes = new QPushButton(tr("Yes"));
        QPushButton *no = new QPushButton(tr("Cancel"));
        QLabel *msg = new QLabel(tr("Do you really want to delete these users?"));

        yes->setFixedSize(75, 40);
        no->setFixedSize(75, 40);

        QHBoxLayout *horizontalLayoutButton = new QHBoxLayout();
        horizontalLayoutButton->addStretch();
        horizontalLayoutButton->addWidget(yes);
        horizontalLayoutButton->addStretch();
        horizontalLayoutButton->addWidget(no);
        horizontalLayoutButton->addStretch();

        QVBoxLayout *virtualLayout = new QVBoxLayout();
        virtualLayout->addWidget(msg);
        virtualLayout->addLayout(horizontalLayoutButton);

        askDeleteUserWindow->setWindowTitle(tr("Delete Users"));
        askDeleteUserWindow->setLayout(virtualLayout);
        askDeleteUserWindow->resize(200, 130);
        askDeleteUserWindow->show();

        connect(no, SIGNAL(clicked(bool)), askDeleteUserWindow, SLOT(close()));
        connect(yes, SIGNAL(clicked(bool)), this,SLOT(DeleteUser()));
        connect(yes, SIGNAL(clicked(bool)), askDeleteUserWindow, SLOT(close()));
    }
}

//delete user funciton
void Database::DeleteUser(){
    recordSelectedUsers();
    if(ifCanDeleteUser == 0){
        QMessageBox::critical(nullptr, tr("Delete Users!"), tr("Some users have not return books!"));
        return;
    }

    for(int i = 0; i < 1000; i++){
        int row = selectedUsers[i];
        if(row >= 0){
            //delete user information
            QString username = manageUser->item(row, 0)->text();
            QSqlQuery query;
            query.exec("delete from users where username = \"" + username + "\";");
            if(!query.isActive()){
                QMessageBox::critical(nullptr, tr("Delete Users!"), tr("Failed to update table users"));
                return;
            }
            else{
                //delete from the table
                manageUser->removeRow(row);
            }
        }
    }
    QMessageBox::information(nullptr, tr("Delete Users!"), tr("Succeed!"));
}

//check all chosen line
void Database::recordSelectedUsers(){
    ifCanDeleteUser = 1;
    int size = 0;
    for(int i = 0; i < 1000; selectedUsers[i++] = -1);

    QList<QTableWidgetSelectionRange> listRanges = manageUser->selectedRanges();
    int n = listRanges.count();
    for(int i = 0; i < n; i++){
        for(int j = listRanges[i].topRow(); j <= listRanges[i].bottomRow(); j++){
            if(manageUser->item(j, 1)->text() != "NULL" || manageUser->item(j, 2)->text() != "NULL"
               || manageUser->item(j, 3)->text() != "NULL"){
                ifCanDeleteUser = 0;
            }
            selectedUsers[size++] = j;
        }
    }

    //sort the users
    std::sort(selectedUsers, selectedUsers + size, std::greater<int>());
}

//grant and release function
void Database::grantOrRelease(bool type){
    recordSelectedUsers();

    for(int i = 0; i < 1000; i++){
        int row = selectedUsers[i];
        if(row >= 0){
            QString username = manageUser->item(row, 0)->text();
            QSqlQuery query;
            QString authority = (type == GRANT) ? "1" : "0";
            query.exec(tr("update users set authority = %1 where username = \"").arg(authority) + username + "\";");
            if(!query.isActive()){
                //fail to update
                if(type == GRANT){
                    QMessageBox::critical(nullptr, tr("Grant Users!"), tr("Failed to grant %1 !").arg(username));
                }
                else if(type == RELEASE){
                    QMessageBox::critical(nullptr, tr("Release Authority!"), tr("Failed to release %1 !").arg(username));
                }
                return;
            }

            manageUser->item(row, 4)->setText(authority);
        }
    }
    if(type == GRANT) QMessageBox::information(nullptr, tr("Grant Users!"), tr("Grant Succeed!"));
    else if(type == RELEASE) QMessageBox::information(nullptr, tr("Release Authority!"), tr("Release Succeed!"));
}

//grant to users
void Database::grantUser(){
    grantOrRelease(GRANT);
}

//release the users
void Database::releaseUserAuthority(){
    grantOrRelease(RELEASE);
}

//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------manage books------------------------------------------------------

//insert books
void Database::insertBooks(){
    QString text[] = {ISBNText->text(), bookNameText->text(), authorText->text(), bookTypeText->currentText(),
                       publishDateText->currentText(), publisherText->text(), "NULL"};
    if(text[0].isEmpty() || text[1].isEmpty() || text[2].isEmpty()
            || text[3].isEmpty() || text[4].isEmpty() || text[5].isEmpty()){
        QMessageBox::critical(nullptr, tr("Insert Books!"), tr("Lack some information!"));
        return;
    }

    QSqlQuery query;
    QString msg;
    msg = tr("insert into books values(\"%1\", \"%2\", \"%3\", \"%4\", \"%5\", \"%6\", 0);").arg(
                text[0], text[1], text[2], text[3], text[4], text[5]);
    query.exec(msg);
    if(!query.isActive()){
        QMessageBox::critical(nullptr, tr("Insert Books!"), tr("Failed to update table books!"));
        return;
    }
    else{
        ISBNText->clear();
        bookNameText->clear();
        authorText->clear();
        publisherText->clear();
        bookTypeText->setCurrentText("");
        publishDateText->setCurrentText("");

        int row = borrowableBookTable->rowCount();
        borrowableBookTable->insertRow(row);

        for(int i = 0; i < 7; i++){
            QTableWidgetItem *newItem = new QTableWidgetItem(text[i]);
            newItem->setTextAlignment(Qt::AlignCenter);
            newItem->setFlags(newItem->flags() & ~Qt::ItemIsEditable);
            borrowableBookTable->setItem(row, i, newItem);
        }
    }
}

//managers serach for books
void Database::showManageBooks(){
    clearTableWidget(borrowableBookTable);

    QString constraint;
    if(!ISBNText->text().isEmpty()){
        constraint += "ISBN like \"%" + ISBNText->text() + "%\"";
    }
    if(!authorText->text().isEmpty()){
        if(constraint != ""){
            constraint += " and ";
        }
        constraint += "author like \"%" + authorText->text() + "%\"";
    }
    if(!bookNameText->text().isEmpty()){
        if(constraint != ""){
            constraint += " and ";
        }
        constraint += "bookname like \"%" + bookNameText->text() + "%\"";
    }
    if(!publisherText->text().isEmpty()){
        if(constraint != ""){
            constraint += " and ";
        }
        constraint += "publisher like \"%" + publisherText->text() + "%\"";
    }
    if(bookTypeText->currentText() != ""){
        if(constraint != ""){
            constraint += " and ";
        }
        constraint += "booktype = \"" + bookTypeText->currentText() + "\"";
    }
    if(publishDateText->currentText() != ""){
        if(constraint != ""){
            constraint += " and ";
        }
        constraint += "publishdate = " + publishDateText->currentText();
    }

    QString msg = constraint == "" ? "select * from books order by ISBN;" : "select * from books where " + constraint + "order by ISBN;";
    int row = 0;
    QSqlQuery query;
    query.exec(msg);
    if(!query.isActive()) QMessageBox::critical(nullptr, tr("Manager Books"), tr("Iuput error!"));
    while(query.next()){
        borrowableBookTable->insertRow(row);

        for(int column = 0; column < 6; column++){
            QString attr = query.value(column).toString();
            QTableWidgetItem *newItem = new QTableWidgetItem(attr);

            newItem->setFlags(newItem->flags() & ~Qt::ItemIsEditable);
            newItem->setTextAlignment(Qt::AlignCenter);
            borrowableBookTable->setItem(row, column, newItem);
        }

        row++;
    }

    //show the user who borrows the book
    int rowNum = borrowableBookTable->rowCount();
    for(int i = 0; i < rowNum; i++){
        QString isbn = borrowableBookTable->item(i, 0)->text();
        QString msg = "select borrower from book_borrow where ISBN = " + isbn + ";";
        qDebug() << msg;
        QSqlQuery newquery;
        newquery.exec(msg);

        if(!query.isActive()){
            QMessageBox::warning(nullptr, tr("Search Books!"), tr("Failed to search borrower!"));
            return;
        }
        else{
            newquery.next();
            QTableWidgetItem *newItem = new QTableWidgetItem(newquery.value(0).toString() == "" ? "NULL" : newquery.value(0).toString());
            newItem->setTextAlignment(Qt::AlignCenter);
            borrowableBookTable->setItem(i, 6, newItem);
        }
    }
}

//--------------------------------------------------------------------------------------------------------------
//--------------------------------------------batch books-------------------------------------------------------

//set batch books interface
void Database::setMultiBookWidget(){
    QPushButton *batchButton = new QPushButton(tr("Insert Books"));
    batchButton->setFixedSize(140, 40);
    QPushButton *fileButton = new QPushButton(tr("Read File"));
    batchButton->setFixedSize(140, 40);

    manageMultiBook = new QTableWidget(50, 7);
    manageMultiBook->setHorizontalHeaderLabels(bookAttrs);
    manageMultiBook->removeColumn(6);
    setTableWidget(manageMultiBook);
    manageMultiBook->setSelectionBehavior(QAbstractItemView::SelectItems);
    manageMultiBook->setEditTriggers(QAbstractItemView::DoubleClicked);
    manageMultiBook->verticalHeader()->setVisible(true);

    for(int row = 0; row < 50; row++){
        for(int column = 0; column < 6; column++){
            QTableWidgetItem *newItem = new QTableWidgetItem("");
            newItem->setTextAlignment(Qt::AlignCenter);
            manageMultiBook->setItem(row, column, newItem);
        }
    }

    QHBoxLayout *horizontalLayoutMulti = new QHBoxLayout();
    horizontalLayoutMulti->addWidget(fileButton);
    horizontalLayoutMulti->addStretch();
    horizontalLayoutMulti->addWidget(batchButton);

    QVBoxLayout *virtualLayoutMulti = new QVBoxLayout();
    virtualLayoutMulti->addWidget(manageMultiBook);
    virtualLayoutMulti->addLayout(horizontalLayoutMulti);
    manageMultiBookWidget->setLayout(virtualLayoutMulti);

    connect(batchButton, SIGNAL(clicked(bool)), this, SLOT(insertMultiBooks()));
    connect(fileButton, SIGNAL(clicked(bool)), this, SLOT(readFileBooks()));
}

//insert many books
void Database::insertMultiBooks(){
    for(int row = 0; row < 50; row++){
        QString text[] = {manageMultiBook->item(row, 0)->text(), manageMultiBook->item(row, 1)->text(),
                          manageMultiBook->item(row, 2)->text(), manageMultiBook->item(row, 3)->text(),
                          manageMultiBook->item(row, 4)->text(), manageMultiBook->item(row, 5)->text()};
        qDebug() <<text[0] << text[1] << text[2];
        if(text[0].isEmpty() && text[1].isEmpty() && text[2].isEmpty() && text[3].isEmpty()
                && text[4].isEmpty() && text[5].isEmpty()){
            break;
        }
        if(text[0].isEmpty()){
            QMessageBox::critical(nullptr, tr("Book Bulk Warehousing"), tr("ISBN"));
            return;
        }
        if(text[1].isEmpty()){
            QMessageBox::critical(nullptr, tr("Book Bulk Warehousing"), tr("Book Name"));
            return;
        }
        if(text[2].isEmpty()){
            QMessageBox::critical(nullptr, tr("Book Bulk Warehousing"), tr("Author"));
            return;
        }
        if(text[3].isEmpty()){
            QMessageBox::critical(nullptr, tr("Book Bulk Warehousing"), tr("Book Type"));
            return;
        }
        if(text[4].isEmpty()){
            QMessageBox::critical(nullptr, tr("Book Bulk Warehousing"), tr("Publish Date"));
            return;
        }
        if(text[5].isEmpty()){
            QMessageBox::critical(nullptr, tr("Book Bulk Warehousing"), tr("Publisher"));
            return;
        }

        QSqlQuery query;
        QString msg = tr("insert into books values(%1, \"%2\", \"%3\", \"%4\", %5, \"%6\", 0);").arg(
                         text[0], text[1], text[2], text[3], text[4], text[5]);
        query.exec(msg);
        if(query.isActive()){
            for(int column = 0; column < 6; column++){
                manageMultiBook->item(row, column)->setText("");
            }
        }
        else{
            qDebug() << msg;
            QMessageBox::critical(nullptr, tr("Book Bulk Warehousing"), tr("ISBN repeat!"));
            return;
        }
    }
    QMessageBox::information(nullptr, tr("Book Bulk Warehousing"), tr("Succeed!"));
}

//read file data
void Database::readFileBooks(){
    QString filename = QFileDialog::getOpenFileName(nullptr, "Read File", QDir::currentPath(), "Data files (*.txt)");
    if (filename.isNull()){
       QMessageBox::information(nullptr, tr("No file"), tr("please choose one file"));
       return;
    }

    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::information(nullptr, tr("Bad file"), tr("please choose right file"));
        return;
    }
    for(int row = 0; !file.atEnd() && row < 50; row++){
        QByteArray line = file.readLine();
        QString str(line);
        QString text[6];
        try{
            for(int i = 0; i < 6; i++){
                text[i] = str.section(",", i, i);
            }
        }
        catch(exception){
            QMessageBox::critical(nullptr, tr("Read File"), tr("No much message"));
            return;
        }
        for(int column = 0; column < 6; column++){
            manageMultiBook->item(row, column)->setText(text[column]);
        }
    }
    QMessageBox::information(nullptr, tr("Read File"), tr("Succeed!"));
}
