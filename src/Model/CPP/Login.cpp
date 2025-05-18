#include "LoginPage.h"
LoginPage::LoginPage(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
    // QMainWindow::showMaximized();
    connect(ui.log, &QPushButton::clicked, this, &LoginPage::Login);
    connect(ui.sign, &QPushButton::clicked, this, &LoginPage::SignUp);
    connect(ui.togglePasswordButton, &QToolButton::clicked, this, &LoginPage::on_togglePasswordButton_clicked);

    QPixmap original("car-background.png");
    QPixmap rounded(original.size());
    rounded.fill(Qt::transparent);
    QPainter painter(&rounded);
    painter.setRenderHint(QPainter::Antialiasing);
    QPainterPath path;
    path.addRoundedRect(original.rect(), 20, 20);
    painter.setClipPath(path);
    painter.drawPixmap(0, 0, original);
    ui.carbackground->setPixmap(rounded);
    ui.pass->setEchoMode(QLineEdit::Password);


}
void LoginPage::Login() {
    QString username = ui.user->text();
    QString password = ui.pass->text();
    if (ui.user->text().isEmpty() or ui.pass->text().isEmpty()) {
        QMessageBox::critical(this, "Error", "Plese Enter The Username And Password");
        return;
    }
    std::string uname = username.toStdString();
    std::string pass = password.toStdString();
    if (!Manager::getInstance()->login(uname, pass)) {
        QMessageBox::critical(this, "Error", "wrong username or password!");
        return;
    }
    HomePage *h=new HomePage;
    h->show();
    this->close();
}

void LoginPage::SignUp() {
    QString username = ui.user->text();
    QString password = ui.pass->text();
    if (ui.user->text().isEmpty() or ui.pass->text().isEmpty()) {
        QMessageBox::critical(this, "Error", "Plese Enter The Username And Password");
        return;
    }
    std::string uname = username.toStdString();
    std::string pass = password.toStdString();
    if(!Tools::validateName(uname, this)) {
        return;
    }
    for(auto user : Manager::getInstance()->users) {
        if(Tools::isEqual(user.first, uname)) {
            QMessageBox::critical(this, "Error", "this username already exists!");
            return;
        }
    }
    for (auto c : username.toStdString()) {
        if (Tools::isSpecialChar(c)) {
            QMessageBox::information(this, "invalid input", "Please enter user name that doesn't contain any special characters.");
            return;
        }
    }
    Manager::getInstance()->signUp(uname, pass);
    HomePage* h = new HomePage;
    h->show();
    this->close();
}

void LoginPage::on_togglePasswordButton_clicked() {
    if (ui.togglePasswordButton->text()== "🙈") {
        ui.pass->setEchoMode(QLineEdit::Password);
        ui.togglePasswordButton->setText("👁️");  
    }
    else {
        ui.pass->setEchoMode(QLineEdit::Normal);
        ui.togglePasswordButton->setText("🙈"); 
    }
    isPasswordVisible = !isPasswordVisible;
}

LoginPage::~LoginPage()
{
}
