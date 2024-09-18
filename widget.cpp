#include "widget.h"
#include "ui_widget.h"
#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QProcess>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);


    // 在界面初始化时直接设置占位符文本
    ui->javalineEdit->setPlaceholderText("输入路径(例如: E:\\Java\\jdk-17)");
    ui->mavenlineEdit->setPlaceholderText("输入路径(例如: E:\\apache-maven-3.8.8\\bin)");
    ui->mysqllineEdit->setPlaceholderText("输入路径(例如: E:\\MySQL\\MySQL Server 9.0\\bin)");
}

Widget::~Widget()
{
    delete ui;
}
// 检查路径是否包含空格
bool Widget::pathContainsSpaces(const QString &path) {
    return path.contains(' ');
}
void Widget::on_java_clicked()
{
    QString javaHome = ui->javalineEdit->text();
    if (javaHome.isEmpty()) {
        QMessageBox::warning(this, "Error", "请输入java路径");
        return;
    }

    // 如果路径包含空格，则添加引号
    QString quotedJavaHome = pathContainsSpaces(javaHome) ? "\"" + javaHome + "\"" : javaHome;

    // 使用QProcess执行命令设置JAVA_HOME
    QProcess process;
    process.start("cmd", QStringList() << "/c" << "setx JAVA_HOME " + quotedJavaHome);
    process.waitForFinished();

    QString newJavaPath = javaHome + "\\bin";

    // 使用 PowerShell 更新 PATH
    QString updatePathCommand = "$env:Path = [System.Environment]::GetEnvironmentVariable('Path', 'User');"
                                "$env:Path += ';' + '"  + newJavaPath + "';"
                                                 "[System.Environment]::SetEnvironmentVariable('Path', $env:Path, 'User');";
    process.start("powershell", QStringList() << "-Command" << updatePathCommand);
    process.waitForFinished();

    QProcess refreshProcess;
    refreshProcess.start("cmd", QStringList() << "/c" << "for /f \"tokens=*\" %i in ('wevtutil') do @set \"%i\"");
    refreshProcess.waitForFinished();

    QMessageBox::information(this, "Success", "配置成功");
    // 关闭应用程序
    //QApplication::quit();
}
void Widget::on_maven_clicked()
{
    QString mavenHome = ui->mavenlineEdit->text();

    if (mavenHome.isEmpty()) {
        QMessageBox::warning(this, "Error", "请输入maven路径");
        return;
    }
    // 如果路径包含空格，则添加引号
    QString quotedMavenHome = pathContainsSpaces(mavenHome) ? "\"" + mavenHome + "\"" : mavenHome;

    // 使用QProcess执行命令设置MAVEN_HOME
    QProcess process;
    QString newMavenPath = mavenHome;
    process.start("cmd", QStringList() << "/c" << "setx MAVEN_HOME " + quotedMavenHome);
    process.waitForFinished();

    // 使用 PowerShell 更新 PATH
    QString updatePathCommand = "$env:Path = [System.Environment]::GetEnvironmentVariable('Path', 'User');"
                                "$env:Path += ';' + '"  + newMavenPath + "';"
                                                                     "[System.Environment]::SetEnvironmentVariable('Path', $env:Path, 'User');";
    process.start("powershell", QStringList() << "-Command" << updatePathCommand);
    process.waitForFinished();


    QProcess refreshProcess;
    refreshProcess.start("cmd", QStringList() << "/c" << "for /f \"tokens=*\" %i in ('wevtutil') do @set \"%i\"");
    refreshProcess.waitForFinished();

    QMessageBox::information(this, "Success", "配置成功");
    // 关闭应用程序
    //QApplication::quit();
}


void Widget::on_msql_clicked()
{
    QString mysqlHome = ui->mysqllineEdit->text();
    if (mysqlHome.isEmpty()) {
        QMessageBox::warning(this, "Error", "请输入mysql路径");
        return;
    }
    QProcess process;
    // 如果路径包含空格，则添加引号
    QString quotedMsqlHome = pathContainsSpaces(mysqlHome) ? "\"" + mysqlHome + "\"" : mysqlHome;
    process.start("cmd", QStringList() << "/c" << "setx MAVEN_HOME " + quotedMsqlHome);
    process.waitForFinished();
    QString newmysqlPath = mysqlHome;
    // 使用 PowerShell 更新 PATH
    QString updatePathCommand = "$env:Path = [System.Environment]::GetEnvironmentVariable('Path', 'User');"
                                "$env:Path += ';' + '"  + newmysqlPath + "';"
                                                 "[System.Environment]::SetEnvironmentVariable('Path', $env:Path, 'User');";
    process.start("powershell", QStringList() << "-Command" << updatePathCommand);
    process.waitForFinished();

    QProcess refreshProcess;
    refreshProcess.start("cmd", QStringList() << "/c" << "for /f \"tokens=*\" %i in ('wevtutil') do @set \"%i\"");
    refreshProcess.waitForFinished();
    QMessageBox::information(this, "Success", "配置成功");
    // 关闭应用程序
    //QApplication::quit();
}

