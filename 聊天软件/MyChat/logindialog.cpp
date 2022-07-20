#include "logindialog.h"
#include "ui_logindialog.h"
#include "QMessageBox"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    //改对话框 标题
    setWindowTitle("登录&注册");
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

//关闭事件  --> 关闭窗口会触发
void LoginDialog::closeEvent(QCloseEvent *event)
{
    event->accept();

    Q_EMIT SIG_Close();
}
//清空登录控件
void LoginDialog::on_pb_clear_clicked()
{
    ui->le_tel->setText("");
    ui->le_password->setText("");
}
//登录提交
void LoginDialog::on_pb_commit_clicked()
{
    //首先获取
    QString tel = ui->le_tel->text();
    QString password = ui->le_password->text();

    QString tmpTel = tel;
    //首先要判断 输入是否合法
    //1.tel 不能空 不能为空格 密码不能空  isEmpty->""
    //2.长度 限制 手机号不超过15位 密码不超过10位
    //3.限制内容 手机号只能是数字 --> 正则表达式
    if( tel.isEmpty() || password.isEmpty()
            || tmpTel.remove(" ").isEmpty()/*去掉空格后是不是空字符串*/ )
    {
        QMessageBox::about( this , "提示" ,"手机号或密码不能为空" );
        return;
    }
    if( tel.length() > 15 || password.length() > 10 )
    {
        QMessageBox::about( this , "提示" ,"手机号不超过15位, 密码不超过10位" );
        return;
    }
    //内容检测 -- 正则表达式 没学 暂时不加
    //提交数据 --> 发射信号
    Q_EMIT SIG_LoginCommit( tel , password );
}
//清空注册控件
void LoginDialog::on_pb_clear_register_clicked()
{
    ui->le_tel_register->setText("");
    ui->le_password_register->setText("");
    ui->le_name_register->setText("");
}
//注册提交
void LoginDialog::on_pb_commit_register_clicked()
{
    //首先获取
    QString tel = ui->le_tel_register->text();
    QString password = ui->le_password_register->text();
    QString name = ui->le_name_register->text();

    QString tmpTel = tel;
    QString tmpName = name;
    //首先要判断 输入是否合法
    //1.tel 不能空 不能为空格 密码不能空  isEmpty->""
    //2.长度 限制 手机号不超过15位 密码不超过10位
    //3.限制内容 手机号只能是数字 --> 正则表达式
    if( tel.isEmpty() || password.isEmpty() || tmpTel.remove(" ").isEmpty()
            || name.isEmpty() || tmpName.remove(" ").isEmpty() )
    {
        QMessageBox::about( this , "提示" ,"手机号,密码, 昵称不能为空" );
        return;
    }
    if( tel.length() > 15 || password.length() > 10 || name.length() > 20 )
    {
        QMessageBox::about( this , "提示" ,"手机号不超过15位,密码不超过10位,昵称不超过20位" );
        return;
    }
    //内容检测 -- 正则表达式 没学 暂时不加
    //提交数据 --> 发射信号
    Q_EMIT SIG_RegisterCommit( tel , password , name );
}
